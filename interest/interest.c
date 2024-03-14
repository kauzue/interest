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
void modify(int, int);
void person_data(int);

int g_person_num;

bool init()
{

	FILE* pb = fopen("person.bin", "rb");
	if (pb == NULL) {
		puts("사람 파일 오픈 실패");
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

		printf("이자 \n");

		MoveCursor(x - 2, y);
		printf("> 사람 등록");

		MoveCursor(x, y + 2);
		printf("등록자 확인");

		MoveCursor(x, y + 4);
		printf("정보 수정");

		MoveCursor(x, y + 6);
		printf("종료");

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
						printf("등록된 사람이 없습니다. \n");
						system("pause");
					}

					else {
						check_register();
					}

					break;
				}

				case 6: {
					if (g_person_num == 0) {
						printf("등록된 사람이 없습니다. \n");
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
		puts("사람 파일 오픈 실패");
		return;
	}

	printf("등록 \n \n");

	printf("이름 : ");
	scanf_s("%s", person.name, MAX_MSG_LEN);

	printf("지불할 금액 : ");
	scanf_s("%llu", &person.money);

	printf("이자율 : ");
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

		printf("등록자 확인 \n \n");

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
		printf("이전");

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

		printf("정보 수정 \n");

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
		printf("이전");

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
				int num_player = y / 2 - 1;

				if (y == g_person_num * 2 + 2) {
					return;
				}

				else {
					while (true) {
						system("cls");

						key = 0;
						x = 2;
						y = 2;

						printf("수정할 정보를 골라주세요. \n");

						MoveCursor(x - 2, y);
						printf("> 이름 : %s \n", s_person[num_player].name);

						MoveCursor(x, y + 2);
						printf("금액 : %llu원 \n", s_person[num_player].money);

						MoveCursor(x, y + 4);
						printf("이자율 : %u%% \n", s_person[num_player].interest_rate);

						MoveCursor(x, y + 6);
						printf("이전");

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

								if (y == 8) {
									goto break_while;
								}

								else {
									y = y / 2 - 1;
									modify(num_player, y);
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

void modify(int num_person, int num_data)
{
	printf("현재 수정할 정보 : ");

	switch (num_data) {
	case NAME: {
		printf("이름 - %s \n", s_person[num_person].name);
		printf("이름 : ");
		scanf_s("%s", s_person[num_person].name, MAX_MSG_LEN);

		break;
	}

	case MONEY: {
		printf("돈 - %llu \n", s_person[num_person].money);
		printf("돈 : ");
		scanf_s("%llu", &s_person[num_person].money);

		break;
	}

	case INTEREST_RATE: {
		printf("이자율 - %u \n", s_person[num_person].interest_rate);
		printf("이자율 : ");
		scanf_s("%u", &s_person[num_person].interest_rate);

		break;
	}
	}

	FILE* pb = fopen("person.bin", "wb");
	if (pb == NULL) {
		puts("사람 파일 오픈 실패");
		return false;
	}

	fwrite(s_person, sizeof(person_t), g_person_num, pb);

	fclose(pb);
}

void person_data(int num_person)
{
	printf("이름 : %s \n", s_person[num_person].name);
	printf("금액 : %llu원 \n", s_person[num_person].money);
	printf("이자율 : %u%% \n", s_person[num_person].interest_rate);
	system("pause");
}