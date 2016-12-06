#include "Hanger.h"

/**
This class exists to help in creating the Hanger for the curtains.
*/
Hanger::Hanger()
{
    this->hangerPole = Rack();
    this->hangerEndRight = Rack();
    this->hangerEndLeft = Rack();
}

Hanger::~Hanger()
{
    //dtor
}

void Hanger::create(){
    hangerPole.init();
    hangerEndLeft.init();
    hangerEndRight.init();
}

void Hanger::draw(glm::mat4x4 matrix, GLint matrixLocation, GLint color){
    glUniform3f(color, 44.0 / 255.0, 62.0 / 255.0, 80.0 / 255.0);
    glm::mat4x4 translate = glm::translate(matrix, glm::vec3(0,7.3,0));
    glm::mat4x4 scale = glm::scale(translate, glm::vec3(17,0.4,0.4));
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, value_ptr(scale));
    hangerPole.draw();

    translate = glm::translate(matrix, glm::vec3(-17,7.3,0));
    scale = glm::scale(translate, glm::vec3(0.7,0.7,0.7));
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, value_ptr(scale));
    glUniform3f(color, 127.0 / 255.0, 140.0 / 255.0, 141.0 / 255.0);
    hangerEndLeft.draw();

    translate = glm::translate(matrix, glm::vec3(17,7.3,0));
    scale = glm::scale(translate, glm::vec3(0.7,0.7,0.7));
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, value_ptr(scale));
    glUniform3f(color, 127.0 / 255.0, 140.0 / 255.0, 141.0 / 255.0);
    hangerEndRight.draw();



    glUniform3f(color, 231.0 / 255.0, 76.0 / 255.0, 60.0 / 255.0);
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, value_ptr(matrix));
}
