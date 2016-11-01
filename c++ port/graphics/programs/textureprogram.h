#ifndef CORE_TEXTUREPROGRAM_H
#define CORE_TEXTUREPROGRAM_H


#include <glm/glm.hpp>
#include "shaderprogram.h"
#include "../gl_structs/color.h"

class TextureProgram: public ShaderProgram {
public:
    glm::mat4 projectionMatrix;
    glm::mat4 modelViewMatrix;

    TextureProgram();
    void loadProgram();
    void setVertexPointer(GLsizei stride, const GLvoid* data);
    void setTexCoordPointer(GLsizei stride, const GLvoid* data);
    void enableDataPointers();
    void disableDataPointers();
    void leftMultProjection(glm::mat4 matrix);
    void leftMultModelView(glm::mat4 matrix);
    void updateProjection();
    void updateModelView();
    void setTextureColor(Color color);
    void setTextureUnit(GLuint unit);
private:
    GLint vertexPosLocation;
    GLint texCoordLocation;
    GLint textureColorLocation;
    GLint textureUnitLocation;
    GLint projectionMatrixLocation;
    GLint modelViewMatrixLocation;
};


#endif //CORE_TEXTUREPROGRAM_H
