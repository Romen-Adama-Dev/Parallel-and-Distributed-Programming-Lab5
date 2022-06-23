#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
        if(strtol(argv[1],NULL,10)>=0){

                if(!argc<2){

                        int rank,ranksent,size,source,dest,tag,i;
                        int n=strtol(argv[1],NULL,10);
                        MPI_Request request1, request2;
                        MPI_Status status1, status2;
                        MPI_Init(&argc,&argv);
                        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
                        MPI_Comm_size(MPI_COMM_WORLD,&size);
                        if(rank==0)
                        {
                        dest=0;
                        tag=0;
                        for(i=1;i<size;i++)
                                MPI_Isend(&rank,1,MPI_INT,i,tag,MPI_COMM_WORLD, &request1);
                        printf("Recived %d process %d\n",rank,n);
                        }
                        else
                        {
                        MPI_Irecv(&ranksent,1,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,&request2);
                        MPI_Wait( &request1, &status1 );
                        printf("Recived %d process %d from %d\n",rank,n,rank-1);
                        MPI_Wait( &request2, &status2 );
                        }
                MPI_Finalize();
                return(0);
                }else{
                        printf("Not enough arguments\n");
                        printf("Try again\n");
                }
	}else{
                printf("Number cannot be negative\n");
        }

}