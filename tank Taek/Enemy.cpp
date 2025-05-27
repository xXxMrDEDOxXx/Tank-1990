#include "Enemy.h"
#include "Map.h"
#include "Bullet.h"
#include <cstdlib>   // สำหรับ rand()

// กำหนดค่าเริ่มต้นให้ Enemy
Enemy::Enemy(int startX, int startY)
    : Tank(startX, startY, 3, 1, 'E'), ทิศทางX(0), ทิศทางY(0) {
    // ตั้งค่าทิศทางเริ่มต้นแบบสุ่ม
    int d = rand() % 4;
    switch(d) {
    case 0: ทิศทางX = 0;  ทิศทางY = -1; break; // ขึ้น
    case 1: ทิศทางX = 0;  ทิศทางY = 1; break;  // ลง
    case 2: ทิศทางX = -1; ทิศทางY = 0; break;  // ซ้าย
    case 3: ทิศทางX = 1;  ทิศทางY = 0; break;  // ขวา
    }
}

// ฟังก์ชัน AI ของศัตรู: เดินสุ่มและยิงสุ่ม
void Enemy::updateAI(Map &map, std::vector<Tank*> &tanks, std::vector<Bullet> &bullets) {
    // เปลี่ยนทิศทางการเดินเป็นค่าใหม่แบบสุ่มบางครั้ง (เช่น 20% ที่จะเปลี่ยนทิศทาง)
    if (rand() % 5 == 0) { // 1 ใน 5 โอกาส (~20%)
        int d = rand() % 4;
        switch(d) {
        case 0: ทิศทางX = 0;  ทิศทางY = -1; break;
        case 1: ทิศทางX = 0;  ทิศทางY = 1; break;
        case 2: ทิศทางX = -1; ทิศทางY = 0; break;
        case 3: ทิศทางX = 1;  ทิศทางY = 0; break;
        }
    }
    // พยายามขยับหนึ่งก้าวในทิศทางปัจจุบัน
    move(ทิศทางX, ทิศทางY, map, tanks);
    // ยิงกระสุนแบบสุ่ม (เช่น โอกาส ~5% ต่อรอบ)
    if (rand() % 5 == 0) { // 1 ใน 5 โอกาส
        // สร้างกระสุน (เป็นกระสุนฝั่งศัตรู: เป็นมิตร = false)
        Bullet b(ตำแหน่งX, ตำแหน่งY, ทิศทางX, ทิศทางY, พลังกระสุน, false);
        bullets.push_back(b);
    }
}
