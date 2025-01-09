#include "header.h"
#include <cstdio>
#include <iostream>

int* fintv_1(int n) {

	int i;
	
	int *v = new int [n];
	
	for(i=0;i<n;i++)  //preenchimento dos valores do tensor
    {
        v[i] = 1;    
    }	
	return v;

}

double* fdoublev_1(int n) {

	int i;

	double *v = new double[n];

	for(i=0;i<n;i++)  //preenchimento dos valores do tensor
    {
        v[i] = 1;
        
    }	

    return v;

}

int**  fintv_2(int n1, int n2) {
 	
 	int i, j;

 	int **v= new int *[n1];  //alocação do espaço do tensor de doubles

	for(i = 0; i < n1; i++){

	    v[i] = new int [n2];
	}

	for(i=0;i<n1;i++)  //preenchimento dos valores do tensor
    {
    	for (int j = 0; j < n2; j++)
    	{
    		v[i][j] = 1;
    	}        
    }
	return v;

}


double*** fdoublev_2(int n1, int n2, int n3)
{
    int i, j, k;
    
    double ***v = new double **[n1];  //alocação do espaço do tensor de doubles
    for(i = 0; i < n1; i++)
    {
       v[i] = new double *[n2];
    }


    for(i = 0; i < n1; i++)
    {
      for(j = 0; j < n2; j++)
     {
         v[i][j] = new double [n3];
      }
    }
    
    for(i = 0; i < n1; i++)  //preenchimento dos valores do tensor
    {
        for(j = 0; j < n2; j++)
        {
            for(k = 0; k < n3; k++)
            {
                v[i][j][k] = 5;
            }
        }
        
    }
    
    return v;
}

void print(double*** v, int n1, int n2, int n3){

    int i, j, k;

    for (i = 0; i < n1; ++i) {

        printf("\n");

          for (j = 0; j < n2; ++j){

             printf("\n");

                  for(k = 0; k < n3; ++k){

                    printf(" %.0lf\n", v[i][j][k]);
                  }
           }  
    }

}








