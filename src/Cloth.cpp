#include "Cloth.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Mass.h"



Cloth::Cloth(glm::vec3 position,int sliceX,int sliceY)
{
    this->sliceX = sliceX;
    this->sliceY = sliceY;
    this->position = position;
    this->t = 0;
}

Cloth::~Cloth()
{
}

void Cloth::draw(float delta){

    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, this->indicesSize, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

void Cloth::rebind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->positionID);
    glBufferData(GL_ARRAY_BUFFER, this->positionSize * sizeof(GLfloat), positionCords, GL_STATIC_DRAW);
}

void Cloth::calculateNormals(){
    for(int i = 0; i < normalsSize; i++){
        normalsCords[i] = 1.0f;
    }

    for(int i = 0; i < indicesSize; i+= 3){
        int index1 = indices[i];
        int index2 = indices[i+1];
        int index3 = indices[i+2];

        glm::vec3 point1 = glm::vec3(positionCords[index1*4], positionCords[(index1*4)+1], positionCords[(index1*4)+2]);
        glm::vec3 point2 = glm::vec3(positionCords[index2*4], positionCords[(index2*4)+1], positionCords[(index2*4)+2]);
        glm::vec3 point3 = glm::vec3(positionCords[index3*4], positionCords[(index3*4)+1], positionCords[(index3*4)+2]);

        glm::vec3 v1 = point2-point1;
		glm::vec3 v2 = point3-point1;

		glm::vec3 crossProduct = glm::cross(v2,v1);

        normalsCords[index1*3]       += crossProduct.x;
        normalsCords[(index1*3) + 1] += crossProduct.y;
        normalsCords[(index1*3) + 2] += crossProduct.z;

        normalsCords[index2*3]       += crossProduct.x;
        normalsCords[(index2*3) + 1] += crossProduct.y;
        normalsCords[(index2*3) + 2] += crossProduct.z;

        normalsCords[index3*3]       += crossProduct.x;
        normalsCords[(index3*3) + 1] += crossProduct.y;
        normalsCords[(index3*3) + 2] += crossProduct.z;
    }

    for(int i = 0; i < normalsSize; i+= 3){
        glm::vec3 normal = glm::vec3(normalsCords[i], normalsCords[i+1], normalsCords[i+2]);

        normal = glm::normalize(normal);

        normalsCords[i] = normal.x;
        normalsCords[i+1] = normal.y;
        normalsCords[i+2] = normal.z;
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->normalID);
    glBufferData(GL_ARRAY_BUFFER, this->normalsSize * sizeof(GLfloat), normalsCords, GL_STATIC_DRAW);
}

void Cloth::update(float delta) {
    int k = 0;
    for (int i = 0; i < masses.size(); i++) {
        float x = this->masses[i]->position.x;
        float y = this->masses[i]->position.y;
        float z = this->masses[i]->position.z;
        this->masses[i]->addForce(glm::vec3(0, -10.4, 0));
        this->masses[i]->addForce(glm::vec3(sin(x*y*t),cos(z*t), sin(cos(5*x*y*z)))*4.8f);
        this->masses[i]->calculateNewPosition();
        this->positionCords[k++] = this->masses[i]->position.x;
        this->positionCords[k++] = this->masses[i]->position.y;
        this->positionCords[k++] = this->masses[i]->position.z;
        k++; //skip w
        t+= 0.009;
    }

    for (int i = 0; i < 16; i++) {
        for (int n = 0; n < masses.size(); n++) {
            this->masses[n]->constraintSolve();
        }
    }

    calculateNormals();

    rebind();
}

int Cloth::byteSizeOfVertexArray(){
    return 2;
}


void Cloth::createVertices(glm::vec3 topLeft, int slicesX, int slicesY) {
    this->normalsCords = new GLfloat[slicesX * slicesY * 3];
    this->positionCords = new GLfloat[slicesX * slicesY * 4];

    float SQUARE_SIZE = 1.0;

    int k = 0;
    int n = 0;
    int j = 0;
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
    this->indices = new GLuint[this->indicesSize];

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

void Cloth::fillMasses() {
    int k = 0;
    for (int i = 0; i < positionSize / 4; i++) {
        GLfloat x = positionCords[k++];
        GLfloat y = positionCords[k++];
        GLfloat z = positionCords[k++];
        k++; //skip the w
        this->masses.push_back(new Mass(glm::vec3(x, y, z), true));
    }
}

void Cloth::attachSprings(int slicesX, int slicesY) {

    int k = 0;
    for (int x = 0; x < slicesX-1; x++) {
        for (int y = 0; y < slicesY-1; y++) {

            // Left
            Mass* m1 = this->masses[(x*slicesY + y)];
            Mass* m2 = this->masses[(x*slicesY + (y+1))];
            Spring spring0(m1, m2);
            m1->addSpring(spring0);
            m2->addSpring(spring0);

            // Top
            m1 = this->masses[(x*slicesY + y)];
            m2 = this->masses[((x+1)*slicesY + y)];
            Spring spring1(m1, m2);
            m1->addSpring(spring1);
            m2->addSpring(spring1);

            // Diagonal
            m1 = this->masses[(x*slicesY + (y+1))];
            m2 = this->masses[((x+1)*slicesY + y)];
            Spring spring2(m1, m2);
            m1->addSpring(spring2);
            m2->addSpring(spring2);

            // Middle Line
            m1 = this->masses[(x*slicesY + y)];
            m2 = this->masses[((x+1)*slicesY + (y+1))];
            Spring spring3(m1, m2);
            m1->addSpring(spring3);
            m2->addSpring(spring3);

            // Bottom line
            if (y == slicesY-2) {
                m1 = this->masses[(x*slicesY + (y+1))];
                m2 = this->masses[((x+1)*slicesY + (y+1))];
                Spring spring4(m1, m2);
                m1->addSpring(spring4);
                m2->addSpring(spring4);
            }

            if (x == slicesX-2) {
                m1 = this->masses[((x+1)*slicesY + (y))];
                m2 = this->masses[((x+1)*slicesY + (y+1))];
                Spring spring5(m1, m2);
                m1->addSpring(spring5);
                m2->addSpring(spring5);
            }
        }
    }
}

void Cloth::stickTop(int sliceX, int slicesY) {
    this->masses[0]->movable = false;
    this->masses[(sliceX-1)*slicesY]->movable = false;
}

void Cloth::initCloth(){

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &positionID);
    glGenBuffers(1, &normalID);
    glGenBuffers(1, &eboID);

    glBindVertexArray(vaoID);

    Cloth::createVertices(position, sliceX, sliceY);
    Cloth::createIndices(sliceX, sliceY);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(GLuint), indices, GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, positionID);
    glBufferData(GL_ARRAY_BUFFER, positionSize * sizeof(GLfloat), positionCords, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, normalID);
    glBufferData(GL_ARRAY_BUFFER,this->normalsSize * sizeof(GLfloat), normalsCords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    fillMasses();
    attachSprings(sliceX, sliceY);
    stickTop(sliceX, sliceY);
}

