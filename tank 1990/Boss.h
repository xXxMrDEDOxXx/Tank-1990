#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

// คลาส Boss สืบทอดจาก Enemy
// เป็นศัตรูบอสในด่านสุดท้าย ยิงแรงกว่าและทนทานกว่า
class Boss : public Enemy {
public:
    // กำหนดค่าเริ่มต้นให้ Boss: พลังชีวิตมากกว่า (เช่น 3), พลังกระสุนแรงกว่า (2), สัญลักษณ์ 'B'
    Boss(int startX, int startY);
    // override ฟังก์ชัน AI สำหรับบอส
    void updateAI(Map &map, std::vector<Tank*> &tanks, std::vector<Bullet> &bullets) override;
};

#endif
