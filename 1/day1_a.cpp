#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>
using namespace std;

int main() {
  ifstream in_file("input.txt");
  string line;
  vector<int> list1;
  vector<int> list2;

  while (getline(in_file, line)) {
    istringstream stream(line);
    string list1_val;
    string list2_val;
    stream >> list1_val;
    stream >> list2_val;
    list1.push_back(stoi(list1_val));
    list2.push_back(stoi(list2_val));
  }

  int difference = 0;
  sort(list1.begin(), list1.end(), greater<int>());
  sort(list2.begin(), list2.end(), greater<int>());
  for (size_t i = 0; i < list1.size(); ++i) {
    difference += abs(list1[i] - list2[i]);
  }

  cout << difference << "\n";
}
