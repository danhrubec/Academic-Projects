//Daniel Hrubec
//netID:dhrube2
//CS 211 - Programming Project 1

#include <stdio.h>
#include <stdlib.h>

/*
This function takes in two arrays and the size of the initial array.
It will store all of the values of the first array into the second array to make
a copy of it. It will return nothing as the array will be changed after the
function is called. 
*/
void makeArrayCopy(int fromArray[], int toArray[], int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		toArray[i] = fromArray[i];
	}


}
/*
This function takes in the array and the size of the array. Then uses the bubble sorting technique
to sort the values in ascending order.
*/

void ascendSort(int arr[], int size)
{

 int k;
 int j;
 int minimum;
  
    //loop through the entire array
    for (k = 0; k < size-1; k++) 
    { 
        // Sets the first as the minimum
        minimum = k; 
        //checks to see if it really is the minimum
        for (j = k+1; j < size; j++) 
        {
          if (arr[j] < arr[minimum]) 
          {
            minimum = j; 
          }
    	}
  
        // swaps the elements if there was any change
        int temp = arr[minimum];
        arr[minimum] = arr[k];
        arr[k] = temp;
                
    } 

}

/*
Not a required function from the program requirements, but a supporting function. This will print
out all the values of the array to ensure that the program is working as intended. 
*/
void printArr(int arr[], int size)
{
	int p = 0;
	for (p = 0; p < size; p++)
	{
		printf("%d ", arr[p]);
	}

}

//linear search method. loops through entire array to find the value, returns -1 if it is not there
int linSearch(int arr[], int size, int target, int* numComparison)
{
	int position = 0;
	int z = 0;
	
	for (z = 0; z < size; z++)
	{
		*numComparison = *numComparison + 1;
		if(arr[z] == target)
		{
			position = z;
			z= size;
		}
		else
			position = -1;
	}
	
	return position;
}

//binary search method. Returns -1 if the value is not found
int binSearch(int arr[], int size, int target, int* numComparison)
{
	int lower = 0;
	int upper = size - 1;
	  while (lower <= upper) 
	  { 
	  	*numComparison = *numComparison + 1;
        int middle = lower + (upper - lower) / 2; 
  
        //returns the middle if its the target
        if (arr[middle] == target) 
            return middle; 
  
        // if target greater than middle, ignore lower half 
        if (arr[middle] < target) 
            lower = middle + 1; 
  
        // if target less than middle, ignore upper half
        else
            upper = middle - 1; 
    } 
  
    // returns this if value was not found
    return -1;   
}

int main (int argc, char** argv)
{
 //starting variables
 int val;
 int arrCount = 0; // keep count of pos in array to assign to each element
 int comparisons1 = 0;
 int comparisons2 = 0;

 /* prompt the user for input */
 printf ("Enter in a list of numbers into be stored in a dynamic array.\n");
 printf ("End the list with the terminal value of -999\n");


 //creating dynamic array
 int* dynamArr;
 int allocate = 10;
 dynamArr = (int*) malloc(allocate * sizeof(int));


 
 /* loop until the user enters -999 */
 scanf ("%d", &val);
 if (val != -999)
 {
	dynamArr[arrCount] = val;
	arrCount++;
 }

 while (val != -999)
 {
    scanf("%d", &val);
    if (val != -999)
 	{
	 	dynamArr[arrCount] = val;
		arrCount++;
 	}

 	if(arrCount >= allocate - 2)
 	{
 		int *temp = dynamArr;
 		dynamArr = (int *) malloc ( allocate * 2 * sizeof(int) );
		int i;
 			for ( i = 0 ; i < allocate ; i++)
 				dynamArr[i] = temp[i];
 		free (temp);
 		allocate = allocate * 2;
 	}
 }


 //creating another array to copy the values into it
 int*dynamArr2;
 dynamArr2 = (int*) malloc(arrCount * sizeof(int));
 printf("\n");


 /* call function to make a copy of the array of values */
 makeArrayCopy(dynamArr,dynamArr2,arrCount);
 //printArr(dynamArr2,arrCount);

 /* call function to sort one of the arrays */
 ascendSort(dynamArr,arrCount);
 printf("\n");
 //printArr(dynamArr,arrCount);
 printf("\n");

 /* loop until the user enters -999 */
 printf ("Enter in a list of numbers to use for searching.  \n");
 printf ("End the list with a terminal value of -999\n");
 scanf ("%d", &val);

 //dynamArr2 is the unsorted, dynamArr1 is the sorted array
 while (val != -999)
   {

    /* call function to use the value in a linear search on the unsorted array */
    printf("Using linear search in an unsorted array, searching for value %d", val);
    printf ("...\n"); 
    if(linSearch(dynamArr2,arrCount,val,&comparisons1) == -1)
    {
    	comparisons1 = 0;
    	printf("value not found.\n"); 
    	
    }
    else
    {
    	comparisons1 = 0;
   		printf("Value found at position:%d ", linSearch(dynamArr2,arrCount,val,&comparisons1));
   		printf("Number of comparisons made:%d ", comparisons1);
   		comparisons1 = 0;
   	}
   	printf ("\n");   

   	printf ("\n");

    /* call function to use the value in a binary search on the sorted array */

	printf("Using binary search in a sorted array, searching for value %d", val);
    printf ("...\n");
    if(binSearch(dynamArr,arrCount,val,&comparisons2) == -1)
    {
    	comparisons2 = 0;
    	printf("value not found.\n"); 
  
    }
    else
    {
    	comparisons2 = 0;
   		printf("Value found at position:%d ", binSearch(dynamArr,arrCount,val,&comparisons2));
   		printf("Number of comparisons made:%d ", comparisons2);
   		comparisons2 = 0;
    }

   	printf ("\n\n\n"); 

    /* get next value */
    scanf("%d", &val);
   }


 printf ("Good bye\n");
 
 return 0;
} 
