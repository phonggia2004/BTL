#ifndef AIR_CONDITIONER_H
#define AIR_CONDITIONER_H

class AirConditioner {
private:
    float x, y, z;          // Vị trí của điều hòa
    float width, height, depth; // Kích thước điều hòa
    bool isOn;              // Trạng thái bật/tắt
    float bodyColor[3];     // Màu thân điều hòa
    float ventColor[3];     // Màu khe gió

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
