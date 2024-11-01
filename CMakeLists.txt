cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Rendell)

set(EXE_NAME waxedit)

set(SOURCE_FILES
    src/rendell.cpp
    src/Renderer.cpp
    src/IndexBuffer.cpp
    src/VertexBuffer.cpp
    src/VertexArray.cpp
    src/VertexBufferLayout.cpp
    src/ShaderProgram.cpp
    src/Texture2D.cpp
    src/OpenGL/OpenGLSpecification.cpp
    src/OpenGL/OpenGLIndexBuffer.cpp
    src/OpenGL/OpenGLVertexBuffer.cpp
    src/OpenGL/OpenGLVertexArray.cpp
    src/OpenGL/OpenGLShaderProgram.cpp
    src/OpenGL/OpenGLTexture2D.cpp

)

add_library(rendell STATIC ${SOURCE_FILES})
target_include_directories(rendell PUBLIC include)

# Gald
add_subdirectory(glad)
target_link_libraries(rendell glad)