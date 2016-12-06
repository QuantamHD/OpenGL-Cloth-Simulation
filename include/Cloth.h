/**
This class header file deals with both the creation, simulation,
and drawing of the Cloth. It requires quite a bit of things to work,
but it does in fact work.
*/

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
#include<Mass.h>


static const int VERTEX_ATTRIBUTE_COUNT = 7;
class Cloth
{
    public:
        Cloth(glm::vec3 position, int sliceX,int sliceY);
        virtual ~Cloth();
        /**
        This will return the VAOID created in init.
        */
        GLuint GetvaoID() { return vaoID; }
        /**
        This will draw the cloth, but it will not affect the physics
        simulation. That requires an explicit call to update
        */
        void draw(float delta);
        void initCloth();
        void printVertices();
        /**
        This will update the vertex positions of the cloth with a standard
        time offset set to 9ms. The physics simulation speed is dependant
        on the speed of the computer. This is not ideal, but it should work
        well enough for most applications.
        */
        void update(float delta);


        float windY;
        float windX;
        float windZ;
        Mass* leftPin;
        Mass* rightPin;
    protected:

    private:
        int sliceX;
        int sliceY;
        int indicesSize;
        int positionSize;
        int normalsSize;

        float t;
        float random;

        GLuint positionID;
        GLuint normalID;
        GLuint eboID;
        GLuint vaoID;

        GLuint* indices;

        GLfloat* positionCords;
        GLfloat* normalsCords;

        glm::vec3 position;

        /**
        Each cloth object is made up of a number of masses.
        */
        std::vector<Mass*> masses;


        /**
        Our cloth changes shape over time so we need to recalcuate the face
        normals using an algorithm based on a normalized contribution algorithm.
        */
        void calculateNormals();

        /**
        This function will rebind the updated verticies on each update call.
        */
        void rebind();

        void createVertices(glm::vec3 position, int slicesX, int slicesY);
        void createIndices(int slicesX, int slicesY);

        /**
        A bit poorly named this function will create, and add the masses to to the
        cloth.
        */
        void fillMasses();
        /**
        This function will attach the springs to the point masses created in fillMasses.
        */
        void attachSprings(int sliceX, int sliceY);
        /**
        Pins certain verticies to get the hanging cloth look.
        */
        void stickTop(int sliceX, int sliceY);
        void normalizeNormals();

};

#endif // CLOTH_H
