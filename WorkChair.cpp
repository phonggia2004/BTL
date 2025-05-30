#include "WorkChair.h"

WorkChair::WorkChair() {
    posX = posY = posZ = 0.0f;
    scaleX = scaleY = scaleZ = 1.0f;
    angleX = angleY = angleZ = 0.0f;
    seatColorR = 0.2f; seatColorG = 0.2f; seatColorB = 0.2f; // Màu đen cho đệm và lưng
    frameColorR = 0.5f; frameColorG = 0.5f; frameColorB = 0.5f; // Màu xám cho khung và chân
}

void WorkChair::setPosition(float x, float y, float z) {
    posX = x; posY = y; posZ = z;
}

void WorkChair::setScale(float sx, float sy, float sz) {
    scaleX = sx; scaleY = sy; scaleZ = sz;
}

void WorkChair::setRotation(float ax, float ay, float az) {
    angleX = ax; angleY = ay; angleZ = az;
}

void WorkChair::setSeatColor(float r, float g, float b) {
    seatColorR = r; seatColorG = g; seatColorB = b;
}

void WorkChair::setFrameColor(float r, float g, float b) {
    frameColorR = r; frameColorG = g; frameColorB = b;
}

void WorkChair::drawBox() {
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

void WorkChair::drawLeg(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.25f, z);
    glScalef(0.1f, 0.5f, 0.1f);
    drawBox();
    glPopMatrix();
}

void WorkChair::draw() {
    glPushMatrix();

    // Áp dụng transformations
    glTranslatef(posX, posY, posZ);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);

    // Vẽ đệm ghế
    glPushMatrix();
    glTranslatef(0.0f, 0.45f, 0.0f); // Điều chỉnh vị trí cho hợp lý
    glScalef(1.0f, 0.1f, 1.0f); // Đệm mỏng
    glColor3f(seatColorR, seatColorG, seatColorB);
    drawBox();
    glPopMatrix();

    // Vẽ lưng ghế
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, -0.4f);
    glScalef(1.0f, 1.0f, 0.1f); // Lưng mỏng
    glColor3f(seatColorR, seatColorG, seatColorB);
    drawBox();
    glPopMatrix();

    // Vẽ 4 chân ghế
    glColor3f(frameColorR, frameColorG, frameColorB);
    drawLeg(-0.4f, -0.4f); // Chân trước trái
    drawLeg(0.4f, -0.4f);  // Chân trước phải
    drawLeg(-0.4f, 0.4f);  // Chân sau trái
    drawLeg(0.4f, 0.4f);   // Chân sau phải

    glPopMatrix();
}
