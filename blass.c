#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>  
#include <time.h>
#include <cblas.h>

#define NR1 123
#define NR2 321

void generate_elements(double *A, int n, double *x, double *y)
{
	double random_number;
	int i, j;
	double nr;

	for(i = 0; i < n; i++)
	{
		for(j = i; j < n; j++)
		{
			random_number = rand();
			nr = (random_number / RAND_MAX) * NR1;
 
			A[i * n + j] = nr;
 			A[j * n + i] = nr;
		}
	}

	for(i = 0; i < n; i++)
	{
		random_number = rand();
		x[i] = (random_number / RAND_MAX) * NR1;
		y[i] = (random_number / RAND_MAX) * NR2;
	}
}

double multiply_by_formula(double *matrix, int n, double *x_array, double *y_array, double alpha, double beta)
{
	int i, j, k;
	double sum;
	struct timeval tv_begin, tv_end;
	double *partial_solution = calloc(n, sizeof(double));
	double *solution = calloc(n, sizeof(double));

	double *A = calloc(n * n, sizeof(double));
	for(i = 0; i < n * n; i++)
		A[i] = matrix[i];

	double *x = calloc(n, sizeof(double));
	double *y = calloc(n, sizeof(double));
	for(i = 0; i < n; i++)
	{
		x[i] = x_array[i];
		y[i] = y_array[i];
	}

	gettimeofday(&tv_begin, NULL);
	for(i = 0; i < n * n; i++)
	{	
		A[i] *= alpha;
	}

	for(i = 0 ; i < n; i++)
	{
		y[i] *= beta;
	}

	sum = 0;
	k = 0;
	for(i = 0, j = 0; i < n * n; i++, j++)
	{
		sum += A[i] * x[j];
		if(j == n - 1)
		{
			partial_solution[k] = sum;
			sum = 0;
			j = -1;
			k++;
		}
	}

	for(i = 0; i < n; i++)
		solution[i] = partial_solution[i] + y[i];

	gettimeofday(&tv_end, NULL);

	double elapsed = (tv_end.tv_sec-tv_begin.tv_sec) + (tv_end.tv_usec-tv_begin.tv_usec) / 1000000.0;

	return elapsed;
}

double multiply_using_dsymv(double *A, int n, double *x, double *y, double alpha, double beta)
{
	struct timeval tv_begin, tv_end;

	gettimeofday(&tv_begin, NULL);
	cblas_dsymv(CblasRowMajor, CblasUpper, n, alpha, A, n, x, 1, beta, y, 1);
	gettimeofday(&tv_end, NULL);
	double elapsed = (tv_end.tv_sec-tv_begin.tv_sec) + (tv_end.tv_usec-tv_begin.tv_usec) / 1000000.0;

	return elapsed;
}
	
int main(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("Wrong execution!\nFormat: ./tema2 MATRIX_DIMENSION PROCESOR_ARHITECTURE\n");
		return -1;
	}
	int n = atoi(argv[1]);
	char *arhitecture = argv[2];

	srand(time(NULL));

	FILE *my_out, *dsymv_out;
	double *A, *x, *y;
	double alpha, beta;
	double random_number = rand();
	alpha = (random_number / RAND_MAX) * NR1;
	beta  = (random_number / RAND_MAX) * NR2; 

	A = calloc(n * n, sizeof(double));
	x = calloc(n, sizeof(double));
	y = calloc(n, sizeof(double));

	generate_elements(A, n, x, y);

	double my_time = multiply_by_formula(A, n, x, y, alpha, beta);

	double dsymv_time = multiply_using_dsymv(A, n, x, y, alpha, beta);

	char file[100];
	sprintf(file, "my_%s", arhitecture);
	my_out = fopen(file, "a");
	if(!my_out)
	{
		printf("Error opening file 'my_out.out!\n");
		return -1;
	}
	sprintf(file, "dsymv_%s", arhitecture);
	dsymv_out = fopen(file, "a");
	if(!dsymv_out)
	{
		printf("Error opening file 'dsymv_out.out'\n");
		return -1;
	}
	fprintf(my_out, "%i	%lf\n", n, my_time);
	fprintf(dsymv_out, "%i	%lf\n", n, dsymv_time);
	fclose(my_out);
	fclose(dsymv_out);
	return 1;
}
