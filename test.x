#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void
	int_handler(int);

int
	main(void)
{
	signal(SIGINT, int_handler);
	while (1)
		pause();
	return (0);
}

void
	int_handler(int sig)
{
	char c;

	signal(sig, SIG_IGN);
	printf("OUCH, did you hit Ctrl-C?\n"
			"Do you really want to quit? [y/n] ");
	c = getchar();
	if (c == 'y' || c == 'Y')
		exit(0);
	else
		signal(SIGINT, int_handler);
	getchar();
}
