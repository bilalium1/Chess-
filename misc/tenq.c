// TEN QUEEN

#include <unistd.h>
#include <stdio.h>

void fill_queen(int places[10][10], int x, int y, int log[10], int *queens)
{
    int i = 0;

    while (i < 10)
    {
        places[i][y] += 1;
        places[x][i] += 1;

        if (i < 10 - x && i < 10 - y) {places[x + i][y + i] += 1;}
        if (x - i >= 0 && i < 10 - y) {places[x - i][y + i] += 1;}
        if (x - i >= 0 && y - i >= 0) {places[x - i][y - i] += 1;}
        if (y - i >= 0 && i < 10 - x) {places[x + i][y - i] += 1;}
        i++;
    }

    log[x] = y;
    (*queens)++;

    places[x][y] = 1;
}

void remove_queen(int places[10][10], int x, int y, int log[10], int *queens)
{
    int i = 0;

    while (i < 10)
    {
        places[i][y] -= 1;
        places[x][i] -= 1;
        if (i < 10 - x && i < 10 - y) {places[x + i][y + i] -= 1;}
        if (x - i >= 0 && i < 10 - y) {places[x - i][y + i] -= 1;}
        if (x - i >= 0 && y - i >= 0) {places[x - i][y - i] -= 1;}
        if (y - i >= 0 && i < 10 - x) {places[x + i][y - i] -= 1;}
        i++;
    }

    log[x] = -1;
    (*queens)--;

    places[x][y] = 0;
}

void display_tab(int places[10][10])
{
    printf("DISPLAY\n");
    for (int i = 0; i< 10; i++)
    {
        for (int j=0; j<10; j++)
        {
            printf("%d ", places[j][i]);
        }
        printf("\n");
    }
}

void display_log(int log[10])
{
    printf("LOG  : ");
    for (int i = 0; i< 10; i++) printf("%d, ", log[i]);
    printf("\n");
}

int place_queen(int places[10][10], int * queens, int log[10])
{
    int i,j;
    i = 0;

    int r = 0;

    if (*queens < 10)
    {
        while (i < 10)
        {
            j = 0;
            while (j < 10)
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
        if (*queens < 10) return 0;
    }
    if (*queens >= 10)
    {
        i = 0;
        while (i < 10)
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
    int places[10][10] = {0};
    int log[10];
    int queens_placed = 0;

    for (int i = 0; i< 10; i++) log[i] = -1;

    place_queen(places, &queens_placed, log);
    int i = 9;

    while (i > -1) 
    {
        //display_log(log);
        int j = log[i] + 1;
        //printf(" to remove : %d, %d\n", i, log[i]);
        remove_queen(places, i, log[i], log, &queens_placed);
        while (j < 10)
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
                    i = 10;
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