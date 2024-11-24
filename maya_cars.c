#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

void move_cursor(uint8_t line, uint8_t column)
{
    fprintf(stdout, "\e[%d;%dH", line, column);
}

void clear_screen()
{
    fprintf(stdout, "\e[2J");
}

void game_init(uint8_t width)
{
    move_cursor(1, 1);
    clear_screen();

    for (uint8_t col = 0; col < width; col++)
        fprintf(stdout, "-");

    fprintf(stdout, "\n\n");

    for (uint8_t col = 0; col < width / 2; col++)
        fprintf(stdout, "- ");

    fprintf(stdout, "\n\n");

    for (uint8_t col = 0; col < width; col++)
        fprintf(stdout, "-");

    fflush(stdout);
}

void game_close()
{
    move_cursor(1, 1);
    clear_screen();

    fflush(stdout);
}

int main(int argc, char **argv)
{
    game_init(40);

    sleep(3);

    game_close();
}
