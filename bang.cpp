#include "bang.h"

Wallboard::Wallboard() {
    posX = posY = posZ = 0.0f;
    scaleX = scaleY = scaleZ = 1.0f;
    angleX = angleY = angleZ = 0.0f;
    boardColorR = 1.0f; boardColorG = 1.0f; boardColorB = 1.0f; 
    frameColorR = 0.5f; frameColorG = 0.3f; frameColorB = 0.1f; 
}

void Wallboard::setPosition(float x, float y, float z) {
    posX = x; posY = y; posZ = z;
}

void Wallboard::setScale(float sx, float sy, float sz) {
    scaleX = sx; scaleY = sy; scaleZ = sz;
}

void Wallboard::setRotation(float ax, float ay, float az) {
    angleX = ax; angleY = ay; angleZ = az;
}

void Wallboard::setBoardColor(float r, float g, float b) {
    boardColorR = r; boardColorG = g; boardColorB = b;
}

void Wallboard::setFrameColor(float r, float g, float b) {
    frameColorR = r; frameColorG = g; frameColorB = b;
}

void Wallboard::drawBox() {
    glBegin(GL_QUADS);
    // Mặt trước
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Mặt sau
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Mặt trên
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    // Mặt dưới
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Mặt trái
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Mặt phải
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void Wallboard::draw() {
    glPushMatrix();

    glTranslatef(posX, posY, posZ);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);

    // mặt bảng chính
    glPushMatrix();
    glScalef(1.0f, 0.6f, 0.02f);
    glColor3f(boardColorR, boardColorG, boardColorB);
    drawBox();
    glPopMatrix();

    // khung bảng
    glColor3f(frameColorR, frameColorG, frameColorB);

    // Khung trên
    glPushMatrix();
    glTranslatef(0.0f, 0.31f, 0.0f);
    glScalef(1.04f, 0.02f, 0.04f);
    drawBox();
    glPopMatrix();

    // Khung dưới
    glPushMatrix();
    glTranslatef(0.0f, -0.31f, 0.0f);
    glScalef(1.04f, 0.02f, 0.04f);
    drawBox();
    glPopMatrix();

    // Khung trái
    glPushMatrix();
    glTranslatef(-0.51f, 0.0f, 0.0f);
    glScalef(0.02f, 0.6f, 0.04f);
    drawBox();
    glPopMatrix();

    // Khung phải
    glPushMatrix();
    glTranslatef(0.51f, 0.0f, 0.0f);
    glScalef(0.02f, 0.6f, 0.04f);
    drawBox();
    glPopMatrix();

    glPopMatrix();
}
