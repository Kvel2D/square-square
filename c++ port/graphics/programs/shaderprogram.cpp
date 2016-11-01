#include "shaderprogram.h"
#include "../../main.h"
#include <cstdio>
#include <fstream>

ShaderProgram::ShaderProgram() {
    programID = 0;
}

ShaderProgram::~ShaderProgram() {
    freeProgram();
}

GLuint ShaderProgram::loadShaderFromFile(std::string path, GLenum shaderType) {
    GLuint shaderID = 0;
    std::string shaderString;
    std::ifstream sourceFile(path.c_str());

    if (sourceFile) {
        shaderString.assign((std::istreambuf_iterator<char>(sourceFile)),
                            std::istreambuf_iterator<char>());
        shaderID = glCreateShader(shaderType);
        const GLchar *shaderSource = shaderString.c_str();
        glShaderSource(shaderID, 1, &shaderSource, NULL);
        glCompileShader(shaderID);
        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
        if (shaderCompiled != GL_TRUE) {
            printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource);
            printShaderLog(shaderID);
            glDeleteShader(shaderID);
            shaderID = 0;
            exitApp(1);
        }
    } else {
        printf("Unable to open file %s\n", path.c_str());
        exitApp(1);
    }

    return shaderID;
}

void ShaderProgram::freeProgram() {
    glDeleteProgram(programID);
}

void ShaderProgram::bind() {
    glUseProgram(programID);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding shader! %s\n", gluErrorString(error));
        printProgramLog(programID);
        exitApp(1);
    }
}

void ShaderProgram::unbind() {
    glUseProgram(0);
}

void ShaderProgram::printProgramLog(GLuint program) {
    if (!glIsProgram(program)) {
        printf("Name %d is not a program\n", program);
        return;
    }

    int infoLogLength = 0;
    int maxLength = infoLogLength;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    char *infoLog = new char[maxLength];

    glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);

    if (infoLogLength > 0) {
        //Print Log
        printf("%s\n", infoLog);
    }

    //Deallocate string
    delete[] infoLog;
}

void ShaderProgram::printShaderLog(GLuint shader) {
    //Make sure name is shader
    if (!glIsShader(shader)) {
        printf("Name %d is not a shader\n", shader);
        return;
    }
    //Shader log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    //Get info string length
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char *infoLog = new char[maxLength];

    //Get info log
    glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
        //Print Log
        printf("%s\n", infoLog);
    }

    //Deallocate string
    delete[] infoLog;
}