#include "Boss.h"
#include "Map.h"
#include "Bullet.h"
#include <cstdlib>

// กำหนดค่าเริ่มต้นให้บอส (ใช้ Enemy constructor แล้วแก้ไขค่าพลังชีวิต/พลังกระสุน/สัญลักษณ์)
Boss::Boss(int startX, int startY)
    : Enemy(startX, startY) {
    พลังชีวิต = 15;      // เพิ่มพลังชีวิตให้บอสมากกว่าปกติ
    พลังกระสุน = 2;     // กระสุนบอสแรงกว่า (damage = 2)
    ตัวอักษร = 'B';     // ใช้ตัว 'B' แทนสัญลักษณ์บอส
}

// ฟังก์ชัน AI ของบอส: คล้าย Enemy แต่ยิงบ่อยและรุนแรงกว่า
void Boss::updateAI(Map &map, std::vector<Tank*> &tanks, std::vector<Bullet> &bullets) {
    // เปลี่ยนทิศทางเป็นค่าใหม่แบบสุ่มบางครั้ง (เหมือน Enemy)
    if (rand() % 5 == 0) { // ~20% เปลี่ยนทิศทาง
        int d = rand() % 4;
        switch(d) {
        case 0: ทิศทางX = 0;  ทิศทางY = -1; break;
        case 1: ทิศทางX = 0;  ทิศทางY = 1; break;
        case 2: ทิศทางX = -1; ทิศทางY = 0; break;
        case 3: ทิศทางX = 1;  ทิศทางY = 0; break;
        }
    }
    // เคลื่อนที่ไปหนึ่งก้าวในทิศทางปัจจุบัน
    move(ทิศทางX, ทิศทางY, map, tanks);
    // ยิงกระสุนแบบสุ่ม แต่ถี่กว่า Enemy (เช่น ~10% ต่อรอบ)
    if (rand() % 10 == 0) { // 1 ใน 10 โอกาส
        Bullet b(ตำแหน่งX, ตำแหน่งY, ทิศทางX, ทิศทางY, พลังกระสุน, false);
        bullets.push_back(b);
    }
}
