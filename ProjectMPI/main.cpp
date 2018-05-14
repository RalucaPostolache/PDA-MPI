#include "mpi.h" 
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0
#define N 4
#define INF 9999

int main(int argc, char **argv)
{
	int graph[N][N] = {
		0,   INF, 9,   INF,
		4,   0,   3,   INF,
		INF, INF, 0,   2,
		INF, 1,   INF, 0
	};

	int numprocs, rc, procid;
	MPI_Status status;
	rc = MPI_Init(&argc, &argv);

	if (rc != MPI_SUCCESS) {
		printf("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);

	for (int k=0; k<N; k++)
	{
		for (int j=0; j<N; j++)
		{
			if (graph[procid][k] + graph[k][j] < graph[procid][j])
				graph[procid][j] = graph[procid][k] + graph[k][j];
		}

		MPI_Allgather(graph[procid], N, MPI_INT, graph, N, MPI_INT, MPI_COMM_WORLD);
		
		MPI_Barrier(MPI_COMM_WORLD);
	}

	if (procid == 0)
	{
		for (int i=0; i<N; i++)
		{
			for (int j=0; j<N; j++)
			{
				printf("%d ",graph[i][j]);
			}
			printf("\n");
		}
	}
	MPI_Finalize();
	return 0;
}