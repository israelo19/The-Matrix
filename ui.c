#include "ui.h"
#include <string.h>
#include <curses.h>
#include <assert.h>
#include <unistd.h>

//pointer to the window that the struct that curses uses to display 
//window on the screen
WINDOW *uiwindow = NULL;

int color_map[MAX_INTENSITY+ 1] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 3, 6};

void set_colors();

bool init_ui(){


    //initialize the curses library
    uiwindow = initscr();
    if(uiwindow == NULL){
        return false;
    } 

    start_color();
    if(!has_colors() || !can_change_color() || COLOR_PAIRS < 6){ 
        printf("Error: UI.C File: Terminal may not support this program\n");
        return false;
    }

    set_colors();

    return true;
}

void cleanup_ui(){
    delwin(uiwindow);
    endwin();
    refresh();
}

void show_matrix(){
    for(int x = 0; x < MAXX; x++){
        for(int y = 0; y < MAXY; y++){
            int intensity = matrix[x][y].intensity;
            color_set(color_map[intensity], NULL); 
            mvaddch(y, x, matrix[x][y].char_value);
        }
    }
    refresh();
}

// void set_colors(){
//     init_pair(1, COLOR_GREEN, COLOR_BLACK);
//     init_pair(2, COLOR_GREEN, COLOR_BLACK);
//     init_pair(3, COLOR_GREEN, COLOR_BLACK);
//     init_pair(4, COLOR_GREEN, COLOR_BLACK);
//     init_pair(5, COLOR_GREEN, COLOR_BLACK);
//     init_pair(6, COLOR_GREEN, COLOR_BLACK);
// }

void set_colors(){
    for(int i=0; i < 8; i++){
        init_pair(i+1, i, COLOR_BLACK);
    }
    //set shades of green
    for(int i=0; i <= 5; i++){
        init_color(i, 0, i*200, 0);
    }

    init_color(6, 800, 1000, 800);
}