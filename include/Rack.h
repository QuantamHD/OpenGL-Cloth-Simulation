#ifndef RACK_H
#define RACK_H

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
#include<vector>

class Rack
{

public:
    Rack();
    virtual ~Rack();

    void init();
    void draw();

private:

    GLuint positionID;
    GLuint normalID;
    GLuint eboID;
    GLuint vaoID;

    int positionSize;


};

#endif // RACK_H
