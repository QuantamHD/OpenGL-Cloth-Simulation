#ifndef HANGER_H
#define HANGER_H

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

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <Rack.h>

class Hanger
{
    public:
        Hanger();
        virtual ~Hanger();
        void create();
        void draw(glm::mat4x4 matrix, GLint matrixLocation, GLint color);

    protected:

    private:
        Rack hangerPole;
        Rack hangerEndLeft;
        Rack hangerEndRight;

};

#endif // HANGER_H
