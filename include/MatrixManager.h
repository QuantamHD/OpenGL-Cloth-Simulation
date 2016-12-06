#ifndef MATRIXMANAGER_H
#define MATRIXMANAGER_H

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

#include<stack>
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class MatrixManager
{
    public:
        MatrixManager(GLint modelViewMatrixID);
        virtual ~MatrixManager();

        void pushMatrix(glm::mat4 matrix);
        void popMatrix();
    protected:

    private:
        std::stack<glm::mat4> matrixStack;
        GLint modelViewMatrixID;
        void updateMatrix();


};

#endif // MATRIXMANAGER_H
