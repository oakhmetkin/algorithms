#include <iostream>
#include "../common_methods/arrays_methods.h"

// shift subarray [l, r] to [l - 1, r - 1]
void left_shift(int* arr, int l, int r)
{
    for (size_t i = l; i <= r; i++)
        arr[i - 1] = arr[i];    
}

// shift subarray [l, r] to [l + 1, r + 1]
void right_shift(int* arr, int l, int r)
{
    for (int i = r; i >= l; i--)
        arr[i + 1] = arr[i];
}

// non-deterministic quick sort
void nd_quick_sort(int* arr, int n)
{
    if (n <= 1) return;

    int pivotIndex = rand() % n;
    int pivot = arr[pivotIndex];

    // partition    
    for (size_t i = 0; i < pivotIndex; i++)
        if (arr[i] >= pivot)
        {
            int tmp = arr[i];
            left_shift(arr, i + 1, pivotIndex);
            arr[pivotIndex--] = tmp;
            i--;
        }

    int rb = pivotIndex; // rb - right border

    while (pivotIndex < n - 1 && arr[pivotIndex + 1] == pivot)
        pivotIndex++;
    
    for (size_t i = pivotIndex + 1; i < n; i++)
        if (arr[i] <= pivot)
        {
            int tmp = arr[i];
            right_shift(arr, rb, i - 1);
            arr[rb++] = tmp;
            pivotIndex++;
        }

    
    // [0, rb)            < pivot
    // [rb, pivotIndex]   = pivot (already sorted)
    // (pivotIndex, n)    > pivot
    nd_quick_sort(arr, rb);
    nd_quick_sort(arr + pivotIndex + 1, n - pivotIndex - 1);
}

int main()
{
    srand(time(NULL));

    int n;
    std:: cout << "enter array length: ";
    std::cin >> n;

    int* arr = create_array(n, true);

    std::cout << "array:  ";
    print_array(arr, n);

    nd_quick_sort(arr, n);
    std::cout << "sorted: ";
    print_array(arr, n);

    delete[] arr;
    return 0;
}