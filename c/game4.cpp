#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

//��Ϸ����
#define FrameX 4   //��Ϸ�������Ͻǵ�X������
#define FrameY 4   //��Ϸ�������Ͻǵ�Y������
#define Frame_height  20 //��Ϸ���ڵĸ߶�
#define Frame_width   20 //��Ϸ���ڵĿ��

//����ȫ�ֱ���
static int n, u;
static int a[2];     //���ڼ�ס��β���꣬����a[0]��a[1]�ֱ��ʾ�ᡢ������

//�����ߵĽṹ��
static struct Snake
{
    int x[100];    //�ߵĺ����꣬����x[0]��ʾ��β�ĺ����꣬x[N-1]��ʾ��ͷ�ĺ�����
    int y[100];    //�ߵ������꣬����y[0]��ʾ��β�������꣬y[N-1]��ʾ��ͷ��������
    int count;    //�߳�ʳ��ĸ���
    int length;    //�ߵĳ���
    int speed;    //�ߵ��ٶ�
};

//����ʳ��Ľṹ��
static struct Food
{
    int x;     //ʳ��ĺ�����
    int y;     //ʳ���������
};

/******����Ƶ�ָ��λ��**************************************************************/
static void gotoxy(HANDLE hOut, int x, int y)
{
    COORD pos;
    pos.X = x;  //������
    pos.Y = y;  //������
    SetConsoleCursorPosition(hOut, pos);
}

/******�����ı�Ϊ��ɫ*****************************************************************/
static void Set_TextColor_Green(void)
{
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
}

/******������Ϸ����******************************************************************/
static void make_frame()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //������ʾ���������
    gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 13);  //��ӡѡ��˵�
    printf("Esc �˳���Ϸ");
    gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 15);
    printf("���������������");

    gotoxy(hOut, FrameX, FrameY);       //��ӡ���
    printf("�X");
    gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY);
    printf("�[");
    gotoxy(hOut, FrameX, FrameY + Frame_height);
    printf("�^");
    gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY + Frame_height);
    printf("�a");
    for (n = 2; n < 2 * Frame_width - 2; n += 2)
    {
        gotoxy(hOut, FrameX + n, FrameY);
        printf("�T");         //��ӡ�Ϻ��
    }
    for (n = 2; n < 2 * Frame_width - 2; n += 2)
    {
        gotoxy(hOut, FrameX + n, FrameY + Frame_height);
        printf("�T");         //��ӡ�º��
    }
    for (n = 1; n < Frame_height; n++)
    {
        gotoxy(hOut, FrameX, FrameY + n);
        printf("�U");         //��ӡ������
    }
    for (n = 1; n < Frame_height; n++)
    {
        gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY + n);
        printf("�U");         //��ӡ������
    }

    gotoxy(hOut, FrameX + Frame_width - 5, FrameY - 2);   //��ӡ��Ϸ���� 
    Set_TextColor_Green();        //������Ϊ��ɫ
    printf("̰������Ϸ");
}

/******�����˵�*******************************************************************/
static void over_game()
{
    system("cls");
    printf("\n\n\n\n\n\n\n\n\t\t\t\t��Ϸ����\n\n\n");
    Sleep(2000);
    _getch();
}

/******�˵���Ϣ***************************************************************/
static void print_information(HANDLE hOut, struct Snake* snake, struct Food* food)
{
    gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 1);
    printf("level : %d", snake->count / 5 + 1);    //��ӡ��Ϸ�ȼ�
    gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 3);
    printf("score : %d", 10 * snake->count);    //��ӡ��Ϸ�÷�
    gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 5);
    printf("eat food : %d", snake->count);    //��ӡ����ʳ����� 
    gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 7);
    printf("speed : %dms", snake->speed);    //��ӡ��Ϸ�ٶ�
    gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 9);
    printf("foodX : %d", food->x);      //��ӡʳ��ĺ�����
    gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 11);
    printf("foodY : %d", food->y);      //��ӡʳ���������
}

/******��ʼ����**********************************************************************/
static void init_snake(struct Snake* snake)
{
    snake->x[0] = FrameX + 2;     //��ʼ���ߵĺ�����
    snake->y[0] = FrameY + Frame_height / 2;  //��ʼ���ߵ�������
    snake->speed = 300;      //��ʼ���ߵ��ٶ�Ϊ300ms
    snake->length = 3;      //��ʼ���ߵĳ���Ϊ3��
    snake->count = 0;       //��ʼ���߳Եĸ���Ϊ0
    for (n = 1; n < snake->length; n++)
    {/* ���εõ�������ͷ������ */
        snake->x[n] = snake->x[n - 1] + 2;
        snake->y[n] = snake->y[n - 1];
    }
}

/******�ƶ���*************************************************************************/
static void move_snake(HANDLE hOut, struct Snake* snake)
{
    gotoxy(hOut, snake->x[0], snake->y[0]);
    printf("  ");       /* �����β*/
    for (n = 1; n < snake->length; n++)
    {/* ��һ�ڵ���������ȡ��ǰһ�ڵ����� */
        snake->x[n - 1] = snake->x[n];
        snake->y[n - 1] = snake->y[n];
    }
}

/******��ӡ��*************************************************************************/
static void print_snake(HANDLE hOut, struct Snake* snake)
{
    for (n = 0; n < snake->length; n++)
    {
        gotoxy(hOut, snake->x[n], snake->y[n]);
        if (n == 0)
        {
            printf("��");       //��ӡ��β
        }
        else if (n == snake->length - 1)
        {
            printf("��");       //��ӡ��ͷ
        }
        else
        {
            printf("��");       //��ӡ����
        }
    }
}

/******�������ʳ��*******************************************************************/
static void get_food(HANDLE hOut, struct Snake* snake, struct Food* food)
{
    srand((unsigned)time(NULL));       //��ʼ�������
    while (1)
    {/* ����ʳ���������1.����Ϸ������ 2.�����ߵ����� */
        food->x = rand() % (Frame_width - 1);
        food->y = rand() % Frame_height;
        if (food->x == 0 || food->y == 0)
        {
            continue;
        }
        food->x = 2 * food->x + FrameX;      //�õ�ʳ��ĺ�����
        food->y += FrameY;         //�õ�ʳ���������
        for (n = 0; n < snake->length; n++)
        {/* �ж�ʳ���Ƿ����ߵ����ϣ�����������ϣ������²��������򣬴�ӡ���� */
            if (food->x == snake->x[n] && food->y == snake->y[n])
            {
                break;
            }
        }
        if (n == snake->length)
        {
            gotoxy(hOut, food->x, food->y);
            printf("��");
            break;
        }
    }
}

/******��ʳ��***************************************************************************/
static void eat_food(HANDLE hOut, struct Snake* snake, struct Food* food)
{
    if (snake->x[snake->length - 1] == food->x && snake->y[snake->length - 1] == food->y)
    {/* �����ͷλ����ʳ��λ����ͬ����ʳ�� */
        snake->length++;      //��һ��ʳ���������һ��
        for (n = snake->length - 1; n >= 1; n--)
        {/* �ߺ���������θ�ֵ����ǰһ�ڵ����꣬���εõ�������ͷ������ */
            snake->x[n] = snake->x[n - 1];
            snake->y[n] = snake->y[n - 1];
        }
        snake->x[0] = a[0];      //�õ���β�ƶ�ǰ�ĺ�����
        snake->y[0] = a[1];      //�õ���β�ƶ�ǰ��������  
        get_food(hOut, snake, food);    //���²���ʳ��
        snake->count++;       //ʳ��ĸ�����1
        if (snake->count % 5 == 0 && snake->speed>50)
        {/* ���߳�Up_level��ʳ��ʱ���ٶȼӿ�Up_speed���벢����һ�� */
            snake->speed -= 50;
        }
    }
}

/******��ǽ**********************************************************************************/
static void through_wall(HANDLE hOut, struct Snake* snake, char ch)
{
    if (ch == 72 && snake->y[snake->length - 1] == FrameY)
    {
        snake->y[snake->length - 1] = FrameY + Frame_height - 1; //��������Ͽ��������ƶ�����ǽ
    }
    if (ch == 80 && snake->y[snake->length - 1] == FrameY + Frame_height)
    {
        snake->y[snake->length - 1] = FrameY + 1;    //��������¿��������ƶ�����ǽ
    }
    if (ch == 75 && snake->x[snake->length - 1] == FrameX)
    {
        snake->x[snake->length - 1] = FrameX + 2 * Frame_width - 4; //�����������������ƶ�����ǽ
    }
    if (ch == 77 && snake->x[snake->length - 1] == FrameX + 2 * Frame_width - 2)
    {
        snake->x[snake->length - 1] = FrameX + 2;    //��������ҿ��������ƶ�����ǽ
    }
}

/******�ж����Ƿ���**************************************************************************/
static int if_die(struct Snake* snake)
{/* ����ͷ��������ʱ������ ������ֵΪ0 */
    for (n = 0; n < snake->length - 1; n++)
    {
        if (snake->x[snake->length - 1] == snake->x[n] && snake->y[snake->length - 1] == snake->y[n])
        {
            return 0;
        }
    }
    return 1;
}

/******��ʼ��Ϸ*******************************************************************************/
static int start_game4()
{

    system("cls");
    unsigned char ch = 77;        //�������ڽ��ռ���������ַ�����
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //������ʾ���������
    struct Snake s, * snake = &s;      //�����ߵĽṹ��ָ�벢ָ���ߵĽṹ��
    struct Food f, * food = &f;       //����ʳ��Ľṹ��ָ�벢ָ��ʳ��Ľṹ��


    make_frame();         //������Ϸ���� 
    init_snake(snake);        //��ʼ����
    get_food(hOut, snake, food);      //�������ʳ��
    while (1)
    {
        print_information(hOut, snake, food);   //��ӡ�˵���Ϣ
        a[0] = snake->x[0];       //��ס��β�ĺ�����
        a[1] = snake->y[0];       //��ס��β��������
        u = 0;
        if (_kbhit())
        {/* �ж��Ƿ��¼��̣�������£�ch���ռ������� */
            ch = _getch();
            if (_kbhit())
            {/* ����������̣������ */
                Sleep(20);
                u = 1;
            }
        }
        switch (ch)
        {
        case 72:
        {/* �����ƶ� */
            move_snake(hOut, snake);   //�ƶ���
            snake->y[snake->length - 1] -= 1; //��ͷ�������������ƣ�����1
            break;
        }
        case 80:
        {/* �����ƶ� */
            move_snake(hOut, snake);   //�ƶ���
            snake->y[snake->length - 1] += 1; //��ͷ�������������ƣ�����1
            break;
        }
        case 75:
        {/* �����ƶ� */
            move_snake(hOut, snake);   //�ƶ���
            snake->x[snake->length - 1] -= 2; //��ͷ�ĺ����������ƣ�����2
            break;
        }
        case 77:
        {/* �����ƶ� */
            move_snake(hOut, snake);   //�ƶ���
            snake->x[snake->length - 1] += 2; //��ͷ�ĺ����������ƣ�����2
            break;
        }
        }
        through_wall(hOut, snake, ch);    //��ǽ   
        eat_food(hOut, snake, food);     //��ʳ��
        print_snake(hOut, snake);     //��ӡ��
        if (if_die(snake) == 0 || ch == 27 || snake->speed < 50)
        {/* ��Ϸ����������1.���������� 2.��Esc�� 3.�ٶ�Ϊ50ms */
            gotoxy(hOut, FrameX + Frame_width - 2, FrameY + Frame_height / 2 - 1);
            printf("Game Over");
            Sleep(2000);
            return snake->count * 10;
            break;
        }
        if (u == 0)
        {
            Sleep(snake->speed);      //�ӳ�ʱ��
        }
        else
        {
            Sleep(10);
        }
    }
}
static int game_4_snack()
{
    int score;
    system("color 0D");  //�����ı�Ϊ�ۺ�ɫ
    score =  start_game4();   //��ʼ��Ϸ

    over_game();   //������Ϸ
    return score;
    
}

