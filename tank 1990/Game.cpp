#include "Game.h"
#include <iostream>
#include <conio.h>   // สำหรับ _kbhit() และ _getch()
#include <windows.h> // สำหรับ Sleep()
#include <cstdlib>

// Constructor: ตั้งค่าเริ่มต้น
Game::Game()
    : ผู้เล่น(0, 0)  // กำหนดค่าเริ่มต้น (จะถูกแก้ไขใน loadLevel)
{
    std::srand((unsigned) std::time(NULL)); // ตั้ง seed สำหรับ rand()
    ด่านปัจจุบัน = 1;
    จบเกม = false;
}

// Destructor: ลบหน่วยความจำที่จัดให้ศัตรู (ถ้ามีเหลือ)
Game::~Game() {
    clearEnemies();
}

// เพิ่มศัตรูทั่วไป (Enemy) ที่ตำแหน่ง (x,y)
void Game::addEnemy(int x, int y) {
    Tank* e = new Enemy(x, y);
    ศัตรูทั้งหมด.push_back(e);
}

// เพิ่มบอส (Boss) ที่ตำแหน่ง (x,y)
void Game::addBoss(int x, int y) {
    Tank* b = new Boss(x, y);
    ศัตรูทั้งหมด.push_back(b);
}

// ลบศัตรูทั้งหมดและคืนหน่วยความจำ
void Game::clearEnemies() {
    for (Tank* t : ศัตรูทั้งหมด) {
        delete t;
    }
    ศัตรูทั้งหมด.clear();
}

// เตรียมโหลดข้อมูลสำหรับด่านใหม่
void Game::loadLevel(int level) {
    // ลบศัตรูและกระสุนจากด่านก่อนหน้า
    clearEnemies();
    กระสุนทั้งหมด.clear();
    // สร้างแผนที่ใหม่สำหรับด่านนี้
    แผนที่.generate(level);
    // กำหนดตำแหน่งเริ่มต้นของผู้เล่น (กลางล่างของแผนที่)
    int startX = แผนที่.getWidth() / 2;
    int startY = แผนที่.getHeight() - 2;
    ผู้เล่น = Player(startX, startY);
    // สร้างศัตรูตามด่าน
    if (level < 3) {
        // ด่าน 1-2: สร้างศัตรูทั่วไปจำนวนเพิ่มขึ้น
        int enemyCount = (level == 1 ? 3 : 4);
        for (int i = 0; i < enemyCount; ++i) {
            // เลือกตำแหน่งสุ่มที่ไม่มีกำแพงและไม่ทับตำแหน่งผู้เล่น
            int ex, ey;
            do {
                ex = 1 + rand() % (แผนที่.getWidth() - 2);
                ey = 1 + rand() % (แผนที่.getHeight() - 2);
            } while (แผนที่.isWall(ex, ey) || (ex == startX && ey == startY));
            addEnemy(ex, ey);
        }
    } else {
        // ด่าน 3: สร้างบอสที่ตำแหน่งบนกลาง และเพิ่มศัตรูทั่วไปอีกเล็กน้อย
        int bossX = แผนที่.getWidth() / 2;
        int bossY = 1;
        // ให้แน่ใจว่าจุดนั้นไม่มีวางกำแพง
        if (แผนที่.isWall(bossX, bossY)) {
            แผนที่.setCell(bossX, bossY, ' '); // เอากำแพงออกเพื่อวางบอส
        }
        addBoss(bossX, bossY);
        // สร้างศัตรูทั่วไปเพิ่ม 2 ตัวในด่านบอส
        for (int i = 0; i < 2; ++i) {
            int ex, ey;
            do {
                ex = 1 + rand() % (แผนที่.getWidth() - 2);
                ey = 1 + rand() % (แผนที่.getHeight() - 2);
            } while (แผนที่.isWall(ex, ey) || (ex == bossX && ey == bossY) || (ex == startX && ey == startY));
            addEnemy(ex, ey);
        }
    }
}

// วาดแผนที่ รถถัง และกระสุนทั้งหมดบนหน้าจอ
void Game::draw() {
    // ล้างหน้าจอ
    system("cls");
    // แสดงข้อมูลด่านและพลังชีวิตผู้เล่น
    std::cout << "ด่าน: " << ด่านปัจจุบัน << "   พลังชีวิตผู้เล่น: " << ผู้เล่น.getHP() << std::endl;
    // วาดแถวแต่ละแถวของแผนที่
    for (int y = 0; y < แผนที่.getHeight(); ++y) {
        for (int x = 0; x < แผนที่.getWidth(); ++x) {
            // ถ้ามีกำแพงที่จุดนี้
            if (แผนที่.getCell(x, y) == '#') {
                std::cout << '#';
                continue;
            }
            // ถ้าผู้เล่นอยู่ที่จุดนี้
            if (ผู้เล่น.getX() == x && ผู้เล่น.getY() == y) {
                std::cout << ผู้เล่น.getSymbol();
                continue;
            }
            // ถ้ามีศัตรูอยู่ที่จุดนี้
            bool enemyPrinted = false;
            for (Tank* t : ศัตรูทั้งหมด) {
                if (t->getX() == x && t->getY() == y) {
                    std::cout << t->getSymbol();
                    enemyPrinted = true;
                    break;
                }
            }
            if (enemyPrinted) continue;
            // ถ้ามีกระสุนอยู่ที่จุดนี้
            bool bulletPrinted = false;
            for (Bullet &b : กระสุนทั้งหมด) {
                if (b.getX() == x && b.getY() == y) {
                    std::cout << Bullet::สัญลักษณ์;
                    bulletPrinted = true;
                    break;
                }
            }
            if (bulletPrinted) continue;
            // มิฉะนั้น พิมพ์ช่องว่าง
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

// ลูปหลักของเกม
void Game::run() {
    // เล่นทีละด่านจนกว่าจะเกินด่าน 3 หรือจนกว่าผู้เล่นตาย
    for (ด่านปัจจุบัน = 1; ด่านปัจจุบัน <= 3 && !จบเกม; ++ด่านปัจจุบัน) {
        // โหลดข้อมูลด่าน
        loadLevel(ด่านปัจจุบัน);
        // วาดฉากเริ่มต้นของด่าน
        draw();
        // หน่วงเวลาเล็กน้อยเพื่อให้ผู้เล่นเห็นแผนที่เริ่มต้น
        Sleep(1000);

        // ลูปการเล่นภายในด่าน
        bool ด่านเคลียร์ = false;
        while (!จบเกม && !ด่านเคลียร์) {
            // ตรวจคีย์บอร์ดของผู้เล่น (ไม่รอการกด ถ้าไม่กดก็ข้าม)
            if (_kbhit()) {
                char key = _getch();
                // แปลงตัวอักษรเป็นพิมพ์ใหญ่ (เผื่อกดตัวเล็ก)
                if (key >= 'a' && key <= 'z') {
                    key -= 32;
                }
                // ประมวลผลการกดปุ่ม
                if (key == 'W') {
                    ผู้เล่น.setDirection(0, -1);
                    ผู้เล่น.move(0, -1, แผนที่, ศัตรูทั้งหมด);
                } else if (key == 'S') {
                    ผู้เล่น.setDirection(0, 1);
                    ผู้เล่น.move(0, 1, แผนที่, ศัตรูทั้งหมด);
                } else if (key == 'A') {
                    ผู้เล่น.setDirection(-1, 0);
                    ผู้เล่น.move(-1, 0, แผนที่, ศัตรูทั้งหมด);
                } else if (key == 'D') {
                    ผู้เล่น.setDirection(1, 0);
                    ผู้เล่น.move(1, 0, แผนที่, ศัตรูทั้งหมด);
                } else if (key == ' ' || key == '\x20') {
                    // spacebar ยิงกระสุน
                    int dx = ผู้เล่น.getDirX();
                    int dy = ผู้เล่น.getDirY();
                    Bullet newBullet(ผู้เล่น.getX(), ผู้เล่น.getY(), dx, dy, ผู้เล่น.getBulletPower(), true);
                    กระสุนทั้งหมด.push_back(newBullet);
                }
            }
            // อัพเดทการเคลื่อนที่ของศัตรูทุกตัว (AI)
            // เตรียม list รถถังทั้งหมดเพื่อใช้ตรวจชน
            std::vector<Tank*> รถถังทั้งหมด = ศัตรูทั้งหมด;
            รถถังทั้งหมด.push_back(&ผู้เล่น);
            for (Tank* t : ศัตรูทั้งหมด) {
                t->updateAI(แผนที่,  รถถังทั้งหมด, กระสุนทั้งหมด);
            }
            // อัพเดทการเคลื่อนที่ของกระสุนทุกนัด
            for (size_t i = 0; i < กระสุนทั้งหมด.size(); ++i) {
                กระสุนทั้งหมด[i].moveForward();
                // ตรวจว่ากระสุนออกนอกแผนที่หรือชนกำแพงหรือไม่
                int bx = กระสุนทั้งหมด[i].getX();
                int by = กระสุนทั้งหมด[i].getY();
                if (bx < 0 || bx >= แผนที่.getWidth() || by < 0 || by >= แผนที่.getHeight()
                    || แผนที่.isWall(bx, by)) {
                    // ลบกระสุนนี้ (ออกนอกเขตหรือชนกำแพง)
                    กระสุนทั้งหมด.erase(กระสุนทั้งหมด.begin() + i);
                    --i;
                    continue;
                }
                // ตรวจการชนของกระสุนกับรถถัง
                if (กระสุนทั้งหมด[i].isFriendly()) {
                    // กระสุนผู้เล่น -> ชนศัตรูหรือไม่
                    for (size_t j = 0; j < ศัตรูทั้งหมด.size(); ++j) {
                        Tank* enemy = ศัตรูทั้งหมด[j];
                        if (enemy->getX() == bx && enemy->getY() == by) {
                            // ศัตรูโดนยิง
                            enemy->ลดพลังชีวิต(กระสุนทั้งหมด[i].getPower());
                            // ลบกระสุนนี้
                            กระสุนทั้งหมด.erase(กระสุนทั้งหมด.begin() + i);
                            --i;
                            // ถ้าศัตรูตาย กำจัดทิ้ง
                            if (enemy->isDestroyed()) {
                                delete enemy;
                                ศัตรูทั้งหมด.erase(ศัตรูทั้งหมด.begin() + j);
                            }
                            break;
                        }
                    }
                } else {
                    // กระสุนศัตรู -> ชนผู้เล่นหรือไม่
                    if (ผู้เล่น.getX() == bx && ผู้เล่น.getY() == by) {
                        // ผู้เล่นโดนยิง
                        ผู้เล่น.ลดพลังชีวิต(กระสุนทั้งหมด[i].getPower());
                        // ลบกระสุนนี้
                        กระสุนทั้งหมด.erase(กระสุนทั้งหมด.begin() + i);
                        --i;
                        // ตรวจพลังชีวิตผู้เล่น
                        if (ผู้เล่น.isDestroyed()) {
                            จบเกม = true;
                        }
                    }
                }
            }
            // ตรวจเงื่อนไขจบด่าน: ไม่มีศัตรูเหลือ
            if (ศัตรูทั้งหมด.empty()) {
                ด่านเคลียร์ = true;
            }
            // วาดเฟรมใหม่หลังอัพเดทสถานการณ์
            draw();
            // หน่วงเวลาเล็กน้อยเพื่อควบคุมความเร็วเกม
            Sleep(100);
        }
        if (จบเกม) break; // ผู้เล่นตาย ออกจาก loop ด่านทั้งหมด
        // หากผ่านด่านและยังมีด่านถัดไป
        if (ด่านเคลียร์ && ด่านปัจจุบัน < 3) {
            std::cout << "ผ่านด่าน " << ด่านปัจจุบัน << " !" << std::endl;
            Sleep(1000);
        }
    }
    // ออกจาก loop ด่าน (เกมจบ: ชนะครบหรือแพ้)
    system("cls");
    if (จบเกม) {
        std::cout << "จบเกม! ผู้เล่นแพ้\n";
    } else {
        std::cout << "ยินดีด้วย คุณชนะเกมครบทุกด่าน!\n";
    }
}
