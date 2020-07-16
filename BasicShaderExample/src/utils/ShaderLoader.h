#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderLoader
{
public:
	ShaderLoader();
	~ShaderLoader();

	/**
	* @brief 编译着色器
	* @param type 着色器的类型，如顶点着色器、片元着色器
	* @param source 着色器的源码
	*
	* @return 着色器id
	*/
	unsigned int compileShader(unsigned int type, const std::string& source);

	/**
	* @brief 获取着色器链接好的着色器程序（program）
	* @param shaderMap <着色器文件的路径, 着色器的类型>
	*
	* @return 链接好的着色器程序对象id
	*/
	unsigned int createProgram(std::map<std::string, unsigned int> shaderMap);

private:
	/**
	* @brief 读取着色器文件，返回内容字符串
	* @param path 着色器文件的路径
	*
	* @return 文件内容字符串
	*/
	std::string readSourceFile(const std::string& path);
};

