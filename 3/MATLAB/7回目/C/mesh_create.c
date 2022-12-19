#include <stdio.h>

int num_elements;
int elements[10000][3];

double matrix[100];

int num_nodes;
double nodes[10000][2];

int num_bcs;
int bc_nodes[10000];
double bc_values[10000];

double sum;

double k_matrix[10000][10000];
double f_vector[10000];
double t_vector[10000];

void inputMesh(char *filename)
{
  FILE *fp;
  int i;

  fp = fopen(filename, "r");
  if (fp == NULL) {
    num_elements = 0;
    num_nodes = 0;
    num_bcs = 0;

    return;
  }

  fscanf(fp, "%d", &num_elements);


  for (i = 0; i < num_elements; i++) {
    fscanf(fp, "%d%d%d",
	   &elements[i][0],
	   &elements[i][1],
	   &elements[i][2]);
  }

  fscanf(fp, "%d", &num_nodes);

 
  for (i = 0; i < num_nodes; i++) {
    fscanf(fp, "%lf%lf",
	   &nodes[i][0],
	   &nodes[i][1]);
  }


  fscanf(fp, "%d", &num_bcs);

  for (i = 0; i < num_bcs; i++) {
    fscanf(fp, "%d%lf",
	   &bc_nodes[i],
	   &bc_values[i]);
  }


  fclose(fp);

  if (num_elements > 10000
      || num_nodes > 10000
      || num_bcs > 10000) {
    printf("Error: 10000 (%d) not large enough\n", 10000);
  }
}

void generateMatrixAndVector(void)
{
  double element_k_matrix[3][3];
  double x[3], y[3];
  double b[3], c[3];
  double S;
  double value;
  int e;
  int i, j, k;

  printf("Generate coefficient matrix and right-hand side vector\n");


  for (i = 0; i < num_nodes; i++) {
    for (j = 0; j < num_nodes; j++) {
      k_matrix[i][j] = 0.0;
    }
  }

  for (e = 0; e < num_elements; e++) {

    for(i = 0;i < 3; i++ ){
        x[i] = nodes[elements[e][i]][0];
        y[i] = nodes[elements[e][i]][1];

    }

    S = 0.5 * (x[0] * abs(y[1] - y[2]) + x[1] * abs(y[2] - y[0]) + x[2] * abs(y[0] - y[1]));
    printf("%lf\n",S);

    for(i = 0; i<3; i++){
        j = (i + 1) % 3;
        k = (i + 2) % 3;
        b[i] = (y[j] - y[k]) / (2*S);
        c[i] = (x[j] - x[k]) / (2*S);
    }

    for(i = 0; i<3 ;i++){
        for(j = 0;j < 3;j++){
            element_k_matrix[i][j] = (b[i] * b[j] + c[i] * c[j]) * S;
        }
    }


    for(i = 0;i < 3 ;i++){
        for(j = 0; j < 3; j++){
            int row = elements[e][i];
            int column = elements[e][j];

            k_matrix[row][column] += element_k_matrix[i][j];
        }
    }
  }

  for (i = 0; i < num_nodes; i++) {
    f_vector[i] = 0.0;
  }

 
  for (k = 0; k < num_bcs; k++) {
 
    i = bc_nodes[k];
    value = bc_values[k];

 
    for(j = 0;j < num_nodes; j++){
        if(i == j){
            k_matrix[i][j] = 1.0;
        }else{
            k_matrix[i][j] = 0.0;
        }
    }
    


    f_vector[i] = value;
  }
}

void solveLinearSystem(void)
{
  int j, k, l;

  printf("Solve linear system by Gaussian elimination method\n");


  for (l = 0; l < num_nodes - 1; l++) {
    for (j = l + 1; j < num_nodes; j++) {
      k_matrix[j][l] = k_matrix[j][l] / k_matrix[l][l];

      for (k = l + 1; k < num_nodes; k++) {
	k_matrix[j][k] = k_matrix[j][k] - k_matrix[j][l] * k_matrix[l][k];
      }

      f_vector[j] = f_vector[j] - k_matrix[j][l] * f_vector[l];
    }
  }


  for (j = num_nodes - 1; j >= 0; j--) {
    t_vector[j] = f_vector[j];

    for (k = j + 1; k < num_nodes; k++) {
      t_vector[j] = t_vector[j] - k_matrix[j][k] * t_vector[k];
    }

    t_vector[j] = t_vector[j] / k_matrix[j][j];
  }

  for(int a = 0;a<num_nodes;a++){
    matrix[a] = sqrt(pow(nodes[a][0],2) + pow(nodes[a][0],2));
    printf("%lf\n",matrix[a]);

  }


}

void outputResult(char *filename)
{
  FILE *fp;
  int i;

  printf("Output result (%s)\n", filename);

  fp = fopen(filename, "w");

  for (i = 0; i < num_nodes; i++) {
    fprintf(fp, "%.15lf\n", t_vector[i]);

  }

  fclose(fp);
}

int main(int argc, char *argv[])
{
  inputMesh(argv[1]);
  generateMatrixAndVector();
  solveLinearSystem();
  outputResult(argv[2]);
}



