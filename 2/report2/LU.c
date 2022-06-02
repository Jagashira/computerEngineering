#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #define G 9.8
#define G 3.7
#define n 3

void matrixOuput(double *matrix, double *b);
void pivot(int j,double *matrix,double *b);
void x_calc(double *matrix,double *b);
void Gauss(double *matrix, double *b, double *L);

int main(){

    double matrix[3][3] = {
        { 1 , -2 ,-3 },
        { 2 , 10 , 1 },
        { 3 , -3 , 4 },
    };
    
    double b[] = {2007,4105,6052};


    double L[n][n] = {
        {1,0,0},
        {0,1,0},
        {0,0,1},

    };

    puts("original");
    matrixOuput(*matrix,b);

    for(int j=0;j<n;j++){

        for(int i=j+1;i<n;i++){
            L[i][j] = matrix[i][j]/matrix[j][j];

            for(int k=0;k<n;k++){
                matrix[i][k] -= L[i][j] * matrix[j][k];
            }
     
                
        
        }
    }
    for(int j=0;j<n;j++){

        for(int i=j+1;i<n;i++){
            double m = L[i][j]/L[j][j];

            for(int k=0;k<n;k++){
                L[i][k] -= m * L[j][k];
            }
            double tmp = b[i];
            b[i] = b[i] - m*b[j];         
        
        }
    }




    
    puts("calclation");
    matrixOuput(*matrix,b);

    x_calc(*matrix,b);

    matrixOuput(*L,b);

    return 0;
}



void matrixOuput(double *matrix,double *b){

    for(int i=0;i<n;i++){
    
        for(int j=0;j<n;j++){
            printf("  %3.3lf  ",*(matrix+(n*i)+j));
        }

        printf("  =  ");
        printf("%.1lf",*(b+i));
        
        puts("");
    }
    puts("");
}


void x_calc(double *pmatrix,double *b){
    double x[n] ={};

    for(int i=n-1;i>=0;i--){
        double sigma = 0;

        for(int j=0;j<n;j++){
            sigma += (*(pmatrix+(n*i)+j))*x[j];
        }
        x[i] = ((*(b+i))-sigma)/(*(pmatrix+(i*n)+i));

    }

    for(int i=0;i<n;i++){
        printf("x[%d] = %.2lf\n",i+1,*(x+i));
    }
}
void Gauss(double *matrix, double *b, double *L){
    for(int j=0;j<n;j++){
        pivot(j,matrix,b);
        for(int i=j+1;i<n;i++){
            *(L+(i*n)+j) = *(matrix+(i*n)+j)/(*matrix+(j*n)+j);

            for(int k=0;k<n;k++){
                *(matrix+(i*n)+k) -= *(L+(i*n)+j) * (*matrix+(j*n)+k);
            }
            double tmp = *(b+i);
            *(b+i) -= *(L+(i*n)+j) *(*(b+j));         
        
        }
    }
}