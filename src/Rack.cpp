#include "Rack.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <stack>
/**
This represents a very simple cube object.
*/
Rack::Rack() {
}

Rack::~Rack(){
}

void Rack::init() {

    GLfloat positionCords[] = {
        -1.0, -1.0,  1.0, 1,
         1.0, -1.0,  1.0, 1,
         1.0,  1.0,  1.0, 1,
        -1.0,  1.0,  1.0, 1,
        -1.0, -1.0, -1.0, 1,
         1.0, -1.0, -1.0, 1,
         1.0,  1.0, -1.0, 1,
        -1.0,  1.0, -1.0, 1
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
        // front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
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

void Rack::draw() {
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

