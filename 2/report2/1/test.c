#include <stdio.h>

int main(){
    // int a[10] = {1,2,3,4,5,6,7,8,9,10};

    // int *p;
    // p = a;
    // printf("%d %d %d\n",a[0],a[1],a[2]);

    // printf("%d %d %d\n",*p,*(p+1),*(p+2));

    int balance[3][2] = {
        {1,2},
        {3,4},
        {5,6},
    };

    int *p;
    p = (int *)balance;

    printf("%d",*(p+(2*2)));


    return 0;

    
}