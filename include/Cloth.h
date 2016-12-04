#ifndef CLOTH_H
#define CLOTH_H
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
#include<Entity.h>


static const int VERTEX_ATTRIBUTE_COUNT = 7;
class Cloth
{
    public:
        Cloth(glm::vec3& position,
              GLfloat width,
              GLfloat height,
              int sliceX,
              int sliceY);
        virtual ~Cloth();
        GLuint GetvboID() { return vboID; }
        GLuint GetvaoID() { return vaoID; }
        void draw(float delta);

    protected:

    private:
        GLuint vboID;
        GLuint vaoID;
        GLfloat height;
        GLfloat width;
        int sliceX;
        int sliceY;
        glm::vec3 position;


        void initCloth();
        int byteSizeOfVertexArray();
        GLfloat* createVertices(glm::vec3 position, int slicesX, int slicesY);



};

#endif // CLOTH_H
