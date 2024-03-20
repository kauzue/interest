#pragma warning(disable:4996)

#include <stdio.h>
#include <windows.h>

#include "cursor.h"
#include "interest.h"

enum DATA { NAME, MONEY, INTEREST_RATE };

void menu();
void regist();
void check_register();
void modify_data();
void delete_data(int);
void modify(int, int);
void person_data(int);

int g_person_num;

bool init()
{

	FILE* pb = fopen("person.bin", "rb");
	if (pb == NULL) {
		puts("��� ���� ���� ����");
		system("pause");
		return false;
	}

	g_person_num = fread(s_person, sizeof(person_t), NUM_MAX_PERSON, pb);

	fclose(pb);
	return true;
}

void menu()
{
	int key, x, y;
	int money;

	while (true) {
		key = 0;
		x = 2;
		y = 2;

		system("cls");

		printf("���� \n");

		MoveCursor(x - 2, y);
		printf("> ��� ���");

		MoveCursor(x, y + 2);
		printf("����� Ȯ��");

		MoveCursor(x, y + 4);
		printf("���� ����");

		MoveCursor(x, y + 6);
		printf("����");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 2) {
					MoveCursor(x - 2, y);
					printf(" ");
					MoveCursor(x - 2, y -= 2);
					printf(">");
				}
				break;
			}

			case DOWN: {
				if (y < 8) {
					MoveCursor(x - 2, y);
					printf(" ");

					MoveCursor(x - 2, y += 2);
					printf(">");
				}
				break;
			}

			case ENTER: {
				system("cls");

				switch (y) {
				case 2: {
					regist();
					break;
				}

				case 4: {
					if (g_person_num == 0) {
						printf("��ϵ� ����� �����ϴ�. \n");
						system("pause");
					}

					else {
						check_register();
					}

					break;
				}

				case 6: {
					if (g_person_num == 0) {
						printf("��ϵ� ����� �����ϴ�. \n");
						system("pause");
					}

					else {
						modify_data();
					}

					break;
				}

				case 8: {
					return;
				}
				}
			}
			}
		}
	}
}

void regist()
{
	person_t person;

	FILE* pb = fopen("person.bin", "ab");
	if (pb == NULL) {
		puts("��� ���� ���� ����");
		return;
	}

	printf("��� \n \n");

	printf("�̸� : ");
	scanf_s("%s", person.name, MAX_MSG_LEN);

	printf("������ �ݾ� : ");
	scanf_s("%llu", &person.money);

	printf("������ : ");
	scanf_s("%u", &person.interest_rate);

	memcpy(&s_person[g_person_num], &person, sizeof(person_t));
	++g_person_num;

	fwrite(&person, sizeof(person_t), 1, pb);
	fclose(pb);
}

void check_register()
{
	int key, x, y;

	while (true) {
		key = 0;
		x = 2;
		y = 2;

		system("cls");

		printf("����� Ȯ�� \n \n");

		for (int i = 0; i < g_person_num; i++) {
			if (i == 0) {
				MoveCursor(x - 2, y + 2 * i);
				printf("> ");
			}

			else {
				MoveCursor(x, y + 2 * i);
			}
			printf("%s", s_person[i].name);
		}

		MoveCursor(x, y + g_person_num * 2);
		printf("����");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 2) {
					MoveCursor(x - 2, y);
					printf(" ");
					MoveCursor(x - 2, y -= 2);
					printf(">");
				}
				break;
			}

			case DOWN: {
				if (y < g_person_num * 2 + 2) {
					MoveCursor(x - 2, y);
					printf(" ");

					MoveCursor(x - 2, y += 2);
					printf(">");
				}
				break;
			}

			case ENTER: {
				system("cls");

				if (y == g_person_num * 2 + 2) {
					return;
				}

				else {
					person_data((y - 2) / 2);
				}
			}
			}
		}
	}
}

void modify_data()
{
	int key, x, y;
	int money;

	while (true) {
		key = 0;
		x = 2;
		y = 2;

		system("cls");

		printf("���� ���� \n");

		for (int i = 0; i < g_person_num; i++) {
			if (i == 0) {
				MoveCursor(x - 2, y + 2 * i);
				printf("> ");
			}

			else {
				MoveCursor(x, y + 2 * i);
			}
			printf("%s", s_person[i].name);
		}

		MoveCursor(x, y + g_person_num * 2);
		printf("����");

		while (key != 4) {
			key = ControlKey();

			switch (key) {
			case UP: {
				if (y > 2) {
					MoveCursor(x - 2, y);
					printf(" ");
					MoveCursor(x - 2, y -= 2);
					printf(">");
				}
				break;
			}

			case DOWN: {
				if (y < g_person_num * 2 + 2) {
					MoveCursor(x - 2, y);
					printf(" ");

					MoveCursor(x - 2, y += 2);
					printf(">");
				}
				break;
			}

			case ENTER: {
				int num_person = y / 2 - 1;

				if (y == g_person_num * 2 + 2) {
					return;
				}

				else {
					while (true) {
						system("cls");

						key = 0;
						x = 2;
						y = 2;

						printf("������ ������ ����ּ���. \n");

						MoveCursor(x - 2, y);
						printf("> �̸� : %s \n", s_person[num_person].name);

						MoveCursor(x, y + 2);
						printf("�ݾ� : %llu�� \n", s_person[num_person].money);

						MoveCursor(x, y + 4);
						printf("������ : %u%% \n", s_person[num_person].interest_rate);

						MoveCursor(x, y + 6);
						printf("����");

						MoveCursor(x, y + 8);
						printf("����");

						while (key != 4) {
							key = ControlKey();

							switch (key) {
							case UP: {
								if (y > 2) {
									MoveCursor(x - 2, y);
									printf(" ");
									MoveCursor(x - 2, y -= 2);
									printf(">");
								}
								break;
							}

							case DOWN: {
								if (y < 10) {
									MoveCursor(x - 2, y);
									printf(" ");

									MoveCursor(x - 2, y += 2);
									printf(">");
								}
								break;
							}

							case ENTER: {

								system("cls");

								if (y == 8) {
									delete_data(num_person);
									goto break_while;
								}

								else if (y == 10) {
									goto break_while;
								}

								else {
									y = y / 2 - 1;
									modify(num_person, y);
								}
							}
							}
						}
					}
				}
			}
			}
		}
	break_while:;
	}
}

void delete_data(int num_person)
{
	printf("������ �����Ǿ����ϴ�.");
	system("cls");

	for (int i = num_person; i < g_person_num; i++) {
		strcpy(s_person[num_person].name, s_person[num_person + 1].name);
		s_person[num_person].money = s_person[num_person + 1].money;
		s_person[num_person].interest_rate = s_person[num_person + 1].interest_rate;
	}
	g_person_num--;

	FILE* pb = fopen("person.bin", "wb");
	if (pb == NULL) {
		puts("��� ���� ���� ����");
		return false;
	}

	fwrite(s_person, sizeof(person_t), g_person_num, pb);

	fclose(pb);
}

void modify(int num_person, int num_data)
{
	printf("���� ������ ���� : ");

	switch (num_data) {
	case NAME: {
		printf("�̸� - %s \n", s_person[num_person].name);
		printf("�̸� : ");
		scanf_s("%s", s_person[num_person].name, MAX_MSG_LEN);

		break;
	}

	case MONEY: {
		printf("�� - %llu \n", s_person[num_person].money);
		printf("�� : ");
		scanf_s("%llu", &s_person[num_person].money);

		break;
	}

	case INTEREST_RATE: {
		printf("������ - %u \n", s_person[num_person].interest_rate);
		printf("������ : ");
		scanf_s("%u", &s_person[num_person].interest_rate);

		break;
	}
	}

	FILE* pb = fopen("person.bin", "wb");
	if (pb == NULL) {
		puts("��� ���� ���� ����");
		return false;
	}

	fwrite(s_person, sizeof(person_t), g_person_num, pb);

	fclose(pb);
}

void person_data(int num_person)
{
	printf("�̸� : %s \n", s_person[num_person].name);
	printf("�ݾ� : %llu�� \n", s_person[num_person].money);
	printf("������ : %u%% \n", s_person[num_person].interest_rate);
	system("pause");
}