#include<iostream>
#include<array>

// cue: "select" min and put it at the front

int main()
{
    std::array<int, 6> arr {11,33,55,22,66,44};

    for (int i=0; i < arr.size(); i++)
    {
         int min_idx = i;
         for (int j=i+1; j < arr.size(); j++)
         {
             if (arr[min_idx] > arr[j])
             {
                 min_idx = j;
             }
         }

         std::swap(arr[i], arr[min_idx]);
    }

    for (auto &elem : arr)
    {
         std::cout << elem << " ";
    }

    std::cout << std::endl;

    return 0;
}