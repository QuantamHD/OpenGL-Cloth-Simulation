#include "Cloth.h"




Cloth::Cloth(glm::vec3& position, GLfloat width,GLfloat height,int sliceX,int sliceY)
{
    this.sliceX = sliceX;
    this.sliceY = sliceY;
    this.height = height;
    this.width = width;
}

int Cloth::byteSizeOfVertexArray(){
    int floatSize = sizeof(GLfloat);
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

Cloth::~Cloth()
{
    //dtor
}

GLfloat* Cloth::createVertices(glm::vec3 topLeft, int slicesX, int slicesY) {
    GLfloat vertices[Cloth::byteSizeOfVertexArray()]; //TODO ChANGE ME
    float SQUARE_SIZE = 1.0;

    int k = 0;
    for (int x = 0; x < slicesX; x++) {
        for (int y = 0; y  slicesY; y++) {

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

    return vertices;
}

GLuint** createIndices(int slicesX, int slicesY) {
    GLuint indices[slicesX * slicesY];
    int k = 0;
    for (int x = 0; x < slicesX-1; x++;) {
        for (int y = 0; y < slicesY-1; y++) {
            //left triangle
            indices[k] = x*slicesY + y; k++;
            indices[k] = (x+1)*slicesY + y; k++;
            indices[k] = x*slicesY + (y+1); k++;

            //Right triangle
            indices[k] = x*slicesY + (y+1); k++;
            indices[k] = (x+1)*slicesY + (y+1); k++;
            indices[k] = (x+1)*slicesY + y; k++;
        }
    }
    return indices;
}



