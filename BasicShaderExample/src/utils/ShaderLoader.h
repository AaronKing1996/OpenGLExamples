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
	* @brief ������ɫ��
	* @param type ��ɫ�������ͣ��綥����ɫ����ƬԪ��ɫ��
	* @param source ��ɫ����Դ��
	*
	* @return ��ɫ��id
	*/
	unsigned int compileShader(unsigned int type, const std::string& source);

	/**
	* @brief ��ȡ��ɫ�����Ӻõ���ɫ������program��
	* @param shaderMap <��ɫ���ļ���·��, ��ɫ��������>
	*
	* @return ���Ӻõ���ɫ���������id
	*/
	unsigned int createProgram(std::map<std::string, unsigned int> shaderMap);

private:
	/**
	* @brief ��ȡ��ɫ���ļ������������ַ���
	* @param path ��ɫ���ļ���·��
	*
	* @return �ļ������ַ���
	*/
	std::string readSourceFile(const std::string& path);
};

