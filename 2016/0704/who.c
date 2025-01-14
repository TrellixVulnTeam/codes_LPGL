#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST 			// include remote machine on output 


int main()
{
	struct utmp		current_record;	// read info into here
	int 			utmpfd;			// read from this descriptor
	int 			reclen = sizeof(current_record);

	if ( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1 ) {
		perror(UTMP_FILE);		// UTMP_FILE is in utmp.h 
		exit(1);
	}

	while ( read(utmpfd, &current_record, reclen) == reclen)
		show_info(&current_record);
	close(utmpfd);

	return 0;				// went ok
}


show_info(struct utmp *utbufp)
{
	printf("%-8.8s", utmpfp->ut_name);
	printf("%-8.8s", utmpfp->ut_name);
	printf("%-8.8s", utmpfp->ut_name);
	printf("%-8.8s", utmpfp->ut_name);
	printf("%-8.8s", utmpfp->ut_name);
}
