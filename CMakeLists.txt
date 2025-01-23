cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Rendell)

set(BINARY_NAME rendell)

set(SOURCE_FILES
    src/rendell.cpp
    src/IndexBuffer.cpp
    src/VertexBuffer.cpp
    src/VertexArray.cpp
    src/VertexBufferLayout.cpp
    src/ShaderProgram.cpp
    src/Texture2D.cpp
    src/Texture2DArray.cpp
    src/ShaderBuffer.cpp
    src/UniformBuffer.cpp
    src/OpenGL/OpenGLUtils.cpp
    src/OpenGL/OpenGLSpecification.cpp
    src/OpenGL/OpenGLIndexBuffer.cpp
    src/OpenGL/OpenGLVertexBuffer.cpp
    src/OpenGL/OpenGLVertexArray.cpp
    src/OpenGL/OpenGLShaderProgram.cpp
    src/OpenGL/OpenGLTexture2D.cpp
    src/OpenGL/OpenGLTexture2DArray.cpp
    src/OpenGL/OpenGLShaderBuffer.cpp
    src/OpenGL/OpenGLUniformBuffer.cpp

)

option(BUILD_SHARED_LIBS "Build shared libraries instead of static" OFF)

if(BUILD_SHARED_LIBS)
    add_library(${BINARY_NAME} SHARED ${SOURCE_FILES})
    target_compile_definitions(${BINARY_NAME} PRIVATE RENDELL_BUILD_DLL)
else()
    add_library(${BINARY_NAME} STATIC ${SOURCE_FILES})
endif()

# Gald
add_subdirectory(glad)
#target_include_directories(glad INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
target_link_libraries(${BINARY_NAME} PRIVATE glad)


install(TARGETS ${BINARY_NAME} EXPORT RendellConfig LIBRARY DESTINATION lib)
export(PACKAGE  ${BINARY_NAME})
install(EXPORT RendellConfig DESTINATION lib/cmake/${PROJECT_NAME})
