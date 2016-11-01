#ifndef CORE_TEXTURE_H
#define CORE_TEXTURE_H


#include <GL/glew.h>
#include <string>
#include "gl_structs/rectangle.h"
#include "programs/textureprogram.h"

class GLTexture {
public:
    static TextureProgram *textureProgram;
    GLuint imageWidth;
    GLuint imageHeight;

    GLTexture();
    ~GLTexture();
    void loadFromFile(std::string path);
    void freeTexture();
    void render(GLfloat x, GLfloat y, Rectangle *clip = NULL);
private:
    static GLuint boundTextureID;
    GLuint textureID;
    GLuint textureWidth;
    GLuint textureHeight;
    GLuint VBOID;
    GLuint IBOID;

    void initVBO();
    void freeVBO();
    GLuint powerOfTwo(GLuint number);
};


#endif //CORE_TEXTURE_H
