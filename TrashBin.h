#ifndef TRASHBIN_H
#define TRASHBIN_H

#include <GL/glut.h>

class TrashBin {
private:
    float posX, posY, posZ; 
    float scaleX, scaleY, scaleZ; 
    float angleX, angleY, angleZ; 
    float bodyColorR, bodyColorG, bodyColorB; 
    float lidColorR, lidColorG, lidColorB; 

public:
    TrashBin();


    void setPosition(float x, float y, float z);
    void setScale(float sx, float sy, float sz);
    void setRotation(float ax, float ay, float az);
    void setBodyColor(float r, float g, float b);
    void setLidColor(float r, float g, float b);


    void draw();
};

#endif