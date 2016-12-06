#include "Rack.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Rack::Rack(glm::vec3 position, int slicesX, int slicesY, float radius) {
    this->position = position;
    this->slicesX = slicesX;
    this->slicesY = slicesY;
    this->radius = r;
}

Rack::~Rack(){
}

Rack::init() {

}

void Rack::createVertices(glm::vec3 topLeft) {

    int k = 0;
    this->positionCords = {
        topLeft.x,     topLeft.y,     topLeft.z,
        topLeft.x,     topLeft.y - 1, topLeft.z,
        topLeft.x + 1, topLeft.y - 1, topLeft.z,
        topLeft.x + 1, topLeft.y,     topLeft.z,
        topLeft.x + 1, topLeft.y - 1, topLeft.z - 1,
        topLeft.x + 1, topLeft.y,     topLeft.z - 1,
        topLeft.x,     topLeft.y,     topLeft.z - 1,
        topLeft.x,     topLeft.y - 1, topLeft.z - 1
    }

    this->normals = {

    }

    this->positionSize = k;
    this->normalsSize = n;
}

void Rack::createIndices() {
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
}
