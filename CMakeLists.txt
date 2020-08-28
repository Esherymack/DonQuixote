cmake_minimum_required(VERSION 3.16)   # CMake version check
project(DonQuixote)                        # Create project "DonQuixote"
# sorry I use some stuff from c++17
set(CMAKE_CXX_STANDARD 17)             # Enable c++17 standard
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# glm stuff
# ...i wanted vec2 and other nice things
find_package(glm REQUIRED)

#add include and link directories
if(APPLE)
    find_library(cf_lib CoreFoundation)
    find_library(cg_lib CoreGraphics)
    find_library(cocoa_lib Cocoa)
    find_library(io_lib IOKit)
    link_directories(${CMAKE_SOURCE_DIR}/lib/MacOSX)
elseif(WIN32)
	file(COPY ${CMAKE_SOURCE_DIR}/lib/Win/glew32.dll DESTINATION ${CMAKE_SOURCE_DIR}/bin)
	file(COPY ${CMAKE_SOURCE_DIR}/lib/Win/glfw3.dll DESTINATION ${CMAKE_SOURCE_DIR}/bin)
    link_directories(${CMAKE_SOURCE_DIR}/lib/Win)
endif()

#Main
set(SOURCE_FILES DonQuixote.cpp utils.cpp)
add_executable(DonQuixote ${SOURCE_FILES})

if(APPLE)
    # Add Apple frameworks
    target_link_libraries(DonQuixote ${cf_lib})
    target_link_libraries(DonQuixote ${cg_lib})
    target_link_libraries(DonQuixote ${cocoa_lib})
    target_link_libraries(DonQuixote ${io_lib})

    # Add GLFW and GLEW libraries
    target_link_libraries(DonQuixote ${OPENGL_gl_LIBRARY})
    target_link_libraries(DonQuixote glfw3)
    target_link_libraries(DonQuixote glew)
    # Add GLM
    target_link_libraries(DonQuixote glm)
elseif(WIN32)
    # Add GLFW and GLEW libraries
    target_link_libraries(DonQuixote ${OPENGL_gl_LIBRARY})
    target_link_libraries(DonQuixote glfw3)
    target_link_libraries(DonQuixote glew32)
    # Add GLM
    target_link_libraries(DonQuixote glm)
else()
    target_link_libraries(DonQuixote OpenGL::GL)
    target_link_libraries(DonQuixote glfw)
    target_link_libraries(DonQuixote GLEW)
endif()


