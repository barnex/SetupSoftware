#include "io.h"

int testmain(int argc, char**argv){
	setProgName(argv[0]);
	int badfd = 77;
	ewrite(badfd, "hello", 5);
	return 0;
}
