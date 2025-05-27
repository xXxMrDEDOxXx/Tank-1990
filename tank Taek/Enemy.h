#ifndef ENEMY_H
#define ENEMY_H

#include "Tank.h"

// คลาส Enemy สืบทอดจาก Tank
// ใช้แทนศัตรูทั่วไปที่ควบคุมด้วยคอมพิวเตอร์ (AI)
class Enemy : public Tank {
protected:
    int ทิศทางX; // ทิศทางปัจจุบันที่ศัตรูกำลังเคลื่อนที่ (แกน X)
    int ทิศทางY; // ทิศทางปัจจุบันที่ศัตรูกำลังเคลื่อนที่ (แกน Y)
public:
    // กำหนดค่าเริ่มต้นให้ Enemy: พลังชีวิต=1, พลังกระสุน=1, สัญลักษณ์ 'E'
    Enemy(int startX, int startY);
    // override ฟังก์ชัน updateAI จาก Tank
    // การเคลื่อนที่และยิงแบบสุ่มของศัตรู
    void updateAI(Map &map, std::vector<Tank*> &tanks, std::vector<Bullet> &bullets) override;
};

#endif
