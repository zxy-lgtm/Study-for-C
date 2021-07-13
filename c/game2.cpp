#define _CRT_SECURE_NO_WARNINGS 1
#ifndef __GAME_H__
#define __GAME_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS ROW+2
#define COLS COL+2
#define ROW  10
#define COL  10
#define MINECOUNT  10      //�����׵ĸ���
static int score_game2 = 0;
static void menu();  //��Ϸ�˵�
static void InitMine(char mine[ROWS][COLS], int row, int col);  //��ʼ������
static void InitShow(char show[ROWS][COLS], int row, int col);  //��ʼ��չʾ������
static void SetMine(char mine[ROWS][COLS], int x, int y, int count);  // �������
static void DisplayBoard(char arr[ROWS][COLS], int row, int col);  // ��ӡչʾ����
static void ResetMine(char mine[ROWS][COLS], int row, int col);  // ��һ�βȵ��ף����²���
static int  GetMineCount(char mine[ROWS][COLS], int i, int j);  //ͳ���׵ĸ���
static void expand(char mine[ROWS][COLS], int x, int y, char show[ROWS][COLS], int* p);  //��չ����
static void PlayGame(char mine[ROWS][COLS], char show[ROWS][COLS]);  // ���߼�
#endif
static void menu()  //��Ϸ�˵�
{
    printf("****************************\n");
    printf("****      ɨ����Ϸ      ****\n");
    printf("****     1.��ʼ��Ϸ     ****\n");
    printf("****     0.�˳���Ϸ     ****\n");
    printf("****************************\n");
}

static void InitMine(char mine[ROWS][COLS], int row, int col) // ��ʼ������
{
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            mine[i][j] = '0';
        }
    }
}

static void InitShow(char show[ROWS][COLS], int row, int col) //��ʼ��չʾ������
{
    int i = 0;
    int j = 0;
    for (i = 1; i <= row; i++)
    {
        for (j = 1; j <= col; j++)
        {
            show[i][j] = '*';
        }
    }
}

static void SetMine(char mine[ROWS][COLS], int row, int col, int count) // �������
{
    while (count)
    {
        int x = rand() % row + 1;
        int y = rand() % col + 1;
        mine[x][y] = '1';
        count--;
    }
}

static void DisplayBoard(char arr[ROWS][COLS], int row, int col) // ��ӡչʾ����
{
    int i = 0;
    int j = 0;
    printf(" ");
    for (i = 0; i <= row; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 1; i <= row; i++)
    {
        printf("%2d", i);
        for (j = 1; j <= col; j++)
        {
            printf(" %c", arr[i][j]);
        }
        printf("\n");
    }
}

static void ResetMine(char mine[ROWS][COLS], int row, int col, int x, int y, int count) // ��һ�βȵ��ף����²���
{
    mine[x][y] = '0';
    while (count)
    {
        int i = rand() % row + 1;
        int j = rand() % col + 1;
        if ((mine[i][j] != '1') && i != x && j != y)
        {
            mine[i][j] = '1';
            count--;
        }
    }
}

static int  GetMineCount(char mine[ROWS][COLS], int i, int j)   //ͳ���׵ĸ���
{
    return mine[i - 1][j] +
        mine[i - 1][j - 1] +
        mine[i][j - 1] +
        mine[i + 1][j - 1] +
        mine[i + 1][j] +
        mine[i + 1][j + 1] +
        mine[i][j + 1] +
        mine[i - 1][j + 1] - 8 * '0';
}

static void expand(char mine[ROWS][COLS], int x, int y, char show[ROWS][COLS], int* p)    //��չ����
{

    int i = -1;
    int j = -1;
    for (i = -1; i < 2; i++)      //�߽�
    {
        for (j = -1; j < 2; j++)
        {
            if (i != 0 || j != 0)      // �����ŵ��Լ�ע��˴����߼���ϵ
            {
                if (x + i >= 1 && x + i <= ROW && y + j >= 1 && y + j <= COL)     //x y�����Ƿ�Ϸ�
                {
                    if (show[x + i][y + j] == '*' && mine[x + i][y + j] != '1')
                    {

                        int count = GetMineCount(mine, x + i, y + j);
                        if (count != 0)
                        {
                            show[x + i][y + j] = count + '0';
                            (*p)++;
                        }
                        else
                        {
                            show[x + i][y + j] = ' ';
                            (*p)++;
                            expand(mine, x + i, y + j, show, p);
                        }

                    }

                }
            }
        }
    }


}

// ���߼�
static void PlayGame(char mine[ROWS][COLS], char show[ROWS][COLS])
{
    int x = 0;
    int y = 0;
    int win = 0;        //ͳ�����׵ĸ���
    int count = 0;     // ͳ���׵ĸ���
    while (win < ROW * COL - MINECOUNT)
    {
        printf("���������꣺>����ʽΪ:number�ո�number)");
        scanf("%d %d", &x, &y);
        if (show[x][y] == count + '0')    //�����ظ�����
        {
            printf("�Ѿ��Ź���\n");
        }
        if (x >= 1 && x <= ROW && y >= 1 && y <= COL)   //���������Ƿ�Ϸ�
        {
            score_game2++;
            if (mine[x][y] == '1')
            {
                if (0 == win)      //Ϊ����Ϸ���飬��һ�βȵ��ף����²���
                {
                    ResetMine(mine, ROW, COL, x, y, 1);
                    //display(mine, ROW, COL);
                    count = GetMineCount(mine, x, y);

                    if (count == 0)
                    {
                        show[x][y] = ' ';
                        win++;
                        expand(mine, x, y, show, &win);  //�����Χû���ף�������չ
                        DisplayBoard(show, ROW, COL);
                    }
                    else
                    {
                        show[x][y] = count + '0';
                        DisplayBoard(show, ROW, COL);
                    }
                }
                else
                {
                    printf("���ź����㱻ը����\n");
                    DisplayBoard(mine, ROW, COL);
                    break;
                }
            }
            else
            {
                count = GetMineCount(mine, x, y);
                if (count == 0)
                {
                    show[x][y] = ' ';
                }
                else
                {
                    show[x][y] = count + '0';
                }
                win++;
                expand(mine, x, y, show, &win);
                DisplayBoard(show, ROW, COL);
                //display(mine, ROW, COL);
            }
        }

        else
        {
            printf("�������겻�Ϸ�\n");
        }

    }
    if (win == ROW * COL - MINECOUNT)
    {
        printf("���׳ɹ�\n");
        DisplayBoard(mine, ROW, COL);
    }
}
//--------------------------------------------
static void game2()
{
    char mine[ROWS][COLS];                 //ɨ������
    char show[ROWS][COLS];                 //չʾ����
    srand((unsigned int)time(NULL));       //���������
    InitMine(mine, ROWS, COLS);            //��ʼ��������
    InitShow(show, ROW, COL);              //��ʼ��չʾ������
    SetMine(mine, ROW, COL, MINECOUNT);    //�������
    DisplayBoard(show, ROW, COL);          //��ӡ����
    PlayGame(mine, show);                  //���߼�����
}

static int game_2_mineClearance()
{
    int input = 0;


    menu();
    printf("��ѡ���Ƿ�ʼ��Ϸ(1/0):>");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        score_game2 = 0;
        game2();
        break;
    case 0:
        printf("��Ϸ�˳���");
        break;
    default:
        printf("����������������룺");
        break;
    }

    // printf("������յ÷��ǣ�%d",score_game2);
    return score_game2;
}