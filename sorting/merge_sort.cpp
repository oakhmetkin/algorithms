#include <iostream>
#include "../common_methods/arrays_methods.h"

void merge_sort(int* arr, int n)
{
    if (n <= 1) return;

    // split
    int mid = n / 2;
    merge_sort(arr, mid);
    merge_sort(arr + mid, n - mid);

    // merge
    int* tmp = new int[n];
    int lp = 0, rp = mid, i = 0;
    
    while (lp < mid && rp < n)
        tmp[i++] = arr[lp] <= arr[rp] ? arr[lp++] : arr[rp++];
    
    while (lp < mid) tmp[i++] = arr[lp++];
    while (rp < n  ) tmp[i++] = arr[rp++];
    
    for (size_t j = 0; j < n; j++)
        arr[j] = tmp[j];
    
    delete[] tmp;
}

int main()
{
    int n;
    std:: cout << "enter array length: ";
    std::cin >> n;

    int* arr = create_array(n, true);

    std::cout << "array:  ";
    print_array(arr, n);

    merge_sort(arr, n);
    std::cout << "sorted: ";
    print_array(arr, n);

    delete[] arr;
    return 0;
}