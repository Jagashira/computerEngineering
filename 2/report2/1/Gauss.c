#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void matlixOuput(int n,double *matlix);
void pivot(int n,int j,double *matlix);



int main(int argc, char const *argv[]){

    int n = 3;
    
    double matlix[3][3] = {
        { 1 , -2 ,-3 },
        { 2 , 10 , 1 },
        { 3 , -3 , 4 },
    };

    double b[1][3] = {
        {2007},
        {4105},
        {6052},
    };

    pivot(n,0,matlix);
    matlixOuput(n,matlix);

    // for(int j=0;j<n;j++){
    //     for(int i=j+1;i<n;i++){
    //         double m = matlix[i][j]/matlix[j][j];
    //         printf("%lf\n",m);
            
    //         for(int tmp=0;tmp<n;tmp++){
                
    //             matlix[i][j] -= matlix[i][tmp]*m; 
    //             double a = (float)matlix[i][j];
    //             printf("%f\n",a);
    //         }
    //     }
    // }

//////////////////////////////////////////////under in the works
    // for(int j=0;j<n;j++){
    //     pivot(n,j,matlix);
    //     for(int i=+1;i<n;i++){
    //         double  m = matlix[i][j]/matlix[][]
    //     }
    // }
////////////////////////////////////////////////////


    return 0;
}



void matlixOuput(int n,double *matlix){

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
        
        puts("");
    }
}


void pivot(int n,int j,double *matlix){
    double tmp;
  
        for(int k=0;k<n;k++){
            //バブルソース
            for(int l=k+1;l<n;l++){
                if(fabs(*(matlix+(n*k)+j)) < fabs(*(matlix+(n*l)+j))){
                    //配列の入れ替え
                    for(int m=0;m<n;m++){
                        tmp = *(matlix+(n*l)+j+m);
                        *(matlix+(n*l)+j+m) = *(matlix+(n*k)+j+m);
                        *(matlix+(n*k)+j+m) = tmp;
                    }
                }
            }
        }

}