/*
 * This is a replacement to the cp command on unix machines that also
 * outputs the time it takes to copy for analysis pruposes. It takes arguments that
 * define the files it is copying and the size of the buffer. Included is a graph
 * that has logged the output times for a varying level of buffer sizes.
 *
 * By: Tyler Sullivan
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main (int argc, char* args[])
{

  size_t size;
  double time_total;
  char* line;
  struct timeval time_start, time_end;

/* checks for arguments */
	if (argc != 2){
		fprintf(stderr, "USAGE: %s size\n", args[0]);
		return EXIT_FAILURE;
	}

/* convert arguments and allocate memory based on them */
  size = atoi(args[1]);
  line = malloc(size);
/* get start time */
  gettimeofday(&time_start, NULL);

/* get buffer from original file supplied by redirect */
	while((read(STDIN_FILENO, line, size)) > 0){
		if (ferror(stdin)) {
			perror("stdin");
			exit(EXIT_FAILURE);
		}
/* write buffer to copy file  suppilied by redirect */
		write(STDOUT_FILENO, line, size);

		if (ferror(stdout)) {
			perror("stdout");
			exit(EXIT_FAILURE);
		}
	}

/* free buffer and get end time */
  free(line);
  gettimeofday(&time_end, NULL);

/* calculate running time accounting for microseconds */
  time_total = (time_end.tv_sec - time_start.tv_sec) + ((time_end.tv_usec - time_start.tv_usec)/1000000.0);

/* output run time to stderr */
  fprintf(stderr, "%f\n", time_total);

	return EXIT_SUCCESS;
}
