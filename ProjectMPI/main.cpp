#include "mpi.h" 
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0

int main(int argc, char **argv[])
{
	int numprocs, rc, procid;
	int values[2];
	MPI_Status status;
	rc = MPI_Init(&argc, &argv);

	if (rc != MPI_SUCCESS) {
		printf("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);

	if (procid == MASTER) {
		int nr = rand() % 100; 
		int i;
		int number = nr;
		int procLeader = 0;
		for (i = 1; i < numprocs; i++) {
			MPI_Recv(&values, 2, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			if (values[1]>number)
			{
				number = values[1];
				procLeader = i;
			}
			else if ((values[1] == number) && (i>procLeader))
			{
				procLeader = i;
			}
		}
		MPI_Send(&values, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else {
		int nr = rand() % 100;
		values[0] = procid;
		values[1] = nr;
		MPI_Send(&values, 2, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}