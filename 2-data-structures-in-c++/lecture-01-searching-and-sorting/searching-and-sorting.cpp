#include<iostream>
using namespace std;

// Print the array
void printArray(int arr[], int n) {
	for(int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// SORTING METHODS: Iterative method 

// SELECTION SORT
void selectionSort(int arr[], int n) {
	for(int i = 0; i < n - 1; i++) { // for n-1 rounds
		int minIndex = i;
		for(int j = i + 1; j < n; j++) {
			if(arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[minIndex];
		arr[minIndex] = temp;
	}
}

// BUBBLE SORT
void bubbleSort(int arr[], int n){
	
    for(int i = 0; i < n - 1; i++) {
        for(int j = 1; j < n - i; j++) {
            if(arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            } 
        }
    }

}

// INSERTION SORT
void insertionSort(int arr[], int n){
	for(int i = 1; i < n; i++) {
        int current = arr[i];
        int j;
        for(j = i - 1; j >= 0; j--) {
            if(current < arr[j]) {
                arr[j + 1] = arr[j]; 
            } else {
                break;
            }
        }
        arr[j + 1] = current;
    }
}

// SORTING METHODS: Recursive method 

// MERGE SORT
void merge(int arr[], int start, int mid, int end) {
	// create a temp array
	int temp[end - start + 1];
	int i = start, j = mid+1, k = 0;
	while(i <= mid && j <= end) {
		if(arr[i] <= arr[j]) {
			temp[k] = arr[i];
			k += 1; i += 1;
		}
		else {
			temp[k] = arr[j];
			k += 1; j += 1;
		}
	}
	while(i <= mid) {
		temp[k] = arr[i];
		k += 1; i += 1;
	}
	while(j <= end) {
		temp[k] = arr[j];
		k += 1; j += 1;
	}
	for(i = start; i <= end; i += 1) {
		arr[i] = temp[i - start];
	}
}

void mergeSort(int arr[], int start, int end) {

	if(start < end) {
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid+1, end);
		merge(arr, start, mid, end);
	}
}

// QUICK SORT
int partition(int arr[], int start, int end) {
	// Find Pivot (the first element)
	// Place Pivot at it's pos
	// Ensure <= pivot towards left and > pivot towards right
	// return pivot position
	int lessThanEqaulToPivot = 0;
	for(int i = start + 1; i <= end; i++) {
		if(arr[i] <= arr[start]) {
			lessThanEqaulToPivot++;				
		}
	}
	int position = lessThanEqaulToPivot + start;
	int temp = arr[position];
	arr[position] = arr[start];
	arr[start] = temp;
	int i = start;
	int j = end;
	while(i < position && j > position) {
		if(arr[i] > arr[position]) {
			if(arr[j] <= arr[position]) {
				int temp1 = arr[i];
				arr[i] = arr[j];
				arr[j] = temp1;
				j--;
				i++;
			} else {
				j--;
			}
		} else { // ith element is less than equal to pivot
			i++;
		}
	}
	return position;		
}
	
void quick_sort(int arr[], int start, int end) {
	if(start >= end) { // Base case
		// as a single element is always sorted so no need to do anything for start == end
		return;			
	}
	int pivotPos = partition(arr, start, end);
	quick_sort(arr, start, pivotPos - 1);
	quick_sort(arr, pivotPos + 1, end);
}

// BINARY SEARCH: Iterative method
int binarySearch(int arr[], int n, int val) {
	int start = 0, end = n -1;
	while(start <= end) {
		int mid = (start + end) / 2;
		if(val == arr[mid]) {
			return mid;
		} else if(val < arr[mid]) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}
	return -1;
}

int main() {
	int input[100];
	int n;
	cout << "Enter the size of the array: ";
	cin >> n;
	
	// Take array input
	int val;
	cout << "Enter the values of the array: ";
	for(int i = 0; i < n; i++) {
		cin >> input[i];
	}
	
	// Display the array
	cout << "Your entered array is: ";
	printArray(input, n);
	
	// sort the array
	bool isSorted = true;
	while(isSorted) {
		int chooseSort;
		cout << "Which algorithm would you like to sort your array with?" << endl
			<< "1. Selection Sort" << endl
			<< "2. Bubble Sort" << endl
			<< "3. Insertion Sort" << endl 
			<< "=> ";
		cin >> chooseSort;
		switch(chooseSort) {
			case 1:
				selectionSort(input, n);
				isSorted = false;
				break;
			case 2:
				bubbleSort(input, n);
				isSorted = false;
				break;
			case 3:
				insertionSort(input, n);
				isSorted = false;
				break;
			case 4:
				mergeSort(input, 0, n);
				isSorted = false;
				break;
			default:
				cout << "The array needs to be sorted!!!";
		}
	}
			
	// Display sorted array
	cout << "The sorted array is: ";
	printArray(input, n);
		
	// search for the element
	int x;
	cout << "Enter the value that has to be searched: ";
	cin >> x;
	int index = binarySearch(input, n, x);
	if(index != -1) {
		cout << "The value is in the index " << index << " of the array";
	} else {
		cout << "The value is not present in the array";
	}
}
