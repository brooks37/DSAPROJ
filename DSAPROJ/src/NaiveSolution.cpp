#include <vector>
#include "NaiveSolution.hpp"
using namespace std;
int NaiveSolution::findWater(const std::vector<int>& vec) const{
    int size = vec.size();
    if(size<3){
        return 0;
    }
    int totalWater = 0;
    
    for(int i = 0;i<size-1;i++){
        int leftMax = 0;
        int rightMax = 0;

        //left bar
        for(int j=0;j <= i;j++){
            leftMax = max(leftMax,vec[j]);
        }
        //right bar
        for(int k=i;k <= size-1;k++){
            rightMax = max(rightMax,vec[k]);
        }
        //calculate water at i
        int waterAtIndex = min(leftMax,rightMax) - vec[i];
        //sum water
        if(waterAtIndex > 0){
            totalWater += waterAtIndex;
        }
    }
    return totalWater;
}