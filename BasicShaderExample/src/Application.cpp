#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

#include "utils\ShaderLoader.h"

int main(void)
{
	GLFWwindow* window;

	// 初始化glfw
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// glewInit必须在context之后
	GLenum err = glewInit();
	if (GLEW_OK == err) {
		std::cout << "Glew init successful!" << std::endl;
		std::cout << glGetString(GL_VERSION) << std::endl;
	}
	else {
		std::cout << "Glew init failed!" << std::endl;
		return -1;
	}

	// 顶点信息
	float positions[6] = {
		0.0f, 1.0f,
		0.5f, 0.0f,
       -0.5f, 0.0f
	};
	// 缓存id
	GLenum bufferId;
	// 申请缓存
	glGenBuffers(1, &bufferId);
	// 选择当前缓存
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	// 缓存中的数据赋值
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), &positions, GL_STATIC_DRAW);
	// 启用（状态机的）顶点属性
	glEnableVertexAttribArray(0);
	// 设置顶点的布局，第一个参数为属性索引，对应glEnableVertexAttribArray(0)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	/*载入着色器*/
	std::map<std::string, unsigned int> shaderMap;
	shaderMap["resources/shaders/BasicVertexShader.shader"] = GL_VERTEX_SHADER;
	shaderMap["resources/shaders/BasicFragmentShader.shader"] = GL_FRAGMENT_SHADER;

	ShaderLoader shaderLoader;
	unsigned int shaderProgram = shaderLoader.createProgram(shaderMap);
	// 启用着色器
	glUseProgram(shaderProgram);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// 绘制缓存数据，最后一个参数为总共几个顶点
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// 删除着色器对象
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}