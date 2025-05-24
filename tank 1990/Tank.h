#ifndef TANK_H
#define TANK_H

#include <vector>
#include <iostream>
#include <string>
class Map;       // forward declare Map (used in method parameters)
class Bullet;    // forward declare Bullet
class Tank {
protected:
    int ตำแหน่งX;         // ตำแหน่งแกน X ของรถถัง
    int ตำแหน่งY;         // ตำแหน่งแกน Y ของรถถัง
    int พลังชีวิต;        // พลังชีวิตของรถถัง (HP ของรถถัง)
    int พลังกระสุน;       // ความแรงของกระสุนที่ยิงออก
    char ตัวอักษร;        // ตัวอักษรที่ใช้แทนรถถังบนแผนที่
public:
    Tank(int x, int y, int hp, int bulletPower, char symbol)
        : ตำแหน่งX(x), ตำแหน่งY(y), พลังชีวิต(hp), พลังกระสุน(bulletPower), ตัวอักษร(symbol) {}
    virtual ~Tank() {}   // destructor ควรเป็น virtual (เพื่อให้ลบถูกชนิดเมื่อ delete ผ่าน pointer คลาสแม่)

    // Getter สำหรับค่าต่าง ๆ (เป็นการ encapsulation)
    int getX() const { return ตำแหน่งX; }
    int getY() const { return ตำแหน่งY; }
    int getHP() const { return พลังชีวิต; }
    char getSymbol() const { return ตัวอักษร; }
    int getBulletPower() const { return พลังกระสุน; }

    // ลดพลังชีวิตเมื่อโดนยิง (damage)
    void ลดพลังชีวิต(int damage) {
        พลังชีวิต -= damage;
        if (พลังชีวิต < 0) พลังชีวิต = 0;
    }
    bool isDestroyed() const {
        return พลังชีวิต <= 0;
    }

    // ฟังก์ชันเคลื่อนที่รถถัง 1 ก้าว (dx, dy) ถ้าไม่ชนกำแพงหรือตัวอื่น
    bool move(int dx, int dy, Map &map, const std::vector<Tank*> &tanks);

    // ฟังก์ชัน virtual สำหรับ AI ของศัตรู (ผู้เล่นจะไม่ override ฟังก์ชันนี้)
    // ใช้ polymorphism เพื่อให้ Enemy/Boss มีพฤติกรรมต่างกัน
    virtual void updateAI(Map &map, std::vector<Tank*> &tanks, std::vector<Bullet> &bullets) {
        // ค่า default ไม่ทำอะไร (สำหรับ Player ซึ่งควบคุมด้วยผู้เล่นเอง)
    }
};

#endif
