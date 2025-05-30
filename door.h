#ifndef DOOR_H
#define DOOR_H


class Door {
private:
    float posX, posY, posZ; 
    float scaleX, scaleY, scaleZ; 
    float angleX, angleY, angleZ;
    float colorR, colorG, colorB; 
    float handleColorR, handleColorG, handleColorB; 
    bool isOpen;

public:
    Door();

  
    void setPosition(float x, float y, float z);
    void setScale(float sx, float sy, float sz);
    void setRotation(float ax, float ay, float az);
    void setColor(float r, float g, float b);
    void setHandleColor(float r, float g, float b);
    void open();
    void close();
    bool getState() const;


    void draw();
};

#endif#pragma once
