#include <cstdio>
#include <glm/gtc/type_ptr.hpp>
#include "textureprogram.h"

TextureProgram::TextureProgram() {
    vertexPosLocation = 0;
    texCoordLocation = 0;
    projectionMatrixLocation = 0;
    modelViewMatrixLocation = 0;
    textureColorLocation = 0;
    textureUnitLocation = 0;
}

void TextureProgram::loadProgram() {
    programID = glCreateProgram();

    // Load and attach shaders
    GLuint vertexShader = loadShaderFromFile("assets/shaders/TextureVertex.glsl", GL_VERTEX_SHADER);
    if (vertexShader == 0) {
        glDeleteProgram(programID);
        programID = 0;
    }
    glAttachShader(programID, vertexShader);
    GLuint fragmentShader = loadShaderFromFile("assets/shaders/TextureFragment.glsl", GL_FRAGMENT_SHADER);
    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        glDeleteProgram(programID);
        programID = 0;
    }
    glAttachShader(programID, fragmentShader);

    // Link program
    glLinkProgram(programID);
    // Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(programID, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        printf("Error linking program %d!\n", programID);
        printProgramLog(programID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(programID);
        programID = 0;
    }

    // Clean up excess shader references
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Get variable locations
    vertexPosLocation = glGetAttribLocation(programID, "VertexPos2D");
    if (vertexPosLocation == -1) {
        printf("%s is not a valid glsl program variable!\n", "VertexPos2D");
    }

    texCoordLocation = glGetAttribLocation(programID, "TexCoord");
    if (texCoordLocation == -1) {
        printf("%s is not a valid glsl program variable!\n", "TexCoord");
    }

    textureColorLocation = glGetUniformLocation(programID, "TextureColor");
    if (textureColorLocation == -1) {
        printf("%s is not a valid glsl program variable!\n", "TextureColor");
    }

    textureUnitLocation = glGetUniformLocation(programID, "TextureUnit");
    if (textureUnitLocation == -1) {
        printf("%s is not a valid glsl program variable!\n", "TextureUnit");
    }

    projectionMatrixLocation = glGetUniformLocation(programID, "ProjectionMatrix");
    if (projectionMatrixLocation == -1) {
        printf("%s is not a valid glsl program variable!\n", "ProjectionMatrix");
    }

    modelViewMatrixLocation = glGetUniformLocation(programID, "ModelViewMatrix");
    if (modelViewMatrixLocation == -1) {
        printf("%s is not a valid glsl program variable!\n", "ModelViewMatrix");
    }
}

void TextureProgram::setVertexPointer(GLsizei stride, const GLvoid *data) {
    glVertexAttribPointer(vertexPosLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void TextureProgram::setTexCoordPointer(GLsizei stride, const GLvoid *data) {
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void TextureProgram::leftMultProjection(glm::mat4 matrix) {
    projectionMatrix = matrix * projectionMatrix;
}

void TextureProgram::leftMultModelView(glm::mat4 matrix) {
    modelViewMatrix = matrix * modelViewMatrix;
}

void TextureProgram::updateProjection() {
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void TextureProgram::updateModelView() {
    glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
}

void TextureProgram::setTextureColor(Color color) {
    glUniform4f(textureColorLocation, color.r, color.g, color.b, color.a);
}

void TextureProgram::setTextureUnit(GLuint unit) {
    glUniform1i(textureUnitLocation, unit);
}

void TextureProgram::enableDataPointers() {
    glEnableVertexAttribArray(vertexPosLocation);
    glEnableVertexAttribArray(texCoordLocation);
}

void TextureProgram::disableDataPointers() {
    glDisableVertexAttribArray(vertexPosLocation);
    glDisableVertexAttribArray(texCoordLocation);
}




