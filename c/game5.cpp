#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#define NUMBER 13
#define SIZE 1000
#define length 100
//���ģ�� 
static struct Player {
	int points;
	int refuse;
	int score;
}player5;
static struct Bot
{
	int points;
	int refuse;
}bot;

static void reset_game5() {
	player5.points = 0;
	player5.refuse = 0;
	bot.points = 0;
	bot.refuse = 0;
}
static int game5() {
	//��ʼ����Ϸ--------------------------------------------
	reset_game5();
	int point_tmp = 0;
	int point_sum = 0;
	int choose = 1;
	//����ѭ��--------------------------------------------
	while (!player5.refuse) {
		point_tmp = (rand() % 13) + 1;
		player5.points += point_tmp;
		printf("\n");
		printf("���õ��Ƶĵ�����:%d\n", point_tmp);
		printf("����ܵ�����:%d\n", player5.points);
		if (player5.points > 21) {
			printf("����������21��,������\n");
			player5.score -= 200;
			return 0;
		}
		else {
			printf("�㻹Ҫ����Ҫ����?(1/��  0/��):"); scanf("%d", &choose);
			if (!choose) {
				break;
			}
		}
	}
	bot.points = rand() % 21 + 1;
	if (bot.points <= 10) {
		bot.points += 10;
	}

	//�ж���Ӯ-------------------------------------------
	if (player5.points > bot.points) {
		printf("����ܵ�����:%d\n", player5.points);
		printf("���Ե��ܵ���:%d\n", bot.points);
		printf("��Ӯ��\n");
		player5.score += 100;
	}
	if (player5.points == bot.points) {
		printf("����ܵ�����:%d\n", player5.points);
		printf("���Ե��ܵ���:%d\n", bot.points);
		printf("ƽ��\n");
	}
	if (player5.points < bot.points) {
		printf("����ܵ�����:%d\n", player5.points);
		printf("���Ե��ܵ���:%d\n", bot.points);
		printf("������\n");
	}
	return 0;
}

static int game_5_heyjack()
{
	int score, choose = 1;
	player5.score = 100;
	printf("��ӭ����21��\n");
	printf("�㽫��100�����÷�\n");
	printf("Ӯ����Ϸ+100,û�б����ƶ������Ϸ-100,���ƶ��佫-200\n");
	printf("����Գ���Ҫ��ֱ���㲻��Ҫ���߱���Ϊֹ\n");
	printf("����21�㽫ֱ�ӱ���\n");
label5:
	game5();
	printf("\n��������21�㣿(1/�� 0/��):");
	scanf("%d", &choose);
	if (choose) {
		goto label5;
	}
	printf("��ķ�����:%d", player5.score);
	return player5.score;
}