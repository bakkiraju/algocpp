#include<iostream>
#include<array>

// cue : "insert" at right place
// No swaps involved, create place and insert

int main()
{
    std::array<int,6> arr {44,22,11,66,33,55};

    for (int i=1; i < arr.size(); i++)
    {
        int key = arr[i];
        int j = i - 1;

        // crate place
        while ( j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j]; //elements march ahead to create space
            j--;
        }

        arr[j+1] = key;
    }

    for (auto &elem : arr)
    {
         std::cout << elem << " ";
    }

    std::cout << std::endl;

    return 0;
}