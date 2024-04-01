#pragma once

#include <stdbool.h>

#define NUM_MAX_PERSON 100
#define MAX_MSG_LEN 256

typedef struct person {
	char name[MAX_MSG_LEN];
	unsigned long long int money;
	double interest_rate;
}person_t;

person_t s_person[NUM_MAX_PERSON];

void init();
void menu();