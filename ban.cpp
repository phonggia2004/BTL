#include <GL/glut.h>
#include "Table.h"

Table::Table(float x, float y, float z, float sx, float sy, float sz)
    : posX(x), posY(y), posZ(z), scaleX(sx), scaleY(sy), scaleZ(sz), rotationAngle(0.0f)
{
    // Mặc định màu mặt bàn nâu
    topColor[0] = 0.6f; topColor[1] = 0.3f; topColor[2] = 0.0f;
    // Mặc định màu chân bàn đậm hơn
    legColor[0] = 0.4f; legColor[1] = 0.2f; legColor[2] = 0.0f;
}

void Table::setPosition(float x, float y, float z) {
    posX = x; posY = y; posZ = z;
}

void Table::setScale(float sx, float sy, float sz) {
    scaleX = sx; scaleY = sy; scaleZ = sz;
}

void Table::setTopColor(float r, float g, float b) {
    topColor[0] = r; topColor[1] = g; topColor[2] = b;
}

void Table::setLegColor(float r, float g, float b) {
    legColor[0] = r; legColor[1] = g; legColor[2] = b;
}

void Table::setRotation(float angle) {
    rotationAngle = angle;
}

void Table::drawCube(float width, float height, float depth) {
    float w = width / 2;
    float h = height / 2;
    float d = depth / 2;
    glBegin(GL_QUADS);
    // Front
    glVertex3f(-w, -h, d); glVertex3f(w, -h, d);
    glVertex3f(w, h, d); glVertex3f(-w, h, d);
    // Back
    glVertex3f(-w, -h, -d); glVertex3f(-w, h, -d);
    glVertex3f(w, h, -d); glVertex3f(w, -h, -d);
    // Top
    glVertex3f(-w, h, -d); glVertex3f(-w, h, d);
    glVertex3f(w, h, d); glVertex3f(w, h, -d);
    // Bottom
    glVertex3f(-w, -h, -d); glVertex3f(w, -h, -d);
    glVertex3f(w, -h, d); glVertex3f(-w, -h, d);
    // Left
    glVertex3f(-w, -h, -d); glVertex3f(-w, -h, d);
    glVertex3f(-w, h, d); glVertex3f(-w, h, -d);
    // Right
    glVertex3f(w, -h, -d); glVertex3f(w, h, -d);
    glVertex3f(w, h, d); glVertex3f(w, -h, d);
    glEnd();
}

void Table::draw() {
    glPushMatrix();
    // Di chuyển đến vị trí bàn
    glTranslatef(posX, posY, posZ);

    // Áp dụng xoay cho toàn bộ bàn
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    // Phóng to theo tỉ lệ scale
    glScalef(scaleX, scaleY, scaleZ);

    // Vẽ mặt bàn
    glPushMatrix();
    glColor3fv(topColor);
    glTranslatef(0.0f, 1.0f, 0.0f);
    drawCube(3.0f, 0.2f, 2.0f);
    glPopMatrix();

    // Vẽ 4 chân bàn
    float legX = 1.3f;
    float legZ = 0.8f;
    float legHeight = 1.0f;
    glColor3fv(legColor);
    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dz = -1; dz <= 1; dz += 2) {
            glPushMatrix();
            glTranslatef(dx * legX, legHeight / 2.0f, dz * legZ);
            drawCube(0.1f, legHeight, 0.1f);
            glPopMatrix();
        }
    }

    glPopMatrix();
}