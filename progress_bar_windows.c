#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // Include for Windows-specific functions
#include <time.h>

const int BAR_LENGTH = 50;
const int MIL_SEC_TO_REFRESH = 400;
const int RANGE = 7;
const int MIN_FOR_RANGE = 3;

#define MAX_TASKS 50

void clear_screen() {
     #ifdef _WIN32
         COORD cursorPosition;
         cursorPosition.X = 0;
         cursorPosition.Y = 0;
         SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
     #else
         printf("\033[H"); // ANSI escape code to move cursor to top (Linux/macOS)
     #endif
 }

typedef struct {
    int id;
    int progress;
    int step;
} Task;

void print_bar(Task task) {
    int progress = task.progress;
    int id = task.id;

    int bars_to_show = (int)(progress * BAR_LENGTH * 0.01);

    printf("Task %2d: [", id);

    for (int i = 0; i < BAR_LENGTH; i++) {
        if (i < bars_to_show) {
            printf("=");
        } else {
            printf(" ");
        }
    }

    printf("] %d%%\n", progress);
}

int main() {
    Task tasks[MAX_TASKS];
    srand(time(NULL));

    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand() % RANGE + MIN_FOR_RANGE; // Random step between 2 and 21
    }

    int tasks_incomplete = 1;
    while (tasks_incomplete) {
        clear_screen();
        tasks_incomplete = 0;

        for (int i = 0; i < MAX_TASKS; i++) {

            tasks[i].progress += tasks[i].step;

            if (tasks[i].progress > 100) {
                tasks[i].progress = 100;
            } else if (tasks[i].progress < 100) {
                tasks_incomplete = 1;
            }

            print_bar(tasks[i]);
        }

        Sleep(MIL_SEC_TO_REFRESH); // Sleep for 1000 milliseconds in Windows (1 second = 1000 milliseconds)
    }

    printf("\nAll tasks completed!\n");

    return 0;
}
