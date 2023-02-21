
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// tamaño de los datos
#define N  5
int countElement;
// Functionpara cambiar dos numeros

static double dataTOTAL1[N];
int valuemayor1=-1;
int valuemayor2=-1;

double* datad2;
double datad[N/4+1];
void calculateDiagonal(int rank,int rows, double matrix[][N], int offset)
{
    //printf("RANK %d ===>MERGE on LIST, rows: %d\n ",rank,rows);
    
    printf("============CALCULATE DIAGONAL=========\n");
    int i2 = 0;
    int i3=0;
    
   printf("RANK %d ===>MN*rows: %d\n ",rank,rows);
    
    // Root process evaluate your data
    for (int i = 0; i < rows; i++)
    {
        /* code */

        for (int j = 0; j < N; j++)
        {
            /* code */
            if(j==offset){
                i2++;
                datad[i]=matrix[i][j];
                
                printf("RANK %d==> element diagonal 1 [%d][%d]=%.2f\n",rank,offset,j,matrix[i][j]);
            }
            if((N-1)-j==N-offset-1){
                i3++;
               
                  //  datad2[i]=matrix[i][j];
                
                                printf("RANK %d==> element diagonal 2 [%d][%d]=%.2f\n",rank,offset,(N-1)-j,matrix[i][N-1-j]);
            
            }
            
        }
        offset+=1;
    }
    for (int i = 0; i < rows; i++)
    {
        /* code */
        printf("CAlculate diagonal RAnk %d===> datad[%d]=%.2f\n",rank,i,datad[i]);
    }
    
    
      // MPI_Send(datad, 1, MPI_DOUBLE,
		//			rank, rank,
			//		MPI_COMM_WORLD);
    //
    
    
    //count(rank,datamerge,N*rows,element,data2);
}
// Funcion que mezcla dos arrays
int *merge(int *arr1, int n1, int *arr2, int n2)
{
    int *result = (int *)malloc((n1 + n2) * sizeof(int));
    int i = 0;
    int j = 0;
    int k;

    for (k = 0; k < n1 + n2; k++)
    {
        if (i >= n1)
        {
            result[k] = arr2[j];
            j++;
        }
        else if (j >= n2)
        {
            result[k] = arr1[i];
            i++;
        }

        else if (arr1[i] < arr2[j])
        {
            result[k] = arr1[i];
            i++;
        }

        // v2[j] <= v1[i]
        else
        {
            result[k] = arr2[j];
            j++;
        }
    }
    return result;
}
int sumPartial[1];

// Driver Code
int main(int argc, char *argv[])
{
   double* data2;
    int *data = NULL;
    int chunk_size, own_chunk_size, dest, offset, rows;
    int *chunk;
    FILE *file = NULL;
    double time_taken;
    MPI_Status status;

    int processCount, rank_of_process;
    int rc = MPI_Init(&argc, &argv);

    if (rc != MPI_SUCCESS)
    {
        printf("Error in creating MPI "
               "program.\n "
               "Terminating......\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
    }
    MPI_File fh;
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_of_process);
    int slaveTaskCount = processCount - 1;
    int element;
    
    if (rank_of_process == 0)
    {
        data2 = (double*)malloc(processCount * sizeof(double));
        // Read input from the keyboard in the root process
        printf("Enter an element for search: ");
        fflush(stdout);
        scanf("%d", &element);
    }
    MPI_Bcast(&element, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank_of_process == 0)
    {
        int input;

        double matrix[N][N];

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                matrix[i][j] = rand() % 20 + 1;
            }
        }

        printf("\n\t\tMatrix - Matrix Sort using MPI\n");

        // Print Matrix A
        printf("\nMatrix \n\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                printf("%.0f\t", matrix[i][j]);
            }
            printf("\n");
        }

        // Determine number of rows of the Matrix A, that is sent to each slave process
        rows = N / processCount;
        printf("========================================================================\n");
        // Offset variable determines the starting point of the row which sent to slave process
        offset = 0;
        int row_root = (N % processCount == 0) ? rows : N - (rows * (processCount - 1));
        printf("rows: %d\n", rows);
        printf("rows_root: %d\n", row_root);

       
        offset = offset + row_root;
        printf("offset %d\n", offset);
        printf("========================================================================\n");
        // Calculation details are assigned to slave tasks. Process 1 onwards;
        // Each message's tag is 1
        for (dest = 1; dest <= slaveTaskCount; dest++)
        {

            // Acknowledging the offset of the Matrix A
            MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            // Send rows of the Matrix A which will be assigned to slave process to compute
            MPI_Send(&matrix[offset][0], rows * N, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
            // Acknowledging the number of rows
            offset += rows;
        }
            double* datad=(double*)malloc(row_root*sizeof(double));
            calculateDiagonal(rank_of_process,row_root, matrix, 0);
            
            
            //=(double*)malloc(N*sizeof(double))
         

         
        for (int i = 0; i < 4; i++)
        {
            /* code */
          //MPI_Recv(&datad, 1, MPI_DOUBLE, i, i, MPI_COMM_WORLD, &status);
            
        }
        
        //calculateSum(rank_of_process,row_root, matrix, data2);
    }
    if (rank_of_process > 0)
    {

        //printf("RANK %d ==>N in slave: %d\n", rank_of_process, N);

        /* code */
        // Slave process waits for the message buffers with tag 1, that Root process sent
        // Each process will receive and execute this separately on their processes

        // The slave process receives the offset value sent by root process
        MPI_Recv(&offset, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        // The slave process receives number of rows sent by root process
        MPI_Recv(&rows, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        double matrix[rows][N];
        // The slave process receives the sub portion of the Matrix A which assigned by Root
        MPI_Recv(&matrix, rows * N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
        ///printf("RANK %d==> rows %d\n", rank_of_process, rows);
       for (int i = 0; i < rows; i++)
       {
            
         for (int j = 0; j < N; j++)
            {
                /* code */ printf("RANK %d , offset %d==>N matrix[row %d][colum %d]: %.2f\n", rank_of_process,offset, i, j, matrix[i][j]);
            }
        }
        double* datad=(double*)malloc(rows*sizeof(double));
        calculateDiagonal(rank_of_process,rows, matrix, offset);

    }

    MPI_Barrier(MPI_COMM_WORLD);
   // MPI_Gather(datad, (N/4+1), MPI_DOUBLE, data2, processCount, MPI_DOUBLE, 0,  MPI_COMM_WORLD);
if(rank_of_process==0){
    int sumTotal=0;
        
        
        for (int i = 0; i < 1; i++)
        {
            
            printf("RANK %d==> data2[%d]=%.2f\n",rank_of_process,i,data2[i]);
        }
         
          
}
    MPI_Finalize();
    return 0;
}