#include "Spring.h"

Spring::Spring(Mass* fixedMass, Mass* dynamicMass, float restLength)
{
    this->fixedMass = fixedMass;
    this->dynamicMass = dynamicMass;
}

Spring::~Spring()
{
    //dtor
}

void Spring::satisfyConstraint(){
    glm::vec3 vecToPointMass = dynamicMass->position - fixedMass->position;
    float distance = glm::length(vecToPointMass);
    glm::vec3 correctionVector = vecToPointMass *(1 - (restLength/distance));
    glm::vec3 halfCorrection = correctionVector * 0.5f;
    fixedMass->addPosition(halfCorrection);
    fixedMass->addPosition(-halfCorrection);
}
