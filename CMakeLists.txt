cmake_minimum_required(VERSION 3.15)
project(computergrafik_praktikum)

set(CMAKE_CXX_STANDARD 14)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp src/game/shader/TerrainShader.cpp src/game/shader/TerrainShader.h src/game/terrain/TerrainChunk.cpp src/game/terrain/TerrainChunk.h src/game/terrain/TerrainControlService.h src/game/terrain/Terrain.cpp src/game/terrain/Terrain.h src/game/terrain/renderer/GraphService.h src/game/terrain/renderer/SinusGraph.cpp src/game/terrain/renderer/SinusGraph.h src/game/util/KeyManager.cpp src/game/util/KeyManager.h src/game/terrain/renderer/FlatGraph.cpp src/game/terrain/renderer/FlatGraph.h src/game/util/GameCamera.cpp src/game/util/GameCamera.h src/game/player/PlayerPositionService.h src/game/terrain/renderer/PerlinGraph.cpp src/game/terrain/renderer/PerlinGraph.h src/game/gui/ShowText.cpp src/game/gui/ShowText.h src/game/shader/GUIShader.cpp src/game/shader/GUIShader.h src/game/gui/Fonts.cpp src/game/gui/Fonts.h src/game/gui/Holder_test.cpp)

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
        libraries/freeimage/include/
        libraries/freeglut/include/
        libraries/freetype/include)

find_package(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}
        OpenGL::GL
        OpenGL::GLU
        ../libraries/assimp/lib/assimp-vc140-mt
        ../libraries/glfw/lib/glfw3
        ../libraries/glew/lib/glew32
        ../libraries/freeimage/lib/FreeImage
        ../libraries/freeglut/lib/freeglut
        ../libraries/freetype/lib/freetype)

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
copyFilePostBuild(${CMAKE_CURRENT_SOURCE_DIR}/libraries/freeglut/lib/freeglut.dll
                  ${CMAKE_CURRENT_BINARY_DIR}/freeglut.dll)
copyFilePostBuild(${CMAKE_CURRENT_SOURCE_DIR}/libraries/freetype/lib/freetype.dll
                    ${CMAKE_CURRENT_BINARY_DIR}/freetype.dll)
