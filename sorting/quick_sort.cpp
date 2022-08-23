#include <iostream>
#include "../common_methods/arrays_methods.h"


#pragma region NON_DET_QS
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
#pragma endregion


#pragma region DET_QS
// min in arr
int* qsmin(int* arr, int n)
{
    int* min_ind = arr;

    for (size_t i = 0; i < n; i++)
        if (arr[i] < *min_ind)
            min_ind = arr + i;    

    return min_ind;
}

// max in arr
int* qsmax(int* arr, int n)
{
    int* max_ind = arr;

    for (size_t i = 0; i < n; i++)
        if (arr[i] > *max_ind)
            max_ind = arr + i;    

    return max_ind;
}

// returns index of median of subarray (length <= 5)
int get_median_index(int* arr, int s, int n)
{
    int size = std::min(5, n - s);

    if (size <= 2) return s;


    int* subarray = new int[size];
    for (size_t i = 0; i < size; i++)
        subarray[i] = arr[s + i];

    // move max and min to the end
    while (size > 2)
    {
        std::swap(subarray[size - 1], *qsmin(subarray, size));
        std::swap(subarray[size - 1], *qsmax(subarray, size));
        size -= 2;
    }

    int ind;
    for (size_t i = 0; i < n - s; i++)
        if (arr[i] == subarray[0])
            ind = s + i;

    delete[] subarray;
    return ind;
}

// deterministic quick select (index, not value)
int det_quick_select_index(int* arr, int* indexes, int n, int k)
{
    int pivotIndex = n / 2;
    int pivot = arr[pivotIndex];

    for (size_t i = 0; i < pivotIndex; i++)
        if (arr[i] >= pivot)
        {
            int tmp = arr[i], tmpi = indexes[i];
            left_shift(arr, i + 1, pivotIndex);
            left_shift(indexes, i + 1, pivotIndex);
            arr[pivotIndex] = tmp;
            arr[pivotIndex--] = tmpi;
            i--;
        }
    
    int rb = pivotIndex; // rb - right border

    while (pivotIndex < n - 1 && arr[pivotIndex + 1] == pivot)
        pivotIndex++;
    
    for (size_t i = pivotIndex + 1; i < n; i++)
        if (arr[i] <= pivot)
        {
            int tmp = arr[i], tmpi = indexes[i];
            right_shift(arr, rb, i - 1);
            right_shift(indexes, rb, i - 1);
            arr[rb] = tmp;
            indexes[rb++] = tmpi;
            pivotIndex++;
        }
    
    if (rb <= k && k <= pivotIndex) return indexes[k];

    if (k < rb) return det_quick_select_index(arr, indexes, rb, k);
    if (k > pivotIndex)
        return det_quick_select_index(
            arr + pivotIndex + 1,
            indexes + pivotIndex + 1,
            n - pivotIndex - 1,
            k - pivotIndex - 1);
    
    return 0;
}

// deterministic quick sort
void det_quick_sort(int* arr, int n)
{
    if (n <= 1) return;

    int rooms_count = n / 5 + (n % 5 > 0); // count of rooms for numbers
    int* median_indexes = new int[rooms_count]; // indexes of rooms medians
    int* median_values = new int[rooms_count]; // rooms medians

    for (size_t i = 0; i < rooms_count; i++)
    {
        median_indexes[i] = get_median_index(arr, i * 5, n);
        median_values[i] = arr[median_indexes[i]];
    }
    
    // mom: median of medians
    int mom_index = det_quick_select_index(median_values, median_indexes, rooms_count, rooms_count / 2);
    delete[] median_indexes, median_values;

    int pivotIndex = mom_index;
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
    det_quick_sort(arr, rb);
    det_quick_sort(arr + pivotIndex + 1, n - pivotIndex - 1);
}
#pragma endregion


int main()
{
    srand(time(NULL));

    int n;
    std:: cout << "enter array length: ";
    std::cin >> n;

    int* arr = create_array(n, true);
    int* arr2 = copy_array(arr, n);

    std::cout << "array:  ";
    print_array(arr, n);

    nd_quick_sort(arr, n);
    std::cout << "sorted: ";
    print_array(arr, n);

    det_quick_sort(arr2, n);
    std::cout << "sorted: ";
    print_array(arr2, n);

    delete[] arr;
    delete[] arr2;
    return 0;
}