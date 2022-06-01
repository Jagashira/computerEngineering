#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #define G 9.8
#define G 3.7
#define n 7

void matrixOuput(double *matrix, double *b);
void pivot(int j,double *matrix,double *b);
void x_calc(double *matrix,double *b);

int main(int argc, char const *argv[]){

    
    // double matrix[3][3] = {
    //     { 1 , -2 ,-3 },
    //     { 2 , 10 , 1 },
    //     { 3 , -3 , 4 },
    // };

    // double b[] = {2007,4105,6052};


    double matrix[n][n] = {
        { 60 , 0 ,  0 ,     0 , -1 ,  0   ,   0 },
        { 0  , 7 ,  0 ,     0 ,  0 , -1   ,  -1 },
        { 0  , 0 , 20 ,     0 ,  2 , -2   ,   0 },
        { 0  , 0 ,  0 , 7.875 ,  0 , -1.5 , 1.5 },
        { 1  , 0 , -2 ,     0 ,  0 ,  0   ,   0 },
        { 0  , 1 ,  0 , -0.75 ,  0 ,  0   ,   0 },
        { 1  , 2 ,  0 ,     0 ,  0 ,  0   ,   0 },
    }; 

    double b[] = {-60*G,-7*G,0,0,0,0,0};

    

    puts("original");
    matrixOuput(*matrix,b);


    for(int j=0;j<n;j++){
        pivot(j,*matrix,b);
        for(int i=j+1;i<n;i++){
            double  m = matrix[i][j]/matrix[j][j];

            for(int k=0;k<n;k++){
                matrix[i][k] -= m * matrix[j][k];
            }
            double tmp = b[i];
            b[i] = b[i] - m*b[j];         
        
        }
    }
    puts("calclation");
    matrixOuput(*matrix,b);

    x_calc(*matrix,b);

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


void pivot(int j,double *matrix,double *b){
    double tmp_matrix;
    double tmp_b;
  
        for(int k=j;k<n;k++){
            
            for(int l=k+1;l<n;l++){
                if(fabs(*(matrix+(n*k)+j)) < fabs(*(matrix+(n*l)+j))){
                   
                    tmp_b = *(b+l);
                    *(b+l) = *(b+k);
                    *(b+k) = tmp_b;
                    for(int m=0;m<n;m++){
                        tmp_matrix = *(matrix+(n*l)+j+m);
                        *(matrix+(n*l)+j+m) = *(matrix+(n*k)+j+m);
                        *(matrix+(n*k)+j+m) = tmp_matrix;
                    }
                }
            }
        }

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