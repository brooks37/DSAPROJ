#include "GreedySolution.hpp"
#include <vector>
int GreedySolution::findWater(const std::vector<int>& vec) const{
      
   int size = vec.size();
   if(size < 3){
    return 0;
   }

   //Pointer Decleration
    int left = 0;
    int rightMax =0;
    int leftMax = 0;
    int totalWater = 0;
    int right = size-1;

   //Main Loop
   while(left < right){

    if(vec[left] < vec[right]){

        if(vec[left] >= leftMax){
            leftMax = vec[left];
        }
        else{
            totalWater = totalWater + (leftMax - vec[left]);
        }
        left++;
    }else{
        if(vec[right]>= rightMax){
            rightMax = vec[right];
        }else{
            totalWater = totalWater +(rightMax - vec[right]);
        }
        right--;
    }
    
   }
   return totalWater;
}