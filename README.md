[[English]](README_en.md)

# **FoCus - README**  
### Môn học: Lập trình nâng cao (INT2215_2 2425)

---

## **Thông tin cá nhân**

- **Họ và tên:** Nguyễn Ngọc Quý - K69I-IT2  
- **Mã sinh viên:** 24020290  
- **Bài tập lớn:** FoCus - Một trò chơi nhịp điệu hành động lấy cảm hứng từ *Osu! Mania* và *Friday Night Funkin’*

---

## **Giới thiệu**

**FoCus** là một trò chơi nhịp điệu hành động. Nhiệm vụ của người chơi là hoàn thành bản nhạc với số điểm cao nhất bằng cách nhấn các phím theo đúng nhịp điệu và thời điểm.  

👉 *Video thử nghiệm game:*

---

## **Mục lục**

- [0. Cách tải game](#0-cách-tải-game)  
  - [a. Cách 1: Không bao gồm mã nguồn](#a-cách-1-không-bao-gồm-mã-nguồn)  
  - [b. Cách 2: Bao gồm mã nguồn và có thể biên dịch](#b-cách-2-bao-gồm-mã-nguồn-và-có-thể-biên-dịch)  
- [1. Bắt đầu game](#1-bắt-đầu-game)  
- [2. Chọn level](#2-chọn-level)  
- [3. Cách chơi](#3-cách-chơi)  
- [4. Kết thúc level](#4-kết-thúc-level)  
- [5. Source code](#5-source-code)  
- [6. Credits](#6-credits)  

---

## 0. Cách tải game

### a. Cách 1: Không bao gồm mã nguồn

- Tải bản `.zip` tại: [FoCus Release](https://github.com/Scopen86/FoCus/releases/tag/published)  
- Cách này tiết kiệm thời gian và dung lượng tải.  
- Sau khi tải, giải nén và chạy `FoCus.exe` để chơi.  

### b. Cách 2: Bao gồm mã nguồn và có thể biên dịch

#### **Bước 1:** Clone repo về máy  
- Sử dụng lệnh:  
  ```
  git clone https://github.com/Scopen86/FoCus.git
  ```
  hoặc chọn **Code → Download ZIP**

![Download](resources/preview/download.png)

> Mã nguồn nằm trong thư mục `src/`, file header trong `include/`

#### **Bước 2:** Cài đặt MinGW và GNU Make

Cài qua [Chocolatey](https://chocolatey.org/install), sau đó mở `cmd` và chạy:

```
choco install mingw -y
choco install make -y
```

#### **Bước 3:** Mở terminal tại thư mục chứa Makefile và gõ:

```
make
```

#### **Bước 4:** Chạy file `FoCus.exe` để bắt đầu chơi.

---

## 1. Bắt đầu game

- Chờ game khởi động, sau đó click vào nút **Bắt đầu** (icon) để vào trò chơi.

---

## 2. Chọn level

- Game hiện có **2 level** với độ khó khác nhau.  
- Khi di chuột lên một level, level đó sẽ phát sáng.  
- Click chuột để bắt đầu chơi level đã chọn.

---

## 3. Cách chơi

- Sử dụng các phím **D, F, J, K** khi mũi tên rơi chạm đúng vạch ngang.  
- Điểm được tính dựa trên độ chính xác.  
- **Combo** sẽ làm tăng hệ số điểm.

---

## 4. Kết thúc level

- Game hiển thị kết quả: tổng điểm, độ chính xác, và combo cao nhất đạt được.  
- Bạn có thể chọn chơi lại hoặc quay lại menu chính.

---

## 5. Source Code

### Thư mục chính:

- `src/`: Mã nguồn chính  
  - `game.cpp` / `game.hpp`: Logic tổng thể và `main()`  
  - `menu.cpp` / `menu.hpp`: Xử lý các menu  
  - `logic.cpp` / `logic.hpp`: Tính điểm, combo, va chạm  
  - `audio.cpp` / `audio.hpp`: Xử lý âm thanh  
  - `timer.cpp` / `timer.hpp`: Quản lý thời gian  
  - `renderwindow.cpp` / `renderwindow.hpp`: Render đối tượng & text  
  - `entity.hpp`: Định nghĩa các đối tượng game (target, khung,...)

- `include/`: Chứa các file header dùng chung

- `res/`: Tài nguyên game  
  - `textures/`: Hình ảnh đối tượng  
  - `level/`: Dữ liệu level (`targetTimings.txt`, `userScore.txt`, nhạc nền,...)

### Kỹ thuật sử dụng:

- SDL2.0, SDL_Image, SDL_TTF, SDL_Mixer  
- Quản lý thời gian bằng `deltaTime` (không phụ thuộc FPS)  
- Sử dụng class, vector, overloading,...  
- Ghi/đọc file: lưu điểm cao, đọc level  
- Hệ thống menu linh hoạt
- Render hiệu quả hình ảnh, văn bản, và âm thanh

---

## 6. Credits

- Cách quản lý thư mục, cài đặt SDL2 và makefile và một vài phần của các class RenderWindow, Entity, Vector2f trên [tutorial kênh Youtube codergopher](https://www.youtube.com/watch?v=KsG6dJlLBDw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS)

- Hình ảnh: Texture game được tạo trên Paint.NET
- Dựa trên cảm hứng từ: Osu! Mania, Friday Night Funkin  
- Âm nhạc: [Nighthawk22 - Isolation (Official LIMBO Remix)](https://www.youtube.com/watch?v=lNjVd00zKDE)

- File README.md dựa trên: https://github.com/nmhienbn/PVZ-Kaito-NMH-Edition/blob/main/README.md
