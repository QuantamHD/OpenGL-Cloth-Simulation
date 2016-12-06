#ifndef RACK_H
#define RACK_H

#define PI 3.14159265

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
    Rack(glm::vec3 position, int width, int height);
    virtual ~Rack();

    void init();
    void draw(float delta);

private:
    glm::vec3 position;
    int slicesX;
    int slicesY;

    GLuint positionID;
    GLuint normalID;
    GLuint eboID;
    GLuint vaoID;

    int positionSize;


};

#endif // RACK_H
