// TEN QUEEN

#include <unistd.h>
#include <stdio.h>

#define N 4

void fill_queen(int places[N][N], int x, int y, int log[N], int *queens)
{
    int i = 0;

    while (i < N)
    {
        places[i][y] += 1;
        places[x][i] += 1;

        if (i < N - x && i < N - y) {places[x + i][y + i] += 1;}
        if (x - i >= 0 && i < N - y) {places[x - i][y + i] += 1;}
        if (x - i >= 0 && y - i >= 0) {places[x - i][y - i] += 1;}
        if (y - i >= 0 && i < N - x) {places[x + i][y - i] += 1;}
        i++;
    }

    log[x] = y;
    (*queens)++;

    places[x][y] = 1;
}

void remove_queen(int places[N][N], int x, int y, int log[N], int *queens)
{
    int i = 0;

    while (i < N)
    {
        places[i][y] -= 1;
        places[x][i] -= 1;
        if (i < N - x && i < N - y) {places[x + i][y + i] -= 1;}
        if (x - i >= 0 && i < N - y) {places[x - i][y + i] -= 1;}
        if (x - i >= 0 && y - i >= 0) {places[x - i][y - i] -= 1;}
        if (y - i >= 0 && i < N - x) {places[x + i][y - i] -= 1;}
        i++;
    }

    log[x] = -1;
    (*queens)--;

    places[x][y] = 0;
}

void display_tab(int places[N][N])
{
    printf("DISPLAY\n");
    for (int i = 0; i< N; i++)
    {
        for (int j=0; j<N; j++)
        {
            printf("%d ", places[j][i]);
        }
        printf("\n");
    }
}

void display_log(int log[N])
{
    printf("LOG  : ");
    for (int i = 0; i< N; i++) printf("%d, ", log[i]);
    printf("\n");
}

int place_queen(int places[N][N], int * queens, int log[N])
{
    int i,j;
    i = 0;

    int r = 0;

    if (*queens < N)
    {
        while (i < N)
        {
            j = 0;
            while (j < N)
            {
                //printf("log %d : %d \n", i, log[i]);
                if (log[i] > -1) break;

                if (places[i][j] == 0)
                {
                    char y = j + '0';
                    
                    fill_queen(places, i, j, log, queens);
                    r = place_queen(places, queens, log);
                    if (r == 1)
                    {
                        return 1;
                    }    
                    else remove_queen(places, i, j, log, queens);
                }
                j++;
            }
            i++;
        }
        if (*queens < N) return 0;
    }
    if (*queens >= N)
    {
        i = 0;
        while (i < N)
        {
            char c = log[i++] + '0';
            write(1, &c, 1);
        }
        write(1, "\n", 1);
        return 1;
    }
}

void ten_queen()
{
    int places[N][N] = {0};
    int log[N];
    int queens_placed = 0;

    for (int i = 0; i< N; i++) log[i] = -1;

    place_queen(places, &queens_placed, log);
    int i = N - 1;

    while (i > -1) 
    {
        //display_log(log);
        int j = log[i] + 1;
        //printf(" to remove : %d, %d\n", i, log[i]);
        remove_queen(places, i, log[i], log, &queens_placed);
        while (j < N)
        {
            if (places[i][j] == 0)
            {
                //printf("x : %d , y : %d\n", i, log[i]);
                //printf("x : %d , y : %d\n", i, j);

                fill_queen(places, i, j, log, &queens_placed);
                int r = place_queen(places, &queens_placed, log);
                //printf("place_queen = %d\n", r);
                if (r == 1)
                {
                    i = N;
                    break;
                } else i++;
            }
            j++;
        }
        i--;
    }
}

int main()
{
    ten_queen();
}