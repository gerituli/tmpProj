#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

int main()
{
   vector<int> nums;
   
   auto seed = chrono::system_clock::now().time_since_epoch().count();
   
   
   for(int i = 0; i<10;i++)
       nums.push_back(i);
       
    shuffle(nums.begin(),nums.end(),default_random_engine(seed));
    
    for(int i = 0; i<10;i++)
        cout<<nums[i]<<" ";
        
   return 0;
}