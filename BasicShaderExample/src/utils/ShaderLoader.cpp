#include "ShaderLoader.h"

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

unsigned int ShaderLoader::compileShader(unsigned int type, const std::string& source) 
{ 
	// 创建着色器
	unsigned int shaderId = glCreateShader(type);
	// 着色器源码
	const char* src = source.c_str();
	glShaderSource(shaderId, 1, &src, nullptr);
	// 编译着色器
	glCompileShader(shaderId);

	/* 验证是否编译成功 */
	int result;
	// 从着色器对象返回参数
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
	// 创建着色器程序
	unsigned int program = glCreateProgram();

	std::map<std::string, unsigned int>::iterator it;
	for (it = shaderMap.begin(); it != shaderMap.end(); it++) {
		// 读取着色器文件
		std::string source = readSourceFile(it->first);
		// 编译着色器
		unsigned int shaderId = compileShader(it->second, source);
		// 将着色器对象附加到程序对象
		glAttachShader(program, shaderId);
	}

	// 链接着色器对象
	glLinkProgram(program);
	// 验证程序对象
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