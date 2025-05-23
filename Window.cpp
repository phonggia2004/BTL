#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include "Window.h"

// Biến toàn cục
float windowAngle = 0.0f;
bool windowOpening = false;
bool windowClosing = false;
const float MAX_WINDOW_ANGLE = 85.0f;
const float WINDOW_SPEED = 60.0f; // độ/giây

// Vẽ khung cửa sổ 3D
void drawWindowFrame(float w, float h, float thickness) {
    float frameDepth = thickness * 0.8f;

    // Màu gỗ nâu
    glColor3f(0.45f, 0.25f, 0.1f);

    // Vẽ khung trái
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glBegin(GL_QUADS);
    // Mặt trước
    glVertex3f(0, 0, 0);
    glVertex3f(thickness, 0, 0);
    glVertex3f(thickness, h, 0);
    glVertex3f(0, h, 0);

    // Mặt sau
    glVertex3f(0, 0, -frameDepth);
    glVertex3f(thickness, 0, -frameDepth);
    glVertex3f(thickness, h, -frameDepth);
    glVertex3f(0, h, -frameDepth);

    // Mặt trên
    glVertex3f(0, h, 0);
    glVertex3f(thickness, h, 0);
    glVertex3f(thickness, h, -frameDepth);
    glVertex3f(0, h, -frameDepth);

    // Mặt dưới
    glVertex3f(0, 0, 0);
    glVertex3f(thickness, 0, 0);
    glVertex3f(thickness, 0, -frameDepth);
    glVertex3f(0, 0, -frameDepth);

    // Mặt ngoài
    glVertex3f(0, 0, 0);
    glVertex3f(0, h, 0);
    glVertex3f(0, h, -frameDepth);
    glVertex3f(0, 0, -frameDepth);

    // Mặt trong
    glVertex3f(thickness, 0, 0);
    glVertex3f(thickness, h, 0);
    glVertex3f(thickness, h, -frameDepth);
    glVertex3f(thickness, 0, -frameDepth);
    glEnd();
    glPopMatrix();

    // Vẽ khung phải
    glPushMatrix();
    glTranslatef(w - thickness, 0, 0);
    glBegin(GL_QUADS);
    // Mặt trước
    glVertex3f(0, 0, 0);
    glVertex3f(thickness, 0, 0);
    glVertex3f(thickness, h, 0);
    glVertex3f(0, h, 0);

    // Mặt sau
    glVertex3f(0, 0, -frameDepth);
    glVertex3f(thickness, 0, -frameDepth);
    glVertex3f(thickness, h, -frameDepth);
    glVertex3f(0, h, -frameDepth);

    // Mặt trên
    glVertex3f(0, h, 0);
    glVertex3f(thickness, h, 0);
    glVertex3f(thickness, h, -frameDepth);
    glVertex3f(0, h, -frameDepth);

    // Mặt dưới
    glVertex3f(0, 0, 0);
    glVertex3f(thickness, 0, 0);
    glVertex3f(thickness, 0, -frameDepth);
    glVertex3f(0, 0, -frameDepth);

    // Mặt ngoài
    glVertex3f(thickness, 0, 0);
    glVertex3f(thickness, h, 0);
    glVertex3f(thickness, h, -frameDepth);
    glVertex3f(thickness, 0, -frameDepth);

    // Mặt trong
    glVertex3f(0, 0, 0);
    glVertex3f(0, h, 0);
    glVertex3f(0, h, -frameDepth);
    glVertex3f(0, 0, -frameDepth);
    glEnd();
    glPopMatrix();

    // Vẽ khung trên
    glPushMatrix();
    glTranslatef(0, h - thickness, 0);
    glBegin(GL_QUADS);
    // Mặt trước
    glVertex3f(0, 0, 0);
    glVertex3f(w, 0, 0);
    glVertex3f(w, thickness, 0);
    glVertex3f(0, thickness, 0);

    // Mặt sau
    glVertex3f(0, 0, -frameDepth);
    glVertex3f(w, 0, -frameDepth);
    glVertex3f(w, thickness, -frameDepth);
    glVertex3f(0, thickness, -frameDepth);

    // Mặt trên
    glVertex3f(0, thickness, 0);
    glVertex3f(w, thickness, 0);
    glVertex3f(w, thickness, -frameDepth);
    glVertex3f(0, thickness, -frameDepth);

    // Mặt dưới
    glVertex3f(0, 0, 0);
    glVertex3f(w, 0, 0);
    glVertex3f(w, 0, -frameDepth);
    glVertex3f(0, 0, -frameDepth);
    glEnd();
    glPopMatrix();

    // Vẽ khung dưới
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glBegin(GL_QUADS);
    // Mặt trước
    glVertex3f(0, 0, 0);
    glVertex3f(w, 0, 0);
    glVertex3f(w, thickness, 0);
    glVertex3f(0, thickness, 0);

    // Mặt sau
    glVertex3f(0, 0, -frameDepth);
    glVertex3f(w, 0, -frameDepth);
    glVertex3f(w, thickness, -frameDepth);
    glVertex3f(0, thickness, -frameDepth);

    // Mặt trên
    glVertex3f(0, thickness, 0);
    glVertex3f(w, thickness, 0);
    glVertex3f(w, thickness, -frameDepth);
    glVertex3f(0, thickness, -frameDepth);

    // Mặt dưới
    glVertex3f(0, 0, 0);
    glVertex3f(w, 0, 0);
    glVertex3f(w, 0, -frameDepth);
    glVertex3f(0, 0, -frameDepth);
    glEnd();
    glPopMatrix();
}

// Vẽ tay nắm cửa sổ
void drawWindowHandle(float w, float h, float thickness) {
    float handleWidth = thickness * 0.8f;
    float handleHeight = thickness * 3.0f;
    float handleDepth = thickness * 1.5f;
    float handleX = w * 0.15f;
    float handleY = h * 0.5f;

    // Màu kim loại
    glColor3f(0.75f, 0.75f, 0.75f);

    // Vẽ phần tay nắm
    glPushMatrix();
    glTranslatef(handleX, handleY - handleHeight / 2, -handleDepth / 2);

    // Đế tay nắm
    glPushMatrix();
    glScalef(handleWidth, handleHeight * 0.2f, handleDepth * 0.7f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Phần tay cầm
    glPushMatrix();
    glTranslatef(0, -handleHeight * 0.3f, handleDepth * 0.2f);
    glScalef(handleWidth, handleHeight * 0.6f, handleDepth * 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

// Vẽ kính cửa sổ với hiệu ứng phản chiếu
void drawWindowGlass(float w, float h, float thickness) {
    float glassWidth = w - 2 * thickness;
    float glassHeight = h - 2 * thickness;

    // Thiết lập thuộc tính vật liệu cho kính
    GLfloat glass_ambient[] = { 0.1f, 0.1f, 0.1f, 0.8f };
    GLfloat glass_diffuse[] = { 0.3f, 0.5f, 0.8f, 0.8f };
    GLfloat glass_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat glass_shininess = 100.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glass_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glass_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glass_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, glass_shininess);

    // Bật blend để tạo hiệu ứng trong suốt
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Vẽ kính
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(glassWidth, 0, 0);
    glVertex3f(glassWidth, glassHeight, 0);
    glVertex3f(0, glassHeight, 0);
    glEnd();

    // Vẽ viền kính mỏng
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0.001f);
    glVertex3f(glassWidth, 0, 0.001f);
    glVertex3f(glassWidth, glassHeight, 0.001f);
    glVertex3f(0, glassHeight, 0.001f);
    glEnd();

    // Vẽ đường chéo trang trí
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0.001f);
    glVertex3f(glassWidth, glassHeight, 0.001f);
    glVertex3f(glassWidth, 0, 0.001f);
    glVertex3f(0, glassHeight, 0.001f);
    glEnd();

    glDisable(GL_BLEND);
}

// Vẽ cửa sổ hoàn chỉnh
void drawWindow(float x, float y, float z, float w, float h, float thickness) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Vẽ khung cửa sổ cố định
    drawWindowFrame(w, h, thickness);

    // Vẽ cánh cửa sổ có thể mở
    glPushMatrix();
    glTranslatef(thickness, thickness, 0);
    glRotatef(-windowAngle, 0, 1, 0); // mở xoay theo trục Y

    // Vẽ khung cánh cửa
    float frameWidth = thickness * 0.7f;
    glColor3f(0.4f, 0.22f, 0.1f); // màu gỗ đậm hơn

    // Khung trái
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(frameWidth, 0, 0);
    glVertex3f(frameWidth, h - 2 * thickness, 0);
    glVertex3f(0, h - 2 * thickness, 0);
    glEnd();
    glPopMatrix();

    // Khung phải
    glPushMatrix();
    glTranslatef(w - 2 * thickness - frameWidth, 0, 0);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(frameWidth, 0, 0);
    glVertex3f(frameWidth, h - 2 * thickness, 0);
    glVertex3f(0, h - 2 * thickness, 0);
    glEnd();
    glPopMatrix();

    // Khung trên
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3f(0, h - 2 * thickness - frameWidth, 0);
    glVertex3f(w - 2 * thickness, h - 2 * thickness - frameWidth, 0);
    glVertex3f(w - 2 * thickness, h - 2 * thickness, 0);
    glVertex3f(0, h - 2 * thickness, 0);
    glEnd();
    glPopMatrix();

    // Khung dưới
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(w - 2 * thickness, 0, 0);
    glVertex3f(w - 2 * thickness, frameWidth, 0);
    glVertex3f(0, frameWidth, 0);
    glEnd();
    glPopMatrix();

    // Vẽ kính cửa sổ
    glPushMatrix();
    glTranslatef(frameWidth, frameWidth, -0.001f); // Tránh z-fighting
    drawWindowGlass(w - 2 * thickness - 2 * frameWidth,
        h - 2 * thickness - 2 * frameWidth,
        thickness);
    glPopMatrix();

    // Vẽ tay nắm cửa sổ
    drawWindowHandle(w - 2 * thickness, h - 2 * thickness, thickness);

    glPopMatrix();
    glPopMatrix();

    // Hiệu ứng ánh sáng đi qua cửa sổ (nếu cửa sổ mở)
    if (windowAngle > 0) {
        float lightIntensity = windowAngle / MAX_WINDOW_ANGLE;
        float lightWidth = (w - 2 * thickness) * 0.8f;
        float lightHeight = (h - 2 * thickness) * 0.8f;

        // Vẽ hình chiếu ánh sáng lên sàn (nếu cần)
        glPushMatrix();
        glTranslatef(x + thickness + (w - 2 * thickness) * 0.1f,
            y - 0.01f, // Hơi thấp hơn sàn
            z - 1.0f); // Chiếu vào trong phòng

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 0.95f, 0.8f, 0.3f * lightIntensity);

        glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(lightWidth, 0, 0);
        glVertex3f(lightWidth * 0.8f, 0, -lightHeight * 0.8f);
        glVertex3f(lightWidth * 0.2f, 0, -lightHeight * 0.8f);
        glEnd();

        glDisable(GL_BLEND);
        glPopMatrix();
    }
}

// Cập nhật trạng thái cửa sổ
void updateWindowState(float deltaTime) {
    if (windowOpening) {
        windowAngle += WINDOW_SPEED * deltaTime;
        if (windowAngle >= MAX_WINDOW_ANGLE) {
            windowAngle = MAX_WINDOW_ANGLE;
            windowOpening = false;
        }
    }
    else if (windowClosing) {
        windowAngle -= WINDOW_SPEED * deltaTime;
        if (windowAngle <= 0.0f) {
            windowAngle = 0.0f;
            windowClosing = false;
        }
    }
}

// Mở/đóng cửa sổ
void toggleWindow() {
    if (windowAngle < 0.1f) {
        windowOpening = true;
        windowClosing = false;
    }
    else if (windowAngle > MAX_WINDOW_ANGLE - 0.1f) {
        windowOpening = false;
        windowClosing = true;
    }
    else if (windowOpening) {
        windowOpening = false;
        windowClosing = true;
    }
    else {
        windowOpening = true;
        windowClosing = false;
    }
}

// Kiểm tra xem cửa sổ đang mở hay không
bool isWindowOpen() {
    return windowAngle > 0.0f;
}

// Cập nhật ánh sáng mặt trời
void updateSunLight(float cx, float cy, float cz, bool enable) {
    if (!enable) {
        glDisable(GL_LIGHT1);
        return;
    }

    glEnable(GL_LIGHT1);

    // Tính toán cường độ ánh sáng dựa trên góc mở cửa sổ
    float lightIntensity = 0.2f + 0.8f * (windowAngle / MAX_WINDOW_ANGLE);

    // Vị trí ánh sáng mặt trời
    GLfloat pos[] = { cx, cy, cz + 0.2f, 1.0f };

    // Hướng ánh sáng chéo xuống trong phòng
    GLfloat dir[] = { 0.0f, -0.2f, -1.0f };

    // Màu ánh sáng mặt trời
    GLfloat amb[] = { 0.1f * lightIntensity, 0.1f * lightIntensity, 0.1f * lightIntensity, 1.0f };
    GLfloat diff[] = { 1.0f * lightIntensity, 0.95f * lightIntensity, 0.85f * lightIntensity, 1.0f };
    GLfloat spec[] = { 0.9f * lightIntensity, 0.9f * lightIntensity, 0.8f * lightIntensity, 1.0f };

    // Thiết lập các thông số ánh sáng
    glLightfv(GL_LIGHT1, GL_POSITION, pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0f);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0f);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.6f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1f);

    // Thêm hiệu ứng hạt bụi trong tia nắng nếu cửa sổ mở
    if (windowAngle > 10.0f) {
        // Vẽ các hạt bụi trong tia nắng (nếu cần)
        // Đây là phần mở rộng có thể thêm vào sau
    }
}