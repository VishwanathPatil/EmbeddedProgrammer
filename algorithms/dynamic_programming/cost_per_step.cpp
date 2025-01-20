
class Solution {
public:
  /**
   * 1. Can start at step 0 or step 1
   * 2. Can climb at one step or 2 steps at any time
   * 3. Looking for cost minimum is goal
   **/
  int costForStep(vector<int> &cost, int i) {

    auto itPrev = costMapStep.find(i - 1);
    auto itPrevPrev = costMapStep.find(i - 2);

    if (itPrev == costMapStep.end()) {
      costMapStep.insert(std::make_pair(i - 1, costForStep(cost, i - 1)));
    }

    if (itPrevPrev == costMapStep.end()) {
      costMapStep.insert(std::make_pair(i - 2, costForStep(cost, i - 2)));
    }

    return min(costMapStep.find(i - 1)->second + cost[i],
               costMapStep.find(i - 2)->second + cost[i]);
  }

  unordered_map<int, int> costMapStep;

  int minCostClimbingStairs(vector<int> &cost) {
    // need to climb all steps to reach to top
    // index and cost
    costMapStep.insert(std::make_pair(0, cost[0]));
    costMapStep.insert(std::make_pair(1, cost[1]));
    costMapStep.insert(
        std::make_pair(cost.size() - 1, costForStep(cost, cost.size() - 1)));
    return min(costMapStep.find(cost.size() - 1)->second,
               costMapStep.find(cost.size() - 2)->second);
  }
};
