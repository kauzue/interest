#include "interest.h"

int main(void)
{
	if (init() == false) {
		return 0;
	}

	menu();

	return 0;
}