#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<MMSystem.h>
#pragma comment(lib,"Winmm.lib")

#define HIGH 20  //��Ϸ����߶�
#define WIDTH 30  // ��Ϸ������
//#define NUM 10  //�л������ٶ�
//int flag=0;
static struct Plane {
    int p;
    int isdeath;
    int position_x;
    int position_y;
    int bullet_x;
    int bullet_y;
    int enemy_x;
    int enemy_y;
}plane;
static int score_plane;  //�÷�

static int speed = 0;
static int NUM = 10, vt;
static int k;
static int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //����������ɫ
    return 0;
}
static void gotoxy(int x, int y) //����������(x,y)��λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

static void HideCursor()  //���ع����ʾ
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

static void startup()//���ݵĳ�ʼ��
{
    //��ʼ���ɻ�
    plane.position_x = HIGH / 2; //�߶�
    plane.position_y = WIDTH / 2; //���

    //��ʼ���ӵ�
    plane.bullet_x = -1;
    plane.bullet_y = plane.position_y;

    //��ʼ���л�
    plane.enemy_x = 0;
    plane.enemy_y = plane.position_y;

    //��ʼ���÷�
    score_plane = 0;
    plane.isdeath = 0;
}

static void show()//��ʾ����
{
    int i, j;
    // system("cls"); //��������  
    gotoxy(0, 0); //ʹ���ص�0��0


    for (i = 0; i < HIGH; i++) //��
    {
        for (j = 0; j < WIDTH; j++) //��
        {
            if (i == plane.position_x && j == plane.position_y)//����ɻ�
            {
                printf("��");
            }
            else if (i == plane.bullet_x && j == plane.bullet_y)//����ӵ�
            {
                printf("|");
            }
            else if (i == plane.enemy_x && j == plane.enemy_y)//����л�
            {
                printf("��");
            }
            else if ((j == WIDTH - 1) || (i == HIGH - 1) || (j == 0) || (i == 0))				//��ӡ�߽� 
                printf("-");
            else
            {
                printf(" ");
            }
        }
        if ((plane.position_x == plane.enemy_x) && (plane.position_y == plane.enemy_y))
        {
            //�ɻ�ײ�� ��Ϸ���� 
            system("cls");
            gotoxy(43, 15);
            printf("����ˣ���Ϸ����!!!\n");
            plane.isdeath = 1;

        }
        printf("\n");
    }

}
static void updateWitoutIput_1()//���û������޹صĸ���
{
    if (plane.bullet_x > -1) //���ӵ�������
    {
        plane.bullet_x--;
    }
    if (plane.bullet_x == plane.enemy_x && plane.bullet_y == plane.enemy_y) //���ел�
    {
        score_plane += vt * 2;  //�÷�+1

        plane.enemy_x = -1;   //�����µķɻ�
        plane.enemy_y = rand() % (WIDTH-1);

        plane.bullet_x = -1;  //���ӵ�ֱ�ӳ�����Ļ�⣬ֱ����һ�η����ӵ�
    }

    //���Ƶл������ٶ�
    if (speed < NUM)  //ÿ����NUM�εл�����һ��
    {
        speed++;
    }
    else
    {
        plane.enemy_x++;
        speed = 0;
    }
    if (plane.enemy_x > HIGH)  //�л�һֱ���䵽�ײ�
    {
        plane.enemy_x = -1;
        plane.enemy_y = rand() % WIDTH;
    }

}
static void updateWithInput()//���û������йصĸ���
{
    //�û�����
    char input;//���Ʒɻ�����
    if (_kbhit())
    {
        input = _getch();
        if (input == 'w' && plane.position_x > 1)
            plane.position_x--;
        if (input == 's' && plane.position_x < HIGH - 1)
            plane.position_x++;
        if (input == 'a' && plane.position_y > 1)
            plane.position_y--;
        if (input == 'd' && plane.position_y < WIDTH - 1)
            plane.position_y++;
        if (input == ' ')
        {
            plane.bullet_x = plane.position_x - 1;
            plane.bullet_y = plane.position_y;
        }
    }
}
static void moden()//�����Ѷ�
{
    if (vt == 3)
        NUM = 5;
    else if (vt == 2)
        NUM = 15;
    else if (vt == 1)
        NUM = 25;
    else if (vt == 9)
        NUM = 1;
    else if (vt == 8)
        NUM = 100;
    else
    {
        printf("��Ҫ̫Ƥ\n");
        exit(0);
    }
}
static void scoreandtips()//��Ϸ�����ʾ 
{
    gotoxy(50, 8);
    color(14);
    printf("��Ϸ�÷֣�%d ", score_plane);
    gotoxy(50, 10);
    printf("��W A S D �ֱ���Ʒɻ����ƶ�");
    gotoxy(50, 12);
    printf("���¿ո����Ϊ�����ڵ�");
    gotoxy(50, 14);
    printf("��  �����Ӿ��ǵ��˵ķɻ�");
    gotoxy(50, 16);
    printf("ײ��������Ŷ");
    gotoxy(50, 18);

}
static void appearance()
{
    system("mode con cols=120 lines=30");
    color(15);
    gotoxy(43, 10);
    printf("    �� �� �� ս       \n");
    color(11);
    gotoxy(42, 12);
    printf("��ӭ�����ɻ���ս ��ѡ��ģʽ\n");
    gotoxy(45, 14);
    printf("  1.����ģʽ    \n");
    gotoxy(45, 15);
    gotoxy(45, 16);
    gotoxy(45, 17);
    gotoxy(42, 18);
    printf("��ʾ��W A S D �ƶ����ո����ӵ�\n");
    gotoxy(45, 1);
    printf("ps:�����Ǳ�����");
    gotoxy(45, 20);
    scanf("%d", &plane.p);

}
static void ssb()
{
    system("cls");
    gotoxy(45, 10);
    printf("��Ƥ����������Ϸ\n");
    gotoxy(45, 12);
    printf("������������666");
    gotoxy(45, 14);
    scanf("%d", &k);
    if (k == 666)
    {
        gotoxy(45, 16);
        color(11);
        printf("��");
        color(12);
        printf("��");
        color(13);
        printf("��");
        color(10);
        gotoxy(45, 17);
        printf("Ƥһ�ºܿ���");
        color(14);
    }
}

static int game_1_plane()
{
    appearance();
    if (plane.p == 1)
    {
        gotoxy(0, 0);
        system("cls");
        color(6);
        gotoxy(43, 10);
        printf("�������Ѷ�\n");
        gotoxy(43, 11);
        printf("1.��\n");
        gotoxy(43, 12);
        printf("2.��ͨ\n");
        gotoxy(43, 13);
        printf("3.����\n");
        gotoxy(43, 14);
        scanf("%d", &vt);
        moden();//ѡ��ģʽ
        system("cls");
        startup();//��ʼ��
        HideCursor();
        srand((unsigned)time(NULL));
        while (1)  //ѭ��ִ��
        {
            gotoxy(0, 0);
            scoreandtips();
            show();//��ʾ����   
            updateWitoutIput_1();//���û������޹صĸ���  �������� 
            updateWithInput(); //���û������йصĸ���  ������� 
            if (plane.isdeath == 1) {
                plane.isdeath = 0;
                break;
            }
        }
        system("pause");
        printf("������յ÷���:%d", score_plane);
        return score_plane;

    }
    else
        ssb();

}