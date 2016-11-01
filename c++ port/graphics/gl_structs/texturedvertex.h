#ifndef CORE_VERTEXDATA_H
#define CORE_VERTEXDATA_H

#include "vertexpos.h"
#include "texcoord.h"

struct TexturedVertex {
    VertexPos position;
    TexCoord texCoord;
};

#endif //CORE_VERTEXDATA_H
