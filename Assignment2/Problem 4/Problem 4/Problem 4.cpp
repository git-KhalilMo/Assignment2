#include <iostream>
#include <cstdlib>
#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0; 
    int j = 0; 
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

bool recursivePairSum(int arr[], int left, int right, int k) {
    if (left >= right) {
        cout << "No pair found." << endl;
        return false; 
    }

    int sum = arr[left] + arr[right];

    if (sum == k) {
        cout << "Pair found: " << arr[left] << " and " << arr[right] << endl;
        return true; 
    }
    else if (sum < k) {
        return recursivePairSum(arr, left + 1, right, k);
    }
    else {
        return recursivePairSum(arr, left, right - 1, k);
    }
}

bool iterativePairSum(int arr[], int size, int k) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j != i) {
                if (arr[i] + arr[j] == k) {
                    cout << "Pair found: " << arr[i] << " and " << arr[j] << endl;
                    return true;
                }
            }
        }
    }
    cout << "No pair found." << endl;
    return false;
}

void randomizeArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << endl;
    }
}

#include <iostream>

int main()
{
    int array[10] = {};
    int array2[100] = {};
    int array3[1000] = {};
    randomizeArray(array, 10);
    randomizeArray(array2, 100);
    randomizeArray(array3, 1000);
    mergeSort(array, 0, 9);
    mergeSort(array2, 0, 99);
    mergeSort(array3, 0, 999);

    printArray(array, 10);
    cout << endl;

    auto start = high_resolution_clock::now();
    iterativePairSum(array3, 1000, 69);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Microseconds: " << duration.count() << endl;
}