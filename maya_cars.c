#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdint.h>

#define WIDTH 40

void move_cursor(uint8_t line, uint8_t column)
{
    fprintf(stdout, "\e[%d;%dH", line, column);
}

void clear_screen()
{
    fprintf(stdout, "\e[2J");
}

void game_init()
{
    move_cursor(1, 1);
    clear_screen();

    for (uint8_t column = 0; column < WIDTH; column++)
        fprintf(stdout, "-");

    fprintf(stdout, "\n\n");

    for (uint8_t column = 0; column < WIDTH / 2; column++)
        fprintf(stdout, "- ");

    fprintf(stdout, "\n\n");

    for (uint8_t column = 0; column < WIDTH; column++)
        fprintf(stdout, "-");

    fflush(stdout);
}

void game_close()
{
    move_cursor(1, 1);
    clear_screen();

    fflush(stdout);
}

// 0: top: <; 1: bottom: >
void *car_thread(void *param)
{
    bool route = *(bool *)param;

    char car = (route) ? '>' : '<';
    uint8_t line = (route) ? 4 : 2;

    uint8_t moves = 0;
    while (moves < WIDTH)
    {
        uint8_t oldcolumn = (route) ? moves : WIDTH - moves + 1;
        uint8_t column = (route) ? moves + 1 : WIDTH - moves;

        move_cursor(line, oldcolumn);
        fprintf(stdout, " ");

        move_cursor(line, column);
        fprintf(stdout, "%c", car);

        move_cursor(1, WIDTH + 1);
        fflush(stdout);

        uint8_t ms = (rand() % 10 + 50);
        usleep(ms * 1000);
        ++moves;
    }

    move_cursor(line, (route) ? WIDTH : 1);
    fprintf(stdout, " ");
    fflush(stdout);

    return NULL;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    game_init();

    pthread_t last;

    bool quit = false;
    while (!quit)
    {
        bool route = 0;

        switch (fgetc(stdin))
        {
        case 'q':
            quit = true;

            break;
        case 'j':
            route = 1;
        case 'k':
            bool copied = route;
            pthread_create(&last, NULL, car_thread, (void *)&copied);

            break;
        }
    }

    pthread_join(last, NULL);

    game_close();
}
