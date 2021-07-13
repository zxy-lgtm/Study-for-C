#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>

//���̣�1Ϊ��Ұ��죬2Ϊ����
int map[19][19] = { 0 };
int x_player = 10, y_player = 10;

//�ٴο�ʼ��Ϸ�ĳ�ʼ��
void reset() {
    int i, j;
    for (i = 0; i < 19; i++) {
        for (j = 0; j < 19; j++) {
            map[i][j] = 0;
        }
    }
}

//��ӡ��Ϸ����
void show() {
    int i, j;
    //��ӡ�ϱ߽�
    for (i = 0; i <= 19; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    for (i = 0; i < 22; i++) {
        printf("---");
    }
    printf("\n");
    for (i = 0; i < 19; i++) {
        printf("%2d|", i + 1);
        for (j = 0; j < 19; j++) {
            switch (map[i][j]) {
            case 0: printf("   "); break;
            case 1: printf(" �� "); break;
            case 2: printf(" �� "); break;
            }
        }
        printf("\n");
    }
}

//���û��йصĸ���
int updateWithUser() {
    int x, y;
    printf("���������꣺"); scanf("%d %d", &x, &y);
    //�ж������Ƿ�Ϸ�
    x = x - 1; y = y - 1;
    if (x < 0 || y < 0 || x>19 || y>19) {
        printf("����Ƿ�\n");
        return -1;
    }
    //�ж������Ƿ�ռ��
    if (map[x][y] != 0) {
        printf("�������Ѿ��������ˣ��㲻���ڴ�����\n");
        return 0;
    }
    map[x][y] = 1;
    x_player = x; y_player = y;
    //updateWithoutUser(x,y);
    return 1;
}

//���û��޹صĸ��£���������
int updateWithoutUser(int px, int py) {
    int x, y;
    int k;
    while (1) {
        x = rand() % 19 + 1;
        y = rand() % 19 + 1;
        k = rand() % 8 + 1;
        switch (k) {
        case 1:x = px;  y = py - 1; break;
        case 2:x = px;  y = py + 1; break;
        case 3:x = px - 1; y = py - 1; break;
        case 4:x = px - 1; y = py;  break;
        case 5:x = px - 1; y = py + 1; break;
        case 6:x = px + 1; y = py - 1; break;
        case 7:x = px + 1; y = py;  break;
        case 8:x = px + 1; y = py + 1; break;
        }
        if (x < 0 || y < 0 || x>19 || y>19) {
            continue;
        }
        else if (map[x][y] == 0) {
            break;
        }
    }
    map[x][y] = 2;
    return 0;
}

//Ѱ��ʤ����
int findWinner() {
    int i, j, k, isover = 0, winner = 0, fflag = 0;;
    int num, flag_x = 1, flag_y = 1, flag_xie1 = 1, flag_xie2 = 1, flag_xie3 = 1;
    for (i = 0; i < 19; i++) {
        for (j = 0; j < 19; j++) {
            flag_x = 1; flag_y = 1; flag_xie1 = 1; flag_xie2 = 1; flag_xie3 = 1;
            if (map[i][j] != 0) {
                num = map[i][j];
                //�ж���
                for (k = 0; k < 5; k++) {
                    if (map[i][j + k] != num) {
                        flag_x = 0;
                    }
                }
                //�ж���
                for (k = 0; k < 5; k++) {
                    if (map[i + k][j] != num) {
                        flag_y = 0;

                    }
                }
                for (k = 0; k < 5; k++) {
                    if (map[i + k][j + k] != num) {
                        flag_xie1 = 0;

                    }
                }
                for (k = 0; k < 5; k++) {
                    if (map[i - k][j + k] != num) {
                        flag_xie2 = 0;

                    }
                }
                for (k = 0; k < 5; k++) {
                    if (map[i + k][j - k] != num) {
                        flag_xie3 = 0;

                    }
                }
                fflag += flag_x; fflag += flag_y; fflag += flag_xie1; fflag += flag_xie2; fflag += flag_xie3;
                printf("%d", fflag);
                if ((fflag) != 0) {
                    isover = 1;
                    printf("win");
                    winner = num;
                    return winner;
                }
            }
        }
    }

    return winner;
}

int game() {
    int flag = 0;
    int winner = 1;
    show();
    while (1) {
    lable:
        flag = updateWithUser();
        if (flag != 1) {
            printf("����Ƿ�");
            goto lable;
        }
        updateWithoutUser(x_player, y_player);
        system("cls");
        show();
        //Sleep(1000);
        winner = findWinner();
        if (winner == 1) {
            printf("��ϲ��Ӯ��");
            return 0;
        }
        else if (winner == 2) {
            printf("���ⶼӮ���ˣ�Ҳ��̫ǿ��\n");
            printf("������");
            return -1;
        }
    }

}

int main()
{
    printf("��ӭ����������");
    system("pause");
    game();
}