# What is Rendell?

Rendell is a cross-platform rendering library.

# Build

To use [Rendell](https://github.com/Soromytko/rendell) in your own project
clone this repository into your project folder and add the following code to your CMakeLists.txt file:

```
add_subdirectory(rendell)
target_link_libraries(${EXE_NAME} rendell)
```

# Sample

This is a sample of drawing a triangle using [Rendell](https://github.com/Soromytko/rendell) and [GLFW](https://github.com/glfw/glfw).

```
#include <GLFW/glfw3.h>
#include <rendell/rendell.h>

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

bool initRendell()
{
	rendell::Initer initer;
	initer.context = static_cast<void*>(glfwGetProcAddress);
	return rendell::init(initer);
}

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!initRendell())
	{
		std::cout << "Failed to initialize Rendell" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Create index buffer
	rendell::IndexBuffer* indexBuffer = rendell::createIndexBuffer(indices);

	// Create vertex buffer and layouts
	rendell::VertexBuffer* vertexBuffer = rendell::createVertexBuffer(vertices);
	vertexBuffer->setLayouts({ vertexLayout, colorLayout });

	// Create vertex array
	std::unique_ptr<rendell::VertexArray> vertexArray{ rendell::createVertexArray() };
	vertexArray->addVertexBuffer(vertexBuffer);
	vertexArray->setIndexBuffer(indexBuffer);

	// Create and prepare shader program
	std::unique_ptr<rendell::ShaderProgram> shaderProgram{
		rendell::createShaderProgram(vertSrc, fragSrc)
	};
	std::string infoLog;
	if (!shaderProgram->compile(&infoLog))
	{
		std::cout << infoLog << std::endl;
		glfwTerminate();
		rendell::release();
		return -1;
	}
	if (!shaderProgram->link(&infoLog))
	{
		std::cout << infoLog << std::endl;
		glfwTerminate();
		rendell::release();
		return -1;
	}
	shaderProgram->freeSrc();

	while (!glfwWindowShouldClose(window))
	{
		rendell::clearColor(0, 0, 0, 1);

		// Draw triangle with rendell
		vertexArray->bind();
		shaderProgram->bind();
		rendell::drawTriangleElements(indexBuffer->getIndices().size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	rendell::release();
	return 0;
}
```