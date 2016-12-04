#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#endif
#include "Cloth.h"
#include <glm/glm.hpp>



Cloth::Cloth(glm::vec3 position, GL_FLOAT width, GL_FLOAT height, int sliceX, int sliceY)
{
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, size(GL_FLOAT)*7*sliceX*sliceY, NULL, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Cloth::~Cloth()
{
    //dtor
}

GL_FLOAT* Cloth::createVertices(glm::vec3 topLeft, int slicesX, int slicesY) {
    GL_FLOAT vertices[100]; //TODO ChANGE ME
    float SQUARE_SIZE = 1.0;

    int k = 0;
    for (int x = 0; x <= slicesX; x++) {
        for (int y = 0; y <= slicesY; y++) {

            // position
            vertices[k] = topLeft.x + x*SQUARE_SIZE; k++; //x
            vertices[k] = topLeft.y - y*SQUARE_SIZE; k++; //y
            vertices[k] = topLeft.z //z
            vertices[k] = 1.0; k++; //w

            // normals
            vertices[k] = 0.0; k++; //x
            vertices[k] = 0.0; k++; //y
            vertices[k] = 1.0; k++; //z
        }
    }

    return GL_FLOAT;
}


