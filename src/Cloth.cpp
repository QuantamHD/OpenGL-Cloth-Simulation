#include "Cloth.h"
#include <iostream>



Cloth::Cloth(glm::vec3 position,int sliceX,int sliceY)
{
    this->sliceX = sliceX;
    this->sliceY = sliceY;
    this->position = position;
    this->indices = new std::vector<GLuint>;
}

Cloth::~Cloth()
{
    delete this->vertices;
    delete this->indices;
}

void Cloth::draw(float delta){

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int Cloth::byteSizeOfVertexArray(){
    int floatSize = sizeof(GLfloat);
    int numberOfVertices = this->sliceX*this->sliceY;
    int sizeInBytesOfCloth = floatSize*numberOfVertices*VERTEX_ATTRIBUTE_COUNT;
}

GLfloat* Cloth::createVertices(glm::vec3 topLeft, int slicesX, int slicesY) {
    GLfloat* vertices = new GLfloat[Cloth::byteSizeOfVertexArray()];
    float SQUARE_SIZE = 1.0;

    int k = 0;
    for (int x = 0; x < slicesX; x++) {
        for (int y = 0; y < slicesY; y++) {

            // position
            vertices[k] = topLeft.x + x*SQUARE_SIZE; k++; //x
            vertices[k] = topLeft.y - y*SQUARE_SIZE; k++; //y
            vertices[k] = topLeft.z; //z
            vertices[k] = 1.0; k++; //w

            // normals
            vertices[k] = 0.0; k++; //x
            vertices[k] = 0.0; k++; //y
            vertices[k] = 1.0; k++; //z
        }
    }

    return vertices;
}

std::vector<GLuint>* Cloth::createIndices(int slicesX, int slicesY) {
    for (int x = 0; x < slicesX-1; x++) {
        for (int y = 0; y < slicesY-1; y++) {
            //left triangle
            indices->push_back(x*slicesY + y);
            indices->push_back((x+1)*slicesY + y);
            indices->push_back(x*slicesY + (y+1));

            //Right triangle
            indices->push_back(x*slicesY + (y+1));
            indices->push_back((x+1)*slicesY + (y+1));
            indices->push_back((x+1)*slicesY + y);
        }
    }
    return indices;
}

void Cloth::initCloth(){
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &eboID);

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    int byteSizeArray = byteSizeOfVertexArray();
    this->vertices = Cloth::createVertices(this->position, this->sliceX, this->sliceY);
    this->indices = Cloth::createIndices(this->sliceX, this->sliceY);
    int indicesByteSize = sizeof(GLuint) * indices->size();
    glBufferData(GL_ARRAY_BUFFER, byteSizeArray, this->vertices, GL_STREAM_DRAW);
    std::cout << glGetError() << std::endl;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, &(indices[0]), GL_STATIC_DRAW);
    std::cout << glGetError() << std::endl;


    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_ATTRIBUTE_COUNT * sizeof(GLfloat), (GLvoid*)4);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

