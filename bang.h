#pragma once
#ifndef WALLBOARD_H
#define WALLBOARD_H

#include <GL/glut.h>

class Wallboard {
private:
    float posX, posY, posZ; 
    float scaleX, scaleY, scaleZ; 
    float angleX, angleY, angleZ; 
    float boardColorR, boardColorG, boardColorB; 
    float frameColorR, frameColorG, frameColorB; 
    void drawBox();
public:
    Wallboard();


    void setPosition(float x, float y, float z);
    void setScale(float sx, float sy, float sz);
    void setRotation(float ax, float ay, float az);
    void setBoardColor(float r, float g, float b);
    void setFrameColor(float r, float g, float b);

    void draw();
};

#endif