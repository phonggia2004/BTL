#ifndef TABLE_H
#define TABLE_H

#include <GL/glut.h>

class Table {
private:
    float posX, posY, posZ;     // Vị trí bàn
    float scaleX, scaleY, scaleZ; // Kích thước phóng to/thay đổi
    float topColor[3];          // Màu mặt bàn (RGB)
    float legColor[3];          // Màu chân bàn (RGB)
    float rotationAngle;        // Góc xoay của bàn
    void drawCube(float width, float height, float depth);
public:
    Table(float x = 0, float y = 0, float z = 0,
        float sx = 1, float sy = 1, float sz = 1);
    void setPosition(float x, float y, float z);
    void setScale(float sx, float sy, float sz);
    void setTopColor(float r, float g, float b);
    void setLegColor(float r, float g, float b);
    void setRotation(float angle);
    void draw();
};

#endif // TABLE_H
