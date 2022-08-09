#include <iostream>
#include "../common_methods/arrays_methods.h"

void merge_sort(int* arr, int l, int r)
{
    if (l >= r - 1) return;

    // split
    int mid = (l + r) / 2;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid, r);

    // merge
    int* tmp = new int[r - l];
    int lp = l, rp = mid, i = 0;
    
    while (lp < mid && rp < r)
        tmp[i++] = arr[lp] <= arr[rp] ? arr[lp++] : arr[rp++];
    
    while (lp < mid) tmp[i++] = arr[lp++];
    while (rp < r  ) tmp[i++] = arr[rp++];
    
    for (size_t j = 0; j < r - l; j++)
        arr[l + j] = tmp[j];
    
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

    merge_sort(arr, 0, n);
    std::cout << "sorted: ";
    print_array(arr, n);

    delete[] arr;
    return 0;
}