#include "dieuhoa.h"
#include "GL/glut.h"

AirConditioner::AirConditioner() {
    x = y = z = 0.0f;
    width = 1.0f;
    height = 0.25f;
    depth = 0.22f;
    isOn = false;

    // Màu trắng cho thân điều hòa
    bodyColor[0] = 1.0f;
    bodyColor[1] = 1.0f;
    bodyColor[2] = 1.0f;

    // Màu xám đậm cho khe gió
    ventColor[0] = 0.2f;
    ventColor[1] = 0.2f;
    ventColor[2] = 0.2f;
}

void AirConditioner::setPosition(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void AirConditioner::setSize(float w, float h, float d) {
    width = w;
    height = h;
    depth = d;
}

void AirConditioner::setBodyColor(float r, float g, float b) {
    bodyColor[0] = r;
    bodyColor[1] = g;
    bodyColor[2] = b;
}

void AirConditioner::setVentColor(float r, float g, float b) {
    ventColor[0] = r;
    ventColor[1] = g;
    ventColor[2] = b;
}

void AirConditioner::turnOn() {
    isOn = true;
}

void AirConditioner::turnOff() {
    isOn = false;
}

bool AirConditioner::getState() const {
    return isOn;
}

void AirConditioner::draw() const {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Đặt màu thân điều hòa
    glColor3fv(bodyColor);

    // Vẽ thân điều hòa (hình hộp chữ nhật)
    glBegin(GL_QUADS);
    // Mặt trước
    glNormal3f(0, 0, 1);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);

    // Mặt sau
    glNormal3f(0, 0, -1);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);

    // Mặt trên
    glNormal3f(0, 1, 0);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);

    // Mặt dưới
    glNormal3f(0, -1, 0);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);

    // Mặt trái
    glNormal3f(-1, 0, 0);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);

    // Mặt phải
    glNormal3f(1, 0, 0);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glEnd();

    // Vẽ khe gió (nhiều nan ngang)
    glDisable(GL_LIGHTING); 
    glColor3fv(ventColor);
    float barHeight = 0.005f;
    float spacing = 0.01f;
    for (float i = 0.0f; i < 0.1f; i += spacing) {
        glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(-width / 2 + 0.1f, -height / 2 + 0.05f + i, depth / 2 + 0.01f);
        glVertex3f(width / 2 - 0.1f, -height / 2 + 0.05f + i, depth / 2 + 0.01f);
        glVertex3f(width / 2 - 0.1f, -height / 2 + 0.05f + i + barHeight, depth / 2 + 0.01f);
        glVertex3f(-width / 2 + 0.1f, -height / 2 + 0.05f + i + barHeight, depth / 2 + 0.01f);
        glEnd();
    }

    // Màn hình LED nhỏ khi bật
    if (isOn) {
        glColor3f(0.8f, 0.8f, 1.0f); // xanh nhạt
        glBegin(GL_QUADS);
        glVertex3f(width / 2 - 0.15f, height / 2 - 0.1f, depth / 2 + 0.01f);
        glVertex3f(width / 2 - 0.1f, height / 2 - 0.1f, depth / 2 + 0.01f);
        glVertex3f(width / 2 - 0.1f, height / 2 - 0.05f, depth / 2 + 0.01f);
        glVertex3f(width / 2 - 0.15f, height / 2 - 0.05f, depth / 2 + 0.01f);
        glEnd();
    }

    glEnable(GL_LIGHTING); // bật lại ánh sáng cho các đối tượng khác
    glPopMatrix();
}
