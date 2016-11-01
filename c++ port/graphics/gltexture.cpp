#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <glm/gtx/transform.hpp>
#include "gltexture.h"
#include "gl_structs/texturedvertex.h"
#include "../main.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
static const Uint32 rmask = 0xFF000000;
static const Uint32 gmask = 0x00FF0000;
static const Uint32 bmask = 0x0000FF00;
static const Uint32 amask = 0x000000FF;
#else
static const Uint32 rmask = 0x000000FF;
static const Uint32 gmask = 0x0000FF00;
static const Uint32 bmask = 0x00FF0000;
static const Uint32 amask = 0xFF000000;
#endif

TextureProgram *GLTexture::textureProgram = NULL;
GLuint GLTexture::boundTextureID = 0;

GLTexture::GLTexture() {
    textureID = 0;
    textureWidth = 0;
    textureHeight = 0;
    imageWidth = 0;
    imageHeight = 0;
    VBOID = 0;
    IBOID = 0;
}

GLTexture::~GLTexture() {
    freeTexture();

    freeVBO();
}

void GLTexture::freeTexture() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
    textureWidth = 0;
    textureHeight = 0;
    imageWidth = 0;
    imageHeight = 0;
}

void GLTexture::loadFromFile(std::string path) {
    // Clear any existing data
    freeTexture();

    // Load file into a surface
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        printf("Failed to load image from %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }

    // Save dimensions
    imageWidth = (GLuint) surface->w;
    imageHeight = (GLuint) surface->h;
    textureWidth = powerOfTwo(imageWidth);
    textureHeight = powerOfTwo(imageHeight);

    // Convert to a power of two textureList
    SDL_Surface *convertedSurface = SDL_CreateRGBSurface(0, textureWidth, textureHeight,
                                                         32, rmask, gmask, bmask, amask);
    if (convertedSurface == NULL) {
        printf("Failed to convert surface for image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }

    // Copy the file surface to a converted power of two surface
    SDL_BlitSurface(surface, 0, convertedSurface, 0);

    // Create OpenGL textureList from the surface
    int mode = GL_RGBA;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, textureWidth, textureHeight, 0, mode,
                 GL_UNSIGNED_BYTE, convertedSurface->pixels);

    // Set textureList parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Unbind textureList
    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error loading textureList from pixels: %s\n", gluErrorString(error));
        exitApp(1);
    }

    initVBO();

    // Free unused surface
    SDL_FreeSurface(convertedSurface);
}

void GLTexture::render(GLfloat x, GLfloat y, Rectangle *clip) {
    if (textureID == 0) {
        printf("Can't render a texture that wasn't loaded");
    }

    GLfloat texTop = 0.f;
    GLfloat texBottom = (GLfloat) imageHeight / (GLfloat) textureHeight;
    GLfloat texLeft = 0.f;
    GLfloat texRight = (GLfloat) imageWidth / (GLfloat) textureWidth;

    // Vertex coordinates
    GLfloat quadWidth = imageWidth;
    GLfloat quadHeight = imageHeight;

    // Clipping
    if (clip != NULL) {
        texLeft = clip->x / textureWidth;
        texRight = (clip->x + clip->width) / textureWidth;
        texTop = clip->y / textureHeight;
        texBottom = (clip->y + clip->height) / textureHeight;

        quadWidth = clip->width;
        quadHeight = clip->height;
    }

    // Move to rendering point
    textureProgram->leftMultModelView(glm::translate(glm::vec3(x, y, 0.f)));
    textureProgram->updateModelView();

    // Set vertex data
    TexturedVertex vData[4];

    // Texture coordinates
    vData[0].texCoord.s = texLeft;
    vData[0].texCoord.t = texTop;
    vData[1].texCoord.s = texRight;
    vData[1].texCoord.t = texTop;
    vData[2].texCoord.s = texRight;
    vData[2].texCoord.t = texBottom;
    vData[3].texCoord.s = texLeft;
    vData[3].texCoord.t = texBottom;

    // Vertex positions
    vData[0].position.x = 0.f;
    vData[0].position.y = 0.f;
    vData[1].position.x = quadWidth;
    vData[1].position.y = 0.f;
    vData[2].position.x = quadWidth;
    vData[2].position.y = quadHeight;
    vData[3].position.x = 0.f;
    vData[3].position.y = quadHeight;

    // Bind if the texture is different than the last
    if (textureID != boundTextureID) {
        glBindTexture(GL_TEXTURE_2D, textureID);
        boundTextureID = textureID;
    }

    // Enable vertex and textureList coordinate arrays
    textureProgram->enableDataPointers();

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);

    // Update VBO data
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(TexturedVertex), vData);

    // Set texture coordinate data
    textureProgram->setTexCoordPointer(sizeof(TexturedVertex), (GLvoid *) offsetof(TexturedVertex, texCoord));

    // Set vertex data
    textureProgram->setVertexPointer(sizeof(TexturedVertex), (GLvoid *) offsetof(TexturedVertex, position));

    // Draw quad using vertex data and index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

    // Disable vertex and textureList coordinate arrays
    textureProgram->disableDataPointers();
}

GLuint GLTexture::powerOfTwo(GLuint number) {
    if (number != 0) {
        number--;
        number |= (number >> 1); //Or first 2 bits
        number |= (number >> 2); //Or next 2 bits
        number |= (number >> 4); //Or next 4 bits
        number |= (number >> 8); //Or next 8 bits
        number |= (number >> 16); //Or next 16 bits
        number++;
    }

    return number;
}

void GLTexture::initVBO() {
    if (textureID == 0) {
        printf("Can't init VBO, because the textureList is not loaded");
        return;
    } else if (VBOID != 0) {
        printf("Can't init VBO, because it is already initialized");
        return;
    }

    TexturedVertex vData[4];
    GLuint iData[4];

    //Set rendering indices
    iData[0] = 0;
    iData[1] = 1;
    iData[2] = 2;
    iData[3] = 3;

    //Create VBO
    glGenBuffers(1, &VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(TexturedVertex), vData, GL_DYNAMIC_DRAW);

    //Create IBO
    glGenBuffers(1, &IBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);

    //Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLTexture::freeVBO() {
    if (VBOID != 0) {
        glDeleteBuffers(1, &VBOID);
        glDeleteBuffers(1, &IBOID);
    }
}