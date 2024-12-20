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

template <typename T>
vector<T> reversed(const vector<T> &v)
{
  vector<T> reversed_v(v);
  reverse(reversed_v.begin(), reversed_v.end());
  return reversed_v;
}

bool valid_level(const vector<int> &nums)
{
  vector<int> adjacent_differences(nums.size());
  adjacent_difference(nums.begin(), nums.end(), adjacent_differences.begin());

  // output adjacent differences
  for (const auto &diff : adjacent_differences)
  {
    cout << diff << " ";
  }
  cout << "\n";

  // make all differences positive
  transform(adjacent_differences.begin(), adjacent_differences.end(), adjacent_differences.begin(), [](int diff)
            { return abs(diff); });

  auto largest_difference = *max_element(adjacent_differences.begin() + 1, adjacent_differences.end());
  auto smallest_difference = *min_element(adjacent_differences.begin() + 1, adjacent_differences.end());
  if (abs(largest_difference) > 3 || smallest_difference == 0)
  {
    return false;
  }

  auto backwards = reversed(nums);
  return is_sorted(nums.begin(), nums.end()) || (is_sorted(backwards.begin(), backwards.end()));
}

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

    // check if a nums is valid or can be valid by removing one element
    if(valid_level(nums))
    {
      valids++;
      continue;
    }

    for (size_t i = 0; i < nums.size(); i++)
    {
      vector<int> nums_copy(nums);
      nums_copy.erase(nums_copy.begin() + i);
      if (valid_level(nums_copy))
      {
        valids++;
        break;
      }
    }
    
    
  }

  cout << "valids: " << valids << "\n";
  cout << "invalid_because_not_sorted: " << invalid_because_not_sorted << "\n";
  cout << "invalid_because_of_difference: " << invalid_because_of_difference << "\n";
}
