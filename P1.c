#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

int index1=0;
int index2=0;

key_t key1;
int shmid1;

key_t key2;
int shmid2;

key_t finkey1;
int finshmid1;

pthread_mutex_t idxmutex1;
pthread_mutexattr_t   mta1;
pthread_mutex_t idxmutex2;
pthread_mutexattr_t   mta2;

FILE* filemat1;
FILE* filemat2;




// int mat1[20][50];
// int mat2[20][50];

long long int* mat1;
long long int* mat2;

int i,j,k;


void* reader(void* targ){
    int mat=(int)targ;
    while(1){
        if(mat==0){
            if (index1 >= i*j) break;
            pthread_mutex_lock(&idxmutex1);
            fscanf(filemat1, "%lld", &mat1[index1]);
            index1++;
            pthread_mutex_unlock(&idxmutex1);
            
        }
        else{
            if (index2 >= k*j) break;
            pthread_mutex_lock(&idxmutex2);
            fscanf(filemat2, "%lld", &mat2[index2]);
            index2++;
            pthread_mutex_unlock(&idxmutex2);
            
            // if (fgetc(filemat2) == EOF){
            //     break;
            // }
            
        }
    }
}

int main(int argc, char**argv){

    i=atoi(argv[1]);
    j=atoi(argv[2]);
    k=atoi(argv[3]);

    finkey1=ftok("P1.c", 69);
    finshmid1=shmget(finkey1, sizeof(int),IPC_CREAT|0666);
    int *finbool1;
    finbool1=(int*)shmat(finshmid1,NULL,0);
    finbool1[0]=0;
    printf("lmao\n");

    // printf("%d\n",i);
    mat1=(long long int*)malloc(i*j*sizeof(long long int));

    mat2=(long long int*)malloc(k*j*sizeof(long long int));
    

    
    key1=ftok("P1.c", 65);
    shmid1=shmget(key1, i*j*sizeof(long long int),IPC_CREAT|0666);
    mat1=(int*)shmat(shmid1,NULL,0);

    key2=ftok("P2.c", 67);
    shmid2=shmget(key2, k*j*sizeof(long long int) ,IPC_CREAT|0666);
    mat2=(long long int*)shmat(shmid2,NULL,0);
   
    char* filename1=argv[4];
    char* filename2=argv[5];
    int numthreads=8;
    // printf("enter number of threads: ");
    // scanf("%d", &numthreads);
    pthread_t* tid=(pthread_t*)malloc(numthreads*sizeof(pthread_t));

    filemat1=fopen(filename1, "r");
    filemat2=fopen(filename2, "r");
    pthread_mutex_init(&idxmutex1, &mta1);
    pthread_mutex_init(&idxmutex2, &mta2);
    for(int i=0; i<numthreads; i++){
        pthread_create(&tid[i], NULL, reader, (void*)(i%2));
    }
    for(int i=0; i<numthreads; i++){
        pthread_join(tid[i], NULL);
    }

    finbool1[0]=1;
    printf("somestuff\n");
    sleep(1);
    /*printf("done\n");
    for(int itr=0; itr<i*j; itr++){
        if(itr%j==0)printf("\n");
        printf("%d ", mat1[itr]);
    }*/
}
