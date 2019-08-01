#include "Shader.h"
#include "Error.h"
#include <fstream>
#include<iostream>
#include <sstream>

namespace PandaEngine {

	Shader::Shader() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
	{
	}


	Shader::~Shader()
	{
	}

	void Shader::loadShaderFromFile(const std::string & vertexFilePath, const std::string & fragmentFilePath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		try
		{
			// Open files
			std::ifstream vertexShaderFile(vertexFilePath);
			std::ifstream fragmentShaderFile(fragmentFilePath);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (std::exception e)
		{
			std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
		}

		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar *fShaderCode = fragmentCode.c_str();

		compileShader(vShaderCode, fShaderCode);
	}

	void Shader::linkShader()
	{

		_programID = glCreateProgram();

		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		glLinkProgram(_programID);

		checkError(_programID, "PROGRAM");

	}

	void Shader::compileShader(const char* vertexFile, const char* fragmentFile)
	{
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

		if (_vertexShaderID == 0)
		{
			fatalError("vertex Shader Failed to Created");
		}

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		if (_fragmentShaderID == 0)
		{
			fatalError("vertex Shader Failed to Created");
		}

		glShaderSource(_vertexShaderID, 1, &vertexFile, nullptr);
		glCompileShader(_vertexShaderID);

		checkError(_vertexShaderID, "VERTEX");

		glShaderSource(_fragmentShaderID, 1, &fragmentFile, nullptr);
		glCompileShader(_fragmentShaderID);

		checkError(_fragmentShaderID, "FRAGMENT");

		linkShader();

	}

	void Shader::use()
	{
		glUseProgram(_programID);
	}

	void Shader::unUse()
	{
		glUseProgram(0);
	}

	void Shader::checkError(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				fatalError("ERROR::SHADER: Compile-time error: Type: " + type + "\n"
					+ infoLog + "\n -- --------------------------------------------------- -- "
				);

				if (type == "VERTEX")
				{
					glDeleteShader(_vertexShaderID);
					return;
				}
				else
				{
					glDeleteShader(_fragmentShaderID);
					return;
				}
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				fatalError("ERROR::Shader: Link-time error: Type: " + type + "\n"
					+ infoLog + "\n -- --------------------------------------------------- -- "
				);

				glDeleteShader(_vertexShaderID);
				glDeleteShader(_fragmentShaderID);
				glDeleteProgram(_programID);

				return;
			}

			glDetachShader(_programID, _vertexShaderID);
			glDetachShader(_programID, _fragmentShaderID);
		}
	}


	void Shader::SetFloat(const GLchar *name, GLfloat value, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform1f(glGetUniformLocation(this->_programID, name), value);
	}
	void Shader::SetInteger(const GLchar *name, GLint value, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform1i(glGetUniformLocation(this->_programID, name), value);
	}
	void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform2f(glGetUniformLocation(this->_programID, name), x, y);
	}
	void Shader::SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform2f(glGetUniformLocation(this->_programID, name), value.x, value.y);
	}
	void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform3f(glGetUniformLocation(this->_programID, name), x, y, z);
	}
	void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform3f(glGetUniformLocation(this->_programID, name), value.x, value.y, value.z);
	}
	void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform4f(glGetUniformLocation(this->_programID, name), x, y, z, w);
	}
	void Shader::SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform4f(glGetUniformLocation(this->_programID, name), value.x, value.y, value.z, value.w);
	}
	void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniformMatrix4fv(glGetUniformLocation(this->_programID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}
}