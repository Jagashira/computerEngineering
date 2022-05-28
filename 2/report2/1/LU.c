#include <stdio.h>
void matlixOuput(int n,double *matlix, double *b);

int main(){
    int n = 3;
    
    double matlix[3][3] = {
        { 1 , -2 ,-3 },
        { 2 , 10 , 1 },
        { 3 , -3 , 4 },
    };

    double b[] = {2007,4105,6052};

    matlixOuput(n,matlix,b);

    
}



void matlixOuput(int n,double *matlix,double *b){

    for(int i=0;i<n;i++){
        if(n == 1) printf("|");
        else if(i==0) printf("/");
        else if(i==n-1) printf("\\");
        else printf("|");

        
        for(int j=0;j<n;j++){
            printf("  %3.3lf  ",*(matlix+(n*i)+j));
        }

        if(n == 1) printf("|");
        else if(i==0) printf("\\");
        else if(i==n-1) printf("/");
        else printf("|");

        printf("  =  ");
        printf("%lf",*(b+i));
        
        puts("");
    }
    puts("");
}