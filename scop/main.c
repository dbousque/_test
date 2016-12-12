
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void    key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	(void)window;
	(void)scancode;
	(void)action;
	(void)mode;
	printf("key : %d\n", key);
}

void    render_triangle(GLFWwindow *window)
{
	(void)window;
	GLfloat		vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	GLuint	VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	char	shader[] =
"	#version 330 code"
""
"	layout (location = 0) vin ec3 position;"
""
"	void main()"
"	{"
"		gl_Position = vec4(position.x, position.y, position.z, 1.0);"
"	}";
	GLuint	shader_object;

	shader_object = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader_object, 1, &shader, NULL);
	glCompileShader(shader_object);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader_object, GL_COMPILE_STATUS, &success);

	
	(void)shader_object;
	(void)shader;
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// macos
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (!window)
	{
	    printf("Failed to create GLFW window\n");
	    glfwTerminate();
	    return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
	    printf("Failed to initialize GLEW\n");
	    return -1;
	}
	int     width;
	int     height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window))
	{
	    glfwPollEvents();

	    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT);

	    glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
