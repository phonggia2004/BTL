#ifndef WINDOW_H
#define WINDOW_H

// Vẽ cửa sổ với các tham số
void drawWindow(float x, float y, float z, float w, float h, float thickness);

// Cập nhật ánh sáng mặt trời
void updateSunLight(float cx, float cy, float cz, bool enable);

// Cập nhật trạng thái cửa sổ
void updateWindowState(float deltaTime);

// Mở/đóng cửa sổ
void toggleWindow();

// Kiểm tra xem cửa sổ đang mở hay không
bool isWindowOpen();

#endif // WINDOW_H
