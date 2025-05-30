#include "DeskLamp.h"
#include <GL/glut.h>
#include <cstdio> // Thêm để debug

DeskLamp::DeskLamp() {
    posX = posY = posZ = 0.0f;
    colorR = 1.0f; colorG = 0.8f; colorB = 0.2f;
    lightOn = true;
}

void DeskLamp::setPosition(float x, float y, float z) {
    posX = x; posY = y; posZ = z;
}

void DeskLamp::setLampColor(float r, float g, float b) {
    colorR = r; colorG = g; colorB = b;
}

void DeskLamp::setLightState(bool on) {
    lightOn = on;
}

bool DeskLamp::getLightState() {
    return lightOn;
}

void DeskLamp::setupLight() {
    // Đặt vị trí ánh sáng tại bóng đèn
    GLfloat lightPos[] = { posX, posY + 0.715f, posZ, 1.0f }; // Vị trí bóng đèn
    GLfloat ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };   // Giảm ánh sáng môi trường để tránh sáng lan tỏa lên trên
    GLfloat diffuse[] = { 10.0f, 9.0f, 6.0f, 1.0f };  // Giữ cường độ cao để chiếu sáng sàn
    GLfloat specular[] = { 3.0f, 3.0f, 2.0f, 1.0f };  // Giữ cường độ phản xạ
    GLfloat direction[] = { -0.5f, -1.5f, -0.5f };    // Hướng xuống sàn và lệch về bàn phím

    glLightfv(GL_LIGHT2, GL_POSITION, lightPos);

    if (lightOn) {
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2f);  // Giữ thấp để ánh sáng lan xa
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.05f); // Giữ thấp để ánh sáng chiếu đến sàn
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0f);        // Thu hẹp góc chiếu sáng để tập trung xuống dưới
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction); // Hướng ánh sáng xuống sàn và lệch về bàn phím
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 5.0f);       // Tăng độ tập trung để ánh sáng không lan tỏa quá rộng
    }
    else {
        GLfloat zero[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT2, GL_AMBIENT, zero);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, zero);
        glLightfv(GL_LIGHT2, GL_SPECULAR, zero);
        glDisable(GL_LIGHT2);
    }
}

void DeskLamp::draw() {
    setupLight();  

    glPushMatrix();
    glTranslatef(posX, posY, posZ);  

    // === Chân đế ===
    // Tạo chân đế phẳng và rộng để đảm bảo độ ổn định
    glColor3f(0.2f, 0.2f, 0.2f);  
    glPushMatrix();
    glTranslatef(0.0f, 0.025f, 0.0f);  
    glScalef(0.3f, 0.05f, 0.3f);      
    glutSolidCube(1.0);               
    glPopMatrix();

    // === Trụ đèn ===
    // Vẽ trụ đèn hình trụ, ngắn hơn để trông thực tế hơn
    glPushMatrix();
    glTranslatef(0.0f, 0.075f, 0.0f);  // Bắt đầu từ đỉnh chân đế (0.025 + 0.05/2)
    glColor3f(0.4f, 0.4f, 0.4f);      // Màu xám trung cho trụ
    glRotatef(-90, 1, 0, 0);          // Xoay để trụ hướng lên theo trục Y
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 0.03f, 0.03f, 0.6f, 16, 16); // Trụ cao 0.6 đơn vị
    gluDeleteQuadric(quad);           
    glPopMatrix();

    // === Khớp nối hình cầu ===
    // Vẽ khớp nối nhỏ giữa trụ và bóng đèn
    glPushMatrix();
    glTranslatef(0.0f, 0.675f, 0.0f);  // Đặt ở đỉnh trụ (0.075 + 0.6)
    glColor3f(0.4f, 0.4f, 0.4f);      // Màu khớp nối đồng bộ với trụ
    glutSolidSphere(0.04f, 16, 16);   // Khớp nối hình cầu nhỏ
    glPopMatrix();

    // === Bóng đèn ===
    // Vẽ bóng đèn sáng hoặc tối tùy trạng thái
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);  
    glPushMatrix();
    glTranslatef(0.0f, 0.715f, 0.0f);  
    if (lightOn)
        glColor3f(1.0f, 1.0f, 0.6f);  
    else
        glColor3f(0.3f, 0.3f, 0.3f);  
    glutSolidSphere(0.05f, 16, 16);   
    glPopMatrix();
    glPopAttrib();

    // === Chụp đèn ===
    // Vẽ chụp đèn hình nón cụt bao quanh bóng đèn
    glPushMatrix();
    glTranslatef(0.0f, 0.765f, 0.0f); 
    glRotatef(-90, 1, 0, 0);          
    glColor3f(colorR, colorG, colorB); 
    GLUquadric* shade = gluNewQuadric();
    gluCylinder(shade, 0.15f, 0.05f, 0.2f, 20, 20); 
    gluDeleteQuadric(shade);         
    glPopMatrix();

    glPopMatrix();
}