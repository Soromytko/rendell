cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(SOURCE_FILES
    src/rendell.cpp
    src/context_creation.cpp
    src/IndexBuffer.cpp
    src/VertexBuffer.cpp
    src/VertexArray.cpp
    src/VertexBufferLayout.cpp
    src/ShaderProgram.cpp
    src/Texture2D.cpp
    src/Texture2DArray.cpp
    src/ShaderBuffer.cpp
    src/UniformBuffer.cpp
    src/OpenGL/glad_initialization.cpp
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
    include/gl/wglext.h

    include/rendell/rendell.h
    include/rendell/rendell_static.h
    include/rendell/IndexBuffer.h
    include/rendell/VertexBuffer.h
    include/rendell/VertexArray.h
    include/rendell/VertexBufferLayout.h
    include/rendell/ShaderProgram.h
    include/rendell/Texture2D.h
    include/rendell/Texture2DArray.h
    include/rendell/ShaderBuffer.h
    include/rendell/UniformBuffer.h

    include/rendell/private/defines.h

    src/context_creation.h
    src/IContext.h
    src/OpenGL/glad_initialization.h
    src/OpenGL/OpenGLContext.h
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

set(WINDOWS_SOURCES
    src/OpenGL/Platform/WindowsOpenGLContext.cpp
)

set(WINDOWS_HEADERS
    src/OpenGL/Platform/WindowsOpenGLContext.h
)

set(LINUX_SOURCES
    src/OpenGL/Platform/LinuxOpenGLContext.cpp
)

set(LINUX_HEADERS
    src/OpenGL/Platform/LinuxOpenGLContext.h
)

add_library(rendell STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(rendell PUBLIC include)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_sources(rendell PRIVATE ${WINDOWS_SOURCES} ${WINDOWS_HEADERS})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(rendell PRIVATE ${LINUX_SOURCES} ${LINUX_HEADERS})

    #x11
    find_package(X11 REQUIRED)
    include_directories(rendell PRIVATE ${X11_INCLUDE_DIR})
    target_link_libraries(rendell ${X11_LIBRARIES})

endif()

# OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(rendell PRIVATE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(rendell ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL not found!")
endif()

# Glad
add_subdirectory(glad)
target_link_libraries(rendell glad)