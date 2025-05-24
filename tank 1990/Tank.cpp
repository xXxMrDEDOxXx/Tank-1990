#include "Tank.h"
#include "Map.h"

using namespace std;

// ฟังก์ชัน move ของ Tank: พยายามขยับรถถังตามค่า dx, dy
bool Tank::move(int dx, int dy, Map &map, const vector<Tank*> &tanks) {
    // คำนวณตำแหน่งใหม่ที่ต้องการไป
    int newX = ตำแหน่งX + dx;
    int newY = ตำแหน่งY + dy;
    // ตรวจสอบว่าตำแหน่งใหม่อยู่นอกขอบเขตแผนที่หรือไม่
    if (newX < 0 || newX >= map.getWidth() || newY < 0 || newY >= map.getHeight()) {
        return false; // ออกนอกเขตแผนที่
    }
    // ตรวจสอบว่าตำแหน่งใหม่เป็นกำแพงหรือไม่
    if (map.isWall(newX, newY)) {
        return false; // มีกำแพงขวางอยู่
    }
    // ตรวจสอบว่าตำแหน่งใหม่ชนกับรถถังคันอื่นหรือไม่
    for (Tank* t : tanks) {
        if (t == this) continue; // ข้ามตัวเอง
        if (t->getX() == newX && t->getY() == newY) {
            return false; // มีรถถังคันอื่นอยู่ที่ตำแหน่งนั้น
        }
    }
    // ถ้าไม่ชนอะไร สามารถย้ายไปตำแหน่งใหม่ได้
    ตำแหน่งX = newX;
    ตำแหน่งY = newY;
    return true;
}
