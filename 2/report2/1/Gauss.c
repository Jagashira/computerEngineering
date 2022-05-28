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

    // double b[1][3] = {
    //     {2007},
    //     {4105},
    //     {6052},
    // };

    double b[] = {2007,4105,6052};

    // pivot(n,0,matlix);
    matlixOuput(n,matlix);


//////////////////////////////////////////////under in the works
    for(int j=0;j<n;j++){
        pivot(n,j,matlix);
        for(int i=j+1;i<n;i++){
            double  m = matlix[i][j]/matlix[j][j];

            for(int k=0;k<n;k++){
                matlix[i][k] -= m * matlix[j][k];
                
                // if(j==0){
                //     printf("%lf\n",matlix[i][k]);
                //     printf("%lf\n",matlix[i][j]);
                //     printf("%lf\n",m);
                // }
            }
            double tmp = b[i];
            b[i] = b[i] - m*b[j];
            printf("m = %lf\n",m);
            printf("%lf = %lf - %lf * %lf\n",b[i],tmp,m,b[j]);
            matlixOuput(n,matlix);
           

        }
    }
    printf("%lf\n",matlix[0][0]);
    printf("%lf\n",b[2]);
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
    puts("");
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