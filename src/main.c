#include "inc\bush.h"

int main(void) {
	readin();
	if (analyse())
		return -1;
	if (hay())
		return -1;
	bind();
	printf("%llf\n", evaluate());
	return 0;
}

