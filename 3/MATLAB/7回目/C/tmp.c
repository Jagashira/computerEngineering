#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846

#define MAX_NUM 100000

#define LENGTH_R1 50.0
#define LENGTH_R2 150.0
#define BC_VALUE_R1 100.0
#define BC_VALUE_R2 0.0

int num_elements;
int elements[MAX_NUM][3];

int num_nodes;
double nodes[MAX_NUM][2];

int num_bcs;
int bc_nodes[MAX_NUM];
double bc_values[MAX_NUM];

void generateMesh(int num_elements_r, int num_elements_theta)
{
  int num_nodes_r = num_elements_r + 1;
  int num_nodes_theta = num_elements_theta + 1;
  int offset;
  int i, j;

  printf("Generate mesh of 1/4 cylinder\n");

  /* Get number of elements */
  num_elements = 2 * num_elements_r * num_elements_theta;

  /* Generate elements */
  offset = 0;
  for (i = 0; i < num_elements_theta; i++) {
    for (j = 0; j < num_elements_r; j++) {
      int element_node_0 = num_nodes_r * i + j;

      elements[offset][0] = element_node_0;
      elements[offset][1] = element_node_0 + 1;
      elements[offset][2] = element_node_0 + num_nodes_r + 1;
      offset++;

      elements[offset][0] = element_node_0;
      elements[offset][1] = element_node_0 + num_nodes_r + 1;
      elements[offset][2] = element_node_0 + num_nodes_r;
      offset++;
    }
  }

  /* Get number of nodes */
  num_nodes = num_nodes_r * num_nodes_theta;

  /* Generate nodes */
  offset = 0;
  for (i = 0; i < num_nodes_theta; i++) {
    double theta
      = 0.5 * M_PI
      * (double)i / (double)(num_nodes_theta - 1);

    for (j = 0; j < num_nodes_r; j++) {
      double r
	= LENGTH_R1
	+ (double)j / (double)(num_nodes_r - 1)
	* (LENGTH_R2 - LENGTH_R1);

      nodes[offset][0] = r * cos(theta);
      nodes[offset][1] = r * sin(theta);
      offset++;
    }
  }

  /* Get number of boundary conditions */
  num_bcs = 2 * num_nodes_theta;

  /* Generate boundary conditions */
  offset = 0;
  for (i = 0; i < num_nodes_theta; i++) {
    bc_nodes[offset] = num_nodes_r * i;
    bc_values[offset] = BC_VALUE_R1;
    offset++;
  }
  for (i = 0; i < num_nodes_theta; i++) {
    bc_nodes[offset] = num_nodes_r * (i + 1) - 1;
    bc_values[offset] = BC_VALUE_R2;
    offset++;
  }

  /* Check numbes */
  if (num_elements > MAX_NUM
      || num_nodes > MAX_NUM
      || num_bcs > MAX_NUM) {
    printf("Error: MAX_NUM (%d) not large enough\n", MAX_NUM);
  }
}

void outputMesh(char *filename)
{
  FILE *fp;
  int i;

  printf("Output mesh (%s)\n", filename);

  /* Open file */
  fp = fopen(filename, "w");

  /* Write number of elements */
  fprintf(fp, "%d\n", num_elements);

  /* Write elements */
  for (i = 0; i < num_elements; i++) {
    fprintf(fp, "%d %d %d\n",
	    elements[i][0], elements[i][1], elements[i][2]);
  }

  /* Write number of nodes */
  fprintf(fp, "%d\n", num_nodes);

  /* Write nodes */
  for (i = 0; i < num_nodes; i++) {
    fprintf(fp, "%.15E %.15E\n",
	    nodes[i][0], nodes[i][1]);
  }

  /* Write number of boundary conditions */
  fprintf(fp, "%d\n", num_bcs);

  /* Write boundary conditions */
  for (i = 0; i < num_bcs; i++) {
    fprintf(fp, "%d %.15E\n",
	    bc_nodes[i], bc_values[i]);
  }

  /* Close file */
  fclose(fp);
}

int main(int argc, char *argv[])
{
  if (argc != 4) {
    printf("Usage: %s num_elements_r num_elements_theta mesh.txt\n", argv[0]);
    return 0;
  }

  generateMesh(atoi(argv[1]), atoi(argv[2]));
  outputMesh(argv[3]);

  return 0;
}
