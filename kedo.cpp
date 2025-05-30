#include <GL/glut.h>
#include "kedo.h"

Shelf::Shelf() {
    width = 2.0f;
    height = 2.0f;
    depth = 0.5f;
    colorR = 0.6f;
    colorG = 0.3f;
    colorB = 0.1f;
}

void Shelf::setSize(float w, float h, float d) {
    width = w;
    height = h;
    depth = d;
}

void Shelf::setColor(float r, float g, float b) {
    colorR = r;
    colorG = g;
    colorB = b;
}

void Shelf::drawBox(float w, float h, float d) {
    glBegin(GL_QUADS);
    // mặt trước
    glNormal3f(0, 0, 1);
    glVertex3f(-w / 2, 0, d / 2);
    glVertex3f(w / 2, 0, d / 2);
    glVertex3f(w / 2, h, d / 2);
    glVertex3f(-w / 2, h, d / 2);

    // mặt sau
    glNormal3f(0, 0, -1);
    glVertex3f(-w / 2, 0, -d / 2);
    glVertex3f(w / 2, 0, -d / 2);
    glVertex3f(w / 2, h, -d / 2);
    glVertex3f(-w / 2, h, -d / 2);

    // mặt bên phải
    glNormal3f(1, 0, 0);
    glVertex3f(w / 2, 0, -d / 2);
    glVertex3f(w / 2, 0, d / 2);
    glVertex3f(w / 2, h, d / 2);
    glVertex3f(w / 2, h, -d / 2);

    // mặt bên trái
    glNormal3f(-1, 0, 0);
    glVertex3f(-w / 2, 0, -d / 2);
    glVertex3f(-w / 2, 0, d / 2);
    glVertex3f(-w / 2, h, d / 2);
    glVertex3f(-w / 2, h, -d / 2);

    // mặt trên
    glNormal3f(0, 1, 0);
    glVertex3f(-w / 2, h, -d / 2);
    glVertex3f(w / 2, h, -d / 2);
    glVertex3f(w / 2, h, d / 2);
    glVertex3f(-w / 2, h, d / 2);

    // mặt dưới
    glNormal3f(0, -1, 0);
    glVertex3f(-w / 2, 0, -d / 2);
    glVertex3f(w / 2, 0, -d / 2);
    glVertex3f(w / 2, 0, d / 2);
    glVertex3f(-w / 2, 0, d / 2);
    glEnd();
}

void Shelf::draw() {
    glColor3f(colorR, colorG, colorB);

    float legWidth = width * 0.1f;
    float legHeight = height;

    // Vẽ 2 chân kệ
    glPushMatrix();
    glTranslatef(-width / 2 + legWidth / 2, 0, -depth / 2 + legWidth / 2);
    drawBox(legWidth, legHeight, legWidth);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(width / 2 - legWidth / 2, 0, -depth / 2 + legWidth / 2);
    drawBox(legWidth, legHeight, legWidth);
    glPopMatrix();

    // Vẽ 3 tầng kệ ngang
    float shelfThickness = legWidth;
    float shelfHeight[3] = { 0.0f, height / 2.0f, height };

    for (int i = 0; i < 3; ++i) {
        glPushMatrix();
        glTranslatef(0, shelfHeight[i], 0);
        drawBox(width, shelfThickness, depth);
        glPopMatrix();
    }
}
