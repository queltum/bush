#define BUSH_DEBUG

#include "inc\io.h"
#include "inc\utils.h"
#include "inc\bush.h"

int main(void) {
	char *s;

	if (analyse(s = readin()))
		return -1;
	bush(s);
	return 0;
}

