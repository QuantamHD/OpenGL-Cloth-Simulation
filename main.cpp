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
#include<cmath>
#include<Cloth.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<vertex.h>


Cloth cloth(glm::vec3(-5,5.0,0), 15,20);

double delta = 0;
long currentTime = 0;
GLuint VBO, VAO, Vpostion, Vnormal;
GLuint shaderProgram;

void calculateDeltaTime(){
    long newTime = glutGet(GLUT_ELAPSED_TIME);
    delta = (newTime - currentTime)/1000.0;
    currentTime = newTime;
}

void update(){
    //std::cout << "Time per frame in seconds " << delta << std::endl;
    cloth.update(delta);
}

void animate(int value){
    update();
    glutPostRedisplay();
    glutTimerFunc(8,animate, 0);
}

GLuint setupShaders() {
    GLuint vertexShader = setShader("vertex", "vertexShader.glsl");
    GLuint fragmentShader = setShader("fragment", "fragmentShader.glsl");
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);
    glUseProgram(programId);
    shaderProgram = programId;
}



void setupCamera(){
        // Frustum call
    glm::mat4 projMat = glm::frustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
    GLint projectionLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projMat));

    // model view call
    glm::mat4 modelView = glm::lookAt(glm::vec3(0, 5, 10), glm::vec3(0,0,0), glm::vec3(0,1,0));
    GLint modelLocation = glGetUniformLocation(shaderProgram, "modelViewMatrix");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(modelView));
}
void init(){
    glEnable(GL_DEPTH_TEST);
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    GLuint programId = setupShaders();
    glCullFace(GL_FRONT_AND_BACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    setupCamera();
    cloth.initCloth();
}


void resizeViewport(int width, int height){
    glViewport(0,0,width, height);
}

void display(){
    glClearColor(0.5019, 0.8, 0.8,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    calculateDeltaTime();

    //drawTriangle();
    glUseProgram(shaderProgram);
    cloth.draw(delta);

    glutSwapBuffers();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutInitWindowSize(720,720);
    glutCreateWindow( "Cloth Simulation" );

    glewExperimental = GL_TRUE;
    glewInit();
    init();

    glutTimerFunc(8, animate, 0);
    glutDisplayFunc(display);
    glutReshapeFunc(resizeViewport);
    glutMainLoop();

    return 0;
}
