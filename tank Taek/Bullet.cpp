#include "Bullet.h"

// กำหนดค่าสัญลักษณ์กระสุน (static)
const char Bullet::สัญลักษณ์ = '*';
// ให้กระสุนเคลื่อนที่ไปข้างหน้า 1 ก้าว (ตามทิศทาง)
void Bullet::moveForward() {
    ตำแหน่งX += ทิศทางX;
    ตำแหน่งY += ทิศทางY;
}