#ifndef PRINTER_H
#define PRINTER_H

#include <GL/glut.h>

class Printer {
private:
    float posX, posY, posZ; 
    float scaleX, scaleY, scaleZ;
    float angleX, angleY, angleZ; 
    float bodyColorR, bodyColorG, bodyColorB; 
    float topColorR, topColorG, topColorB; 
    float trayColorR, trayColorG, trayColorB;
    float outputColorR, outputColorG, outputColorB;
    float buttonColorR, buttonColorG, buttonColorB; 

public:
    Printer();


    void setPosition(float x, float y, float z);
    void setScale(float sx, float sy, float sz);
    void setRotation(float ax, float ay, float az);
    void setBodyColor(float r, float g, float b);
    void setTopColor(float r, float g, float b);
    void setTrayColor(float r, float g, float b);
    void setOutputColor(float r, float g, float b);
    void setButtonColor(float r, float g, float b);


    void draw();
};

#endif