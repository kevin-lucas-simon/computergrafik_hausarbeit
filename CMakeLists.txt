cmake_minimum_required(VERSION 3.15)
project(computergrafik_praktikum)

set(CMAKE_CXX_STANDARD 14)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp src/shader/TerrainShader.cpp src/shader/TerrainShader.h src/game/world/Terrain.cpp src/game/world/Terrain.h src/game/PlayerCar.cpp src/game/PlayerCar.h src/game/world/TerrainControlService.h src/game/world/TerrainChunk.cpp src/game/world/TerrainChunk.h src/game/world/GraphService.h src/game/world/SinusGraph.cpp src/game/world/SinusGraph.h)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC
        src/util/Aabb.cpp
        src/Application.cpp
        src/model/BaseModel.cpp
        src/shader/BaseShader.cpp
        src/camera/Camera.cpp
        src/util/CGUtilities.cpp
        src/texture/color.cpp
        src/object/Tank.cpp
        src/shader/ConstantShader.cpp
        src/buffer/IndexBuffer.cpp
        src/model/LinePlaneModel.cpp
        src/game/world/Terrain.cpp
        src/main.cpp
        src/util/Matrix.cpp
        src/model/Model.cpp
        src/shader/PhongShader.cpp
        src/texture/rgbimage.cpp
        src/texture/Texture.cpp
        src/util/vector.cpp
        src/buffer/VertexBuffer.cpp
)

include_directories(
        src
        assets
        libraries/assimp/include/
        libraries/glfw/include/
        libraries/glew/include/
        libraries/freeimage/include)

find_package(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}
        OpenGL::GL
        OpenGL::GLU
        ../libraries/assimp/lib/assimp-vc140-mt
        ../libraries/glfw/lib/glfw3
        ../libraries/glew/lib/glew32
        ../libraries/freeimage/lib/FreeImage)

function(copyFilePostBuild src dst)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${src} ${dst})
endfunction()

copyFilePostBuild(${CMAKE_CURRENT_SOURCE_DIR}/libraries/glew/lib/glew32.dll
                  ${CMAKE_CURRENT_BINARY_DIR}/glew32.dll)
copyFilePostBuild(${CMAKE_CURRENT_SOURCE_DIR}/libraries/freeimage/lib/FreeImage.dll
                  ${CMAKE_CURRENT_BINARY_DIR}/FreeImage.dll)
copyFilePostBuild(${CMAKE_CURRENT_SOURCE_DIR}/libraries/assimp/lib/assimp-vc140-mt.dll
                  ${CMAKE_CURRENT_BINARY_DIR}/assimp-vc140-mt.dll)
