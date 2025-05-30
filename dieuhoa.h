#ifndef AIR_CONDITIONER_H
#define AIR_CONDITIONER_H

class AirConditioner {
private:
    float x, y, z;          
    float width, height, depth; 
    bool isOn;             
    float bodyColor[3];    
    float ventColor[3];     

public:
    AirConditioner();
    void setPosition(float x, float y, float z);
    void setSize(float w, float h, float d);
    void setBodyColor(float r, float g, float b);
    void setVentColor(float r, float g, float b);
    void turnOn();
    void turnOff();
    bool getState() const;
    void draw() const;
};

#endif#pragma once
