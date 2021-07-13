#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <winsock.h>
#include <mysql.h>
#include <string.h>
#pragma comment(lib,"libmysql.lib")
#include "game1.cpp"
#include "game2.cpp"
#include "game3.cpp"
#include "game4.cpp"
#include "game5.cpp"

//����ȫ�ֱ������û���sid
int sid = 0;

typedef struct g {
	int gid;
	int score;
}game;

void ScorePrint(MYSQL* mysqlPrint) {

	MYSQL_RES* result;/*ָ���ѯ�����ָ��*/
	int numFields = 0;
	int numRows = 0;
	MYSQL_FIELD* field;/*�ֶνṹָ��*/
	MYSQL_ROW row; /*���з��صĲ�ѯ��Ϣ*/
	int i = 0;
	result = mysql_store_result(mysqlPrint);//����ѯ��ȫ�������ȡ���ͻ���
	numFields = mysql_num_fields(result);//ͳ�ƽ�����е��ֶ���
	numRows = mysql_num_rows(result);//ͳ�ƽ����������
	while (field = mysql_fetch_field(result))//���ؽ�����е�����Ϣ(�ֶ�)
		printf("%s\t", field->name);
	printf("\n");
	if (result)
	{
		while (row = mysql_fetch_row(result))//���ؽ�������еļ�¼
		{
			for (i = 0; i < numFields; i++)
			{
				printf("%s\t", row[i]);
			}
			printf("\n");
		}
	}
	mysql_free_result(result);//�ͷ�result�ռ䣬�����ڴ�й©
}

//�ú���ִ��һ��select�͵�sql��䣬����ӡ��ֵ����ʧ���򷴻�0
void SelectMYSQL(MYSQL* mysql, const char* query) {
	int res;

	res = mysql_real_query(mysql, query,strlen(query));
	//�����0��ִ�гɹ�
	if (res) {
		printf("failed");
	}
	else {
		ScorePrint(mysql);
	}
}

void Show_ranking_list(MYSQL* mysql) {
	int gid;
	char query[200] = { 0 };
	printf("��ѡ�������Ϸ\n");
	printf("1.....�ɻ���ս\n");
	printf("2.....ɨ    ��\n");
	printf("3.....2 0 4  8\n");
	printf("4.....̰ �� ��\n");
	printf("5.....2  1  ��\n");
	scanf("%d", &gid);

	sprintf(query, "SELECT s.sname �û��� ,p.score ���� FROM student s,play p WHERE s.sid = p.sid AND p.gid = %d ORDER BY p.score DESC LIMIT 5 ", gid);
	//printf("%s", query);
	SelectMYSQL(mysql, query);

}

game* (Game(MYSQL* mysql))
{
	game play = { 0 };
	printf("��ѡ����Ĳ���\n");
	printf("1.....�ɻ���ս\n");
	printf("2.....ɨ    ��\n");
	printf("3.....2 0 4  8\n");
	printf("4.....̰ �� ��\n");
	printf("5.....2  1  ��\n");
	printf("6.....�� �� ��\n");
	printf("7.....��    ��\n");
	scanf("%d", &play.gid);
	switch (play.gid) {
	case 1: play.score = game_1_plane(); return &play; break;
	case 2: play.score = game_2_mineClearance(); return &play; break;
	case 3:play.score = game_3_2048(); return &play;break;
	case 4:play.score = game_4_snack(); return &play; break;
	case 5:play.score = game_5_heyjack(); return &play; break;
	case 6:Show_ranking_list(mysql); return 0; break;
	case 7: printf("�Ѿ��˳���Ϸϵͳ��"); return &play;
	}

}

void InsertScore(MYSQL* mysql, int sid,int gid, int score)
{
	int t;
	char query[120];

	/* ƴ��sql���� */
	sprintf(query, "INSERT INTO play VALUES (null,%d,%d,%d)", sid, gid, score);
	//printf("%s\n", query);

	t = mysql_real_query(mysql, query, strlen(query));
	if (t) {
		//printf("Failed to query: %s\n", mysql_error(mysql));
	}
	else {
		//printf("\nInsert sucessfully!\n");
	}

}

const char* (FindMYSQL(MYSQL* mysql, const char* find_table, const char* find_name, const char* field_name, const char* id))
{
	MYSQL_RES* result;
	int numFields = 0;
	int numRows = 0;
	MYSQL_FIELD* field;/*�ֶνṹָ��*/
	MYSQL_ROW row; /*���з��صĲ�ѯ��Ϣ*/
	const char* tresult;
	int t;

	char query[120];

	sprintf(query, "SELECT %s FROM %s WHERE %s =\"%s\"", find_name, find_table, field_name, id);
	//printf("%s\n", query);

	int res = mysql_query(mysql, query);
	if (res) {
		printf("failed");
		return "";
	}
	else {
		result = mysql_store_result(mysql);//����ѯ��ȫ�������ȡ���ͻ���
		numFields = mysql_num_fields(result);//ͳ�ƽ�����е��ֶ���
		numRows = mysql_num_rows(result);//ͳ�ƽ����������
		while (field = mysql_fetch_field(result))//���ؽ�����е�����Ϣ(�ֶ�)
			//printf("%s\t", field->name);
			printf("\n");
		if (result)
		{
			while (row = mysql_fetch_row(result))//���ؽ�������еļ�¼
			{
				for (int i = 0; i < numFields; i++)
				{
					//printf("%s\t", row[i]);
					mysql_free_result(result);//�ͷ�result�ռ䣬�����ڴ�й©
					return row[i];
				}
				printf("\n");
			}
		}
		else {
			return NULL;
		}
	}

}

MYSQL* (Connect(MYSQL connect)) {
	mysql_init(&connect);

	//ʵ���������ݿ�
	if (mysql_real_connect(&connect, "localhost", "root", "123456", "G", 3306, 0, 0)) {
		//printf("���ӳɹ�\n");
		//���ñ����ʽ
		mysql_query(&connect, "set names gbk;");
		return &connect;
	}
	else {
		//printf("����ʧ��");
		exit(-1);
	}
}

int LoginIn(MYSQL* mysql) 
{

	const char* acount;
	char scanf_acount[20] = { 0 };
	char scanf_password[20] = { 0 };
	const char* password;
	int choice = -1;

	printf("�������˺ţ�");
	scanf("%s", scanf_acount);
	printf("���������룺");
	scanf("%s", scanf_password);
	acount = FindMYSQL(mysql, "student", "acount", "acount", scanf_acount);
	if (acount) {
		password = FindMYSQL(mysql, "student", "password", "acount", scanf_acount);
		if (strcmp(password, scanf_password) == 0) {
			printf("��¼�ɹ���\n��ӭ�û���¼��\n");
			sid = atoi(FindMYSQL(mysql, "student","sid", "acount", scanf_acount));
			//printf("\n%d!!!!!!!!\n",sid);
			return choice;

		}
		else {
			printf("�������\n�Ƿ�ע�᣿��1.yes��0.no��:");
			scanf("%d", &choice);
			return choice;
			
		}
	}
	else {
		printf("�û������ڣ�\n�Ƿ�ע�᣿��1.yes��0.no��:");
		scanf("%d", &choice);
		return choice;
	}
}

void LoginUp(MYSQL* mysql)
{
	int t;
	char query[120] = { 0 };
	char sname[20] = { 0 };
	char acount[20] = { 0 };
	char password[20] = { 0 };

	printf("�������û�����");
	scanf("%s", sname);
	printf("�������˺ţ�");
	scanf("%s", acount);
	printf("���������룺");
	scanf("%s", password);

	char i = '"';

	/* ƴ��sql���� */
	sprintf(query, "INSERT INTO student values (null, %c%s%c, %c%s%c, %c%s%c)",i,sname,i,i,acount,i,i,password,i);
	//printf("%s\n", query);

	t = mysql_real_query(mysql, query, strlen(query));
	if (t) {
		//printf("Failed to query: %s\n", mysql_error(mysql));
		printf("ע��ʧ�ܣ�\n");
	}
	else {
		//printf("\nInsert sucessfully!\n");
		printf("ע��ɹ�!\n");
	}

}

int main() {
	MYSQL connect = { 0 };
	MYSQL* mysql=NULL;
	game* play = NULL;
	int choice;

	mysql = Connect(connect);
	printf("��ӭ��\n����������ѡ��(1.��¼��2.ע�ᣬ0.�˳���ϵͳ����");
	scanf("%d", &choice);
	while (choice) {
		if (choice == 1) {
loginin:
			int e = LoginIn(mysql);
			if (e == -1) {
				printf("��ӭ������Ϸϵͳ��");
			}
			else if (e == 1) {
				goto loginup;
			}
			else if (e == 0) {
				goto loginin;
			}

playagain:
			play = Game(mysql);
			if(play != NULL)
				InsertScore(mysql, sid, play->gid, play->score);
			int ch = 0;
			printf("�Ƿ����½�����Ϸϵͳ��(1.yes��0.no)");
			scanf("%d", &ch);
			if (ch == 1) goto playagain; else {
				printf("����������ѡ��(1.��¼��2.ע�ᣬ0.�˳���ϵͳ����");
				scanf("%d", &choice);
			}
		}
		else if (choice == 2) {
loginup:
			LoginUp(mysql);
			printf("����������ѡ��(1.��¼��2.ע�ᣬ0.�˳���ϵͳ����");
			scanf("%d", &choice);
		}
		else {
			;
			printf("�޷�ʶ���ѡ���\n����������ѡ��(1.��¼��2.ע�ᣬ0.�˳���ϵͳ����");
			scanf("%d", &choice);
		}
	}

	mysql_close(&connect);

	return 0;

}