#include <vector>
#include "DynamicSolution.hpp"
using namespace std;
int DynamicSolution::findWater(const std::vector<int>& vec) const{

int size = vec.size();

if(size<3){
    return 0;
}
vector<int> leftMax(size);
vector<int> rightMax(size);
//fill left max
leftMax[0] = vec[0];
for(int i=1;i<=size-1;i++){
leftMax[i] = max(leftMax[i-1],vec[i]);
}
//fill righMax
rightMax[size-1] = vec[size-1];
for(int i = size-2; i >= 0;i--){
rightMax[i] = max(rightMax[i+1],vec[i]);
}
//calculate total water
int totalWater = 0;
for(int i=0;i<size-1;i++){
    int trapped = min(leftMax[i], rightMax[i]) -vec[i];
    if(trapped > 0){
        totalWater += trapped;
    }
}
return totalWater;
}