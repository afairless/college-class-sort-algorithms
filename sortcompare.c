/* Andrew H. Fairless
 * transcribed and slightly modified January 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionsort (int a[], int n);
void mergesort (int a[], int n);
void rmerge (int a[], int mid, int n);
void merge (int a[], int n, int b[], int m, int c[]);
void quicksort (int a[], int n);
int split (int a[], int n);

int a[], b[], c[];
int size;

/****************************************
 * Sorting main function		*
 * Andrew Fairless			*
 ****************************************
 *
 * This program gives the user the option to sort a randomly selected set of
 * integers using one of three different algorithms and times the process so
 * that the algorithms' efficiencies can be compared.  The main calls the
 * functions selectionsort, mergesort, and quicksort.  It also interfaces
 * with the user and times the algorithm.
 */

main()

{

	int whichsort, i, *a, maxprintsize;

	maxprintsize = 500;
	srandom (time (0));
	printf ("How many integers would you like to sort?\n");
	scanf ("%d", &size);
	printf ("Type the number of the sort you would like to perform.\n\n");
	printf ("1)  Selection sort\n");
	printf ("2)  Merge sort\n");
	printf ("3)  Quick sort\n");
	scanf ("%d", &whichsort);
	a = (int *) malloc(size * sizeof(int));
	printf ("\nHere is the array:\n");
	for (i = 0; i < size; i++)
		{
		a[i] = (random() % 100) + 1;
		if (size < maxprintsize)
			printf ("%d ", a[i]);
		}
	printf ("\n");
	clock();
	switch (whichsort)
		{
		case  1:  selectionsort(a, size);
			  break;
		case  2:  mergesort(a, size);
			  break;
		case  3:  quicksort(a, size);
			  break;
		default:  printf ("invalid input--use only 1, 2, or 3\n");
			  break;
		}
	printf ("\ntime = %g s\n", clock() / (double) CLOCKS_PER_SEC);
	printf ("\nHere is the sorted array:\n");
	if (size < maxprintsize)
		for (i = 0; i < size; i++)
			printf ("%d ", a[i]);
	printf ("\n");
	return 0;
}



/****************************************
 * Selectionsort function		*
 * Andrew Fairless			*
 ****************************************
 *
 * The code for this function was taken from class notes.
 * It is called by the main function.  It sorts the data set by using a 
 * nested loop which causes its time to run on the order of n^2 (n-squared).
 * The code compares two integers from the array at a time and swaps if 
 * needed.
 */

void selectionsort (int a[], int n)

{
	int i, j, biggest, temp;

	for (i = n - 1; i >= 0; i--)	/* i loop counts down array as j loop */
		{
		biggest = 0; /* biggest tracks the index of the largest array element */
		for (j = 1; j <= i; j++)
			{
			if (a[j] > a[biggest])
				{
				biggest = j;
				}
			}
		temp = a[i];
		a[i] = a[biggest];
		a[biggest] = temp;
		}
}



/****************************************
 * Mergesort function			*
 * Andrew Fairless			*
 ****************************************
 *
 * The code for this function was taken from class notes.  
 * It is called by the main function and calls itself (recursion) to split
 * the array into two parts repeatedly.  Then i tcalls rmerge to rearrange
 * and merge the lists back together.  The entire process is executed on the
 * order of n log n time.
 */

void mergesort (int a[], int n)

{
	int mid;

	if (n > 1)
		{
		mid = n / 2;
		mergesort (a, mid);
		mergesort (a + mid, n - mid);
		rmerge (a, mid, n);
		}
}


/****************************************
 * Rmerge function			*
 * Andrew Fairless			*
 ****************************************
 *
 * The code for this function was taken from class notes.  
 * This function is called by mergesort.  It allocates memory for the c
 * array which acts as a "dummy" array in which to copy integers into the
 * correct order.  The call to the function merge recombines the lists (see
 * comments under mergesort function) and the i-loop copies the correct
 * order from the dummy array to the original array.
 */

void rmerge (int a[], int mid, int n)

{
	int i, *c;

	c = (int *)malloc(n * sizeof(int));
	merge (a, mid, a + mid, n - mid, c);
	for (i = 0; i < n; i++)
		a[i] = c[i];
	free (c);
}



/****************************************
 * Merge function			*
 * Andrew Fairless			*
 ****************************************
 *
 * The code for this function was taken from class notes.  
 * This function is called by the rmerge function.  Through recursive calls,
 * it copies the elements one-by-one into the "dummy" c array from least to 
 * greatest.
 */

void merge (int a[], int n, int b[], int m, int c[])

{
	int i;

	if (n > 0 || m > 0)	/* if both arrays are not empty */
		{
		if (n <= 0 || (m > 0 && b[0] < a[0]))	
			{
			c[0] = b[0];
			merge (a, n, b + 1, m - 1, c + 1);
			}
		else
			{
			c[0] = a[0];
			merge (a + 1, n - 1, b, m, c + 1);
			}
		}
}



/****************************************
 * Quicksort function			*
 * Andrew Fairless			*
 ****************************************
 *
 * The code for this function was taken from class notes.  
 * This function is called by the main.  It calls the function split to
 * determine an effective pivot point by which to divide the elements into
 * two parts and rearrange the elements.  The following recursive calls
 * repeatedly divide and rearrange the elements until the array is sorted.
 * The entire process executes on the order of n log n.
 */

void quicksort (int a[], int n)

{
	int mid;

	if (n > 1)
		{
		mid = split (a , n);
		quicksort (a, mid);
		quicksort (a + mid, n - mid);
		}
}



/****************************************
 * Split function			*
 * Andrew Fairless			*
 ****************************************
 *
 * The code for this function was taken from class notes.  
 * This function is called by the quicksort function.  It first locates a
 * pivot point by finding the largest and smallest array elements and taking
 * their average.  Then it swaps the values so that all values greater than
 * the pivot are on one end of the array and the lesser values are on the
 * other side.
 */

int split (int a[], int n)

{
	int i, point, big, small, pivot, temp;

	big = 0;
	small = 0;
	for (i = 0; i < n; i++)		/* i-loop locates extreme values in array */
		{
		if (a[i] > a[big])
			big = i;
		if (a[i] < a[small])
			small = i;
		}
	pivot = (a[big] + a[small])/2;
	if (big == small)
		return (n/2);
	point = 0;
	for (i = 0; i < n; i++)		/* i-loop swaps elements about pivot */
		{
		if (a[i] <= pivot)
			{
			temp = a[i];
			a[i] = a[point];
			a[point] = temp;
			point++;
			}
		}
	return (point);
}





















