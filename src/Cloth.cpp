#include "Cloth.h"
#include <iostream>



Cloth::Cloth(glm::vec3 position,int sliceX,int sliceY)
{
    this->sliceX = sliceX;
    this->sliceY = sliceY;
    this->position = position;
}

Cloth::~Cloth()
{
    delete this->positionCords;
    delete this->normalsCords;
    delete this->indices;
}

void Cloth::draw(float delta){

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    //glDrawElements(GL_TRIANGLES, this->indicesSize, GL_UNSIGNED_INT, (void*)0);
    glDrawArrays(GL_POLYGON, 0, this->normalsSize);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

int Cloth::byteSizeOfVertexArray(){
    int floatSize = sizeof(GLfloat);
    int numberOfVertices = this->sliceX*this->sliceY;
    int sizeInBytesOfCloth = floatSize*numberOfVertices*VERTEX_ATTRIBUTE_COUNT;
}

void Cloth::createVertices(glm::vec3 topLeft, int slicesX, int slicesY) {
    this->normalsCords = new GLfloat[slicesX * slicesY * 3];
    this->positionCords = new GLfloat[slicesX * slicesY * 4];
    float SQUARE_SIZE = 1.0;

    int k = 0;
    int n = 0;
    for (int x = 0; x < slicesX; x++) {
        for (int y = 0; y < slicesY; y++) {

            // position
            positionCords[k++] = topLeft.x + x*SQUARE_SIZE; //x
            positionCords[k++] = topLeft.y - y*SQUARE_SIZE; //y
            positionCords[k++] = topLeft.z;//z
            positionCords[k++] = 1.0; //w

            // normals
            normalsCords[n++] = 0.0;//x
            normalsCords[n++] = 0.0;//y
            normalsCords[n++] = 1.0;//z
        }
    }

    this->positionSize = k;
    this->normalsSize = n;
}

void Cloth::createIndices(int slicesX, int slicesY) {
    this->indicesSize = ((sliceX-1)*(sliceY-1))*6;
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
}

void Cloth::initCloth(){

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &positionID);
    glGenBuffers(1, &normalID);
    glGenBuffers(1, &eboID);

    glBindVertexArray(vaoID);

    Cloth::createVertices(position, sliceX, sliceY);
    for(int i = 0; i < positionSize; i++){
        std::cout << "Vertex" << this->positionCords[i] << std::endl;
    }
    Cloth::createIndices(sliceX, sliceY);

    glBindBuffer(GL_ARRAY_BUFFER, positionID);
    glBufferData(GL_ARRAY_BUFFER,this->positionSize * sizeof(GLfloat), this->positionCords, GL_STREAM_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normalID);
    glBufferData(GL_ARRAY_BUFFER,this->normalsSize * sizeof(GLfloat), this->normalsCords, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

