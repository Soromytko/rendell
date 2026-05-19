cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)

project(Rendell)

set(SOURCE_FILES
    src/logging.cpp
    src/ByteRingBuffer.cpp

    src/hash.cpp
    src/Instance.cpp
    src/InstanceImpl.cpp
    src/context_creation.cpp
    src/Color.cpp
    src/CallbackTable.cpp
    src/ResourceCommandBuffer.cpp
    src/ResourceCommandBufferImpl.cpp
    src/RenderCommandBuffer.cpp
    src/RenderPipelineStorage.cpp
    src/ResourceExecutor.cpp
    src/DataContainerStorage.cpp
    src/TextureFormat.cpp
    src/Service.cpp
    src/GarbageCollector.cpp

    src/OpenGL/OpenGLShaderCompilation.cpp
    src/OpenGL/OpenGLRenderPipeline.cpp
    src/OpenGL/OpenGLRenderPipelineSync.cpp
    src/OpenGL/OpenGLResourceExecutor.cpp
    src/OpenGL/OpenGLRenderExecutor.cpp
    src/OpenGL/OpenGLResourceStorage.cpp
    src/OpenGL/glad_initialization.cpp
    src/OpenGL/OpenGLTextureFormat.cpp
    src/OpenGL/OpenGLIndexBuffer.cpp
    src/OpenGL/OpenGLVertexBuffer.cpp
    src/OpenGL/OpenGLVertexBufferLayout.cpp
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
    include/rendell/init_types.h
    include/rendell/hash.h
    include/rendell/consts.h

    include/rendell/Instance.h
    include/rendell/ResourceId.h
    include/rendell/DataType.h
    include/rendell/DrawType.h
    include/rendell/Color.h
    include/rendell/DataContainer.h
    include/rendell/TextureFormat.h
    include/rendell/ResourceCommandBuffer.h
    include/rendell/RenderCommandBuffer.h
    include/rendell/VertexLayout.h
    include/rendell/Service.h
    include/rendell/GarbageCollector.h

    internal/InstanceImpl.h
    internal/RendellExtractor.h
    internal/ResourceIdsAllocator.h
    internal/ReleasedResourceIds.h
    
    internal/config.h
    internal/IContext.h
    internal/context_creation.h
    internal/logging.h
    internal/Command.h
    internal/Pool.h
    internal/CommandBufferPool.h
    internal/RenderPipelineStorage.h
    internal/ResourceIdStorage.h
    internal/DrawCallState.h
    internal/RenderPipeline.h
    internal/ResourceCommandBufferImpl.h
    internal/RenderCommandBufferImpl.h
    internal/ResourceExecutor.h
    internal/DataContainerStorage.h
    internal/ResourceDataProvider.h
    internal/CallbackTable.h
    internal/InstanceRegistry.h

    internal/Buffers/Buffer.h
    internal/Buffers/ByteBuffer.h
    internal/Buffers/RingBuffer.h
    internal/Buffers/ByteRingBuffer.h

    internal/utils/MPMC_Queue.h
    internal/utils/ConcurrentQueue.h
    internal/utils/Registry.h

    internal/OpenGL/OpenGLContext.h
    internal/OpenGL/OpenGLRenderPipeline.h
    internal/OpenGL/OpenGLRenderPipelineSync.h
    internal/OpenGL/OpenGLResourceExecutor.h
    internal/OpenGL/OpenGLRenderExecutor.h
    internal/OpenGL/OpenGLIndexBuffer.h
    internal/OpenGL/OpenGLVertexBuffer.h
    internal/OpenGL/OpenGLVertexBufferLayout.h
    internal/OpenGL/OpenGLVertexArray.h
    internal/OpenGL/OpenGLShaderProgram.h
    internal/OpenGL/OpenGLTexture2D.h
    internal/OpenGL/OpenGLTexture2DArray.h
    internal/OpenGL/OpenGLShaderBuffer.h
    internal/OpenGL/OpenGLUniformBuffer.h
    internal/OpenGL/OpenGLVertexShader.h
    internal/OpenGL/OpenGLFragmentShader.h
    internal/OpenGL/OpenGLResourceStorage.h

    include/rendell/ResourceIdGuard.h

    # OpenGL specific
    internal/gl/wglext.h

    src/OpenGL/glad_initialization.h
    src/OpenGL/OpenGLShaderCompilation.h
    src/OpenGL/OpenGLTextureFormat.h
)

set(WINDOWS_SOURCES
    src/OpenGL/Platform/WindowsOpenGLContext.cpp
)

set(WINDOWS_HEADERS
    internal/OpenGL/Platform/WindowsOpenGLContext.h
)

set(LINUX_SOURCES
    src/OpenGL/Platform/LinuxOpenGLContext.cpp
)

set(LINUX_HEADERS
    internal/OpenGL/Platform/LinuxOpenGLContext.h
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

# logr

if(NOT TARGET logr)
    add_subdirectory(logr)
endif()
target_link_libraries(rendell PRIVATE logr)
