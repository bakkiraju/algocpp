#include<iostream>
#include<array>

// cue : Make a heap
template<std::size_t SIZE>
void heapify(std::array<int, SIZE> &arr, int n, int i)
{
   int largest = i;
   int l = 2*i + 1;
   int r = 2*i + 2;

   if (l < n && arr[l] > arr[largest])
   {
       largest = l;
   }

   if (r < n && arr[r] > arr[largest])
   {
       largest = r;
   }

   if (largest != i)
   {
       std::swap(arr[i], arr[largest]);
       heapify(arr, n, largest);
   }
}
template<std::size_t SIZE>
void heapSort(std::array<int, SIZE> &arr)
{
    int n = arr.size();

    // make a heap
    for (int i=n/2-1; i >=0; i--)
       heapify(arr, n, i);
    
    // heap sort
    for (int i = n-1; i > 0 ; i --)
    {   
        std::swap(arr[0], arr[i]);
        heapify(arr, i , 0);
    }

}
int main()
{
    std::array<int,6> arr{11,44,55,22,66,33};
   
    heapSort(arr);
 
    for(auto e : arr)
    {
       std::cout << e << " ";
    }  
 
    std::cout << std::endl;

    return 0;
}
