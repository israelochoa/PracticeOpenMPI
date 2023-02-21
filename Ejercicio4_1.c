
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// tamaño de los datos
static const int N = 5;
int countElement;
// Functionpara cambiar dos numeros
void count(int rank,double *data, int size,int element, int *data2)
{
    
//printf("RANK %d ---->COUNT: element od search %d\n", rank, element );
    for ( int i=0 ; i < size; i++)
    {
        /* code */
        if (element == data[i])
        {
            /* code */
            countElement++;
            if(data[i+1]!=element){
                break;
            }
        }
        
    }
   // printf("RANK %d ----> COUNT: counts of elements %d\n", rank,countElement);
        
}

void swap(double *arr, int i, int j)
{
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

// Funcion quicksort
void quicksort(double *arr, int start, int end)
{
    int pivot, index;

    // Base Case
    if (end <= 1)
        return;

    // Selecciona un pivote y lo intercambia con el primet elemento

    pivot = arr[start + end / 2];
    swap(arr, start, start + end / 2);

    index = start;

    // Iterate over the range [start, end]
    for (int i = start + 1; i < start + end; i++)
    {

        // Swap if the element is less
        // than the pivot element
        if (arr[i] < pivot)
        {
            index++;
            swap(arr, i, index);
        }
    }

    // Swap the pivot into place
    swap(arr, start, index);

    // Recursive Call for sorting
    // of quick sort function
    quicksort(arr, start, index - start);
    quicksort(arr, index + 1, start + end - index - 1);
}
void mergeonelist(int rank,int rows, double matrix[][N], int element, int *data2)
{
    //printf("RANK %d ===>MERGE on LIST, rows: %d\n ",rank,rows);
    int i2 = 0;
   // printf("RANK %d ===>MN*rows: %d\n ",rank,(N*rows));
    double datamerge[N * rows];
    // Root process evaluate your data
    for (int i = 0; i < rows; i++)
    {
        /* code */

        for (int j = 0; j < N; j++)
        {
            /* code */
            
            datamerge[i2] = matrix[i][j];
            i2++;
        }
        
    }
    for (int i = 0; i < N*rows; i++)
    {
        /* code */
        //printf("RANK==>%dMERGEONLIST=>> data[%d]=%.2f\n",rank,i, datamerge[i]);
    }
    
    quicksort(datamerge, 0, N * rows);
    count(rank,datamerge,N*rows,element,data2);
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
    int *data2 = NULL;
    if (rank_of_process == 0)
    {
        data2 = (int *)malloc(processCount * sizeof(int));
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
                matrix[i][j] = rand() % 1000 + 1;
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

        printf("rows_new: %d\n", rows);
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
         
        mergeonelist(rank_of_process,row_root, matrix, element, data2);
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
       // for (int i = 0; i < rows; i++)
       // {
            /* code */
            //for (int j = 0; j < N; j++)
         //   {
           //     /* code */ printf("RANK %d ==>N matrix[row %d][colum %d]: %.2f\n", rank_of_process, i, j, matrix[i][j]);
           // }
       // }
mergeonelist(rank_of_process,rows, matrix, element, data2);
        
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(&countElement, 1, MPI_INT, data2, 1, MPI_INT, 0,
                   MPI_COMM_WORLD);
if(rank_of_process==0){
    int sumTotal=0;
        
        for (int i = 0; i < 4; i++)
        {
            /* code */sumTotal+=data2[i];
        }
         
            printf("RANK %d ----->TOTAL COUNT for element %d = %d\n",rank_of_process, element,sumTotal);
}
    MPI_Finalize();
    return 0;
}