#include "lamp.h"
#include <iostream>

lamp::lamp(glm::vec3 position)
{
    this->position = position;
}

lamp::~lamp()
{
    //dtor
}

void lamp::draw(float delta){

}

void lamp::fillPoleVertices(int slicesX, int slicesY) {
    this->poleLength = slicesX * slicesY;
    poleVertices = new Vertex[this->poleLength];

    int k = 0;
    for (int y = 0; y <= slicesY; y++) {
        for (int x = 0; x <= slicesX; x++) {
            this->poleVertices[k].x = cos( (-1 + 2 (float)x / slicesX) * PI);
            this->poleVertices[k].y = sin( (-1 + 2 (float)x / slicesX) * PI);
            this->poleVertices[k].z = -1 + 2 * (float)y / slicesY;
            this->poleVertices[k].coords.w = 1.0;
            this->poleVertices[k].normal.x = cos( (-1 + 2 * (float)x / slicesX) * PI );
            //this->poleVertices[k].normal.y = cos( )
        }
    }
}
