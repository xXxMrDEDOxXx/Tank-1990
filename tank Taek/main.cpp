#include "Game.h"
#include <windows.h>
int main() {
    // ให้ terminal encrpy สามารถภาษาไทยได้
    system("chcp 65001 > nul");
    // สร้างเกมและเริ่มเล่น
    Game game;
    game.run();
    return 0;
}
