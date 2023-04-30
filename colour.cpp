#include <ncurses.h>
#include <bits/stdc++.h>

int main() {
    // Initialize ncurses
    initscr();
    start_color();

    // Define colors
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    // Define the matrix
    int matrix[3][3] = {{1, 0, 1},
                        {0, 1, 0},
                        {1, 0, 1}};

    // Loop through the matrix and print it
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == 0) {
                attron(COLOR_PAIR(1));
                printw("%d ", matrix[i][j]);
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                printw("%d ", matrix[i][j]);
                attroff(COLOR_PAIR(2));
            }
        }
        printw("\n");
    }

    // Clean up ncurses
    endwin();

    return 0;
}
