#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <cstdlib>
using namespace std;

int main()
{
  ifstream in_file("input.txt");
  string line;
  int valids = 0;
  int invalid_because_not_sorted = 0;
  int invalid_because_of_difference = 0;

  while (getline(in_file, line))
  {
    istringstream stream(line);
    string num;
    vector<int> nums;

    while (stream >> num)
    {
      nums.push_back(stoi(num));
    }

    vector<int> adjacent_differences(nums.size());

    adjacent_difference(nums.begin(), nums.end(), adjacent_differences.begin());

    // output adjacent differences
    for (const auto &diff : adjacent_differences)
    {
      cout << diff << " ";
    }
    cout << "\n";

    // make all differences positive
    transform(adjacent_differences.begin(), adjacent_differences.end(), adjacent_differences.begin(), [](int diff) {
      return abs(diff);
    });
  
    auto largest_difference = *max_element(adjacent_differences.begin() + 1, adjacent_differences.end());
    auto smallest_difference = *min_element(adjacent_differences.begin() + 1, adjacent_differences.end());
    if (abs(largest_difference) > 3 || smallest_difference == 0)
    {
      invalid_because_of_difference++;
      continue;
    }

    // check if nums is either descending or ascending order
    if (is_sorted(nums.begin(), nums.end()))
    {
      valids++;
    }
    else
    {
      reverse(nums.begin(), nums.end());
      if (is_sorted(nums.begin(), nums.end()))
      {
        valids++;
      }
      else
      {
        invalid_because_not_sorted++;
      }
    }
  }

  cout << "valids: " << valids << "\n";
  cout << "invalid_because_not_sorted: " << invalid_because_not_sorted << "\n";
  cout << "invalid_because_of_difference: " << invalid_because_of_difference << "\n";
}
