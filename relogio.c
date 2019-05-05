/* 
 * File:   relogio.c
 * Author: Alef Duarte
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "kbhit.h"

/*
 * 
 */


int main(int argc, char** argv) {

    nonblock(NB_ENABLE);

    int nm = 0;
    int tempo[40][4];
    int op = 0, i = 0;
    char opt, sair;
    do {
        printf("Escolha uma opção\n");
        printf("1. Hora atual.\n");
        printf("2. Cronômetro progressivo.\n");
        printf("3. Cronômetro regressivo.\n");
        printf("Opção: \n");
        scanf("%d", &op);

        struct tm *ptr;
        time_t lt;
        lt = time(NULL);

        switch (op) {
            case 1:

                while (1) {
                    printf("Pressione enter ou espaço para continuar");
                    printf("\nPressione esc para sair\n");
                    setbuf(stdin, NULL);
                    opt = fgetc(stdin);
                    if (opt == '\n')
                        timenow();
                    else if (opt == ' ')
                        timenow();
                    else
                        break;
                    break;
                }
                break;
            case 2:
                printf("Pressione enter ou espaço para continuar");
                printf("\nPressione esc para sair e espaço para resetar\n");
                setbuf(stdin, NULL);
                opt = fgetc(stdin);
                if (opt == '\n')
                    print(&nm, tempo);
                else if (opt == ' ')
                    print(&nm, tempo);
                else
                    break;
                for (i = 0; i < nm; i++)
                    printf("\n%dº tempo %d:%d:%d:%d\n", i + 1, tempo[i][0], tempo[i][1], tempo[i][2], tempo[i][3]);
                break;
            case 3:
                progress();
                break;

            default:
                break;

        }
        printf("\nAperte enter para continuar ou esc para sair.\n");
        setbuf(stdin, NULL);
        sair = fgetc(stdin);
    } while (sair != 27);
    return (EXIT_SUCCESS);
}

