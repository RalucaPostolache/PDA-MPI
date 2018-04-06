#include "mpi.h" 
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0

int v[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
int main(int argc, char **argv[])
{
	int numprocs, int rc, int nrElem, procid, int sum, int suma, int temp, int i;
	MPI_Status status;
	rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS) {
		printf("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	nrElem = 20 / numprocs;
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	if (procid == MASTER) {
		sum = 0;
		for (i = 0; i<nrElem; i++)
			sum += v[i];
		MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
	else {
		for (i = 1; i<numprocs; i++) {
			MPI_Recv(&temp, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
			suma += temp;
		}
	}
	printf("Suma este %d", suma);
	MPI_Finalize();
	return 0;
}