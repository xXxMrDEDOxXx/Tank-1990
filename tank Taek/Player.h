#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"

// คลาส Player สืบทอดจาก Tank (คลาสแม่)
// ใช้แทนผู้เล่นที่ควบคุมโดยคนเล่น
class Player : public Tank {
private:
    int ทิศทางX; // ทิศทางล่าสุดที่ผู้เล่นหัน (แกน X)
    int ทิศทางY; // ทิศทางล่าสุดที่ผู้เล่นหัน (แกน Y)
public:
    // Constructor: กำหนดตำแหน่งเริ่มต้น, พลังชีวิต=3, พลังกระสุน=1, สัญลักษณ์ 'P'
    Player(int startX, int startY);
    // Setter และ Getter สำหรับทิศทางที่หันของผู้เล่น
    void setDirection(int dx, int dy) {
        ทิศทางX = dx;
        ทิศทางY = dy;
    }
    int getDirX() const { return ทิศทางX; }
    int getDirY() const { return ทิศทางY; }
};

#endif
