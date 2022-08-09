#include <iostream>
#include "arrays_methods.h"

using namespace std;

// creates array of length n, fill by random values [min, max) if fill_rnd_vals == true
int* create_array(int n, bool fill_rnd_vals /*= false*/, int min /*= 0*/, int max /*= 10*/)
{
    int* arr = new int[n];

    if (fill_rnd_vals)
    {
        srand(time(NULL));

        for (size_t i = 0; i < n; i++)
            arr[i] = rand() % (max - min) + min;
    }
    
    return arr;
}

// printes array to console
void print_array(int* arr, int n)
{
    for (size_t i = 0; i < n; i++)
        cout << arr[i] << " ";
    
    cout << endl;  
}
