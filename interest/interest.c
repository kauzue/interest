#pragma warning(disable:4996)

#include <stdio.h>
#include <windows.h>

#include "cursor.h"
#include "interest.h"

int g_person_num;

bool init()
{

	FILE* pb = fopen("person.bin", "rb");
	if (pb == NULL) {
		puts("��� ���� ���� ����");
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
				if (y < 6) {
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
	scanf_s("%d", &person.money);

	printf("������ : ");
	scanf_s("%d", &person.interest_rate);

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

	system("cls");
}

void person_data(int num_person)
{
	printf("�̸� : %s \n", s_person[num_person].name);
	printf("�ݾ� : %d�� \n", s_person[num_person].money);
	printf("������ : %d%% \n", s_person[num_person].interest_rate);
	system("pause");
}