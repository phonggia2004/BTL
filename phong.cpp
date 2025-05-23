#include <GL/glut.h>
#include <math.h>
#include "Table.h"
#include "ComputerMonitor.h"
#include "Keyboard.h"
#include "computercase.h"
#include "mouse.h"
#include "Window.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Table myTable1;
Table myTable2;

/* ----------  Biến cửa sổ (extern từ Window.cpp)  ---------- */
extern float windowAngle;
extern bool windowOpening;

/* ----------  Camera & Chuyển động  ---------- */
float cameraX = 0.0f, cameraY = 2.5f, cameraZ = 5.0f;
float yaw = -90.0f;                 // xoay ngang
float pitch = 0.0f;                 // xoay dọc
float dirX, dirY, dirZ;             // hướng nhìn
const float moveSpeed = 0.05f;
const float turnSpeed = 1.0f;
const float upDownSpeed = 0.05f;     // Tốc độ di chuyển lên xuống

// Biến trạng thái phím
bool keyStates[256] = { false };    // Trạng thái các phím thường
bool specialKeyStates[256] = { false }; // Trạng thái các phím đặc biệt

/* ----------  Ánh sáng  ---------- */
const float lightX = 0.0f, lightY = 4.8f, lightZ = 0.0f;
bool  lightOn = true;               // trạng thái đèn (bật/tắt)

/* ----------  Hàm tiện ích  ---------- */
void updateDirection() {
    dirX = cosf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);
    dirY = sinf(pitch * M_PI / 180.0f);
    dirZ = sinf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);
}

/* ----------  Khởi tạo  ---------- */
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    /* Thuộc tính vật liệu & chuẩn hoá pháp tuyến  */
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE);
    updateDirection();
}

/* ----------  Cập nhật nguồn sáng (tuỳ trạng thái) ---------- */
void updateLight() {
    GLfloat light_position[] = { lightX, lightY, lightZ, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    if (lightOn) {
        GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat diffuse[] = { 1.0f, 1.0f, 0.9f, 1.0f };
        GLfloat specular[] = { 1.0f, 1.0f, 0.9f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);
        glEnable(GL_LIGHT0);           // Bật đèn
    }
    else {
        GLfloat zero[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT, zero);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, zero);
        glLightfv(GL_LIGHT0, GL_SPECULAR, zero);
        glDisable(GL_LIGHT0);          // Tắt đèn
    }
}

/* ----------  Vẽ bóng đèn  ---------- */
void drawLightBulb() {
    glPushAttrib(GL_LIGHTING_BIT);     // Lưu trạng thái ánh sáng
    glDisable(GL_LIGHTING);            // Vẽ bóng đèn không chịu ảnh hưởng
    glPushMatrix();
    glTranslatef(lightX, lightY, lightZ);
    if (lightOn)
        glColor3f(1.0f, 1.0f, 0.6f);   // vàng sáng khi bật
    else
        glColor3f(0.4f, 0.4f, 0.4f);   // xám khi tắt
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();
    glPopAttrib();                     // Khôi phục lighting
}

/* ----------  Cập nhật vị trí camera dựa trên phím đang được nhấn ---------- */
void updateCamera() {
    float dirXxz = cosf(yaw * M_PI / 180.0f);
    float dirZxz = sinf(yaw * M_PI / 180.0f);

    // Di chuyển tiến/lùi (W/S)
    if (keyStates['w'] || keyStates['W'])
    {
        cameraX += dirXxz * moveSpeed; cameraZ += dirZxz * moveSpeed;
    }
    if (keyStates['s'] || keyStates['S'])
    {
        cameraX -= dirXxz * moveSpeed; cameraZ -= dirZxz * moveSpeed;
    }

    // Di chuyển trái/phải (A/D)
    if (keyStates['a'] || keyStates['A'])
    {
        cameraX -= dirZxz * moveSpeed; cameraZ += dirXxz * moveSpeed;
    }
    if (keyStates['d'] || keyStates['D'])
    {
        cameraX += dirZxz * moveSpeed; cameraZ -= dirXxz * moveSpeed;
    }

    // Di chuyển lên/xuống (Q/E)
    if (keyStates['q'] || keyStates['Q'])
        cameraY += upDownSpeed;
    if (keyStates['e'] || keyStates['E'])
        cameraY -= upDownSpeed;

    // Giới hạn độ cao camera để không đi xuyên sàn hoặc trần
    if (cameraY < 0.5f) cameraY = 0.5f;
    if (cameraY > 4.5f) cameraY = 4.5f;

    if (cameraX < -4.5f) cameraX = -4.5f;  // hơi nhỏ hơn 5 để không xuyên tường
    if (cameraX > 4.5f) cameraX = 4.5f;
    if (cameraZ < -4.5f) cameraZ = -4.5f;
    if (cameraZ > 4.5f) cameraZ = 4.5f;

    // Cập nhật góc cửa sổ
    if (windowOpening && windowAngle < 90.0f)  windowAngle += 1.0f;
    if (!windowOpening && windowAngle > 0.0f)  windowAngle -= 1.0f;

    // Xoay camera bằng phím mũi tên
    if (specialKeyStates[GLUT_KEY_LEFT])
        yaw -= turnSpeed;
    if (specialKeyStates[GLUT_KEY_RIGHT])
        yaw += turnSpeed;
    if (specialKeyStates[GLUT_KEY_UP]) {
        pitch += turnSpeed;
        if (pitch > 89) pitch = 89;
    }
    if (specialKeyStates[GLUT_KEY_DOWN]) {
        pitch -= turnSpeed;
        if (pitch < -89) pitch = -89;
    }

    updateDirection();
}

/* ----------  Vẽ phòng  ---------- */
void drawRoom(void) {
    // Cập nhật vị trí camera dựa trên phím đang được nhấn
    updateCamera();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ,
        cameraX + dirX, cameraY + dirY, cameraZ + dirZ,
        0.0, 1.0, 0.0);
    updateLight();   // đặt lại nguồn sáng

    /* --- Sàn --- */
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-5, 0, -5); glVertex3f(-5, 0, 5);
    glVertex3f(5, 0, 5);   glVertex3f(5, 0, -5);
    glEnd();

    /* --- Trần --- */
    glColor3f(0.7, 0.9, 0.9);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(-5, 5, -5); glVertex3f(-5, 5, 5);
    glVertex3f(5, 5, 5);   glVertex3f(5, 5, -5);
    glEnd();

    /* --- Tường trái --- */
    glColor3f(1.0, 1.0, 0.9);
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(-5, 0, -5); glVertex3f(-5, 5, -5);
    glVertex3f(-5, 5, 5);  glVertex3f(-5, 0, 5);
    glEnd();

    /* --- Tường phải --- */
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(5, 0, -5);  glVertex3f(5, 5, -5);
    glVertex3f(5, 5, 5);   glVertex3f(5, 0, 5);
    glEnd();

    /* --- Tường sau --- */
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-5, 0, -5); glVertex3f(-5, 5, -5);
    glVertex3f(5, 5, -5);  glVertex3f(5, 0, -5);
    glEnd();

    /* --- Tường trước --- */
    glColor3f(1.0, 0.95, 0.9);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(-5, 0, 5);  glVertex3f(-5, 5, 5);
    glVertex3f(5, 5, 5);   glVertex3f(5, 0, 5);
    glEnd();

    drawLightBulb();// vẽ bóng đèn

    //Vẽ bàn
    myTable1.setPosition(4.35f, 0.0f, -2.0f);  // Move to right wall (x=4.0)
    myTable1.setScale(0.8f, 1.0f, 0.6f);      // Make it smaller
    myTable1.setTopColor(0.7f, 0.4f, 0.1f);
    myTable1.setLegColor(0.5f, 0.25f, 0.1f);
    myTable1.setRotation(90.0f);
    // Trong hàm vẽ:
    myTable1.draw();

    glPushMatrix();
    glTranslatef(4.7f, 1.69f, -2.0f);  // nâng lên y=1.0f cho trên mặt bàn
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f); // xoay màn hình quay mặt vào giữa phòng
    drawComputerMonitor();
    glPopMatrix();

    //Vẽ bàn phím và case
    drawKeyboard(4.2f, 1.1f, -2.0f, 270.0f);
    drawMouse(4.2f, 1.1f, -1.5f, 270.0f);

    // Vẽ case đặt dưới bàn (bên phải)
    drawComputerCase(4.2f, 0.25f, -2.65f, 270.0f);

    //Vẽ cửa sổ với mặt trời
    // ---- vẽ cửa sổ trên tường trái ----
    float winWidth = 2.5f, winHeight = 1.8f, winThickness = 0.15f;
    float winY = 1.5f; // Độ cao từ sàn

    float winX = 0.0f, winZ = 4.99f; // Giữa tường trước

    glPushMatrix();
    glTranslatef(winX, winY, winZ);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);  // Xoay 180° để quay vào trong phòng
    drawWindow(-winWidth / 2, 0, 0, winWidth, winHeight, winThickness);
    glPopMatrix();

    // Ánh sáng từ phía trước
    updateSunLight(winX, winY + winHeight / 2, winZ - 0.2f, windowAngle > 10.0f);


    myTable2.setPosition(4.35f, 0.0f, 0.5f);  // Move to right wall (x=4.0)
    myTable2.setScale(0.8f, 1.0f, 0.6f);      // Make it smaller
    myTable2.setTopColor(0.7f, 0.4f, 0.1f);
    myTable2.setLegColor(0.5f, 0.25f, 0.1f);
    myTable2.setRotation(90.0f);
    // Trong hàm vẽ:
    myTable2.draw();

    glutSwapBuffers();
}

/* ----------  Điều khiển phím (WASD + QE + L) ---------- */
void keyboard(unsigned char key, int x, int y) {
    // Ghi nhận phím được nhấn
    keyStates[key] = true;

    // Xử lý các phím đặc biệt không cần liên tục
    switch (key) {
    case 'l': case 'L':                 // Bật / tắt đèn
        lightOn = !lightOn;
        break;
    case 'o': case 'O':        // bật/tắt mở cửa
        windowOpening = !windowOpening;
        break;
    }

    glutPostRedisplay();
}

/* ----------  Xử lý khi phím được thả ra ---------- */
void keyboardUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
    glutPostRedisplay();
}

/* ----------  Xoay camera bằng phím mũi tên ---------- */
void specialKeys(int key, int x, int y) {
    specialKeyStates[key] = true;
    glutPostRedisplay();
}

/* ----------  Xử lý khi phím đặc biệt được thả ra ---------- */
void specialKeysUp(int key, int x, int y) {
    specialKeyStates[key] = false;
    glutPostRedisplay();
}

/* ----------  Hàm cập nhật liên tục ---------- */
void idle() {
    glutPostRedisplay();
}

/* ----------  Phối cảnh ---------- */
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

/* ----------  main ---------- */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Phòng làm việc");
    init();
    glutDisplayFunc(drawRoom);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(specialKeysUp);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}