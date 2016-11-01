#ifndef CORE_SHADERPROGRAM_H
#define CORE_SHADERPROGRAM_H


#include <GL/glew.h>
#include <string>

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();
    GLuint loadShaderFromFile(std::string path, GLenum shaderType);
    virtual void loadProgram() = 0;
    virtual void freeProgram();
    void bind();
    void unbind();
protected:
    GLuint programID;
    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);
};


#endif //CORE_SHADERPROGRAM_H
