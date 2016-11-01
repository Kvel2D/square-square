cmake_minimum_required(VERSION 3.4)
project(Core)

# Flags
set(SDL2_Flags "-Wl,--no-undefined,-subsystem,windows -static-libgcc ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${SDL2_Flags}")

set(SOURCE_FILES
        main.cpp
        main.h
        entity/engine.cpp
        entity/engine.h
        entity/system.h
        entity/family.h
        entity/components/transform.h
        entity/components/texture.h
        entity/components/particle.h
        entity/systems/inputsystem.cpp
        entity/systems/inputsystem.h
        entity/systems/spawnsystem.cpp
        entity/systems/spawnsystem.h
        entity/systems/expansionsystem.cpp
        entity/systems/expansionsystem.h
        entity/systems/gameoversystem.cpp
        entity/systems/gameoversystem.h
        entity/systems/rendersystem.cpp
        entity/systems/rendersystem.h
        graphics/gl_structs/color.h
        graphics/gl_structs/rectangle.h
        graphics/gl_structs/texcoord.h
        graphics/gl_structs/texturedvertex.h
        graphics/gl_structs/vertexpos.h
        graphics/gltexture.cpp
        graphics/gltexture.h
        graphics/programs/shaderprogram.cpp
        graphics/programs/shaderprogram.h
        graphics/programs/textureprogram.cpp
        graphics/programs/textureprogram.h
        assets.cpp
        assets.h
        math/random.h
        math/vector2.h
        globals.cpp
        globals.h
        sound/sound.cpp
        sound/sound.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Define libraries
set(LIBRARIES mingw32 SDL2main SDL2 SDL2_image SDL2_ttf freetype
        SDL2_mixer opengl32 glu32 glew32 freeglut m dinput8 dxguid dxerr8
        user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)

# Link against SDL
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})