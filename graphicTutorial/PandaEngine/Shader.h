#ifndef SHADER_H
#define SHADER_H
#include <string>
#include<GL/glew.h>
#include<GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
namespace PandaEngine {

	class Shader
	{
	public:
		Shader();
		~Shader();

		void loadShaderFromFile(const std::string& vertexFilePath, const std::string& fragmentFilePath);
		void linkShader();
		void compileShader(const char* vertexFile, const char* fragmentFile);
		void use();
		void unUse();


		void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
		void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
		void SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
		void SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
		void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
		void SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
		void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
		void SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
		void SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
	private:

		void checkError(GLuint shader, std::string type);

		GLuint _programID;
		GLuint _vertexShaderID, _fragmentShaderID;
	};
}
#endif // !SHADER_H




