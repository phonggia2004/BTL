#include <GL/glut.h>
#include "Mouse.h"

void drawMouse(float x, float y, float z, float rotationY) {
	GLfloat mouseColor[] = { 0.3f, 0.3f, 0.3f };     // màu xám đậm
	GLfloat wheelColor[] = { 0.1f, 0.1f, 0.1f };     // bánh xe màu đen

	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

	// Vỏ chuột (hình elip thấp - scaled sphere)
	glColor3fv(mouseColor);
	glPushMatrix();
	glScalef(0.06f, 0.02625f, 0.09f); 
	glutSolidSphere(1.0f, 30, 30);
	glPopMatrix();

	// Bánh xe chuột (ở giữa)
	glColor3fv(wheelColor);
	glPushMatrix();
	glTranslatef(0.0f, 0.01875f, 0.01f); 
	glScalef(0.005f, 0.01125f, 0.015f);  
	glutSolidCube(1.0f);
	glPopMatrix();

	glPopMatrix();
}
