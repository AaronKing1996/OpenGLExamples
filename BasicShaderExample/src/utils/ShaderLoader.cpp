#include "ShaderLoader.h"

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

unsigned int ShaderLoader::compileShader(unsigned int type, const std::string& source) 
{ 
	// ������ɫ��
	unsigned int shaderId = glCreateShader(type);
	// ��ɫ��Դ��
	const char* src = source.c_str();
	glShaderSource(shaderId, 1, &src, nullptr);
	// ������ɫ��
	glCompileShader(shaderId);

	/* ��֤�Ƿ����ɹ� */
	int result;
	// ����ɫ�����󷵻ز���
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(shaderId, length, &length, message);
		
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(shaderId);
		return -1;
	}

	return shaderId;
}

unsigned int ShaderLoader::createProgram(std::map<std::string, unsigned int> shaderMap)
{
	// ������ɫ������
	unsigned int program = glCreateProgram();

	std::map<std::string, unsigned int>::iterator it;
	for (it = shaderMap.begin(); it != shaderMap.end(); it++) {
		// ��ȡ��ɫ���ļ�
		std::string source = readSourceFile(it->first);
		// ������ɫ��
		unsigned int shaderId = compileShader(it->second, source);
		// ����ɫ�����󸽼ӵ��������
		glAttachShader(program, shaderId);
	}

	// ������ɫ������
	glLinkProgram(program);
	// ��֤�������
	glValidateProgram(program);

	return program;
}

std::string ShaderLoader::readSourceFile(const std::string& path)
{

	std::ifstream stream(path.c_str());
	std::stringstream ss;

	if (!stream.is_open()) {
		std::cout << "Failed to open shader file, path = " << path << std::endl;
		return "";
	}

	std::string str;
	while (getline(stream, str)) {
		ss << str << std::endl;
	}

	stream.close();

	return ss.str();
}