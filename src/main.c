#include "inc\bush.h"

int main(void) {
	readin();
	if (analyse())
		return -1;
	if (hay())
		return -1;
	bind();
	return 0;
}

