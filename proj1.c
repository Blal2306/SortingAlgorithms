#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/**** HELPER METHODS *****/
//print the given array of size n
void print_array(int* in,int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%3d ",*in++);
		if((i+1) % 10 == 0)
		{
			printf("\n");
		}
	}
}
void print_array_v(int* in, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = *in; j > 0; j--)
		{
			printf("*");
		}
		printf("\n");
		in++;		
	}
}
//fill the array of given size with random numbers
void fill_random(int* in, int n)
{
	srand(time(NULL));
	for(int i = 0; i < n; i++)
	{
		*in++ = rand()%1000 + 1;
	}
}
//fill the array with random number visual
void fill_random_v(int* in, int n)
{
	srand(time(NULL));
	for(int i = 0; i < n; i++)
	{
		*in++ = rand()%14 +1;
	}
}
//random number generator for counting sort
void fill_random_c(int* in, int n)
{
	srand(time(NULL));
	for(int i = 0; i < n; i++)
	{
		*in++ = rand()%99 +0;
	}
}

/***** SORTING ALGORITHMS *******/
//*********** INSERTION SORT ***********/
void insertion_sort(int n)
{
	//create an array of n random numbers
	int num[n];
	fill_random(&num, n);
	
	//print the array
	printf("ORIGINAL\n\n");
	print_array(&num, n);
	
	//sort
	for(int j = 1; j < n; j++)
	{
		int key = num[j];
		int i = j - 1;
		while(i >= 0 && num[i] > key)
		{
			num[i+1] = num[i];
			i = i - 1;
		}
		num[i+1] = key;
		
	}
	
	//print
	printf("\nSORTED\n\n");
	print_array(&num, n);
}
void insertion_sort_v(int n)
{
	//create an array of n random numbers
	int num[n];
	fill_random_v(&num, n);
	
	//print the array
	printf("ORIGINAL\n\n");
	print_array_v(&num, n);
	printf("\n");
	
	//sort
	for(int j = 1; j < n; j++)
	{
		int key = num[j];
		int i = j - 1;
		while(i >= 0 && num[i] > key)
		{
			num[i+1] = num[i];
			i = i - 1;
		}
		num[i+1] = key;
		
		//print the iteration of this step
		print_array_v(&num,n);
		printf("\n");
	}
	
	//print
	printf("\nSORTED\n\n");
	print_array_v(&num, n);	
}
//************ MERGE SORT **************//
//merge method
void merge(int* a, int p, int q, int r)
{
	int n1 = q-p+1; //length of the first part
	int n2 = r-q; //length of the second part
	
	//temp array for the left and right side
	int L[n1];
	int R[n2];
	
	//get the left part of the array
	for(int i = 0; i < n1; i++)
	{
		L[i] = a[p+i];
	}
	
	//get the right part of the array
	for(int j = 0; j < n2; j++)
	{
		R[j] = a[q+j+1];
	}
	
	int i = 0;
	int j = 0;
	
	for(int k = p; k <= r; k++)
	{
		if((i < n1) && (j != n2) && L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else if(j == n2)
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j = j + 1;
		}
	}
}
void mergeSort(int n)
{
	//create an array of size n
	int a[n];
	//fill the array with random numbers
	fill_random(&a,n);
	
	//print the array
	printf("ORIGINAL\n\n");
	print_array(&a, n);
	
	//sort
	mergeSort_2(&a, 0, n-1);
	
	printf("\nSORTED\n\n");
	print_array(&a, n);
}
void mergeSort_2_v(int* a, int p, int r, int size)
{
	if(p < r)
	{
		int q = (int) ((p+r)/2);
		mergeSort_2_v(a,p,q,size);
		mergeSort_2_v(a,q+1,r,size);
		merge(a,p,q,r);
		print_array_v(a, size);
		printf("\n");
	}
}
void mergeSort_v(int n)
{
	int a[n];
	fill_random_v(&a,n);
	
	//print the array
	printf("ORIGINAL\n\n");
	print_array_v(&a, n);
	printf("\n");
	
	//sort
	mergeSort_2_v(a,0,n-1,n);
	
	//print the sorted things
	printf("\nSORTED\n\n");
	print_array_v(&a, n);
	
}
void mergeSort_2(int* a, int p, int r)
{
	if(p < r)
	{
		int q = (int) ((p+r)/2);
		mergeSort_2(a,p,q);
		mergeSort_2(a,q+1,r);
		merge(a,p,q,r);
	}
}

//**** QUICK SORT RANDOMIZED ****/
//partition
int partition(int* A, int p, int r)
{
	int x = A[r]; //pick the last item as the pivot by default
	int i = p - 1;
	for(int j = p; j <= r-1; j++)
	{
		if(A[j] <= x) //if the element is less than the pivot
		{
			i++;
			int temp = A[j];
			A[j] = A[i];
			A[i] = temp;
		}
	}
	
	//Move the pivot into position
	int temp = A[r];
	A[r] = A[i+1];
	A[i+1] = temp;
	
	return i+1;
}
int rand_partition(int* A, int p, int r)
{
	srand(time(NULL));
	int randomNum = rand() % (r + 1 - p) + p; 
	int temp = A[r];
	A[r] = A[randomNum];
	A[randomNum] = temp;
	
	return partition(A,p,r);
}
void quickSort(int n)
{
	//create an array of size of n
	int a[n];
	
	//fill it with random numbers
	fill_random(&a,n);
	
	//print the array
	printf("ORIGINAL\n\n");
	print_array(&a, n);
	
	//sort the numbers
	quickSort_2(a,0,n-1);
	
	//print the sorted things
	printf("\nSORTED\n\n");
	print_array(&a, n);
}
void quickSort_v(int n)
{
	//create an array of size of n
	int a[n];
	
	//fill it with random numbers
	fill_random_v(&a,n);
	
	//print the array
	printf("ORIGINAL\n\n");
	print_array_v(&a, n);
	printf("\n");
	
	//sort the numbers
	quickSort_2_v(a,0,n-1,n);
	
	//print the sorted things
	printf("\nSORTED\n\n");
	print_array_v(&a, n);
}
void quickSort_2(int* A, int p, int r)
{
	if(p < r)
	{
		int q = rand_partition(A, p, r);
		quickSort_2(A,p,q-1);
		quickSort_2(A,q+1,r);
	}
}
void quickSort_2_v(int* A, int p, int r, int size)
{
	if(p < r)
	{
		int q = rand_partition(A, p, r);
		print_array_v(A, size);
		printf("\n");
		quickSort_2_v(A,p,q-1, size);
		quickSort_2_v(A,q+1,r, size);
	}
}
void init_array(int* a, int n)
{
	for(int i = 0; i < n; i++)
	{
		a[i] = 0;
	}
}
void counting_sort(int n)
{
	int C[100]; //temp data holder
	int A[n];
	int B[n];
	
	//initialize all the arrays
	init_array(&C,100);
	init_array(&A, n);
	init_array(&B, n);
	//fill the array with random numbers
	fill_random_c(&A,n);
	
	//print the array
	printf("ORIGINAL\n\n");
	print_array(&A, n);
	
	//count the number of occurences
	for(int i = 0; i < n; i++)
	{
		C[A[i]]++;
	}
	//calculate the position by summing the number of elements before
	//and current position
	for(int i = 1; i < 100; i++)
	{
		C[i] = C[i]+C[i-1];
	}
	
	//finalize
	for(int j = n-1; j>=0; j--)
	{
		B[C[A[j]]-1] = A[j];
		C[A[j]]--;
	}
	
	//print the final result
	printf("\nSORTED\n\n");
	print_array(&B,n);	
}
//counting sort visual
void counting_sort_v(int n)
{
	int C[20]; //temp data holder
	int A[n];
	int B[n];
	
	//initialize all the arrays
	init_array(&C,20);
	init_array(&A, n);
	init_array(&B, n);
	//fill the array with random numbers
	fill_random_v(&A,n);
	
	//print the array
	printf("ORIGINAL\n\n");
	print_array_v(&A, n);
	printf("\n");
	
	//count the number of occurences
	for(int i = 0; i < n; i++)
	{
		C[A[i]]++;
	}
	//calculate the position by summing the number of elements before
	//and current position
	for(int i = 1; i < 20; i++)
	{
		C[i] = C[i]+C[i-1];
	}
	
	//finalize
	for(int j = n-1; j>=0; j--)
	{
		B[C[A[j]]-1] = A[j];
		C[A[j]]--;
		print_array_v(&B,n);
		printf("\n");
	}
	
	//print the final result
	printf("\nSORTED\n\n");
	print_array_v(&B,n);	
}
//READ THE TYPE OF ALGO TO USE
int algo_type()
{
	printf("Please select the sorting algorithm to use ...\n\n");
	printf("1 : INSERTION SORT\n");
	printf("2 : COUNTING SORT\n");
	printf("3 : MERGE SORT\n");
	printf("4 : RANDOMIZED QUICK SORT\n\n");
	printf("CHOICE > ");
	int x;
	scanf("%d",&x);
	return x;
}
int get_range()
{
	printf("Please enter n (1 to 1000) > ");
	int r;
	scanf("%d",&r);
	return r;
}
void main()
{
	while(1){

		//GET THE TYPE OF THE ALGORITHM TO USE
		int t = 0;
		while(!(t>=1) || !(t<=4))
		{
			t = algo_type();
			if(t == 0 || t > 4)
			{
				printf("ERROR : Algorithm is not supported ...\n");
			}
		}
	
		//GET THE RANGE FOR THE ALGORITHM
		int range = 0;
		while((range < 1 ) || (range > 1000))
		{
			range = get_range();
			if((range < 1 ) || (range > 1000))
			{
				printf("ERROR : The range must be from 1 to 1000 ...\n");
			}
		}
	
		//ADJUST FOR VISUAL ALGORITHM
		if(range<= 20)
		{
			t = t + 4;
		}
	
		switch(t)
		{
			case 1 : 
				insertion_sort(range);
				break;
			case 5 :
				insertion_sort_v(range);
				break;
			case 2 : 
				counting_sort(range);
				break;
			case 6 :
				counting_sort_v(range);
				break;
			case 3 :
				mergeSort(range);
				break;
			case 7 :
				mergeSort_v(range);
				break;
			case 4 :
				quickSort(range);
				break;
			case 8 :
				quickSort_v(range);
				break;
		}
		printf("\n");
	}
	
}

