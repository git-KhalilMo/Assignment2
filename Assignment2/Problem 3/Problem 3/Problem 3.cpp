#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;

void initializeArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << endl;
    }
}

void randomizeArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

int* rearrangeIterative(int* arr, int size, int k) {
    if (size <= 1) {
        return arr;
    }
    int smallSize = 0;
    for (int i = 0; i < size; i++) { // finding amount of elements <= k
        if (arr[i] <= k) {
            smallSize++;
        }
    }

    int largeSize = size - smallSize; // amount of elements > k
    int* small = new int[smallSize]; // array to hold elements <= k
    int* large = new int[largeSize]; // array to hold elements > k

    int smallIterator = 0;
    int largeIterator = 0;
    for (int i = 0; i < size; i++) { // iterating through original arr to insert elements <= k into small, and elements > k into large
        if (arr[i] <= k) {
            small[smallIterator] = arr[i];  
            smallIterator++;
        }
        else {
            large[largeIterator] = arr[i]; 
            largeIterator++;
        }
    }

    for (int i = 0; i < smallSize; i++) { // this and the next for loop rearrange the array
        arr[i] = small[i];  
    }

    for (int i = 0; i < largeSize; i++) {
        arr[smallSize + i] = large[i];
    }

    for (int i = 0; i < size; i++) {
        if (arr[i] == k && arr[i + 1] <= k) {
            arr[i] = arr[i + 1];
            arr[i + 1] = k;

        }
    }
    return arr;
}

void recursiveRearrange(int* arr, int start, int end, int k) {
    if (end - start <= count(arr, arr + end, k)) {
        return;
    }
    int left = start;
    int right = end;

    while (left <= right && arr[left] < k) {
        left++;
    }
    while (left <= right && arr[right] > k) {
        right--;
    }
    if (left < right) {
        if (arr[left] == arr[right]) {
            swap(arr[left], arr[right-1]);
            swap(arr[right], arr[left+1]);
        }
        else {
            swap(arr[left], arr[right]);;
        }
    }
    recursiveRearrange(arr, left, right, k);
} 


int main()
{
    int array[10] = {};
    int array2[100] = {};
    int array3[1000] = {};
    randomizeArray(array, 10);
    randomizeArray(array2, 100);
    randomizeArray(array3, 1000);
    printArray(array2, 100);
    cout << endl;

    cout << "Value of k: " << array2[50] << endl;
    auto start = high_resolution_clock::now();
    recursiveRearrange(array2, 0, 99, array2[50]);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Microseconds: " << duration.count() << endl;
    printArray(array2, 100);
    
    //rearrangeIterative(array3, 1000, array3[500]);
}
