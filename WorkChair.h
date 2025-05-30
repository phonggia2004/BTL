#ifndef WORK_CHAIR_H
#define WORK_CHAIR_H

#include <GL/glut.h>

class WorkChair {
private:
    float posX, posY, posZ; 
    float scaleX, scaleY, scaleZ; 
    float angleX, angleY, angleZ; 
    float seatColorR, seatColorG, seatColorB; 
    float frameColorR, frameColorG, frameColorB;
    void drawBox();                   
    void drawLeg(float x, float z);

public:
    WorkChair();


    void setPosition(float x, float y, float z);
    void setScale(float sx, float sy, float sz);
    void setRotation(float ax, float ay, float az);
    void setSeatColor(float r, float g, float b);
    void setFrameColor(float r, float g, float b);

 
    void draw();
};

#endif