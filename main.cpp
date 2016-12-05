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


GLfloat position[] = {
    -0.5f, -0.5f, 0.0f, 1,
     0.5f, -0.5f, 0.0f, 1,
     0.0f,  0.5f, 0.0f, 1
};

GLfloat normals[] = {
    0,0,1,
    0,0,1,
    0,0,1
};

Cloth cloth(glm::vec3(0,0,0), 3,3);

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

void drawTriangle() {
    //glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //glBindVertexArray(0);
    cloth.draw(delta);
}

void genVAOandVBO() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &Vpostion);
    glGenBuffers(1, &Vnormal);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, Vpostion);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, Vnormal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void setupCamera(){
        // Frustum call
    glm::mat4 projMat = glm::frustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
    GLint projectionLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projMat));

    // model view call
    glm::mat4 modelView = glm::lookAt(glm::vec3(0, 5, 3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    GLint modelLocation = glGetUniformLocation(shaderProgram, "modelViewMatrix");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(modelView));

}
void init(){
    glEnable(GL_DEPTH_TEST);
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    GLuint programId = setupShaders();
    genVAOandVBO();
    cloth.initCloth();
    setupCamera();
}


void resizeViewport(int width, int height){
    glViewport(0,0,width, height);
}

void display(){
    glClearColor(0.5019, 0.8, 0.8,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    calculateDeltaTime();

    drawTriangle();
    //cloth.draw(delta);

    glutSwapBuffers();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitContextVersion( 4, 0 );
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
