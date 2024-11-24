#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void game_init()
{
}

void game_close()
{
}

int main(int argc, char **argv)
{
    game_init();

    sleep(3);

    game_close();
}
