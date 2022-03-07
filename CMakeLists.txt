cmake_minimum_required(VERSION 3.15)
project(computergrafik_praktikum)

set(CMAKE_CXX_STANDARD 14)


add_executable(${CMAKE_PROJECT_NAME} src/main.cpp src/game/shader/TerrainShader.cpp src/game/shader/TerrainShader.h src/game/terrain/TerrainChunk.cpp src/game/terrain/TerrainChunk.h src/game/terrain/TerrainControlService.h src/game/terrain/Terrain.cpp src/game/terrain/Terrain.h src/game/terrain/renderer/GraphService.h src/game/terrain/renderer/SinusGraph.cpp src/game/terrain/renderer/SinusGraph.h src/game/util/KeyManager.cpp src/game/util/KeyManager.h src/game/terrain/renderer/FlatGraph.cpp src/game/terrain/renderer/FlatGraph.h src/game/util/GameCamera.cpp src/game/util/GameCamera.h src/game/player/PlayerPositionService.h src/game/terrain/renderer/PerlinGraph.cpp src/game/terrain/renderer/PerlinGraph.h)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC
        src/framework/util/Aabb.cpp
        src/game/Application.cpp
        src/framework/model/BaseModel.cpp
        src/framework/shader/BaseShader.cpp
        src/framework/camera/Camera.cpp
        src/framework/util/CGUtilities.cpp
        src/framework/texture/color.cpp
        src/game/player/Tank.cpp
        src/framework/shader/ConstantShader.cpp
        src/framework/buffer/IndexBuffer.cpp
        src/framework/model/LinePlaneModel.cpp
        src/game/terrain/TerrainChunk.cpp
        src/main.cpp
        src/framework/util/Matrix.cpp
        src/framework/model/Model.cpp
        src/framework/shader/PhongShader.cpp
        src/framework/texture/rgbimage.cpp
        src/framework/texture/Texture.cpp
        src/framework/util/vector.cpp
        src/framework/buffer/VertexBuffer.cpp
)

include_directories(
        src
        assets
        libraries/assimp/include/
        libraries/glfw/include/
        libraries/glew/include/
        libraries/freeimage/include)

find_package(OpenGL REQUIRED)

find_library(AASIMP NAMES assimp-vc140-mt.lib assimp-vc140-mt PATHS ${CMAKE_CURRENT_SOURCE_DIR}/libraries/assimp/lib/)
find_library(GLFW glfw3.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/libraries/glfw/lib/)
find_library(GLEW glew32.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/libraries/glew/lib/)
find_library(FREEIMAGE FreeImage.lib PATHS  ${CMAKE_CURRENT_SOURCE_DIR}/libraries/freeimage/lib/)



target_link_libraries(${CMAKE_PROJECT_NAME}
        OpenGL::GL
        OpenGL::GLU
        ${AASIMP}
        ${GLFW}
        ${GLEW}
        ${FREEIMAGE})
        

function(copyFilePostBuild src dst)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${src} ${dst})
endfunction()

message(PROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
message(PROJECT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")


add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/libraries/assimp/lib/assimp-vc140-mt.dll" $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/libraries/glew/lib/glew32.dll" $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/libraries/freeimage/lib/FreeImage.dll" $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/libraries/glfw/lib/glfw3.dll" $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)


copyFilePostBuild(${CMAKE_CURRENT_SOURCE_DIR}/libraries/glew/lib/glew32.dll
                  ${CMAKE_CURRENT_BINARY_DIR}/glew32.dll)
copyFilePostBuild(${CMAKE_CURRENT_SOURCE_DIR}/libraries/freeimage/lib/FreeImage.dll
                  ${CMAKE_CURRENT_BINARY_DIR}/FreeImage.dll)
copyFilePostBuild(${CMAKE_CURRENT_SOURCE_DIR}/libraries/assimp/lib/assimp-vc140-mt.dll
                  ${CMAKE_CURRENT_BINARY_DIR}/assimp-vc140-mt.dll)
