#include <stdio.h>
#include <math.h>

#define n 3 
#define max 10000
#define epslon 1.0e-6 
#define a 1 //問題によって、aの値を3,1に変更する
void matrixOuput(double *matrix,double *b);
void pivot(int j,double *matrix,double *b,double *x_old,double *x_new);


int main(){
    double err;

    double matrix[n][n] = {
            { a , -3   , 4   },
            { 3 , -4*a , 1   },
            { 4 , -1   , 3*a },
        };

    double x_old[n]={
            1.0,
            1.0,
            1.0
        };
    double x_new[n] = {};
    double b[n] = {
            5857,
            5170,
            8049,
        };
    
    matrixOuput(*matrix,b);

    for(int k=0;k<max;k++) {
        err=0.0;
        pivot(k,*matrix,b,x_old,x_new);
        for(int i=0;i<n;i++) {
            x_new[i]=b[i];
            for(int j=0;j<n;j++) {
                if(j!=i) {
                    x_new[i]-=matrix[i][j]*x_old[j];
                }
            }
            x_new[i]=x_new[i]/matrix[i][i];
        }


        for(int i=0;i<n;i++) {
            err+=fabs(x_old[i]-x_new[i]);
            x_old[i]=x_new[i];
        }

        if(err<epslon) break;
    }


    for(int i=0;i<n;i++) {
        printf("%8.4f\n",x_new[i]);
    }


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


void pivot(int j,double *matrix,double *b,double *x_old,double *x_new){
    double tmp_matrix;
    double tmp_b;
  
        for(int k=j;k<n;k++){
            
            for(int l=k+1;l<n;l++){
                if(fabs(*(matrix+(n*k)+j)) < fabs(*(matrix+(n*l)+j))){
                   
                    tmp_b = *(b+l);
                    *(b+l) = *(b+k);
                    *(b+k) = tmp_b;
                    // for(int m=0;m<n;m++){
                    //     tmp_matrix = *(matrix+(n*l)+j+m);
                    //     *(matrix+(n*l)+j+m) = *(matrix+(n*k)+j+m);
                    //     *(matrix+(n*k)+j+m) = tmp_matrix;
                    // }
                    pivot3(k,l,j,matrix);
                    pivot1(k,l,b);
                    pivot1(k,l,x_new);
                    pivot1(k,l,x_old);

                }
            }
        }

}
void pivot3(int k,int l,int j,double matrix[3][3]){
    for(int m=0;m<n;m++){
        double tmp_matrix;
        // tmp_matrix = *(matrix+(n*l)+j+m);
        // *(matrix+(n*l)+j+m) = *(matrix+(n*k)+j+m);
        // *(matrix+(n*k)+j+m) = tmp_matrix;
        tmp_matrix = matrix[l][j+m];
        matrix[l][j+m] = matrix[k][j+m];
        matrix[k][j+m] = tmp_matrix;
    }
}

void pivot1(int k,int l,double b[3]){
    double tmp_b;
    // tmp_b = *(b+l);
    // *(b+l) = *(b+k);
    // *(b+k) = tmp_b;
    tmp_b = b[l];
    b[l] = b[k];
    b[k] = tmp_b;
}