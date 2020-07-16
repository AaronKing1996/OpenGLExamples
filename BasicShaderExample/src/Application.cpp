#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

#include "utils\ShaderLoader.h"

int main(void)
{
	GLFWwindow* window;

	// ��ʼ��glfw
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

	// glewInit������context֮��
	GLenum err = glewInit();
	if (GLEW_OK == err) {
		std::cout << "Glew init successful!" << std::endl;
		std::cout << glGetString(GL_VERSION) << std::endl;
	}
	else {
		std::cout << "Glew init failed!" << std::endl;
		return -1;
	}

	// ������Ϣ
	float positions[6] = {
		0.0f, 1.0f,
		0.5f, 0.0f,
       -0.5f, 0.0f
	};
	// ����id
	GLenum bufferId;
	// ���뻺��
	glGenBuffers(1, &bufferId);
	// ѡ��ǰ����
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	// �����е����ݸ�ֵ
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), &positions, GL_STATIC_DRAW);
	// ���ã�״̬���ģ���������
	glEnableVertexAttribArray(0);
	// ���ö���Ĳ��֣���һ������Ϊ������������ӦglEnableVertexAttribArray(0)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	/*������ɫ��*/
	std::map<std::string, unsigned int> shaderMap;
	shaderMap["resources/shaders/BasicVertexShader.shader"] = GL_VERTEX_SHADER;
	shaderMap["resources/shaders/BasicFragmentShader.shader"] = GL_FRAGMENT_SHADER;

	ShaderLoader shaderLoader;
	unsigned int shaderProgram = shaderLoader.createProgram(shaderMap);
	// ������ɫ��
	glUseProgram(shaderProgram);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// ���ƻ������ݣ����һ������Ϊ�ܹ���������
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// ɾ����ɫ������
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}