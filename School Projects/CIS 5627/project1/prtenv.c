#include <stdio.h>

// Austin Leach

void main() {
	char* myshell = getenv("MYSHELL");
	if (myshell)
		printf ("MYSHELL is %x\n", (unsigned int)myshell);
	char* dashp = getenv("dashP");
	if (dashp)
		printf ("DASHP is %x\n", (unsigned int)dashp);
	char* shell = getenv("SHELL");
	if (shell)
		printf ("SHELL is %x\n", (unsigned int)shell);
}


