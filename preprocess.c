#include<stdio.h>
#include<stdlib.h>

int main(int argc, char**argv){
    FILE* filemat;
    int filerow=atoi(argv[1]);
    int filecol=atoi(argv[2]);
    int ** mat=(int**)malloc(filerow*sizeof(int*));
    filemat=fopen(argv[3], "r");
    for(int i=0; i<filerow; i++){
        mat[i]=(int*)malloc(filecol*sizeof(int));
        for(int j=0; j<filecol; j++){
            int temp;
            fscanf(filemat, "%d", &temp);
            mat[i][j]=temp;
            // char misc;
            // fscanf("%c", misc);
        }
    }
    fclose(filemat);
    filemat=fopen(argv[3], "w+");
    for(int i=0; i<filecol; i++){
        for(int j=0; j<filerow; j++){
            fprintf(filemat, "%d ", mat[j][i]);
        }
        fprintf(filemat, "%c", '\n');
    }
    fclose(filemat);
}