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
#include<Rack.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<vertex.h>



Cloth cloth(glm::vec3(-15,7.0,0), 15,30);
Cloth cloth1(glm::vec3(0,7.0,0), 15,30);
Rack rack(glm::vec3(-7, 0.0, 2.0), 5, 5);

double delta = 0;
int mouseDelta = -1;
int mousePreviousPosition = -1;
long currentTime = 0;
float angle = 0;
glm::vec3 lightPos = glm::vec3(7.0, 10.0, 1.0);
glm::vec3 cameraPos = glm::vec3(0, 5, 20);
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
    cloth1.update(delta);
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

    GLint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
}



void setupCamera(){
        // Frustum call
    glm::mat4 projMat = glm::frustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
    GLint projectionLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projMat));

    // model view call
    glm::mat4 modelView = glm::lookAt(cameraPos, glm::vec3(0,0,0), glm::vec3(0,1,0));
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
    cloth1.initCloth();
    rack.init();
}

void passiveMouseMovement(int x, int y){
    mouseDelta =  x - mousePreviousPosition ;
    //std::cout << mouseDelta << std::endl;
    mousePreviousPosition = x;

}

void mouseMovement(int x, int y){
    float angleDelta = mouseDelta/100.0;
    angle += angleDelta;
    glm::mat4 modelView = glm::lookAt(glm::vec3(sin(angle)*20, 5, cos(angle)*20), glm::vec3(0,0,0), glm::vec3(0,1,0));
    GLint modelLocation = glGetUniformLocation(shaderProgram, "modelViewMatrix");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(modelView));
    glutPostRedisplay();
    mouseDelta =  x - mousePreviousPosition ;
    mousePreviousPosition = x;
}

void resizeViewport(int width, int height){
    glViewport(0,0,width, height);
}

void keyboardf(unsigned char keycode, int x, int y){
    //std::cout << keycode << std::endl;
    if(keycode == 'c'){
        float length = glm::distance(cloth.rightPin->position - glm::vec3(1, 0, 0), cloth.leftPin->position);
        if(length > 0.5){
            cloth.rightPin->position -= glm::vec3(1, 0, 0);
            cloth1.leftPin->position += glm::vec3(1, 0, 0);
        }
    }

    if(keycode == 'd'){
        float length = glm::distance(cloth.rightPin->position + glm::vec3(1, 0, 0), cloth.leftPin->position);
        if(length < 15){
            cloth.rightPin->position += glm::vec3(1, 0, 0);
            cloth1.leftPin->position -= glm::vec3(1, 0, 0);
        }
    }
}

void display(){
    glClearColor(52 /255.0, 152 / 255.0, 219/ 255.0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    calculateDeltaTime();

    //drawTriangle();
    glUseProgram(shaderProgram);
    cloth.draw(delta);
    cloth1.draw(delta);
    rack.draw(delta);
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
    glutMotionFunc(mouseMovement);
    glutPassiveMotionFunc(passiveMouseMovement);
    glutReshapeFunc(resizeViewport);
    glutKeyboardFunc(keyboardf);
    glutMainLoop();

    return 0;
}
