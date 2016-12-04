#ifndef CLOTH_H
#define CLOTH_H
#include<glm/glm.hpp>

class Cloth
{
    public:
        Cloth(glm::vec3 position, GL_FLOAT width, GL_FLOAT height);
        virtual ~Cloth();
        GLuint GetvboID() { return vboID; }
        GLuint GetvaoID() { return vaoID; }
    protected:

    private:
        GLuint vboID;
        GLuint vaoID;
        GL_FLOAT height;
        GL_FLOAT width;
        GL_FLOAT* createVertices(glm::vec3 position, int slicesX, int slicesY);



};

#endif // CLOTH_H
