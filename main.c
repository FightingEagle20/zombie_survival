#include "Globals.h"
#include "Start.h"
#include "Menu.h"
#include "Game.h"
#include "Finish.h"

int main(int argc, char *args[]) {
    init();

    srand((unsigned int) time(NULL));

    bool quit = false;
    setup_menu();
    menu_loop(&quit);
    close_menu();
    while(!quit) {
        setup_game();
        game_loop();
        end_screen();
        close_game();

        setup_menu();
        menu_loop(&quit);
        close_menu();
    }

    close();
    return 0;
}