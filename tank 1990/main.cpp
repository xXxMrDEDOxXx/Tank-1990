#include "Game.h"
#include <windows.h>
int main() {
    // สร้างเกมและเริ่มเล่น
    system("chcp 65001 > nul");
    Game game;
    game.run();
    return 0;
}
