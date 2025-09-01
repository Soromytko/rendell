cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)

project(Rendell)

set(SOURCE_FILES
    src/CommandBuffer.cpp
    src/CommandExecutor.cpp
    src/logging.cpp

    src/init.cpp
    src/rendell.cpp
    src/context_creation.cpp
    src/RenderContext.cpp
    src/RenderContextManager.cpp
    src/IndexBuffer.cpp
    src/VertexBuffer.cpp
    src/VertexArray.cpp
    src/VertexBufferLayout.cpp
    src/ShaderProgram.cpp
    src/Texture2D.cpp
    src/Texture2DArray.cpp
    src/ShaderBuffer.cpp
    src/UniformBuffer.cpp
    src/Factory.cpp
    src/OpenGL/glad_initialization.cpp
    src/OpenGL/OpenGLUtils.cpp
    src/OpenGL/OpenGLFactory.cpp
    src/OpenGL/OpenGLSpecification.cpp
    src/OpenGL/OpenGLIndexBuffer.cpp
    src/OpenGL/OpenGLVertexBuffer.cpp
    src/OpenGL/OpenGLVertexArray.cpp
    src/OpenGL/OpenGLShaderProgram.cpp
    src/OpenGL/OpenGLTexture2D.cpp
    src/OpenGL/OpenGLTexture2DArray.cpp
    src/OpenGL/OpenGLShaderBuffer.cpp
    src/OpenGL/OpenGLUniformBuffer.cpp
    src/OpenGL/OpenGLVertexShader.cpp
    src/OpenGL/OpenGLFragmentShader.cpp
)

set(HEADER_FILES
    include/rendell/rendell.h
    include/rendell/init.h
    include/rendell/ResourceId.h
    include/rendell/DataType.h
    include/rendell/Ref.h
    include/rendell/TextureFormat.h
    include/rendell/RenderContext.h

    include/rendell/private/defines.h
    
    internal/raii.h
    internal/logging.h
    internal/Command.h
    internal/CommandBuffer.h
    internal/CommandExecutor.h
    internal/RenderContextManager.h
    internal/RenderContextImpl.h
    internal/ResourceIdStorage.h
    internal/DrawCallState.h

    internal/backend/Factory.h
    internal/backend/IndexBuffer.h
    internal/backend/VertexBuffer.h
    internal/backend/VertexArray.h
    internal/backend/VertexBufferLayout.h
    internal/backend/Texture2D.h
    internal/backend/Texture2DArray.h
    internal/backend/ShaderBuffer.h
    internal/backend/UniformBuffer.h
    internal/backend/VertexShader.h
    internal/backend/FragmentShader.h
    internal/backend/ShaderProgram.h
    internal/backend/Uniform.h

    # OpenGL specific
    internal/gl/wglext.h

    src/context_creation.h
    src/IContext.h
    src/OpenGL/glad_initialization.h
    src/OpenGL/OpenGLShaderCompilation.h
    src/OpenGL/OpenGLContext.h
    src/OpenGL/OpenGLUtils.h
    src/OpenGL/OpenGLFactory.h
    src/OpenGL/OpenGLSpecification.h
    src/OpenGL/OpenGLIndexBuffer.h
    src/OpenGL/OpenGLVertexBuffer.h
    src/OpenGL/OpenGLVertexArray.h
    src/OpenGL/OpenGLShaderProgram.h
    src/OpenGL/OpenGLTexture2D.h
    src/OpenGL/OpenGLTexture2DArray.h
    src/OpenGL/OpenGLShaderBuffer.h
    src/OpenGL/OpenGLUniformBuffer.h
    src/OpenGL/OpenGLVertexShader.h
    src/OpenGL/OpenGLFragmentShader.h
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
target_include_directories(rendell PRIVATE internal)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_sources(rendell PRIVATE ${WINDOWS_SOURCES} ${WINDOWS_HEADERS})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(rendell PRIVATE ${LINUX_SOURCES} ${LINUX_HEADERS})

    #x11
    find_package(X11 REQUIRED)
    include_directories(rendell PRIVATE ${X11_INCLUDE_DIR})
    target_link_libraries(rendell PRIVATE ${X11_LIBRARIES})

endif()

# OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(rendell PRIVATE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(rendell PRIVATE ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL not found!")
endif()

# Glad
add_subdirectory(glad)
target_link_libraries(rendell PRIVATE glad)
