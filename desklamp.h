#ifndef DESKLAMP_H
#define DESKLAMP_H

class DeskLamp {
public:
    DeskLamp();
    void setPosition(float x, float y, float z);
    void setLampColor(float r, float g, float b);
    void setLightState(bool on);
    bool getLightState(); 
    void draw();

private:
    float posX, posY, posZ;
    float colorR, colorG, colorB;
    bool lightOn;

    void setupLight();
};

#endif