#ifndef BULLET_H
#define BULLET_H

// คลาส Bullet แทนกระสุนที่ถูกยิง
class Bullet {
private:
    int ตำแหน่งX;       // ตำแหน่งแกน X ของกระสุน
    int ตำแหน่งY;       // ตำแหน่งแกน Y ของกระสุน
    int ทิศทางX;        // ทิศทางการเคลื่อนที่ของกระสุน (แกน X)
    int ทิศทางY;        // ทิศทางการเคลื่อนที่ของกระสุน (แกน Y)
    int พลังกระสุน;     // ความแรงของกระสุน (ใช้ลดพลังชีวิตเป้าหมาย)
    bool เป็นมิตร;      // ระบุว่ากระสุนนี้มาจากฝั่งผู้เล่นหรือไม่ (true = ผู้เล่น, false = ศัตรู)
public:
    static const char สัญลักษณ์ = '*'; // สัญลักษณ์แทนกระสุนบนแผนที่
    // Constructor: กำหนดตำแหน่ง, ทิศทาง, ความแรง และฝ่ายของกระสุน
    Bullet(int startX, int startY, int dirX, int dirY, int power, bool friendly)
        : ตำแหน่งX(startX), ตำแหน่งY(startY), ทิศทางX(dirX), ทิศทางY(dirY),
          พลังกระสุน(power), เป็นมิตร(friendly) {}
    // ให้กระสุนเคลื่อนที่ไปข้างหน้า 1 ก้าว (ตามทิศทาง)
    void moveForward() {
        ตำแหน่งX += ทิศทางX;
        ตำแหน่งY += ทิศทางY;
    }
    // Getter ต่าง ๆ
    int getX() const { return ตำแหน่งX; }
    int getY() const { return ตำแหน่งY; }
    int getPower() const { return พลังกระสุน; }
    bool isFriendly() const { return เป็นมิตร; }
};

#endif
