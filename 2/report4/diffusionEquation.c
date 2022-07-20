#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 12

double init(double x);

int main(){
    FILE *data[n], *gp;
    char *data_file[n];
    // char file_name[][12] = {"2-b-0.dat", "2-b-5.dat", "2-b-10.dat", "2-b-15.dat", "2-b-20.dat", "2-b-25.dat", "2-b-30.dat", "2-b-35.dat", "2-b-40.dat", "2-b-45.dat", "2-b-50.dat", "2-b-55.dat", "2-b-60.dat", "2-b-65.dat", "2-b-70.dat", "2-b-75.dat", "2-b-80.dat", "2-b-85.dat", "2-b-90.dat", "2-b-95.dat", "2-b-100.dat"};
    char file_name[][12] = {"2-d-0.dat", "2-d-5.dat", "2-d-10.dat", "2-d-15.dat", "2-d-20.dat", "2-d-25.dat", "2-d-30.dat", "2-d-35.dat", "2-d-40.dat", "2-d-45.dat", "2-d-50.dat", "2-d-55.dat", "2-d-60.dat", "2-d-65.dat", "2-d-70.dat", "2-d-75.dat", "2-d-80.dat", "2-d-85.dat", "2-d-90.dat", "2-d-95.dat", "2-d-100.dat"};

    double **u;

    double T = 100;
    double X = 10;

    double dt = 0.05; // 0.01  //0.05
    double dx = 0.2;
 
    int tn = (T / dt) + 2;
    int xn = (X / dx) + 1;

    double r = dt / (dx * dx);

    u = malloc(sizeof(double *) * (xn + 1));
    for (int i = 0; i <= xn + 1; i++){
        u[i] = malloc(sizeof(double) * tn);
    }

    for (int i = 0; i < xn; i++){
        u[i][0] = init(i * dx);
    }

    for (int j = 0; j <= tn - 1; j++){
        u[0][j] = 1;
        u[50][j] = 2;
        for (int i = 1; i <= xn; i++){
            u[i][j + 1] = r * u[i - 1][j] + (1 - 2 * r) * u[i][j] + r * u[i + 1][j];
        }
    }

    for (int i = 0; i < n; i++){
        data_file[i] = file_name[i];
        data[i] = fopen(data_file[i], "w");
        int l = 5 * i / dt;
        for (int k = 0; k <= xn; k++){
            fprintf(data[i], "%f\t%f\n", k * dx, u[k][l]);
        }
        fclose(data[i]);
    }
  
    for (int i = 0; i <= xn + 1; i++){
        free(u[i]);
    }
    free(u);
    return 0;
}


double init(double x){
  
    if (x == 0){
        return 1;
    }else if (x == 10){
        return 2;
    }else{
        return 0;
    }
}