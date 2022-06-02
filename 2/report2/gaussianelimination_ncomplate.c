#include <stdio.h>
#include <math.h>


int main(void){

    double a[3][3] = {
        { 1 , -2 ,-3 },
        { 2 , 10 , 1 },
        { 3 , -3 , 4 },
    };

    double b[3] = {2007,4105,6052};
    double x[3];
    
    int const n=3;
    double mjl;

    for(int l=0;l<=n-2;l++){
        for(int j=l+1;j<=n-1;j++){
            mjl = a[j][l]/a[l][l];
            for(int k=0;k<=n-1;k++){
                a[j][k] -= mjl*a[l][k];
            }
            b[j] = b[j] -mjl*b[l];
        }
    }

    
    for(int j=n-1;j>=0;j--){
      

        double sum = 0;
        for(int k=0;k<=n-1;k++){
            sum += a[j][k]*x[k];//
        }

        x[j] = (b[j]-sum)/a[j][j];//
    }

    for(int i=0;i<n;i++){
        printf("x %d = %lf \n",i,x[i]);
    }
    printf("\n");
    return 0;
}