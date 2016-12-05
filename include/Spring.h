#ifndef SPRING_H
#define SPRING_H
#include<Mass.h>
#include<glm/glm.hpp>

class Mass;

const float SPRING_CONST = 20;
const float REST_LENGTH = 0.5;

class Spring
{
    public:
        Spring(Mass* fixedMass, Mass* dynamicMass);
        virtual ~Spring();
        void satisfyConstraint();

    protected:

    private:
        Mass* fixedMass;
        Mass* dynamicMass;
        float restLength;
};

#endif // SPRING_H
