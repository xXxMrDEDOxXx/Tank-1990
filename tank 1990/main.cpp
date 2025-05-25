#include "Game.h"
#include <windows.h>
int main() {
    // ทำให้ terminal ใน visual studio code อ่านภาษาไทยออก
    system("chcp 65001 > nul");
    // สร้างเกมและเริ่มเล่น
    Game game;
    game.run();
    return 0;
}
