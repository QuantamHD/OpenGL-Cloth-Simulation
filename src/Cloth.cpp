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
    this.sliceX = sliceX;
    this.sliceY = sliceY;
    this.height = height;
    this.width = width;
}

int Cloth::byteSizeOfVertexArray(){
    int floatSize = sizeof(GL_FLOAT);
    int numberOfVertices = this.sliceX*this.sliceY;
    int attributeCountPerVertex = 7;
    int sizeInBytesOfCloth = floatSize*numberOfVertices*attributeCountPerVertex;
}

Cloth::~Cloth()
{
    //dtor
}

void Cloth::initCloth(){
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);

    int byteSizeArray = byteSizeOfVertexArray();

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, byteSizeArray, NULL, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributeCountPerVertex * sizeof(GLfloat), (GLvoid*)4);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


