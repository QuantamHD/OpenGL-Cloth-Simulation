#ifndef CLOTHSIMULATION_H
#define CLOTHSIMULATION_H
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#endif
#include<glm/glm.hpp>

const glm::vec3 GRAVITY_VECTOR(0,-9.81,0);
const float MASS = 1;//kg
const float springConstK = 100;

class ClothSimulation
{
    public:
        ClothSimulation();
        virtual ~ClothSimulation();
        void init();
        void update();

    protected:

    private:
};

#endif // CLOTHSIMULATION_H
