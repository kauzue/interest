#pragma once

#include <stdbool.h>

#define NUM_MAX_PERSON 100
#define MAX_MSG_LEN 256

typedef struct person {
	char name[MAX_MSG_LEN];
	int money;
	int interest_rate;
}person_t;

person_t s_person[NUM_MAX_PERSON];

bool init();
void menu();
void regist();
void check_register();
void person_data(int);