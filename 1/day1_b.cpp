#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>
#include <unordered_map>
using namespace std;

int main()
{
  ifstream in_file("input.txt");
  string line;
  vector<int> list1;
  vector<int> list2;
  unordered_map<int, int> list2_counts;

  while (getline(in_file, line))
  {
    istringstream stream(line);
    string list1_val;
    string list2_val;
    stream >> list1_val;
    stream >> list2_val;
    int list2_int = stoi(list2_val);
    list1.push_back(stoi(list1_val));
    list2.push_back(list2_int);

    if (list2_counts.find(list2_int) == list2_counts.end())
    {
      list2_counts.insert({list2_int, 1});
    }
    else
    {
      list2_counts[list2_int] += 1;
    }
  }

  // calculate similarity score
  long similarity_score = 0;
  for (const auto &x : list1)
  {
    if (list2_counts.find(x) != list2_counts.end())
    {
      similarity_score += (x * list2_counts[x]);
    }
  }

  cout << similarity_score << "\n";
}
