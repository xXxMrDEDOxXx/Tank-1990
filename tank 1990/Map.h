#ifndef MAP_H
#define MAP_H

#include <cstdlib>  // สำหรับ rand()
#include <ctime>    // สำหรับ time()

// คลาส Map สำหรับแผนที่เกม
class Map {
private:
    static const int ความกว้าง = 20;  // ความกว้างของแผนที่ (จำนวนคอลัมน์)
    static const int ความสูง = 15;   // ความสูงของแผนที่ (จำนวนแถว)
    char grid[ความสูง][ความกว้าง];   // เมทริกซ์ของช่องแผนที่ (# กำแพง, ' ' พื้นที่ว่าง)
public:
    Map() {
        // Constructor อาจไม่ต้องทำอะไร เพราะจะเรียก generate ก่อนใช้แผนที่
    }
    int getWidth() const { return ความกว้าง; }
    int getHeight() const { return ความสูง; }
    bool isWall(int x, int y) const {
        return grid[y][x] == '#';
    }
    char getCell(int x, int y) const {
        return grid[y][x];
    }
    void setCell(int x, int y, char value) {
        grid[y][x] = value;
    }
    // สร้างแผนที่ใหม่สำหรับด่าน โดยสุ่มวางกำแพง
    void generate(int level);
};

#endif
