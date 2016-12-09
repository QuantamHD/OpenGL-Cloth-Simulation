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
#include <Hanger.h>


Cloth cloth(glm::vec3(-15,7.0,0), 15,30);
Cloth cloth1(glm::vec3(0,7.0,0), 15,30);
Hanger hanger;

double delta = 0;
float angle = 0;

int mouseDelta = -1;
int mousePreviousPosition = -1;

bool fillPolys = true;

long currentTime = 0;

glm::vec3 lightPos = glm::vec3(7.0, 10.0, 1.0);
glm::vec3 cameraPos = glm::vec3(0, 5, 25);
GLuint shaderProgram;
GLint objectcolore;


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

    objectcolore = glGetUniformLocation(shaderProgram, "objectColor");
    glUniform3f(objectcolore, 231.0 / 255.0, 76.0 / 255.0, 60.0 / 255.0);
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
    hanger.create();
}

void passiveMouseMovement(int x, int y){
    mouseDelta =  x - mousePreviousPosition ;
    mousePreviousPosition = x;
}

void mouseMovement(int x, int y){
    float angleDelta = mouseDelta/100.0;
    angle += angleDelta;
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

    if(keycode == ' '){
        if(fillPolys){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            fillPolys = !fillPolys;
        }else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            fillPolys = !fillPolys;
        }
    }
}

void display(){
    glClearColor(52 /255.0, 152 / 255.0, 219/ 255.0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    calculateDeltaTime();

    glm::mat4x4 modelView = glm::lookAt(glm::vec3(sin(angle)*25, 5, cos(angle)*25), glm::vec3(0,0,0), glm::vec3(0,1,0));
    GLint modelLocation = glGetUniformLocation(shaderProgram, "modelViewMatrix");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(modelView));

    glUseProgram(shaderProgram);
    cloth.draw(delta);
    cloth1.draw(delta);

    hanger.draw(modelView, modelLocation, objectcolore);
    glutSwapBuffers();
}

void printInstructions(){
    std::cout << "Description: This project uses the latest, and greatest in Verlet Integration to provide you with the premier Cloth Simulator 2016." << std::endl << std::endl;
    std::cout << "Thanks To The following Sources" << std::endl << std::endl;
    std::cout << "https://learnopengl.com/" << " For tutorials on OpenGL" << std::endl;
    std::cout << "https://graphics.stanford.edu/~mdfisher/cloth.html" << " For Dr. Fisher's explanation of Physics Simulations in OpenGL." << std::endl << std::endl;

    std::cout << "Instruction" << std::endl << std::endl;
    std::cout << "Press C - to open curtains" << std::endl;
    std::cout << "Press D - to close curtains" << std::endl;
    std::cout << "Click and drag to move camera" << std::endl;
    std::cout << "Press space bar to see polygons." << std::endl;
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    printInstructions();

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
