#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <set>
using namespace std;

long part_a(ifstream &in_file)
{
  string line;
  long sum = 0;
  regex multiplication_pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");

  while (getline(in_file, line))
  {
    for (auto it = sregex_iterator(line.begin(), line.end(), multiplication_pattern); it != sregex_iterator(); it++)
    {
      smatch match = *it;
      auto first_num = stoi(match.str(1));
      auto second_num = stoi(match.str(2));
      auto result = first_num * second_num;

      sum += result;
    }
  }

  return sum;
}

bool in_disabled_range(int index, set<pair<int, int>> &disabled_ranges)
{
  for (const auto &range : disabled_ranges)
  {
    if (index >= range.first && index <= range.second)
    {
      return true;
    }
  }

  return false;
}

long part_b(ifstream &in_file)
{
  string line;
  long sum = 0;
  regex multiplication_pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");

  string whole_input = "";

  while (getline(in_file, line))
  {
    whole_input += line;
  }

  set<pair<int, int>> enable_disable_pairs;

  smatch multiplication_start, multiplication_end;

  regex disabled_pattern("don't\\(\\)(?:(?!don't\\(\\)).)*?do\\(\\)");

  for (auto it = sregex_iterator(whole_input.begin(), whole_input.end(), disabled_pattern); it != sregex_iterator(); it++)
  {
    smatch match = *it;
    auto start = match.position();
    auto end = start + match.length();
    enable_disable_pairs.insert({start, end});
  }


  for (auto it = sregex_iterator(whole_input.begin(), whole_input.end(), multiplication_pattern); it != sregex_iterator(); it++)
  {
    smatch match = *it;
    auto first_num = stoi(match.str(1));
    auto second_num = stoi(match.str(2));

    if (in_disabled_range(match.position(), enable_disable_pairs))
    {
      continue;
    }

    sum += first_num * second_num;
  }

  return sum;
}

int main(int argc, char *argv[])
{
  auto mode = string(argv[1]);
  auto filename = string(argv[2]);
  ifstream in_file(filename);
  string line;

  if (mode == "-a")
  {
    cout << part_a(in_file) << "\n";
    return 0;
  }
  else if (mode == "-b")
  {
    cout << part_b(in_file) << "\n";
    return 0;
  }
  else
  {
    cout << "Invalid mode\n";
    return 1;
  }
}