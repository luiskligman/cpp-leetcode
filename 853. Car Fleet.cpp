#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int, int>> cars;

        for (int i = 0; i < position.size(); i++) {
            cars.push_back({position[i], speed[i]});
        }

        sort(cars.begin(), cars.end());

        vector<double> fleets; // arrival time of each fleet's lead car
        for (int i = cars.size() - 1; i >= 0; i--) {
            double time = (double)(target - cars[i].first) / cars[i].second;
            if (fleets.empty() || time > fleets.back()) {
                fleets.push_back(time);
            }
        }

        return fleets.size();
    }
};