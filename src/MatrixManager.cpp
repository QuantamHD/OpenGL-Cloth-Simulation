#include "MatrixManager.h"

MatrixManager::MatrixManager(GLint modelViewMatrixID)
{
    this->modelViewMatrixID = modelViewMatrixID;
}

MatrixManager::~MatrixManager()
{
    //dtor
}

void MatrixManager::popMatrix(){
    if(this->matrixStack.size() > 1){
        this->matrixStack.pop();
        updateMatrix();
    }
}

void MatrixManager::pushMatrix(glm::mat4 modelViewMatrix){
    this->matrixStack.push(modelViewMatrix);
    updateMatrix();
}

void MatrixManager::updateMatrix(){
    if(this->matrixStack.size() > 0){
        glm::mat4 modelViewMatrix = this->matrixStack.top();
        glUniformMatrix4fv(this->modelViewMatrixID,1, GL_FALSE, value_ptr(modelViewMatrix));
    }
}
