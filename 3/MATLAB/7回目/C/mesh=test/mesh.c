#include <stdio.h>

#define MAX_NUM 10000




void inputMesh(char *filename){
    int num_elements;
double elements[MAX_NUM][3];
double results[MAX_NUM][2];
    FILE *fp;
    int i;
    fp = fopen(filename, "r");

    if (fp == NULL) {
    printf("Error: mesh file (%s) not found\n", filename);

    return;
  }
  
  /* Read elements */
  for (i = 0; i < num_elements; i++) {
    fscanf(fp, "%d%d%d",
	   &elements[i][0],
	   &elements[i][1],
	   &elements[i][2]);
  }

  for(int i=0;i<15;i++){
    double x = elements[i][0];
        printf("%lf\n",x);
    }

    
}
int solveLinearSystem(){

    // for(int i=0;i<15;i++){
    //     printf("%lf\n",elements[i][0]);
    // }

}

int main(int argc,char *argv[]){

    if (argc != 3) {
    printf("Usage: %s mesh.txt result.txt\n", argv[0]);

    return 0;
  }else{
    inputMesh(argv[1]);

    solveLinearSystem();
    // outputResult(argv[2]);

  return 0;
  }
}