/*
 * BufferMPI.c

 *
 *  Created on: 18 Tem 2016
 *      Author: servet
 */

/* example of sequential Unix write into a common file */
#include "mpi.h"
#include <stdio.h>
#define BUFSIZE 100
int main(int argc, char *argv[])
{
	int	 i, myrank, numprocs, buf[BUFSIZE];

	MPI_Status status;

	FILE *myfile;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	for (i=0; i<BUFSIZE; i++)
		buf[i] = myrank * BUFSIZE + i;

	if (myrank != 0)
		MPI_Send(buf, BUFSIZE, MPI_INT, 0, 99, MPI_COMM_WORLD);

	else {
		myfile = fopen("testfile.txt", "w");
		fwrite(buf, sizeof(int), BUFSIZE, myfile);
		for (i=1; i<numprocs; i++) {
			MPI_Recv(buf, BUFSIZE, MPI_INT, i, 99, MPI_COMM_WORLD,&status);
			printf("%d\t",buf[i]);
			}
		printf("\n");
		fclose(myfile);
	}

	MPI_Finalize();
	return 0;
}

