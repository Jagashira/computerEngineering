#include <stdio.h>

#define MAX_NUM 10000

int num_elements;
int elements[MAX_NUM][3];

int num_nodes;
double nodes[MAX_NUM][2];

int num_bcs;
int bc_nodes[MAX_NUM];
double bc_values[MAX_NUM];

double k_matrix[MAX_NUM][MAX_NUM];
double f_vector[MAX_NUM];
double t_vector[MAX_NUM];

void inputMesh(char *filename)
{
  FILE *fp;
  int i;

  printf("Input mesh (%s)\n", filename);

  /* Open file */
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: mesh file (%s) not found\n", filename);

    num_elements = 0;
    num_nodes = 0;
    num_bcs = 0;

    return;
  }

  /* Read number of elements */
  fscanf(fp, "%d", &num_elements);

  /* Read elements */
  for (i = 0; i < num_elements; i++) {
    fscanf(fp, "%d%d%d",
	   &elements[i][0],
	   &elements[i][1],
	   &elements[i][2]);
  }

  /* Read number of nodes */
  fscanf(fp, "%d", &num_nodes);

  /* Read nodes */
  for (i = 0; i < num_nodes; i++) {
    fscanf(fp, "%lf%lf",
	   &nodes[i][0],
	   &nodes[i][1]);
  }

  /* Read number of boundary conditions */
  fscanf(fp, "%d", &num_bcs);

  /* Read boundary conditions */
  for (i = 0; i < num_bcs; i++) {
    fscanf(fp, "%d%lf",
	   &bc_nodes[i],
	   &bc_values[i]);
  }

  /* Close file */
  fclose(fp);

  /* Check numbes */
  if (num_elements > MAX_NUM
      || num_nodes > MAX_NUM
      || num_bcs > MAX_NUM) {
    printf("Error: MAX_NUM (%d) not large enough\n", MAX_NUM);
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

  /* Zeroize [K] */
  for (i = 0; i < num_nodes; i++) {
    for (j = 0; j < num_nodes; j++) {
      k_matrix[i][j] = 0.0;
    }
  }

  for (e = 0; e < num_elements; e++) {
    /* Get {x} and {y} */
    for(i = 0;i < 3; i++ ){
        x[i] = nodes[elements[e][i]][0];
        y[i] = nodes[elements[e][i]][1];

    }

    /* Calculate S */
    S = 0.5 * (x[0] * (y[1] - y[2]) + x[1] * (y[2] - y[0]) + x[2] * (y[0] - y[1]));

    /* Calculate {b} and {c} */
    for(i = 0; i<3; i++){
        j = (i + 1) % 3;
        k = (i + 2) % 3;
        b[i] = (y[j] - y[k]) / (2*S);
        c[i] = (x[j] - x[k]) / (2*S);
    }

    /* Generate element [K] */
    for(i = 0; i<3 ;i++){
        for(j = 0;j < 3;j++){
            element_k_matrix[i][j] = (b[i] * b[j] + c[i] * c[j]) * S;
        }
    }

    /* Generate [K] */
    for(i = 0;i < 3 ;i++){
        for(j = 0; j < 3; j++){
            int row = elements[e][i];
            int column = elements[e][j];

            k_matrix[row][column] += element_k_matrix[i][j];
        }
    }
  }

  /* Zeroize {f} */
  for (i = 0; i < num_nodes; i++) {
    f_vector[i] = 0.0;
  }

  /* Process boundary conditions */
  for (k = 0; k < num_bcs; k++) {
    /* Get node and value */
    i = bc_nodes[k];
    value = bc_values[k];

    /* Modify [K] */
    for(j = 0;j < num_nodes; j++){
        if(i == j){
            k_matrix[i][j] = 1.0;
        }else{
            k_matrix[i][j] = 0.0;
        }
    }

    /* Modify {f} */
    f_vector[i] = value;
  }
}

void solveLinearSystem(void)
{
  int j, k, l;

  printf("Solve linear system by Gaussian elimination method\n");

  /* Forward elimination */
  for (l = 0; l < num_nodes - 1; l++) {
    for (j = l + 1; j < num_nodes; j++) {
      k_matrix[j][l] = k_matrix[j][l] / k_matrix[l][l];

      for (k = l + 1; k < num_nodes; k++) {
	k_matrix[j][k] = k_matrix[j][k] - k_matrix[j][l] * k_matrix[l][k];
      }

      f_vector[j] = f_vector[j] - k_matrix[j][l] * f_vector[l];
    }
  }

  /* Backward substitution */
  for (j = num_nodes - 1; j >= 0; j--) {
    t_vector[j] = f_vector[j];

    for (k = j + 1; k < num_nodes; k++) {
      t_vector[j] = t_vector[j] - k_matrix[j][k] * t_vector[k];
    }

    t_vector[j] = t_vector[j] / k_matrix[j][j];
  }
}

void outputResult(char *filename)
{
  FILE *fp;
  int i;

  printf("Output result (%s)\n", filename);

  /* Open file */
  fp = fopen(filename, "w");

  /* Write {T} */
  for (i = 0; i < num_nodes; i++) {
    fprintf(fp, "%.15E\n", t_vector[i]);
  }

  /* Close file */
  fclose(fp);
}

int main(int argc, char *argv[])
{
    // for(int i = 0;i<argc;i ++){
    //     printf("%s",argv[i]);
    // }
  if (argc != 3) {
    printf("Usage: %s mesh.txt result.txt\n", argv[0]);

    return 0;
  }

  inputMesh(argv[1]);
  generateMatrixAndVector();
  solveLinearSystem();
  outputResult(argv[2]);

  return 0;
}