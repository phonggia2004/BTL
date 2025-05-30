#ifndef CAR_H
#define CAR_H

class Car {
public:
    Car();
    void setColor(float r, float g, float b);
    void draw();

private:
    float colorR, colorG, colorB;

    void drawBox(float w, float h, float d);
    void drawCylinder(float radius, float height);
};

#endif
#pragma once
