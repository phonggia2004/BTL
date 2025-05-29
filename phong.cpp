//#include "GL/glut.h"
//#include <math.h>
//#include "Table.h"
//#include "ComputerMonitor.h"
//#include "Keyboard.h"
//#include "computercase.h"
//#include "mouse.h"
//#include "Window.h"
//#include "DongHo.h"
//
//#ifndef M_PI
//#define M_PI 3.14159265358979323846
//#endif
//
//Table myTable1;
//Table myTable2;
//
///* ----------  Biến cửa sổ (extern từ Window.cpp)  ---------- */
//extern float windowAngle;
//extern bool windowOpening;
//
///* ----------  Camera & Chuyển động  ---------- */
//float cameraX = 0.0f, cameraY = 2.5f, cameraZ = 5.0f;
//float yaw = -90.0f;                 // xoay ngang
//float pitch = 0.0f;                 // xoay dọc
//float dirX, dirY, dirZ;             // hướng nhìn
//const float moveSpeed = 0.05f;
//const float turnSpeed = 1.0f;
//const float upDownSpeed = 0.05f;     // Tốc độ di chuyển lên xuống
//
//// Biến trạng thái phím
//bool keyStates[256] = { false };    // Trạng thái các phím thường
//bool specialKeyStates[256] = { false }; // Trạng thái các phím đặc biệt
//
///* ----------  Ánh sáng  ---------- */
//const float lightX = 0.0f, lightY = 4.8f, lightZ = 0.0f;
//bool  lightOn = true;               // trạng thái đèn (bật/tắt)
//
///* ----------  Hàm tiện ích  ---------- */
//void updateDirection() {
//    dirX = cosf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);
//    dirY = sinf(pitch * M_PI / 180.0f);
//    dirZ = sinf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);
//}
//
///* ----------  Khởi tạo  ---------- */
//void init(void) {
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_LIGHT1);
//    /* Thuộc tính vật liệu & chuẩn hoá pháp tuyến  */
//    glEnable(GL_COLOR_MATERIAL);
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//    glEnable(GL_NORMALIZE);
//    updateDirection();
//}
//
///* ----------  Cập nhật nguồn sáng (tuỳ trạng thái) ---------- */
//void updateLight() {
//    GLfloat light_position[] = { lightX, lightY, lightZ, 1.0f };
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//    if (lightOn) {
//        GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
//        GLfloat diffuse[] = { 1.0f, 1.0f, 0.9f, 1.0f };
//        GLfloat specular[] = { 1.0f, 1.0f, 0.9f, 1.0f };
//        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
//        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
//        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
//        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
//        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);
//        glEnable(GL_LIGHT0);           // Bật đèn
//    }
//    else {
//        GLfloat zero[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//        glLightfv(GL_LIGHT0, GL_AMBIENT, zero);
//        glLightfv(GL_LIGHT0, GL_DIFFUSE, zero);
//        glLightfv(GL_LIGHT0, GL_SPECULAR, zero);
//        glDisable(GL_LIGHT0);          // Tắt đèn
//    }
//}
//
///* ----------  Vẽ bóng đèn  ---------- */
//void drawLightBulb() {
//    glPushAttrib(GL_LIGHTING_BIT);     // Lưu trạng thái ánh sáng
//    glDisable(GL_LIGHTING);            // Vẽ bóng đèn không chịu ảnh hưởng
//    glPushMatrix();
//    glTranslatef(lightX, lightY, lightZ);
//    if (lightOn)
//        glColor3f(1.0f, 1.0f, 0.6f);   // vàng sáng khi bật
//    else
//        glColor3f(0.4f, 0.4f, 0.4f);   // xám khi tắt
//    glutSolidSphere(0.2, 20, 20);
//    glPopMatrix();
//    glPopAttrib();                     // Khôi phục lighting
//}
//
///* ----------  Cập nhật vị trí camera dựa trên phím đang được nhấn ---------- */
//void updateCamera() {
//    float dirXxz = cosf(yaw * M_PI / 180.0f);
//    float dirZxz = sinf(yaw * M_PI / 180.0f);
//
//    // Di chuyển tiến/lùi (W/S)
//    if (keyStates['w'] || keyStates['W'])
//    {
//        cameraX += dirXxz * moveSpeed; cameraZ += dirZxz * moveSpeed;
//    }
//    if (keyStates['s'] || keyStates['S'])
//    {
//        cameraX -= dirXxz * moveSpeed; cameraZ -= dirZxz * moveSpeed;
//    }
//
//    // Di chuyển trái/phải (A/D)
//    if (keyStates['a'] || keyStates['A'])
//    {
//        cameraX -= dirZxz * moveSpeed; cameraZ += dirXxz * moveSpeed;
//    }
//    if (keyStates['d'] || keyStates['D'])
//    {
//        cameraX += dirZxz * moveSpeed; cameraZ -= dirXxz * moveSpeed;
//    }
//
//    // Di chuyển lên/xuống (Q/E)
//    if (keyStates['q'] || keyStates['Q'])
//        cameraY += upDownSpeed;
//    if (keyStates['e'] || keyStates['E'])
//        cameraY -= upDownSpeed;
//
//    // Giới hạn độ cao camera để không đi xuyên sàn hoặc trần
//    if (cameraY < 0.5f) cameraY = 0.5f;
//    if (cameraY > 4.5f) cameraY = 4.5f;
//
//    if (cameraX < -4.5f) cameraX = -4.5f;  // hơi nhỏ hơn 5 để không xuyên tường
//    if (cameraX > 4.5f) cameraX = 4.5f;
//    if (cameraZ < -4.5f) cameraZ = -4.5f;
//    if (cameraZ > 4.5f) cameraZ = 4.5f;
//
//    // Cập nhật góc cửa sổ
//    if (windowOpening && windowAngle < 90.0f)  windowAngle += 1.0f;
//    if (!windowOpening && windowAngle > 0.0f)  windowAngle -= 1.0f;
//
//    // Xoay camera bằng phím mũi tên
//    if (specialKeyStates[GLUT_KEY_LEFT])
//        yaw -= turnSpeed;
//    if (specialKeyStates[GLUT_KEY_RIGHT])
//        yaw += turnSpeed;
//    if (specialKeyStates[GLUT_KEY_UP]) {
//        pitch += turnSpeed;
//        if (pitch > 89) pitch = 89;
//    }
//    if (specialKeyStates[GLUT_KEY_DOWN]) {
//        pitch -= turnSpeed;
//        if (pitch < -89) pitch = -89;
//    }
//
//    updateDirection();
//}
//
///* ----------  Vẽ phòng  ---------- */
//void drawRoom(void) {
//    // Cập nhật vị trí camera dựa trên phím đang được nhấn
//    updateCamera();
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(cameraX, cameraY, cameraZ,
//        cameraX + dirX, cameraY + dirY, cameraZ + dirZ,
//        0.0, 1.0, 0.0);
//    updateLight();   // đặt lại nguồn sáng
//
//    /* --- Sàn --- */
//    glColor3f(0.5, 0.5, 0.5);
//    glBegin(GL_QUADS);
//    glNormal3f(0, 1, 0);
//    glVertex3f(-5, 0, -5); glVertex3f(-5, 0, 5);
//    glVertex3f(5, 0, 5);   glVertex3f(5, 0, -5);
//    glEnd();
//
//    /* --- Trần --- */
//    glColor3f(0.7, 0.9, 0.9);
//    glBegin(GL_QUADS);
//    glNormal3f(0, -1, 0);
//    glVertex3f(-5, 5, -5); glVertex3f(-5, 5, 5);
//    glVertex3f(5, 5, 5);   glVertex3f(5, 5, -5);
//    glEnd();
//
//    /* --- Tường trái --- */
//    glColor3f(1.0, 1.0, 0.9);
//    glBegin(GL_QUADS);
//    glNormal3f(1, 0, 0);
//    glVertex3f(-5, 0, -5); glVertex3f(-5, 5, -5);
//    glVertex3f(-5, 5, 5);  glVertex3f(-5, 0, 5);
//    glEnd();
//
//    /* --- Tường phải --- */
//    glColor3f(0.9, 0.9, 0.9);
//    glBegin(GL_QUADS);
//    glNormal3f(-1, 0, 0);
//    glVertex3f(5, 0, -5);  glVertex3f(5, 5, -5);
//    glVertex3f(5, 5, 5);   glVertex3f(5, 0, 5);
//    glEnd();
//
//    /* --- Tường sau --- */
//    glColor3f(1.0, 1.0, 1.0);
//    glBegin(GL_QUADS);
//    glNormal3f(0, 0, 1);
//    glVertex3f(-5, 0, -5); glVertex3f(-5, 5, -5);
//    glVertex3f(5, 5, -5);  glVertex3f(5, 0, -5);
//    glEnd();
//
//    /* --- Tường trước --- */
//    glColor3f(1.0, 0.95, 0.9);
//    glBegin(GL_QUADS);
//    glNormal3f(0, 0, -1);
//    glVertex3f(-5, 0, 5);  glVertex3f(-5, 5, 5);
//    glVertex3f(5, 5, 5);   glVertex3f(5, 0, 5);
//    glEnd();
//
//    drawLightBulb();// vẽ bóng đèn
//
//    //Vẽ bàn
//    myTable1.setPosition(4.35f, 0.0f, -2.0f);  // Move to right wall (x=4.0)
//    myTable1.setScale(0.8f, 1.0f, 0.6f);      // Make it smaller
//    myTable1.setTopColor(0.7f, 0.4f, 0.1f);
//    myTable1.setLegColor(0.5f, 0.25f, 0.1f);
//    myTable1.setRotation(90.0f);
//
//    // Vẽ đồng hồ ở góc trên bên phải tường nhìn từ cửa sổ
//    drawClock(4.9f, 4.0f, 3.5f, 0.4f);  // Gần tường phải (x=4.9), cao (y=4.0)
//
//    // Trong hàm vẽ:
//    myTable1.draw();
//
//    glPushMatrix();
//    glTranslatef(4.7f, 1.69f, -2.0f);  // nâng lên y=1.0f cho trên mặt bàn
//    glRotatef(270.0f, 0.0f, 1.0f, 0.0f); // xoay màn hình quay mặt vào giữa phòng
//    drawComputerMonitor();
//    glPopMatrix();
//
//    //Vẽ bàn phím và case
//    drawKeyboard(4.2f, 1.1f, -2.0f, 270.0f);
//    drawMouse(4.2f, 1.1f, -1.5f, 270.0f);
//
//    // Vẽ case đặt dưới bàn (bên phải)
//    drawComputerCase(4.2f, 0.25f, -2.65f, 270.0f);
//
//    //Vẽ cửa sổ với mặt trời
//    // ---- vẽ cửa sổ trên tường trái ----
//    float winWidth = 2.5f, winHeight = 1.8f, winThickness = 0.15f;
//    float winY = 1.5f; // Độ cao từ sàn
//
//    float winX = 0.0f, winZ = 4.99f; // Giữa tường trước
//
//    glPushMatrix();
//    glTranslatef(winX, winY, winZ);
//    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);  // Xoay 180° để quay vào trong phòng
//    drawWindow(-winWidth / 2, 0, 0, winWidth, winHeight, winThickness);
//    glPopMatrix();
//
//    // Ánh sáng từ phía trước
//    updateSunLight(winX, winY + winHeight / 2, winZ - 0.2f, windowAngle > 10.0f);
//
//
//    myTable2.setPosition(4.35f, 0.0f, 0.5f);  // Move to right wall (x=4.0)
//    myTable2.setScale(0.8f, 1.0f, 0.6f);      // Make it smaller
//    myTable2.setTopColor(0.7f, 0.4f, 0.1f);
//    myTable2.setLegColor(0.5f, 0.25f, 0.1f);
//    myTable2.setRotation(90.0f);
//    // Trong hàm vẽ:
//    myTable2.draw();
//
//
//    glutSwapBuffers();
//}
//
///* ----------  Điều khiển phím (WASD + QE + L) ---------- */
//void keyboard(unsigned char key, int x, int y) {
//    // Ghi nhận phím được nhấn
//    keyStates[key] = true;
//
//    // Xử lý các phím đặc biệt không cần liên tục
//    switch (key) {
//    case 'l': case 'L':                 // Bật / tắt đèn
//        lightOn = !lightOn;
//        break;
//    case 'o': case 'O':        // bật/tắt mở cửa
//        windowOpening = !windowOpening;
//        break;
//    }
//
//    glutPostRedisplay();
//}
//
///* ----------  Xử lý khi phím được thả ra ---------- */
//void keyboardUp(unsigned char key, int x, int y) {
//    keyStates[key] = false;
//    glutPostRedisplay();
//}
//
///* ----------  Xoay camera bằng phím mũi tên ---------- */
//void specialKeys(int key, int x, int y) {
//    specialKeyStates[key] = true;
//    glutPostRedisplay();
//}
//
///* ----------  Xử lý khi phím đặc biệt được thả ra ---------- */
//void specialKeysUp(int key, int x, int y) {
//    specialKeyStates[key] = false;
//    glutPostRedisplay();
//}
//
///* ----------  Hàm cập nhật liên tục ---------- */
//void idle() {
//    glutPostRedisplay();
//}
//
///* ----------  Phối cảnh ---------- */
//void reshape(int w, int h) {
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(60.0, (float)w / h, 0.1, 100.0);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
///* ----------  main ---------- */
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Phòng làm việc");
//    init();
//    glutDisplayFunc(drawRoom);
//    glutReshapeFunc(reshape);
//    glutKeyboardFunc(keyboard);
//    glutKeyboardUpFunc(keyboardUp);
//    glutSpecialFunc(specialKeys);
//    glutSpecialUpFunc(specialKeysUp);
//    glutIdleFunc(idle);
//    glutDisplayFunc(drawRoom);
//
//    glPushMatrix();
//    glTranslatef(2.4f, 1.8f, -1.9f);
//    glColor3f(1.0f, 0.0f, 0.0f); // màu đỏ để dễ thấy
//    glutSolidCube(0.1);
//    glPopMatrix();
//
//
//    glutMainLoop();
//    return 0;
//}

#include "GL/glut.h"
#include <math.h>
#include "Table.h"
#include "ComputerMonitor.h"
#include "Keyboard.h"
#include "computercase.h"
#include "mouse.h"
#include "Window.h"
#include "DongHo.h"
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
const float lightX = 0.0f, lightY = 4.8f, lightZ = 0.0f; // Nguồn sáng chính (trần)
const float windowLightX = 0.0f, windowLightY = 2.5f, windowLightZ = 4.9f; // Nguồn sáng cửa sổ
const float monitorLightX = 4.7f, monitorLightY = 1.8f, monitorLightZ = -2.0f; // Nguồn sáng màn hình
bool lightOn = true;               // Trạng thái đèn chính
bool windowLightOn = true;         // Trạng thái đèn cửa sổ
bool monitorLightOn = true;        // Trạng thái đèn màn hình

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
    glEnable(GL_LIGHT0); // Đèn chính
    glEnable(GL_LIGHT1); // Đèn cửa sổ
    glEnable(GL_LIGHT2); // Đèn màn hình
    /* Thuộc tính vật liệu & chuẩn hoá pháp tuyến  */
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE);
    updateDirection();
}

/* ----------  Cập nhật nguồn sáng (tuỳ trạng thái) ---------- */
void updateLight() {
    // Nguồn sáng chính (GL_LIGHT0)
    GLfloat light0_position[] = { lightX, lightY, lightZ, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    if (lightOn) {
        GLfloat ambient0[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat diffuse0[] = { 1.0f, 1.0f, 0.9f, 1.0f };
        GLfloat specular0[] = { 1.0f, 1.0f, 0.9f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);
        glEnable(GL_LIGHT0);
    }
    else {
        GLfloat zero0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT, zero0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, zero0);
        glLightfv(GL_LIGHT0, GL_SPECULAR, zero0);
        glDisable(GL_LIGHT0);
    }

    // Nguồn sáng cửa sổ (GL_LIGHT1)
    GLfloat light1_position[] = { windowLightX, windowLightY, windowLightZ, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    if (windowLightOn) {
        GLfloat ambient1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat diffuse1[] = { 0.7f, 0.7f, 1.0f, 1.0f }; // Ánh sáng xanh nhạt như ban ngày
        GLfloat specular1[] = { 0.5f, 0.5f, 0.7f, 1.0f };
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.3f);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1f);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.02f);
        glEnable(GL_LIGHT1);
    }
    else {
        GLfloat zero1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT1, GL_AMBIENT, zero1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, zero1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, zero1);
        glDisable(GL_LIGHT1);
    }

    // Nguồn sáng màn hình (GL_LIGHT2)
    GLfloat light2_position[] = { monitorLightX, monitorLightY, monitorLightZ, 1.0f };
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    if (monitorLightOn) {
        GLfloat ambient2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat diffuse2[] = { 0.9f, 0.6f, 0.6f, 1.0f }; // Ánh sáng ấm áp
        GLfloat specular2[] = { 0.7f, 0.4f, 0.4f, 1.0f };
        glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
        glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.4f);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.08f);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.01f);
        glEnable(GL_LIGHT2);
    }
    else {
        GLfloat zero2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT2, GL_AMBIENT, zero2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, zero2);
        glLightfv(GL_LIGHT2, GL_SPECULAR, zero2);
        glDisable(GL_LIGHT2);
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

    drawLightBulb(); // vẽ bóng đèn

    // Vẽ bàn
    myTable1.setPosition(4.35f, 0.0f, -2.0f);  // Move to right wall (x=4.0)
    myTable1.setScale(0.8f, 1.0f, 0.6f);      // Make it smaller
    myTable1.setTopColor(0.7f, 0.4f, 0.1f);
    myTable1.setLegColor(0.5f, 0.25f, 0.1f);
    myTable1.setRotation(90.0f);

    // Vẽ đồng hồ ở góc trên bên phải tường nhìn từ cửa sổ
    drawClock(4.9f, 4.0f, 3.5f, 0.4f);  // Gần tường phải (x=4.9), cao (y=4.0)

    // Trong hàm vẽ:
    myTable1.draw();

    glPushMatrix();
    glTranslatef(4.7f, 1.69f, -2.0f);  // nâng lên y=1.0f cho trên mặt bàn
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f); // xoay màn hình quay mặt vào giữa phòng
    drawComputerMonitor();
    glPopMatrix();

    // Vẽ bàn phím và chuột
    drawKeyboard(4.2f, 1.1f, -2.0f, 270.0f);
    drawMouse(4.2f, 1.1f, -1.5f, 270.0f);

    // Vẽ case đặt dưới bàn (bên phải)
    drawComputerCase(4.2f, 0.25f, -2.65f, 270.0f);

    // Vẽ cửa sổ với mặt trời
    // ---- vẽ cửa sổ trên tường trước ----
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

    // Vẽ bàn thứ hai
    myTable2.setPosition(4.35f, 0.0f, 0.5f);  // Move to right wall (x=4.0)
    myTable2.setScale(0.8f, 1.0f, 0.6f);      // Make it smaller
    myTable2.setTopColor(0.7f, 0.4f, 0.1f);
    myTable2.setLegColor(0.5f, 0.25f, 0.1f);
    myTable2.setRotation(90.0f);
    myTable2.draw();

    // Vẽ điều hòa
    myAC.setPosition(0.0f, 4.5f, 4.9f); // Đặt ở giữa tường trước, gần trần
    myAC.setSize(1.2f, 0.4f, 0.2f);     // Kích thước điều hòa
    myAC.setBodyColor(0.9f, 0.9f, 0.9f); // Màu trắng xám
    myAC.setVentColor(0.3f, 0.3f, 0.3f); // Màu xám đậm cho khe gió
    myAC.draw();

    // Vẽ ghế làm việc
    myChair.setPosition(4.35f, 0.7f, -2.5f); // Đặt đối diện bàn và màn hình
    myChair.setSize(0.5f, 0.1f, 0.5f);      // Kích thước mặt ngồi
    myChair.setBackHeight(0.5f);             // Chiều cao lưng ghế
    myChair.setBodyColor(0.2f, 0.2f, 0.2f); // Màu xám đậm
    myChair.setLegColor(0.4f, 0.4f, 0.4f);  // Màu xám sáng
    myChair.updateRotation();                // Cập nhật xoay
    myChair.draw();

    // Vẽ tủ sách
    myBookshelf.setPosition(3.35f, 0.0f, -4.3f); // Điều chỉnh vị trí để mép phải sát tường
    myBookshelf.setSize(3.3f, 1.7f, 0.4f);      // Rộng 1/3 tường, cao 1/3 tường
    myBookshelf.setColor(0.6f, 0.3f, 0.1f);     // Màu gỗ nâu
    myBookshelf.draw();

    glutSwapBuffers();
}

/* ----------  Điều khiển phím (WASD + QE + L + K + C + P + M) ---------- */
void keyboard(unsigned char key, int x, int y) {
    // Ghi nhận phím được nhấn
    keyStates[key] = true;

    // Xử lý các phím đặc biệt không cần liên tục
    switch (key) {
    case 'l': case 'L': // Bật/tắt đèn chính
        lightOn = !lightOn;
        break;
    case 'o': case 'O': // Bật/tắt mở cửa
        windowOpening = !windowOpening;
        break;
    case 'k': case 'K': // Bật/tắt điều hòa
        if (myAC.getState()) myAC.turnOff();
        else myAC.turnOn();
        break;
    case 'c': case 'C': // Bật/tắt xoay ghế
        myChair.toggleRotate();
        break;
    case 'p': case 'P': // Bật/tắt đèn cửa sổ
        windowLightOn = !windowLightOn;
        break;
    case 'm': case 'M': // Bật/tắt đèn màn hình
        monitorLightOn = !monitorLightOn;
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