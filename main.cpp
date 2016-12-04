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

#include<iostream>
#include "shader.h"

double delta = 0;
long currentTime = 0;

void calculateDeltaTime(){
    long newTime = glutGet(GLUT_ELAPSED_TIME);
    delta = (newTime - currentTime)/1000.0;
    currentTime = newTime;
}

void update(){
    std::cout << "Time per frame in seconds " << delta << std::endl;
}

void animate(int value){
    update();
    glutPostRedisplay();
    glutTimerFunc(8,animate, 0);
}

void setupShaders() {
    GLuint vertexShader = setShader("vertex", "vertexShader.glsl");
    GLuint fragmentShader = setShader("fragment", "fragmentShader.glsl");
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);
    glUseProgram(programId);
}

void init(){
    glEnable(GL_DEPTH_TEST);
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    setupShaders();
}

void resizeViewport(int width, int height){
    glViewport(0,0,width, height);
}

void display(){
    glClearColor(0.5019, 0.8, 0.8,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    calculateDeltaTime();

    glutSwapBuffers();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutInitWindowSize(720,720);
    glutCreateWindow( "Cloth Simulation" );

    glewInit();
    init();

    glutTimerFunc(8, animate, 0);
    glutDisplayFunc(display);
    glutReshapeFunc(resizeViewport);
    glutMainLoop();

    return 0;
}
