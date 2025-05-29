#ifndef OFFICE_CHAIR_H
#define OFFICE_CHAIR_H

class OfficeChair {
private:
    float x, y, z;          // Vị trí ghế
    float width, height, depth; // Kích thước ghế (mặt ngồi)
    float backHeight;       // Chiều cao lưng ghế
    float rotationAngle;    // Góc xoay của ghế
    bool isRotating;        // Trạng thái xoay
    float bodyColor[3];     // Màu thân ghế
    float legColor[3];      // Màu chân ghế

public:
    OfficeChair();
    void setPosition(float x, float y, float z);
    void setSize(float w, float h, float d);
    void setBackHeight(float h);
    void setBodyColor(float r, float g, float b);
    void setLegColor(float r, float g, float b);
    void toggleRotate();
    void updateRotation();
    void draw() const;
};

#endif