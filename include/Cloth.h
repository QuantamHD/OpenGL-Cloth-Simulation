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
#include<vector>


static const int VERTEX_ATTRIBUTE_COUNT = 7;
class Cloth
{
    public:
        Cloth(glm::vec3 position,
              int sliceX,
              int sliceY);
        virtual ~Cloth();
        GLuint GetvboID() { return vboID; }
        GLuint GetvaoID() { return vaoID; }
        void draw(float delta);
        void initCloth();
    protected:

    private:
        GLuint vboID;
        GLuint vaoID;
        GLuint eboID;
        int sliceX;
        int sliceY;
        glm::vec3 position;
        std::vector<GLuint> *indices;
        GLfloat* vertices;

        int byteSizeOfVertexArray();
        GLfloat* createVertices(glm::vec3 position, int slicesX, int slicesY);
        std::vector<GLuint>* createIndices(int slicesX, int slicesY);

};

#endif // CLOTH_H
