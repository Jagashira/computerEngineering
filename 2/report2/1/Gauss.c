#include <stdio.h>
#include <stdlib.h>

void matlix_display(int row,int col,double *matlix[]);

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
    
    //配列のinput
    double matlix[row][col];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            scanf("%d",&matlix[i][j]);
            // scanf("%lf",&matlix[i][j]);
        }
    }

    //配列のoutput
    for(int i=0;i<row;i++){
        if(row == 1) printf("|");
        else if(i==0) printf("/");
        else if(i==row-1) printf("\\");
        else printf("|");
        
        for(int j=0;j<col;j++){
            printf("  %d  ",matlix[i][j]);
        }

        if(row == 1) printf("|");
        else if(i==0) printf("\\");
        else if(i==row-1) printf("/");
        else printf("|");
        
        puts("");
    }
    
    for(int j=0;j<col;j++){
        for(int i=0;i<row;i++){
            double m = matlix[i][j]/matlix[i][0];
            printf("%lf\n",m);
            matlix[i][j] /= m;
            printf("%d %d\n",i,j);
        }
    }

    // matlix_display(row,col,&matlix);

    for(int i=0;i<row;i++){
        if(row == 1) printf("|");
        else if(i==0) printf("/");
        else if(i==row-1) printf("\\");
        else printf("|");
        
        for(int j=0;j<col;j++){
            printf("  %d  ",matlix[i][j]);
        }

        if(row == 1) printf("|");
        else if(i==0) printf("\\");
        else if(i==row-1) printf("/");
        else printf("|");
        
        puts("");
    }


    


    
    return 0;
}



void matlix_display(int row,int col,double *matlix[]){

    for(int i=0;i<row;i++){
        if(row == 1) printf("|");
        else if(i==0) printf("/");
        else if(i==row-1) printf("\\");
        else printf("|");
        
        for(int j=0;j<col;j++){
            printf("  %d  ",matlix[i][j]);
        }

        if(row == 1) printf("|");
        else if(i==0) printf("\\");
        else if(i==row-1) printf("/");
        else printf("|");
        
        puts("");
    }
}