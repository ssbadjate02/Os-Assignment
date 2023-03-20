# Os-Assignment
Problem Statements:
This assignment requires you to multiply arbitrarily large matrices using parallelism provided by the Linux process and threads libraries
Write a C program P1 which takes three filenames (in1.txt, in2.txt and out.txt) as command line arguments. The first two files (in1.txt and in2.txt) contain two matrices of arbitrary size but satisfying the criteria for matrix multiplication. The sizes will be passed in the command line. P1 spawns n threads which each read row(s) and column(s) each from in1.txt and in2.txt.
Different threads should read different parts of the file. Vary the number of threads from 1… to arbitrarily large
Record the time that it takes to read the entire file into memory with different number of threads (1, 2, … n). The timing should be at the granularity of nanoseconds.
Plot time against the number of threads for different input sizes. Analyse the findings from the plots.
Write a C program (P2) which uses IPC mechanisms to receive the rows and columns read by P1. P2 spawns multiple threads to compute the cells in the product matrix. The program stores the product matrix in the file out.txt
Vary the number of threads from 1… to arbitrarily large.
Record the time it takes to compute the product with different number of threads.  The timing should be at the granularity of nanoseconds.
Plot the time against the number of threads for different input sizes. Analyse the findings from the plots.
Write a scheduler program S. S spawns 2 children processes which exec to become the processes P1 and P2 in part (b) and part (c) above. S uses some mechanism to simulate a uniprocessor scheduler. That is, it suspends P1 and lets P2 execute, and vice versa. Simulate the following scheduling algorithms in S:
Round Robin with time quantum 2 ms
Round Robin with time quantum 1 ms
Completely Fair Scheduler where the vruntime is updated every 1 ms
Plot the total turnaround time vs workload size and waiting time vs workload size for the different scheduling algorithms. How do the two algorithms compare for the same workload size? Analyse your findings.
What is the switching overhead in the different cases?
You might need to take care of race conditions which might arise at different parts of the assignment
Using high level maths libraries is not allowed. It will be ensured in the test cases that each element of the product matrix fits into a long long int
Sample input, output and a python script to generate and multiply matrices is here.
How to run: ./groupX_assignment2.out i j k in1.txt in2.txt out.txt
Where in1.txt contains a ixj matrix, in2.txt contains a jxk matrix and the ixk product matrix is stored in out.txt


