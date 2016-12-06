#include "Mass.h"
#include<iostream>

Mass::Mass(glm::vec3 position, bool movable)
{
    this->position = position;
    this->previousPosition = position;
    this->movable = movable;
}

Mass::~Mass()
{
}

void Mass::addPosition(glm::vec3 positionDelta){
    if(this->movable){
        this->position += positionDelta;
    }
}

void Mass::addSpring(Spring spring){
    this->springs.push_back(spring);
}

void Mass::addForce(glm::vec3 force){
    this->acceleration += force/(MASS);
}

void Mass::calculateNewPosition(){
    if(this->movable){
        glm::vec3 temporary = this->position;
        this->position = this->position + (this->position- this->previousPosition)*(0.9f) + (this->acceleration * TIME_STEP);
        this->previousPosition = temporary;
        this->acceleration = glm::vec3(0,0,0);//The acceleration is added on time step and is thus cleared after.
    }
}
/**
will calculate the constracts for this mass, and all the others
it is connected to.
*/
void Mass::constraintSolve(){
    for(int i = 0; i < this->springs.size(); i++){
        springs[i].satisfyConstraint();
    }
}
