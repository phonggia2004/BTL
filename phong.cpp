#include "GL/glut.h"
#include <math.h>
#include <cstdio> // Thêm để debug
#include "Table.h"
#include "ComputerMonitor.h"
#include "Keyboard.h"
#include "computercase.h"
#include "mouse.h"
#include "DongHo.h"
#include "dieuhoa.h"
#include "Bookshelf.h"
#include "desklamp.h"
#include "carpet.h"
#include "chaucay.h"
#include "tudungdo.h"
#include "kedo.h"
#include "car.h"
#include "window.h"
#include "door.h"
#include "WorkChair.h"
#include "Printer.h"
#include "NotebookPen.h"
#include "TrashBin.h"
#include "bang.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Wallboard bang;
Table myTable1;
Table myTable2;
TrashBin myTrashBin;
NotebookPen myNotebookPen;
WorkChair myChair;
Printer myPrinter;
AirConditioner myAC;
Bookshelf myBookshelf;
DeskLamp myLamp;
Shelf myShelf;
Door myDoor;
Car car1;
Car car2;
Car car3;
Car car4;
Car car5;
Car car6;


/* ----------  Biến cửa sổ (extern từ Window.cpp)  ---------- */

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
bool lightOn = true;               // Trạng thái đèn chính
const float windowLightX = 0.0f, windowLightY = 2.5f, windowLightZ = 4.9f;
bool windowLightOn = true;

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
    glEnable(GL_LIGHT2); // Đèn bàn

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

    GLfloat windowLight_position[] = { windowLightX, windowLightY, windowLightZ, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, windowLight_position);
    if (windowLightOn) {
        GLfloat ambient1[] = { 0.2f, 0.2f, 0.25f, 1.0f }; // Ánh sáng môi trường rất nhẹ
        GLfloat diffuse1[] = { 0.7f, 0.7f, 0.55f, 1.0f }; // Ánh sáng khuếch tán dịu, trắng ấm
        GLfloat specular1[] = { 0.5f, 0.5f, 0.3f, 1.0f }; // Ánh sáng phản xạ yếu
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.8f); // Hơi giảm cường độ cơ bản
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1f);   // Tăng suy giảm tuyến tính
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.02f); // Tăng suy giảm bậc hai
        glEnable(GL_LIGHT1);
    }
    else {
        GLfloat zero1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT1, GL_AMBIENT, zero1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, zero1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, zero1);
        glDisable(GL_LIGHT1);
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
    if (keyStates['w'] || keyStates['W']) {
        cameraX += dirXxz * moveSpeed; cameraZ += dirZxz * moveSpeed;
    }
    if (keyStates['s'] || keyStates['S']) {
        cameraX -= dirXxz * moveSpeed; cameraZ -= dirZxz * moveSpeed;
    }

    // Di chuyển trái/phải (A/D)
    if (keyStates['a'] || keyStates['A']) {
        cameraX -= dirZxz * moveSpeed; cameraZ += dirXxz * moveSpeed;
    }
    if (keyStates['d'] || keyStates['D']) {
        cameraX += dirZxz * moveSpeed; cameraZ -= dirXxz * moveSpeed;
    }

    // Di chuyển lên/xuống (Q/E)
    if (keyStates['q'] || keyStates['Q'])
        cameraY += upDownSpeed;
    if (keyStates['e'] || keyStates['E'])
        cameraY -= upDownSpeed;

    // Giới hạn độ cao camera để không đi xuyên sàn hoặc trần
    if (cameraY < 0.5f) cameraY = 0.5f;
   /* if (cameraY > 4.5f) cameraY = 4.5f;*/

    if (cameraX < -4.5f) cameraX = -4.5f;  // hơi nhỏ hơn 5 để không xuyên tường
    if (cameraX > 4.5f) cameraX = 4.5f;
    if (cameraZ < -4.5f) cameraZ = -4.5f;
    if (cameraZ > 4.5f) cameraZ = 4.5f;

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
    //glColor3f(0.7, 0.9, 0.9);
    //glBegin(GL_QUADS);
    //glNormal3f(0, -1, 0);
    //glVertex3f(-5, 5, -5); glVertex3f(-5, 5, 5);
    //glVertex3f(5, 5, 5);   glVertex3f(5, 5, -5);
    //glEnd();

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

    glPushMatrix();
    myDoor.setPosition(0.0f, 0.0f, -5.0f); // Đặt ở tường trước
    myDoor.setScale(2.0f, 1.6f, 0.1f); // Kích thước: rộng 1m, cao 2m, dày 0.1m
    myDoor.setColor(0.6f, 0.3f, 0.1f); // Màu gỗ
    myDoor.setHandleColor(0.7f, 0.7f, 0.7f); // Màu tay nắm bạc
    myDoor.draw();
    glPopMatrix();

    drawLightBulb(); // vẽ bóng đèn

    glPushMatrix();
    myTable1.setPosition(4.35f, 0.0f, -2.0f);
    myTable1.setScale(0.8f, 1.0f, 0.6f);
    myTable1.setTopColor(0.7f, 0.4f, 0.1f);
    myTable1.setLegColor(0.5f, 0.25f, 0.1f);
    myTable1.setRotation(90.0f);
    myTable1.draw();
    glPopMatrix();

    // Vẽ đồng hồ
    glPushMatrix();
    drawClock(4.9f, 4.0f, 3.5f, 0.4f);
    glPopMatrix();

    //Vẽ bảng
    glPushMatrix();
    bang.setPosition(-5.0f, 2.0f, 0.0f); // Đặt bảng trên tường phía sau (gần tường z = -4)
    bang.setScale(3.0f, 3.0f, 3.0f); // Kích thước mặc định
    bang.setRotation(0.0f, 90, 0.0f); // Không xoay
    bang.setBoardColor(1.0f, 1.0f, 1.0f); // Màu trắng cho mặt bảng
    bang.setFrameColor(0.5f, 0.3f, 0.1f); // Màu nâu cho khung
    bang.draw();
    glPopMatrix();

    // Vẽ màn hình
    glPushMatrix();
    glTranslatef(4.7f, 1.69f, -2.0f);
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
    drawComputerMonitor();
    glPopMatrix();

    // Vẽ bàn phím
    glPushMatrix();
    drawKeyboard(4.2f, 1.1f, -2.0f, 270.0f);
    glPopMatrix();

    // Vẽ chuột
    glPushMatrix();
    drawMouse(4.2f, 1.1f, -1.5f, 270.0f);
    glPopMatrix();

    // Vẽ case
    glPushMatrix();
    drawComputerCase(4.2f, 0.25f, -2.65f, 270.0f);
    glPopMatrix();

    // Vẽ đèn bàn
    glPushMatrix();
    myLamp.setPosition(4.7f, 1.1f, -1.2f);
    myLamp.setLampColor(1.0f, 0.8f, 0.2f);
    myLamp.draw();
    glPopMatrix();

  
    glPushMatrix();
    myChair.setPosition(3.0f, 0.0f, -2.0f); // Đặt gần bàn làm việc
    myChair.setScale(1.0f, 1.0f, 1.0f); // Kích thước mặc định
    myChair.setRotation(0.0f, 90.0f, 0.0f); // Xoay 90 độ để hướng vào bàn
    myChair.setSeatColor(0.2f, 0.2f, 0.2f); // Màu đen cho đệm và lưng
    myChair.setFrameColor(0.5f, 0.5f, 0.5f); // Màu xám cho khung và chân
    myChair.draw();
    glPopMatrix();

    // Vẽ bàn thứ hai
    glPushMatrix();
    myTable2.setPosition(4.35f, 0.0f, 0.5f);
    myTable2.setScale(0.8f, 1.0f, 0.6f);
    myTable2.setTopColor(0.7f, 0.4f, 0.1f);
    myTable2.setLegColor(0.5f, 0.25f, 0.1f);
    myTable2.setRotation(90.0f);
    myTable2.draw();
    glPopMatrix();

    glPushMatrix();
    myTrashBin.setPosition(4.2f, 0.0f, 2.0f); // Đặt thùng rác ở góc phòng
    myTrashBin.setScale(2.0f, 1.3f, 2.0f); // Kích thước mặc định
    myTrashBin.setRotation(0.0f, 0.0f, 0.0f); // Không xoay
    myTrashBin.setBodyColor(0.5f, 0.5f, 0.5f); // Màu xám cho thân thùng
    myTrashBin.setLidColor(0.0f, 0.0f, 0.0f); // Màu đen cho nắp thùng
    myTrashBin.draw();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    myPrinter.setPosition(4.6f, 1.11f, -0.25f); // Đặt máy in trên bàn hoặc gần bàn làm việc
    myPrinter.setScale(1.0f, 1.0f, 1.0f); // Kích thước mặc định
    myPrinter.setRotation(0.0f, 90.0f, 0.0f); // Xoay 45 độ để giống góc nhìn trong ảnh
    myPrinter.setBodyColor(0.9f, 0.9f, 0.9f); // Màu trắng cho phần thân dưới
    myPrinter.setTopColor(0.3f, 0.3f, 0.3f); // Màu xám đậm cho phần trên
    myPrinter.setTrayColor(0.0f, 0.0f, 0.0f); // Màu trắng cho khay giấy
    myPrinter.setOutputColor(0.2f, 0.2f, 0.2f); // Màu xám đậm cho khe đầu ra
    myPrinter.setButtonColor(0.1f, 0.1f, 0.1f); // Màu xám rất đậm cho nút
    myPrinter.draw();
    glPopMatrix();

    glPushMatrix();
    myNotebookPen.setPosition(4.3f, 1.11f, 1.0f); // Đặt trên bàn làm việc
    myNotebookPen.setScale(1.0f, 1.0f, 1.0f); // Kích thước mặc định
    myNotebookPen.setRotation(0.0f, 45.0f, 0.0f); // Xoay 45 độ để dễ nhìn
    myNotebookPen.setPageColor(1.0f, 1.0f, 1.0f); // Màu trắng cho trang giấy
    myNotebookPen.setCoverColor(0.0f, 0.0f, 0.5f); // Màu xanh đậm cho bìa
    myNotebookPen.setPenColor(0.0f, 0.0f, 0.0f); // Màu đen cho bút
    myNotebookPen.draw();
    glPopMatrix();

    // Vẽ điều hòa
    glPushMatrix();
    glTranslatef(0.0f, 4.5f, 4.9f);  // vị trí gần tường trước
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f); 
    myAC.setSize(2.0f,0.5f,0.5f);
    myAC.setBodyColor(1.0f, 1.0f, 1.0f);// quay ngược lại để mặt trước quay vào phòng
    myAC.setVentColor(0.3f, 0.3f, 0.3f);
    myAC.draw();
    glPopMatrix();

    // Vẽ tủ sách
    glPushMatrix();
    myBookshelf.setPosition(3.32f, 0.02f, -4.7f);
    myBookshelf.setSize(1.2f, 2.5f, 0.4f);
    myBookshelf.setColor(0.6f, 0.3f, 0.1f);
    myBookshelf.draw();
    glPopMatrix();

    //Vẽ thảm
    glPushMatrix();
    glTranslatef(1.2f, 0.1f, -1.2f);
    drawCarpet(-3.0f, -2.0f, 3.0f, 6.0f); // width = 2.0 (ngắn theo Z), depth = 4.0 (dài theo X)
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0f, 1.5f, 4.5f);
    glRotatef(180, 1.0f, 0.0f, 0.0f);// Góc dưới bên trái phòng
    drawWardrobe();
    glPopMatrix();
    //vẽ kệ
    glPushMatrix();
    glTranslatef(-4.0f, 0.1f, 4.5f);  // dịch kệ sang phải 1 đơn vị
    glRotatef(180, 0, 1, 0 );          // xoay 30 độ quanh trục Y
    myShelf.draw();
    glPopMatrix();

    //Vẽ ô tô trên kệ
    glPushMatrix();
    // Dịch chuyển và xoay xe ngoài class
    glTranslatef(-4.3f,0.3f,4.5f);
    glRotatef(45, 0, 1, 0);
    glScalef(0.2f, 0.1f, 0.2f);
    car1.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.4f, 0.3f, 4.5f);
    glRotatef(39, 0, 1, 0);
    glScalef(0.2f, 0.1f, 0.2f);
    car2.setColor(0.0f, 1.0f, 0.0f);
    car2.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.4f, 1.3f, 4.5f);
    glRotatef(45, 0, 1, 0);
    glScalef(0.2f, 0.1f, 0.2f);
    car3.setColor(1.0f, 1.0f, 0.0f);
    car3.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.3f, 1.3f, 4.5f);
    glRotatef(45, 0, 1, 0);
    glScalef(0.2f, 0.1f, 0.2f);
    car4.setColor(1.0f, 0.5f, 0.0f);
    car4.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0f, 2.3f, 4.5f);
    glRotatef(0, 0, 0, 1);
    glScalef(0.4f, 0.2f, 0.4f);
    car5.setColor(0.6f, 0.0f, 0.6f);
    car5.draw();
    glPopMatrix();


    //Vẽ cây
    glPushMatrix();
    glTranslatef(-4.5f, -0.2f, -4.5f); // Góc dưới bên trái phòng
    drawPlantPot();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.5f, -0.2f, -4.5f); // Góc dưới bên trái phòng
    drawPlantPot();
    glPopMatrix();

    glPushMatrix();
    Window window;
    window.draw();
    glPopMatrix();


    glutSwapBuffers();
}

void printControls() {
    printf("Hướng dẫn điều khiển:\n");
    printf("  W, A, S, D : Di chuyển camera\n");
    printf("  Q, E       : Thay đổi chiều cao\n");
    printf("  L          : Bật/tắt đèn chính\n");
    printf("  K          : Bật/tắt điều hòa\n");
    printf("  B          : Bật/tắt đèn bàn\n");
    printf("  N          : Bật/tắt ánh sáng cửa sổ\n");
    printf("  Phím mũi tên : Xoay camera\n");
    printf("\n");
}
/* ----------  Điều khiển phím (WASD + QE + L + K + B) ---------- */
void keyboard(unsigned char key, int x, int y) {
    // Ghi nhận phím được nhấn
    keyStates[key] = true;

    // Xử lý các phím đặc biệt không cần liên tục
    switch (key) {
    case 'l': case 'L': // Bật/tắt đèn chính
        lightOn = !lightOn;
        break;

    case 'k': case 'K': // Bật/tắt điều hòa
        if (myAC.getState()) myAC.turnOff();
        else myAC.turnOn();
        break;

    case 'b': case 'B': // Bật/tắt đèn bàn
        myLamp.setLightState(!myLamp.getLightState());
        glutPostRedisplay();
        break;
    case 'n': case 'N': // Bật/tắt ánh sáng cửa sổ
        windowLightOn = !windowLightOn;
        glutPostRedisplay();
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
    printControls();
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