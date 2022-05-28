#include <stdio.h>
#include <math.h>
void matlixOuput(int n,double *matlix, double *b);
void pivot(int n,int j,double *matlix,double *b);
double *L_calc(int n,double *matlix, double *b);

int main(){
    int n = 3;
    
    double matlix[3][3] = {
        { 1 , -2 ,-3 },
        { 2 , 10 , 1 },
        { 3 , -3 , 4 },
    };

    double b[3] = {2007,4105,6052};
    double L[3][3];
    double U[3][3];

    matlixOuput(n,matlix,b);


/////////////////////////mの保存  
    // for(int j=0;j<n;j++){
    //     pivot(n,j,matlix,b);
    //     for(int i=j+1;i<n;i++){
    //         double  m = matlix[i][j]/matlix[j][j];

    //         for(int k=0;k<n;k++){
    //             matlix[i][k] -= m * matlix[j][k];
    //         }
    //         double tmp = b[i];
    //         b[i] = b[i] - m*b[j];
            
        
    //     }
    // }
/////////////////////////////
L_calc(n,matlix,b);
return 0;

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



double *L_calc(int n,double *matlix, double *b){
    double m_L[3][3] ={};
    for(int j=0;j<n;j++){
        pivot(n,j,matlix,b);
        for(int i=j+1;i<n;i++){
            double m= (*(matlix+(n*i)+j)) / (*(matlix+(n*j)+j));

            for(int k=0;k<n;k++){
                *(matlix+(n*i)+k) -= m* (*(matlix+(j*n)+k));
            }
            double tmp = b[i];
            b[i] = b[i] - m *b[j];
            
        
        }
    }
    // for(int i=0;i<3;i++){
    //     for(int j=0;j<3;j++){
    //         printf("%lf\n",m_L[i][j]);
    //     }
        
    // }

    return m_L;
}