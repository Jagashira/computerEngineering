#include<stdio.h>

int main()
{   
 
    double a[10][10] = {
        { 1 , -2 ,-3 },
        { 2 , 10 , 1 },
        { 3 , -3 , 4 },
    };
    double b[10] = {2007.0,4105.0,6052.0};
    double m[10][10];
    double x[10];
    double y[10];
    double sum;
  
    int j, k, l, n;
    
    n=3;

                               //Ⅰ//
                               puts("1");

    for(l=1;l<n;l++)                              //Ⅱ//
    {   
	for(j=l+1;j<=n;j++)
	{   
	    m[j][l]=a[j][l]/a[l][l];
	    for(k=l;k<=n;k++)
	    {  
		a[j][k]=a[j][k]-m[j][l]*a[l][k];
	    }   
		b[j]=b[j]-m[j][l]*b[l];              //Ⅱ//
	}   
    }   

    m[1][1]=1;
    m[1][0]=0;
    m[1][3]=0;
    m[2][2]=1;
    m[2][3]=0;
    m[3][3]=1;                                    //Ⅱ//
puts("2");
    y[1]=b[1];                                    //Ⅲ//
    y[2]=b[2]-a[2][1]*y[1]; 
    y[3]=b[3]-a[3][2]*y[2]-a[3][1]*y[1];              //Ⅲ//
    puts("3");

    for(j=n;j>=1;j--)                               //Ⅳ//
    {
	k=j+1;

	if(k>n)
	{  
	    x[j]=y[j]/a[j][j];                        //Ⅳ//
	}   
	else
	{  
	    sum=0;	
	    for(k=j+1;k<=n;k++)
	    {  
		sum=sum+a[j][k]*x[k];
	    }   
	    x[j]=(y[j]-sum)/a[j][j];      
                   //Ⅳ//
                   
	}   
    puts("4");
	printf("x[%d]=%lf\n", j, x[j]);              //Ⅴ//
    }   
    puts("5");
}   
