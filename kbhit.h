#include <termios.h>
#define NB_ENABLE 0
#define NB_DISABLE 1

int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void nonblock(int state) {
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state == NB_ENABLE) {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    } else if (state == NB_DISABLE) {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

}

void timenow() {
    int h = 0, m = 0, s = 0, i = 0;
    char sair;
    struct tm *ptr;
    time_t lt;
    lt = time(NULL);
    ptr = localtime(&lt);
    s = ptr -> tm_sec;
    m = ptr -> tm_min;
    h = ptr -> tm_hour;


    while (h < 60 && i != 1) {
        while (m < 60 && i != 1) {
            while (s < 60 && i != 1) {
                nonblock(NB_ENABLE);
                i = kbhit();
                if (i != 0) {
                    sair = fgetc(stdin);
                    if (sair == 27)
                        i = 1;
                    else
                        i = 0;
                }
                fprintf(stderr, "%d:%d:%d\n", h, m, s);
                sleep(1);
                s++;
                //       nonblock(NB_DISABLE);
            }
            if (sair == 27)
                break;
            m++;
            s = 0;
        }
        h++;
        m = 0;
    }

}

void print(int *nm, int tempo[][4]) {
    int h = 0, m = 0, s = 0, ms = 0, i = 0, j = 0, x = 0;
    int aux = *nm;
    char sair;

    while (h < 60 && i != 1) {
        while (m < 60 && i != 1) {
            while (s < 60 && i != 1) {
                while (ms < 1000 && i != 1) {

                    usleep(1000);

                    nonblock(NB_ENABLE);
                    i = kbhit();
                    if (i != 0) {
                        sair = fgetc(stdin);
                        if (sair == 27)
                            i = 1;
                        else if (sair == ' ')
                            i = 1;
                        else
                            i = 0;
                    }
                    ms++;
                    fprintf(stderr, "%d:%d:%d:%d\n", h, m, s, ms);
                    //   nonblock(NB_DISABLE);
                }
                if (sair == ' ') {
                    tempo[aux][j] = h;
                    j++;
                    tempo[aux][j] = m;
                    j++;
                    tempo[aux][j] = s;
                    j++;
                    tempo[aux][j] = ms;
                    j = 0;
                    aux++;
                    *nm = aux;
                    print(nm, tempo);
                } else if (sair == 27) {
                    tempo[aux][j] = h;
                    j++;
                    tempo[aux][j] = m;
                    j++;
                    tempo[aux][j] = s;
                    j++;
                    tempo[aux][j] = ms;
                    j = 0;
                    aux++;
                    *nm = aux;
                    break;
                }
                ms = 0;
                s++;
            }
            m++;
            s = 0;
        }
        h++;
        m = 0;
    }
}

void progress() {
    int h = 0, m = 0, s = 0;
    nonblock(NB_DISABLE);
    printf("\nAjuste o tempo");
    printf("\nHoras: ");
    scanf("%d", &h);
    printf("\nMinutos: ");
    scanf("%d", &m);
    printf("\nSegundos: ");
    scanf("%d", &s);

    while (h >= 0) {
        while (m >=0) {
            while (s >= 0) {
                fprintf(stderr, "%d:%d:%d\n", h, m, s);
                sleep(1);
                s--;
            }
            m--;
            s = 59;
        }
        h--;
        m = 59;
    }

    nonblock(NB_ENABLE);
}

