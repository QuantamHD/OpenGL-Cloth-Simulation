#include "Cloth.h"
#include <iostream>



Cloth::Cloth(glm::vec3 position,int sliceX,int sliceY)
{
    this->sliceX = sliceX;
    this->sliceY = sliceY;
    this->position = position;
    this->indicesSize = ((sliceX-1)*(sliceY-1))*6;
}

Cloth::~Cloth()
{
    delete this->vertices;
    delete this->indices;
}

void Cloth::draw(float delta){

    glBindVertexArray(this->GetvaoID());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glDrawElements(GL_TRIANGLES, this->indicesSize, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Cloth::printVertices() {
    for (int i = 0; i < 7; i++) {
        std::cout << this->vertices[i] << "\n";
    }
}

int Cloth::byteSizeOfVertexArray(){
    int floatSize = sizeof(GLfloat);
    int numberOfVertices = this->sliceX*this->sliceY;
    int sizeInBytesOfCloth = floatSize*numberOfVertices*VERTEX_ATTRIBUTE_COUNT;
}

GLfloat* Cloth::createVertices(glm::vec3 topLeft, int slicesX, int slicesY) {
    GLfloat* vertices = new GLfloat[(slicesX * slicesY)*7];
    float SQUARE_SIZE = 1.0;

    int k = 0;
    for (int x = 0; x < slicesX; x++) {
        for (int y = 0; y < slicesY; y++) {

            // position
            vertices[k] = topLeft.x + x*SQUARE_SIZE; k++; //x
            vertices[k] = topLeft.y - y*SQUARE_SIZE; k++; //y
            vertices[k] = topLeft.z; k++; //z
            vertices[k] = 1.0; k++; //w

            // normals
            vertices[k] = 0.0; k++; //x
            vertices[k] = 0.0; k++; //y
            vertices[k] = 1.0; k++; //z
        }
    }

    return vertices;
}

GLfloat* Cloth::createIndices(int slicesX, int slicesY) {
    this->indices = new GLfloat[this->indicesSize];

    int k = 0;
    for (int x = 0; x < slicesX-1; x++) {
        for (int y = 0; y < slicesY-1; y++) {
            //left triangle
            this->indices[k] = (x*slicesY + y); k++;
            this->indices[k] = ((x+1)*slicesY + y); k++;
            this->indices[k] = (x*slicesY + (y+1));  k++;

            //Right triangle
            this->indices[k] = (x*slicesY + (y+1));  k++;
            this->indices[k] = ((x+1)*slicesY + (y+1)); k++;
            this->indices[k] = ((x+1)*slicesY + y);  k++;
        }
    }

    return this->indices;
}

void Cloth::initCloth(){

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &positionID);
    glGenBuffers(1, &normalID);
    glGenBuffers(1, &eboID);

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, positionID);
    glBufferData(GL_ARRAY_BUFFER,positionSize, positionCoords, GL_STREAM_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normalID);
    glBufferData(GL_ARRAY_BUFFER,normalSize, normalCoords, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));
    glEnableVertexAttribArray(1);






    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

