#pragma once
#include <vector>

 class Solution {
  public:
   /**
    * @brief Default constructor for the SeasonalBehaviour class.
    *
    * @details Initializes a SeasonalBehaviour object. This is typically called
    * by derived classes.
    */
   Solution();
 
   /**
    * @brief Virtual destructor for the SeasonalBehaviour class.
    *
    * @details Ensures proper cleanup of resources in derived classes.
    */
   virtual ~Solution();
 
   /**
    * @brief Executes a seasonal task for a bird.
    *
    * @param bird A pointer to the Bird object on which the task is performed.
    *
    * @details This pure virtual method must be implemented by derived classes
    * to define a specific seasonal behavior.
    */
   virtual int findWater(const std::vector<int>& vec) const = 0;
 };
 