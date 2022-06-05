#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable: 4996)
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

//Ƶ���õ��𳵱����Ϣ
#define HEADER1 "------------------------------------BOOK TICKET------------------------------------\n"
#define HEADER2 "|   number    |start city|reach city|takeoff time|receive time|price|ticket number|\n"
#define HEADER3 "|-------------|----------|----------|------------|------------|-----|-------------|\n"
#define FORMAT "|%-10s   |%-10s|%-10s|%-10s  |%-10s  |%5d| %5d       |\n"
#define DATA p->data.num,p->data.startcity,p->data.reachcity,p->data.takeofftime,p->data.receivetime,p->data.price,p->data.ticketnum

//��Ʊ��Ϣ
struct train
{	
	char num[10];//�г���
	char startcity[10];//��������
	char reachcity[10];//�ﵽ����
	char takeofftime[10];//����ʱ��
	char receivetime[10];//����ʱ��
	int price;//Ʊ��
	int ticketnum;//Ʊ��
};

//��Ʊ�˵���Ϣ
struct man
{
	char num[10];//ID
	char name[10];//����
	int bookNum;//����Ʊ��
};

//��Ʊ��Ϣ����Ľ��ṹ
typedef struct node
{
	struct train data;
	struct node* next;
}TrainNode,*TrainLink;

//��Ʊ������Ľ��ṹ
typedef struct Man
{
	struct man data;
	struct Man* next;
}BookNode,*BookLink;

//ȫ�ֱ����Ƿ񱣴���Ϣ
int saveflag;

//��������
void menu();//�˵���ʾ
void TrainInfo(TrainLink trainHeader);//��ӻ���Ϣ
void searchtrain(TrainLink trainHeader);//��ѯ����Ϣ
void printHeader();//��ʽ�������ͷ
void printData(TrainLink trainNode);//��ʽ�������������
void SaveTrainInfo(TrainLink trainHeader);//�������Ϣ
void SaveBookInfo(BookLink trainHeader);//�����û���Ϣ
void Bookticket(TrainLink trainHeader, BookLink bookHeader);//��Ʊ
void Modify(TrainLink trainHeader);//�޸���Ϣ
void showTrain(TrainLink trainHeader);//��ʾ�г���Ϣ
//#include "header.h"

/*
	��Ҫ���ܣ�
	��0���˳��𳵶�Ʊϵͳ
	��1��������ӻ�Ʊ��Ϣ���棬����ʾ������𳵵ĳ��Ρ���㡢�յ㡢����ʱ�䡢����ʱ�䡢Ʊ�ۺͶ�����Ʊ����
	��2����ѯ��Ʊ��Ϣ�����ֲ�ѯ��ʽ��һ�ְ����β�ѯ����һ�ְ�����ص��ѯ��
	��3�����붩Ʊϵͳ�����ݵ��׵ص��ѯ��Ʊ��
	��4�������޸Ļ�Ʊ���棬������ʾ�޸Ļ�Ʊ��Ϣ��
	��5��չʾ���еĻ�Ʊ��
	��6����Ʊ��Ϣ�Ͷ�Ʊ����Ϣ�ı��档
*/

int main()
{
	FILE* fp1, * fp2;
	TrainLink trainTemp2, trainTemp1, trainHeader;//����Ϣ��ʱ���1��2��ͷ���
	BookLink bookTemp2, bookTemp1, bookHeader;//Ԥ����Ϣ��ʱ���1��2��ͷ���
	char ch1 = 0, ch2 = 0;
	int sel = 0;//ѡ��

	trainHeader = (TrainNode*)malloc(sizeof(TrainNode));//����ͷ���
	if (trainHeader == NULL)
	{
		printf("Memory allocation error!\n");//�ڴ����ʧ��
		exit(1);
	}
	trainHeader->next = NULL;
	trainTemp1 = trainHeader;

	bookHeader = (BookNode*)malloc(sizeof(BookNode));
	if (bookHeader == NULL)
	{
		printf("Memory allocation error!\n");//�ڴ����ʧ��
		exit(1);
	}
	bookHeader->next = NULL;
	bookTemp1 = bookHeader;

	fp1 = fopen("train.txt", "ab+");//�򿪴洢��Ʊ��Ϣ���ļ�
	if (fp1 == NULL)
	{
		printf("can't open this file!\n");
		exit(1);
	}
	while (!feof(fp1))
	{
		trainTemp2 = (TrainNode*)malloc(sizeof(TrainNode));
		if (trainTemp2 == NULL)
		{
			printf("Memory allocation error!\n");
			exit(1);
		}
		if (fread(trainTemp2, sizeof(TrainNode), 1, fp1) == 1)//�Ӵ����ļ���ȡ���ݣ�����������
		{
			trainTemp2->next = NULL;
			trainTemp1->next = trainTemp2;
			trainTemp1 = trainTemp2;
		}
	}
	fclose(fp1);

	fp2 = fopen("man.txt", "ab+");//�򿪶�Ʊ�ͻ���Ϣ���ļ�
	if (fp2 == NULL)
	{
		printf("can't open this file!\n");
		exit(1);
	}
	while (!feof(fp2))
	{
		bookTemp2 = (BookNode*)malloc(sizeof(BookNode));
		if (bookTemp2 == NULL)
		{
			printf("Memory allocation error!\n");
			exit(1);
		}
		if (fread(bookTemp2, sizeof(BookNode), 1, fp2) == 1)
		{
			bookTemp2->next = NULL;
			bookTemp1->next = bookTemp2;
			bookTemp1 = bookTemp2;
		}
	}
	fclose(fp2);

	while (1)
	{
		system("cls");
		menu();
		printf("\tplease choose (0-6):   ");
		scanf("%d", &sel);//����ѡ��
		system("cls");
		if (sel == 0)
		{
			if (saveflag == 1)//���˳�ʱ�ж���Ϣ�Ƿ񱣴�
			{
				getchar();
				printf("\nthe file have been chagned!do you want to save it(y/n)?\n");
				scanf("%c", &ch1);
				if (ch1 == 'y' || ch1 == 'Y')
				{
					SaveBookInfo(bookHeader);
					SaveTrainInfo(trainHeader);
				}
			}
			printf("\nThank you!!!You are Welcome too\n");
			Sleep(1000);
			exit(0);
		}
		switch (sel)//���벻ͬ��ֵѡ���Ӧ�Ĳ���
		{
		case 1:
			TrainInfo(trainHeader);//�����Ʊ��Ϣ
			break;
		case 2:
			searchtrain(trainHeader);//���һ�Ʊ��Ϣ
			break;
		case 3:
			Bookticket(trainHeader, bookHeader);//����Ʊ
			break;
		case 4:
			Modify(trainHeader);//�޸Ļ�Ʊ��Ϣ
			break;
		case 5:
			showTrain(trainHeader);//չʾ��Ʊ
			break;
		case 6:
			SaveTrainInfo(trainHeader);//�����Ʊ��Ϣ
			SaveBookInfo(bookHeader);//���涩Ʊ��Ϣ
			break;
		case 0:
			return 0;
		}
		printf("\nplease press any key to continue.......\n");
		getch();
	}
}

void menu()
{
	printf("\n\n\n\n");
	puts("\t\t----------------------------------------------------------------|");
	puts("\t\t|                        Booking Tickets                        |");
	puts("\t\t----------------------------------------------------------------|");
	puts("\t\t|         0.quit the system                                     |");
	puts("\t\t|         1.Insert a train information                          |");
	puts("\t\t|         2.Search a train information                          |");
	puts("\t\t|         3.Book a train ticket                                 |");
	puts("\t\t|         4.Modify the train information                        |");
	puts("\t\t|         5.Show the train information                          |");
	puts("\t\t|         6.save information to file                            |");
	puts("\t\t----------------------------------------------------------------|");
}

void TrainInfo(TrainLink trainHeader)
{
	TrainLink p, r, s;
	char num[10];
	r = trainHeader;//ͷ���
	s = trainHeader->next;//��һ�����

	while (r->next != NULL)
	{
		r = r->next;
	}	//rΪβ�ڵ�

	while (1)
	{
		printf("please input the number of the train(0-return)");//0���ţ�����������
		scanf("%s", num);
		if (strcmp(num, "0") == 0)
		{
			break;
		}
		while (s)//�Ƚϳ���
		{
			if (strcmp(s->data.num, num) == 0)//���Ŵ���
			{
				printf("the train '%s' is existing!\n", num);
				return;
			}
			s = s->next;
		}
		p = (TrainNode*)malloc(sizeof(TrainNode));//�����½��
		if (p == NULL)
		{
			printf("Memory allocation error!\n");//����ʧ��
			exit(1);
		}
		strcpy(p->data.num, num);//���Ƴ���
		printf("Input the city where the train will start:");//�����������
		scanf("%s", p->data.startcity);
		printf("Input the city where the train will reach:");//���뵽�����
		scanf("%s", p->data.reachcity);
		printf("Input the time which the train take off:");//���뵽��ʱ��
		scanf("%s", p->data.takeofftime);
		printf("Input the time which the train receive:");//���뵽��ʱ��
		scanf("%s", p->data.receivetime);
		printf("Input the price of ticket:");//�����Ʊ��
		scanf("%d", &p->data.price);
		printf("Input the number of booked tickets:");//����Ԥ��Ʊ��
		scanf("%d", &p->data.ticketnum);
		p->next = NULL;//�½��ָ��NULL
		r->next = p;//β���ָ���½��
		r = p;//����β���
		saveflag = 1;
	}
}

void searchtrain(TrainLink trainHeader)
{
	TrainLink s[10], r;
	int sel = 0, k = 0, i = 0;
	char str1[5], str2[10];
	str1[0] = '\0';
	str2[0] = '\0';

	if (!trainHeader->next)
	{
		puts("There is no any record!");
		return;
	}
	printf("Choose the way:\n\n1:according to the number of train;\n2:according to the city:\n");
	scanf("%d", &sel);//����ѡ���ź�
	if (sel == 1)
	{
		printf("Input the number of train you want:");//���Ų�ѯ
		scanf("%s", str1);
		r = trainHeader->next;
		while (r != NULL)
		{
			if (strcmp(str1, r->data.num) == 0)
			{
				s[i++] = r;//�����¼
				break;
			}
			else
			{
				r = r->next;
			}
		}
	}
	else if (sel == 2)
	{
		printf("Input the city you want:");//Ŀ�ĳ��в�ѯ
		scanf("%s", str2);
		r = trainHeader->next;
		while (r != NULL)
		{
			if (strcmp(str2, r->data.reachcity) == 0)
			{
				s[i++] = r;//�����¼
			}
			r = r->next;
		}
	}
	if (i == 0)
	{
		puts("can not find!");//û����Ӧ��¼
		return;
	}
	else
	{
		printHeader();//�����ͷ
		for (k = 0; k < i; ++k)
		{
			printData(s[k]);//�������Ϣ
		}
	}
}


void printHeader()
{
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
}

void printData(TrainLink trainNode)
{
	TrainLink p;
	p = trainNode;
	printf(FORMAT, DATA);
}

void SaveTrainInfo(TrainLink trainHeader)
{
	FILE* fp;
	TrainLink p;
	int count = 0, flag = 1;
	fp = fopen("train.txt", "wb");//��ֻд�������ļ�
	if (fp == NULL)
	{
		printf("the file can't be opened!");
		return;
	}
	p = trainHeader->next;
	while (p)
	{
		if (fwrite(p, sizeof(TrainNode), 1, fp) == 1)//������ļ�д�����ݿ�
		{
			p = p->next;
			count++;
		}
		else
		{
			flag = 0;
			break;
		}
	}
	if (flag)
	{
		printf("save %d train records\n", count);
		saveflag = 0;
	}
	fclose(fp);
}

void SaveBookInfo(BookLink trainHeader)
{
	FILE* fp;
	BookLink p;
	int count = 0, flag = 1;
	fp = fopen("man.txt", "wb");
	if (fp == NULL)
	{
		printf("the file can't be opened!\n");
		return;
	}
	p = trainHeader->next;
	while (p)
	{
		if (fwrite(p, sizeof(p), 1, fp) == 1)
		{
			p = p->next;
			count++;
		}
		else
		{
			flag = 0;
			break;
		}
	}
	if (flag)
	{
		printf("saved %d booking records\n", count);
		saveflag = 0;
	}
	fclose(fp);
}

void Bookticket(TrainLink trainHeader, BookLink bookHeader)
{
	TrainLink r[10], p;
	char ch[2], tnum[10], str[10], str1[10], str2[10];
	ch[0] = '\0';
	tnum[0] = '\0';
	str1[0] = '\0';
	str2[0] = '\0';
	BookLink q, h;
	int i = 0, t = 0, flag = 0, dnum;
	q = bookHeader;
	while (q->next != NULL)
	{
		q = q->next;
	}
	printf("Input the city you want to go:");
	scanf("%s", &str);//����Ҫ����ĳ���
	p = trainHeader->next;
	while (p != NULL)//����pָ��
	{
		if (strcmp(p->data.reachcity, str) == 0)//����Ƿ�ƥ��
		{
			r[i++] = p;//��¼��������r
		}
		p = p->next;
	}
	printf("\n\nthe number of record have %d\n", i);
	printHeader();
	for (t = 0; t < i; ++t)
	{
		printData(r[t]);
	}
	if (i == 0)
	{
		printf("\nSorry!Can't find the train for you!\n");
	}
	else
	{
		printf("\ndo you want to book it?<y/n>\n");
		scanf("%s", ch);
		if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
		{
			h = (BookNode*)malloc(sizeof(BookNode));
			if (h == NULL)
			{
				printf("Memory allocation error!\n");
				exit(1);
			}
			printf("Input your name:");
			scanf("%s", str1);
			strcpy(h->data.name, str1);
			printf("Input your id:");
			scanf("%s", str2);
			strcpy(h->data.num, str2);
			printf("please input the number of the train:");
			scanf("%s", tnum);
			for (t = 0; t < i; ++t)
			{
				if (strcmp(r[t]->data.num, tnum) == 0)
				{
					if (r[t]->data.ticketnum < 1)
					{
						printf("sorry,no ticket!\n");
						Sleep(2000);
						return;
					}
					printf("remain %d tickets\n", r[t]->data.ticketnum);//��ʾʣ���Ʊ
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				printf("input error!\n");
				Sleep(2000);
				return;
			}
			printf("Input your bookNum:");
			scanf("%d", &dnum);//������ҪԤ����Ʊ��
			r[t]->data.ticketnum = r[t]->data.ticketnum - dnum;//���»�Ʊ
			h->data.bookNum = dnum;
			h->next = NULL;
			q->next = h;
			q = h;
			printf("\nLucky!you have booked a ticket!\n");
			saveflag = 1;
		}
	}
}

void Modify(TrainLink trainHeader)
{
	showTrain(trainHeader);
	TrainLink p;
	char tnum[10], ch;
	tnum[0] = '\0';
	p = trainHeader->next;
	if (!p)
	{
		printf("\nthere isn't record for you to modify\n");
		return;
	}
	else
	{
		printf("\nDo you want to modify it?(y/n)\n");
		getchar();
		scanf("%c", &ch);
		if (ch == 'y' || ch == 'Y')
		{
			printf("\nInput the number of the train:");
			scanf("%s", tnum);
			int isFind = 0;
			while (p != NULL)
			{
				if (strcmp(p->data.num, tnum) == 0)
				{
						printf("Input new number of train:");
						scanf("%s", p->data.num);
						printf("Input new city the train will start:");
						scanf("%s", p->data.startcity);
						printf("Input new city the train will receive:");
						scanf("%s", p->data.reachcity);
						printf("Input new time the train take off:");
						scanf("%s", p->data.takeofftime);
						printf("Input new time the train reach:");
						scanf("%s", p->data.receivetime);
						printf("Input new price of the ticket:");
						scanf("%d", &p->data.price);
						printf("Input new number of people who have booked ticket:");
						scanf("%d", &p->data.ticketnum);
						saveflag = 1;
						isFind = 1;
						break;
				}
				else
				{
					p = p->next;
				}
			}
			if (!isFind)
			{
				printf("\tCan't find the record!\n");
			}
		}
	}
}

void showTrain(TrainLink trainHeader)
{
	TrainLink p;
	p = trainHeader->next;
	printHeader();
	if (p == NULL)
	{
		printf("no records!\n");
	}
	else
	{
		while (p != NULL)
		{
			printData(p);
			p = p->next;
		}
	}
}

