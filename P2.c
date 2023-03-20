#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <math.h>


int index1=0;
int index2=0;

key_t key1;
int shmid1;

key_t key2;
int shmid2;

key_t finkey2;
int finshmid2;

int numthreads;

pthread_mutex_t idxmutex1;
pthread_mutexattr_t   mta1;
pthread_mutex_t idxmutex2;
pthread_mutexattr_t   mta2;

FILE* filemat1;
FILE* filemat2;

long long int* mat1;
long long int* mat2;
long long int** prod;

int i,j,k;


struct pair{
    int row;
    int col;
}pair;

struct pair rccalc(int n){
    n=n+1;
    struct pair p;
    int x = ceil(sqrt((double)n));
    int sqx=x*x;
    int offset=sqx-n;
    if(offset<x){
        p.row=offset+1-1;
        p.col=x-1;
    }
    else{
        p.row=x-1;
        p.col=p.row+p.row-offset;
    }
    return p;
}


// void* multiplier(void* targs){
//     for(int a=0; a<i; a++){
//         for(int b=(int)targs; b<k; b+=numthreads){
//             for(int c=0; c<j; c++){
//                 prod[a][b]+=(mat1[(a*j)+c]*mat2[(b*j)+c]);
//             }
//         }
//     }
// }


void* multiplier(void* targs){
    int minik=(i<k)?i:k;
    for(int a=(int)targs; a<minik*minik; a+=numthreads){
        struct pair p=rccalc(a);
        int r=p.row;
        int c=p.col;
        printf("%d: %d,%d\n",a,r,c);
        for(int b=0; b<j; b++){
            prod[r][c]+=(mat1[(r*j)+b]*mat2[(c*j)+b]);
        }
    }
    if(minik==i){
        for(int a=(int)targs; a<i; a+=numthreads){
            for(int b=i; b<k; b++){
                for(int c=0; c<j; c++)
                prod[a][b]+=(mat1[a*j+c]*mat2[b*j+c]);
            }
        }
    }
    else{
        for(int b=(int)targs; b<k; b+=numthreads){
            for(int a=k; a<i; a++){
                for(int c=0; c<j; c++)
                prod[a][b]+=(mat1[a*j+c]*mat2[b*j+c]);
            }
        }
    }
}

int main(int argc, char* argv[]){
    i=atoi(argv[1]);
    j=atoi(argv[2]);
    k=atoi(argv[3]);

    finkey2=ftok("P1.c", 71);
    finshmid2=shmget(finkey2, sizeof(int),IPC_CREAT|0666);
    int *finbool2;
    finbool2=(int*)shmat(finshmid2,NULL,0);
    finbool2[0]=0;
    //printf("lmaoded\n");
    
    key1=ftok("P1.c", 65);
    shmid1=shmget(key1, i*j*sizeof(long long int),IPC_CREAT|0666);
    mat1=(long long int*)shmat(shmid1,NULL,0);

    key2=ftok("P2.c", 67);
    shmid2=shmget(key2, k*j*sizeof(long long int) ,IPC_CREAT|0666);
    mat2=(long long int*)shmat(shmid2,NULL,0);

    prod=(long long int**)malloc(i*sizeof(long long int*));
    for(int itr=0; itr<i; itr++){
        prod[itr]=(long long int*)malloc(k*sizeof(long long int));
    }

    numthreads=16;
    // printf("enter number of threads: ");
    // scanf("%d", &numthreads);
    pthread_t* tid=(pthread_t*)malloc(numthreads*sizeof(pthread_t));

    for(int i=0; i<numthreads; i++){
        pthread_create(&tid[i], NULL, multiplier, (void*)(i));
    }
    for(int i=0; i<numthreads; i++){
        pthread_join(tid[i], NULL);
    }

    FILE* output=fopen("output.txt", "w+");
    for(int a=0; a<i; a++){
        for(int b=0; b<k; b++){
            fprintf(output,"%lld ", prod[a][b]);
        }
        fprintf(output,"\n");
    }
    fclose(output);
    shmdt(mat1);
    shmdt(mat2);
    shmctl(shmid1, IPC_RMID, NULL);
    shmctl(shmid2, IPC_RMID, NULL);
    finbool2[0]=1;
}