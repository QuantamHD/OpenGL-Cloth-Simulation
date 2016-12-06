#include "Rack.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Rack::Rack(glm::vec3 position, int slicesX, int slicesY) {
    this->position = position;
    this->slicesX = slicesX;
    this->slicesY = slicesY;
}

Rack::~Rack(){
}

void Rack::init() {

    GLfloat positionCords[] = {
        position.x,     position.y,     position.z,
        position.x,     position.y - 1, position.z,
        position.x + 1, position.y - 1, position.z,
        position.x + 1, position.y,     position.z,
        position.x + 1, position.y - 1, position.z - 1,
        position.x + 1, position.y,     position.z - 1,
        position.x,     position.y,     position.z - 1,
        position.x,     position.y - 1, position.z - 1
    };

    GLfloat normalsCords[] = {
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
        1, 1, 1
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 3, 2,
        3, 2, 4,
        5, 3, 4,
        6, 5, 7,
        6, 5, 3,
        0, 3, 6,
        0, 1, 7,
        0, 6, 7
    };


    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &positionID);
    glGenBuffers(1, &normalID);
    glGenBuffers(1, &eboID);


    glBindVertexArray(vaoID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, positionID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionCords), positionCords, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normalID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normalsCords), normalsCords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void Rack::draw(float delta) {
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, 9*3, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

