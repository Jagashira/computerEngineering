#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COORDINATE_LENGTH 13
#define ELEMENT_LENGTH 12

int main()
{

    double coordinate[COORDINATE_LENGTH][2] =
        [[ 0, 0 ]
                [1, 0]
                [0.5, 0.8602540378]
                [-0.5, 0.8602540378]
                [-1, 0]
                [-0.5, -0.8602540378]
                [0.5, -0.8602540378]
                [0, -1.732050808]
                [1.5, -0.8602540378]
                [1.5, 0.8602540378]
                [0, 1.732050808]
                [-1.5, 0.8602540378]
                [-1.5, -0.8602540378]
                [-1, -1.732050808]
                [1, -1.732050808]];

    double elements[ELEMENT_LENGTH][3] =
        [
            [ 0, 1, 2 ],
            [ 0, 2, 3 ],
            [ 0, 3, 4 ],
            [ 0, 4, 5 ],
            [ 0, 5, 6 ],
            [ 0, 6, 1 ],
            [ 5, 7, 6 ],
            [ 6, 8, 1 ],
            [ 1, 9, 2 ],
            [ 2, 10, 3 ],
            [ 3, 11, 4 ],
            [ 4, 12, 5 ]
        ];
    double elements_pre[ELEMENT_LENGTH][3];
    for (int i = 0; i < ELEMENT_LENGTH; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            elements_pre[i][j] = 1 + elements[i][j];
        }
    }
    double S[ELEMENT_LENGTH];

    for (int i = 0; i < ELEMENT_LENGTH; i++)
    {
        double *x1 = coordinate[elements_pre[i, 1], 1];
        double *x2 = coordinate[elements_pre[i, 2], 1];
        double *x3 = coordinate[elements_pre[i, 3], 1];
        double *y1 = coordinate[elements_pre[i, 1], 2];
        double *y2 = coordinate[elements_pre[i, 2], 2];
        double *y3 = coordinate[elements_pre[i, 3], 2];

        S[i] = abs((x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2) / 2);
    }
    for (int i = 0; i < ELEMENT_LENGTH; i++)
    {
        printf("%lf\n", S[i]);
    }
    D
}
