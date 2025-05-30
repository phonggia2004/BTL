#include <GL/glut.h>
#include "Keyboard.h"

void drawKeyboard(float x, float y, float z, float rotationY) {
    GLfloat keyboardColor[] = { 0.2f, 0.2f, 0.2f };
    GLfloat keyColor[] = { 0.4f, 0.4f, 0.4f };
    GLfloat spaceColor[] = { 0.3f, 0.3f, 0.3f };

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    glColor3fv(keyboardColor);
    glPushMatrix();
    glScalef(0.6f, 0.02f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();


    glColor3fv(keyColor);
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 10; ++col) {
            glPushMatrix();
            glTranslatef(-0.25f + col * 0.055f, 0.015f, 0.08f - row * 0.05f);
            glScalef(0.045f, 0.01f, 0.04f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }

    glColor3fv(spaceColor);
    glPushMatrix();
    glTranslatef(0.0f, 0.01f, -0.08f); 
    glScalef(0.35f, 0.01f, 0.035f);   
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}
