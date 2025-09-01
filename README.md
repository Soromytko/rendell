# What is Rendell?

Rendell is a cross-platform rendering library. Rendell does not impose its own data formats (e.g., shader language, images, etc.), by creating a black box. Its task is to be clear and provide a convenient and cross-platform API.

# Build

```
cd build
cmake ..
cmake --build .
```

# How to use Rendell?

To use [Rendell](https://github.com/Soromytko/rendell) in your own project
clone this repository into your project folder and add the following code to your CMakeLists.txt file:

```
add_subdirectory(rendell)
target_link_libraries(${EXE_NAME} rendell)
```

## Rendell-UI sample

This is a sample of drawing a triangle using [Rendell](https://github.com/Soromytko/rendell) and [Rendell-UI](https://github.com/Soromytko/rendell-ui).

```
#include <rendell/rendell.h>
#include <rendell_ui/rendell_ui.h>

std::vector<uint32_t> indices{ 0, 1, 2 };
std::vector<float> vertices{
	-0.5f, -0.5f, 0.0f,		1.0, 0.0, 0.0,
	0.5f, -0.5f, 0.0f,		0.0, 1.0, 0.0,
	0.0f, 0.5f, 0.0f,		0.0, 0.0, 1.0,
};
rendell::VertexBufferLayout vertexLayout{ rendell::ShaderDataType::float3, false, 0 };
rendell::VertexBufferLayout colorLayout{ rendell::ShaderDataType::float3, false, 1 };

std::string vertSrc = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	out vec3 vColor;
	void main()
	{
		vColor = aColor;
		gl_Position = vec4(aPos, 1.0);
	}
)";

std::string fragSrc = R"(
	out vec4 FragColor;
	in vec3 vColor;
	void main()
	{
		FragColor = vec4(vColor, 1.0f);
	}
)";

bool initRendell(rendell_ui::WindowSharedPtr window)
{
	rendell::Initer initer;
	initer.nativeWindowHandle = window->getNativeWindowHandle();
	initer.x11Display = window->getX11Display();
	return rendell::init(initer);
}

int main(void)
{
	// Create Window
	rendell_ui::WindowSharedPtr window;
	window = rendell_ui::makeWindow(600, 400, "Hello from Rendell and Rendell-UI");

	if (!initRendell(window)) {
		std::cerr << "Failed to initialize Rendell" << std::endl;
		return -1;
	}

	if (!rendell_ui::init()) {
		std::cerr << "Failed to initialize Rendell-UI" << std::endl;
		rendell::release();
		return -1;
	}

	// Create index buffer
	const auto indexBuffer = rendell::createIndexBuffer(indices);

	// Create vertex buffer and layouts
	const auto vertexBuffer = rendell::createVertexBuffer(vertices);
	vertexBuffer->setLayouts({ vertexLayout, colorLayout });

	// Create vertex array
	const auto vertexArray = rendell::createVertexArray(indexBuffer, { vertexBuffer });

	// Create and prepare shader program
	const auto shaderProgram = rendell::createShaderProgram(vertSrc, fragSrc);
	std::string infoLog;
	if (!shaderProgram->compile(&infoLog)) {
		std::cerr << infoLog << std::endl;
		rendell_ui::release();
		rendell::release();
		return -1;
	}
	if (!shaderProgram->link(&infoLog)) {
		std::cerr << infoLog << std::endl;
		rendell_ui::release();
		rendell::release();
		return -1;
	}
	shaderProgram->freeSrc();

	while (window->isOpen()) {
		rendell::clearColor(0, 0, 0, 1);

		// Draw triangle with Rendell
		vertexArray->bind();
		shaderProgram->bind();
		rendell::drawTriangleElements(indexBuffer->getIndices().size());

		rendell::swapBuffers();

		window->processEvents();
	}

	rendell_ui::release();
	rendell::release();
	return 0;
}
```

## GLFW sample

Rendell can be used with libraries that can open an operating system window (like GLFW and SDL2). But note that Rendell creates its own rendering context.

This is a sample of drawing a triangle using [Rendell](https://github.com/Soromytko/rendell) and [GLFW](https://github.com/glfw/glfw).

```
#include <iostream>
#include <rendell/init.h>
#include <rendell/oop/rendell_oop.h>
#include <rendell/rendell.h>
#include <cassert>

// GLFW specifics
#if defined(_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(__linux__)
#define GLFW_EXPOSE_NATIVE_X11
#endif
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

std::vector<uint32_t> indices{0, 1, 2};
std::vector<float> vertices{
    // Vertices
    -0.5f, -0.5f, 0.0f,
    1.0, 0.0, 0.0,
    0.5f, -0.5f, 0.0f,
    // Colors
    0.0, 1.0, 0.0,
    0.0f, 0.5f, 0.0f,
};
std::string vertSrc = R"(
	#version 450 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	out vec3 vColor;
	void main()
	{
		vColor = aColor;
		gl_Position = vec4(aPos, 1.0);
	}
)";

std::string fragSrc = R"(
    #version 450 core
	out vec4 FragColor;
	in vec3 vColor;
	void main()
	{
		FragColor = vec4(vColor, 1.0f);
	}
)";

void shaderCallback(bool success, const std::string &infoLog) {
    std::cout << infoLog << std::endl;
    assert(success);
}

bool initRendell(GLFWwindow *window) {
    rendell::Initer initer{.api = rendell::SpecificationAPI::OpenGL45};
    if (!rendell::init(initer)) {
        return false;
    }
    rendell::NativeView nativeView;
    nativeView.nativeWindowHandle = (void *)glfwGetWin32Window(window);
    if (!rendell::registerNativeView(nativeView)) {
        return false;
    }
    return true;
}

int run(GLFWwindow *window) {
    // Create index buffer
    const auto indexBuffer = rendell::oop::makeIndexBuffer(indices.data(), indices.size());

    // Create vertex buffer
    const auto vertexBuffer = rendell::oop::makeVertexBuffer(vertices.data(), vertices.size());

    // Create vertex assembly
    const auto vertexAssembly = rendell::oop::makeVertexAssembly(
        indexBuffer,
        std::vector{vertexBuffer},
        std::vector{rendell::VertexLayout()
                        .addAttribute(0, rendell::ShaderDataType::float3, false, 0)
                        .addAttribute(1, rendell::ShaderDataType::float3, false, 0)});

    // Create shader program
    const auto vertexShader = rendell::oop::makeVertexShader(vertSrc, shaderCallback);
    const auto fragmentShader = rendell::oop::makeFragmentShader(fragSrc, shaderCallback);
    const auto shaderProgram =
        rendell::oop::makeShaderProgram(vertexShader, fragmentShader, shaderCallback);

    while (!glfwWindowShouldClose(window)) {
        rendell::setClearBits(rendell::c::colorBufferBit);
        rendell::setClearColor(0, 0, 0, 1);

        // Draw triangle with Rendell
        vertexAssembly->use();
        shaderProgram->use();
        rendell::submit(rendell::DrawMode::Elements, rendell::PrimitiveTopology::Triangles);

        rendell::renderFrame();

        glfwPollEvents();
    }

    return 0;
}

int main(void) {
#if defined(__linux__)
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Disable automatic context creation
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello from Rendell and GLFW", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        return -1;
    }

    if (!initRendell(window)) {
        std::cerr << "Failed to initialize Rendell" << std::endl;
        return -1;
    }

    const int result = run(window);
    rendell::release();
    glfwTerminate();

    return result;
}
```