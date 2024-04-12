MPI Prime Number Generator
To compile the program, use the following command:  mpicc -o primes primes.c
To execute the program, use the following command:mpiexec -n x ./primes N

Replace x with the number of processes and N with a positive integer greater than 2 and less than or equal to 10,000,000.
For example:  mpiexec -n 2 ./primes 100

This will generate a file named 100.txt containing prime numbers from 2 to 100.
The output file (N.txt) contains the list of prime numbers separated by single spaces and ordered.

