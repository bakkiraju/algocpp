#include<iostream>
#include<array>

// cue : last i elements are already sorted
// Heavier ones go down, lighter ones "bubble" up in the 
// internal for loop  
int main()
{
   std::array<int,6> arr{11,44,55,22,66,33};
   
   for (int i=0; i < arr.size()-1; i++)
   {
       bool swapped = false;
 
       for (int j=0; j < arr.size()-i-1; j++)
       {
          if (arr[j] > arr[j+1])
          {
             std::swap(arr[j],arr[j+1]);  
             swapped = true;
          } 
       }   
       
       if (swapped == false) break; 
    }

 
    for(auto e : arr)
    {
       std::cout << e << " ";
    }  
 
    std::cout << std::endl;

    return 0;
}
