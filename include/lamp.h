#ifndef LAMP_H
#define LAMP_H
#define PI 3.14159265

#include "Vertex.h"


class lamp
{
    public:
        lamp();
        virtual ~lamp();
        void draw(float delta);

    protected:

    private:
        int poleLength;
        Vertex* poleVertices;
        GLuint* poleIndices;

        void fillPoleVertices(int slicesX, int slicesY);
};

#endif // LAMP_H
