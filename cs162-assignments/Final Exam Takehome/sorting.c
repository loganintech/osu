#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

typedef struct timeval time;
void print_array(int *, int);
void merge(int *, int, int, int);
void merge_sort(int *, int, int);
void selection_sort(int *, int);
void insertion_sort(int *, int);
void bubble_sort(int *, int);
void fill_array(int **, int *);
void add_num(int **, int *, int);

int main()
{
      int *nums = NULL;
      int size = 0;
      time stop, start;

      fill_array(&nums, &size);
      print_array(nums, size);

      //Time the function here
      gettimeofday(&start, NULL);

      //bubble_sort(nums, size);
      //insertion_sort(nums, size);
      //merge_sort(nums, 0, size-1);
      selection_sort(nums, size);

      gettimeofday(&stop, NULL);

      printf("MicroSeconds: %d\n", stop.tv_usec - start.tv_usec);
      //printf("Seconds: %d\n", stop.tv_sec-start.tv_sec);

      print_array(nums, size);
      free(nums);

      return 0;
}

/*************************************************
 * Description: This prints the contents of an array
 * Params: array of integers and size of the array
 * Returns: none
 * Post-conditions: none
 * Pre-conditions: size is accurate number of 
 *                 elements in the array >=0
 * **********************************************/
void print_array(int *nums, int size)
{
      int i;

      printf("The array elements are:\n");
      for (i = 0; i < size; i++)
            printf("%d\t", nums[i]);
      printf("\n\n");
}

/*************************************************
 * Description: Merges two arrays together in order
 * Parameters: A number array, left bound, middle location, and right bound
 * Returns: none
 * Pre-Conditions: Two sections of array are sorted smallest to largest
 * Post-Conditions: The two sections of array are merged together into one sorted section
 *************************************************/
void merge(int *nums, int left, int mid, int right)
{
      int i, j, lower_half, upper_half;
      int temp[(right - left) + 1];

      lower_half = left;    //What is this for? This is so we can use the original left-value for later
      upper_half = mid + 1; //What is this for? This is so we can use the original mid-value for later

      //What does this loop do? This loop checks if the lower half (which changes locations) is still less than the mid value
      //It also checks to make sure that upper half does not exceed the rightmost value;
      for (i = 0; (lower_half <= mid) && (upper_half <= right); i++)
      {
            //What does this condition do? It checks to see if the left number is less than the right number
            if (nums[lower_half] <= nums[upper_half])
            {
                  //If it is, make add the left number to the temp array
                  temp[i] = nums[lower_half];
                  lower_half++;
            }
            //What does this condition do? This is if the right number is less than the upper number
            else
            {
                  //If the right half is smaller, add that to the temp array instead.
                  temp[i] = nums[upper_half];
                  upper_half++;
            }
      }

      //What does this condition and loop do? If lower half is over mid (we're done adding the left to temp)
      //Add the rest of the right side to the temp
      if (lower_half > mid) 
            for (j = upper_half; j <= right; j++, i++)
                  temp[i] = nums[j];
      //What does this else and loop do? If the lower half has elements left (we're done adding the right to temp)
      //Add the rest of the left side to the temp
      else
            for (j = lower_half; j <= mid; j++, i++)
                  temp[i] = nums[j];

      //What does this loop do? //Overwrite the source elements in the original array with the sorted ones
      for (j = 0, i = left; i <= right; i++, j++)
            nums[i] = temp[j];
}

/*************************************************
 * Description: Creates partitions elements, sorts them, compares adjacent partitions upwards until the entire list is sorted
 * Parameters: Numbers, location of left and right bound
 * Returns: none
 * Pre-Conditions: Array is created
 * Post-Conditions: Array is sorted
 * Worse-Case: O(n log(n))
 *************************************************/
void merge_sort(int *nums, int left, int right)
{
      int mid;
      if (left < right)
      {
            mid = (right + left) / 2;
            merge_sort(nums, left, mid);      //what does this call do? Calls the merge sort algo on the beginning to half way to the right
            merge_sort(nums, mid + 1, right); //what does this call do? Calls the merge sort algo on the middle to the end
            merge(nums, left, mid, right);    //what does this call do? Merges the smaller section into properly sorted items
      }
}

/*************************************************
 * Description: Picks the smallest number in future elements and swaps it with the start of where we're looking
 * Parameters: Array of numbers, size of array
 * Returns: Sorted array of numbers
 * Pre-Conditions: Array is created
 * Post-Conditions: Array is sorted
 * Worse-Case: O(n^2) - The list is in reverse order, causing both loops to iterate over the max number of items
 *************************************************/
void selection_sort(int *nums, int size)
{
      int i, j;
      int temp, min;

      //What does this loop do? It loops through all elements except for the last
      for (i = 0; i < size - 1; i++)
      {
            min = i;
            //What does this loop do? It loops through all elements starting at I and ending at the last
            for (j = i; j < size; j++)
                  if (nums[j] < nums[min])
                        min = j;
            //What elements are being swaped? The element at index `i` and the smallest element from i to end
            temp = nums[i];
            nums[i] = nums[min];
            nums[min] = temp;
      }
}

/*************************************************
 * Description: Loops through all numbers, moving them backwards in the list one place until the previous item is larger than our stored item. Puts the stored item where it belongs
 * Parameters: Array of numbers, size of array
 * Returns: none
 * Pre-Conditions: Array is created
 * Post-Conditions: Array is sorted
 * Worse-Case: O(n^2)
 *************************************************/
void insertion_sort(int *nums, int size)
{
      int i, j;
      int temp;

      //What does this loop do? This loop goes over all elements from start to finish
      for (i = 0; i < size; i++)
      {
            temp = nums[i];
            //What does this loop do? This loop makes sure J > 0 and that the previous number checked is larger than the temporary. If so, it sets the number to the previous number, and goes backwards
            for (j = i; j > 0 && nums[j - 1] > temp; j--)
                  nums[j] = nums[j - 1];
            //What does this statment do? Sets the number to the temp. This is the insertion.
            nums[j] = temp;
      }
}

/*************************************************
 * Description: Loops through all the numbers, Checks if the checking number is larger than the next number, swap them. Ignores items that have already been swapped into place.
 * Parameters: Array of numbers, size of array
 * Returns: none
 * Pre-Conditions: Array is created
 * Post-Conditions: Array is sorted
 * Worse-Case: O(n^2)
 * ***********************************************/
void bubble_sort(int *nums, int size)
{
      int i, j;
      int temp;

      //What does this loop do? It loops over every element
      for (i = 0; i < size; i++)
      {
            //What does this loop do? This loops over every element, skipping the already sorted ones at the end.
            for (j = 0; j < size - i - 1; j++)
            {
                  if (nums[j] > nums[j + 1]) //If left side bigger than right side, swap elements
                  {
                        temp = nums[j];
                        nums[j] = nums[j + 1];
                        nums[j + 1] = temp;
                  }
            }
      }
}

/*************************************************
 * Description: This adds an element to the array
 * and sets the contents to num
 * Params: address of array pointer to ints and 
 *         address of size of the array
 * Returns: none
 * Post-conditions: size is increased by one and
 * nums points to new array with one more element
 * where the contents are the same with num at the end
 * Pre-conditions: nums points to valid array or NULL
 * and size is accurate number of elements in array >=0
 * **********************************************/
void add_num(int **nums, int *size, int num)
{
      int *old_nums, i;

      *size += 1;
      old_nums = *nums;
      *nums = (int *)malloc(sizeof(int) * (*size));

      for (i = 0; i < *size - 1; i++)
            (*nums)[i] = old_nums[i];
      (*nums)[*size - 1] = num;

      free(old_nums);
}

/*************************************************
 * Description: This fills an array with contents
 * from a file
 * Params: address of array pointer to ints and 
 *         address of size of the array
 * Returns: none
 * Post-conditions: array pointer is pointing to
 * valid array of integers or NULL and size has
 * a positive integer
 * Pre-conditions: nums points to valid array or NULL
 * and size is accurate number of elements in array >=0
 * **********************************************/
void fill_array(int **nums, int *size)
{
      FILE *fptr;
      char filename[20], num[10];
      printf("Enter the filename: ");
      scanf("%s",filename);
      fptr=fopen(filename,"r");

      while (fscanf(fptr, "%s", num) != EOF)
      {
            add_num(nums, size, atoi(num));
      }

      fclose(fptr);
}
