#ifndef MASS_H
#define MASS_H
#include<vector>
#include<Spring.h>
#include<glm/glm.hpp>

class Spring;

const float MASS = 1;
const float TIME_STEP = 0.009;
class Mass
{
    public:
        Mass(glm::vec3 position, bool movable);
        virtual ~Mass();
        void addSpring(Spring spring);
        void addForce(glm::vec3 force);
        void addPosition(glm::vec3 positionDelta);
        void calculateNewPosition();
        void constraintSolve();
    protected:

    private:
        std::vector<Spring> springs;
        glm::vec3 position;
        glm::vec3 previousPosition;
        glm::vec3 acceleration;
        bool movable;



};

#endif // MASS_H
