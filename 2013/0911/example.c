#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

#define ASK			"Do you want another transaction"
#define TRIES		3
#define SLEEPTIME	2
#define BEEP		putchar('\a')

main()
{
	int response;
	void ctrl_c_handler(int);

	tty_mode(0);
	set_cr_noecho_mode();
	set_nodelay_mode();
	signal(SIGINT, ctrl_c_handler);
	response = get_response(ASK, TRIES);
	tty_mode(1);
	return response;
}
get_response(char *question, int maxtries)
{
	int input;
	printf("%s(y/n)?", question);
	fflush(stdout);
	while (1)
	{
		sleep(SLEEPTIME);
		input = tolower(get_ok_char());
		if (input == 'y') return 0;
		if (input == 'n') return 1;
		if (maxtries-- == 0) return 2;
		BEEP;
	}
}
get_ok_char()
{
	int c;
	while ((c = getchar()) != EOF && strchr("yYnN", c) == NULL);
	return c;
}
set_cr_noecho_mode()
{
	struct termios ttystate;
	tcgetattr(0, &ttystate);
	ttystate.c_lflag &= ~ICANON;
	ttystate.c_lflag &= ~ECHO;
	ttystate.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &ttystate);
}
set_nodelay_mode()
{
	int termflags;
	termflags = fcntl(0, F_GETFL);
	termflags |= O_NODALAY;
	fcntl(0, F_SETFL, termflags);
}

tty_mode(int how)
{
	static struct termious original_mode;
	static int 		original_flags;
	static int 		stored = 0;
	if ( how == 0 )
	{
		tcgetattr(0, &orginal_mode);
		original_flags = fcntl(0, F_GETFL);
		stored = 1;
	}
	else if (stored)
	{
		tcsetattr(0, TCSAOW, &original_mode);
		fcntl(0, F_SETFL, original_flags);
	}
}
void ctrl_c_handler(int signum)
{
	tty_mode(1);
	exit(1);
}
