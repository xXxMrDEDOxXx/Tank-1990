#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bullet.h"

// คลาส Game สำหรับควบคุมการเล่นเกมทั้งหมด
class Game {
private:
    Map แผนที่;                     // แผนที่ของเกม
    Player ผู้เล่น;                 // ผู้เล่น (รถถังคันของผู้เล่น)
    std::vector<Tank*> ศัตรูทั้งหมด; // รายชื่อศัตรูทั้งหมด (Enemy และ Boss) ใช้ Tank* เพื่อ polymorphism
    std::vector<Bullet> กระสุนทั้งหมด; // รายชื่อกระสุนทั้งหมดในเกม
    int ด่านปัจจุบัน;               // หมายเลขด่านปัจจุบัน (1-3)
    bool จบเกม;                    // สถานะว่าเกมจบแล้วหรือไม่
public:
    Game();
    ~Game();
    // เริ่มเกม (เล่นทุกด่านจนจบหรือจนผู้เล่นตาย)
    void run();
private:
    // ฟังก์ชันช่วยในการสร้างศัตรู
    void addEnemy(int x, int y);
    void addBoss(int x, int y);
    // ลบศัตรูทั้งหมด (เรียกตอนจบด่านหรือจบเกม เพื่อคืนหน่วยความจำ)
    void clearEnemies();
    // โหลดข้อมูลและตั้งค่าใหม่สำหรับด่านที่กำหนด
    void loadLevel(int level);
    // วาดสถานะปัจจุบันของเกม (แผนที่, รถถัง, กระสุน) ลงบนหน้าจอ
    void draw();
};

#endif
