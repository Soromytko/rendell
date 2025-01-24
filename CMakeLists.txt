cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(EXE_NAME waxedit)

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

set(HEADER_FILES
    src/rendell.h
    src/IndexBuffer.h
    src/VertexBuffer.h
    src/VertexArray.h
    src/VertexBufferLayout.h
    src/ShaderProgram.h
    src/Texture2D.h
    src/Texture2DArray.h
    src/ShaderBuffer.h
    src/UniformBuffer.h
    src/OpenGL/OpenGLUtils.h
    src/OpenGL/OpenGLSpecification.h
    src/OpenGL/OpenGLIndexBuffer.h
    src/OpenGL/OpenGLVertexBuffer.h
    src/OpenGL/OpenGLVertexArray.h
    src/OpenGL/OpenGLShaderProgram.h
    src/OpenGL/OpenGLTexture2D.h
    src/OpenGL/OpenGLTexture2DArray.h
    src/OpenGL/OpenGLShaderBuffer.h
    src/OpenGL/OpenGLUniformBuffer.h

)

add_library(rendell STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(rendell PUBLIC include)

# Glad
add_subdirectory(glad)
target_link_libraries(rendell glad)