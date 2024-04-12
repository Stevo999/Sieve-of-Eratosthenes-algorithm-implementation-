#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Function to generate prime numbers using Sieve of Eratosthenes algorithm
void generate_primes(int N, int rank) {
    // Allocating memory for marking prime numbers
    char *marked = (char *)malloc((N + 1) * sizeof(char));
    if (marked == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Initialize marked array
    // 1 indicates prime, 0 indicates composite
    for (int i = 0; i <= N; i++) {
        marked[i] = 1; 
    }

    // Mark multiples of each prime number starting from 2
    for (int p = 2; p * p <= N; p++) {
        if (marked[p]) {
            for (int i = p * p; i <= N; i += p) {
                marked[i] = 0;
            }
        }
    }

    // Write prime numbers to file
    char filename[20];
    sprintf(filename, "%d.txt", N);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        free(marked);
        return;
    }

    // Write prime numbers to file
    for (int i = 2; i <= N; i++) {
        if (marked[i]) {
            fprintf(fp, "%d ", i);
        }
    }

    fclose(fp);
    free(marked);
}

int main(int argc, char *argv[]) {
    int rank, size, N, start, end, chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) {
            printf("Usage: mpiexec -n x ./primes N\n");
        }
        MPI_Finalize();
        return 1;
    }

    N = atoi(argv[1]);

    // Calculate chunk size and range for each process
    chunk_size = (N - 1) / size;
    start = rank * chunk_size + 2; // Start from 2
    end = (rank == size - 1) ? N : start + chunk_size - 1;

    // Generate prime numbers
    generate_primes(N, rank);

    MPI_Finalize();
    return 0;
}
