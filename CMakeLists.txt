# CMakeList.txt : CMake project for OpenGL3dRenderer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OpenGL3dRenderer")

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)


# Add source to this project's executable.
add_executable (OpenGL3dRenderer "src/main.cpp" "src/common.h" "src/util/stb_image.h"
"src/util/shader.cpp" "src/util/shader.h" 
"src/util/ResourceManager.cpp" "src/util/ResourceManager.h" 
"src/util/texture.cpp" "src/util/texture.h"
"src/cube_mesh.cpp" "src/cube_mesh.h" 
"src/Camera.h" "src/game_map.h" 
"src/util/vertex.h" 
"src/util/mesh.h" "src/util/mesh.cpp"
"src/util/primitives/primitive.h"  
"src/util/primitives/cube.h" "src/util/primitives/cube.cpp" 
"src/util/primitives/pyramid.h" 
"src/chunk.cpp" "src/chunk.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGL3dRenderer PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(OpenGL3dRenderer PRIVATE glfw glad::glad glm::glm)

# TODO: Add tests and install targets if needed.
