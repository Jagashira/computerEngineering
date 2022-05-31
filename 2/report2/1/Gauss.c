#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void matlixOuput(int n,double *matlix, double *b);
void pivot(int n,int j,double *matlix,double *b);
void x_calc(double *matlix,double *b,int n);

int main(int argc, char const *argv[]){

    int n = 3;
    
    double matlix[3][3] = {
        { 1 , -2 ,-3 },
        { 2 , 10 , 1 },
        { 3 , -3 , 4 },
    };

    double b[] = {2007,4105,6052};

    puts("original");
    matlixOuput(n,*matlix,b);


    for(int j=0;j<n;j++){
        pivot(n,j,*matlix,b);
        for(int i=j+1;i<n;i++){
            double  m = matlix[i][j]/matlix[j][j];

            for(int k=0;k<n;k++){
                matlix[i][k] -= m * matlix[j][k];
            }
            double tmp = b[i];
            b[i] = b[i] - m*b[j];
            
        
        }
    }
    puts("calclation");
    matlixOuput(n,*matlix,b);

    x_calc(*matlix,b,n);

    return 0;
}



void matlixOuput(int n,double *matlix,double *b){

    for(int i=0;i<n;i++){
    
        for(int j=0;j<n;j++){
            printf("  %3.3lf  ",*(matlix+(n*i)+j));
        }

        printf("  =  ");
        printf("%lf",*(b+i));
        
        puts("");
    }
    puts("");
}


void pivot(int n,int j,double *matlix,double *b){
    double tmp_matlix;
    double tmp_b;
  
        for(int k=j;k<n;k++){
            //バブルソース
            for(int l=k+1;l<n;l++){
                if(fabs(*(matlix+(n*k)+j)) < fabs(*(matlix+(n*l)+j))){
                    //配列の入れ替え
                    tmp_b = *(b+l);
                    *(b+l) = *(b+k);
                    *(b+k) = tmp_b;
                    for(int m=0;m<n;m++){
                        tmp_matlix = *(matlix+(n*l)+j+m);
                        *(matlix+(n*l)+j+m) = *(matlix+(n*k)+j+m);
                        *(matlix+(n*k)+j+m) = tmp_matlix;
                    }
                }
            }
        }

}


void x_calc(double *pMatlix,double *b,int n){
    double x[3] ={};

    for(int i=2;i>=0;i--){
        double sigma = 0;

        for(int j=0;j<n;j++){
            sigma += (*(pMatlix+(n*i)+j))*x[j];
        }
        x[i] = ((*(b+i))-sigma)/(*(pMatlix+(i*n)+i));

    }

    for(int i=0;i<n;i++){
        printf("x[%d] = %.2f\n",i+1,*(x+i));
    }
}