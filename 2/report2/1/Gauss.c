#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]){

    int row;
    int col;

    if(argc == 3){
        row = atoi(argv[1]);
        col = atoi(argv[2]);
    }else{
        puts("Enter two arguments on the command line");
        return 1;
    }
    int matlix[row][col];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            scanf("%d",&matlix[i][j]);
            // scanf("%lf",&matlix[i][j]);
        }
    }


    for(int i=0;i<row;i++){
        if(i==0){
            printf("/");
        }else if(i==row-1){
            printf("\\");
        }else{
            printf("|");
        }

        for(int j=0;j<col;j++){
            printf("  %d  ",matlix[i][j]);
        }

        if(i==0){
            printf("\\");
        }else if(i==row-1){
            printf("/");
        }else{
            printf("|");
        }


        puts("");
    }


    // printf("%d %d\n",row,col);
    
    return 0;
}