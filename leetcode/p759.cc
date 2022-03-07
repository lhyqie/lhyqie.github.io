#include "common.h"

/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
      vector<Interval> free_intervals;
        
      vector<Interval> merged = mergeIntervals(schedule);
      if (merged.size() <= 1) return {}; // no free time that excludes Inf
      for (int j = 1; j < merged.size(); ++j) {
        free_intervals.push_back(Interval(merged[j-1].end, merged[j].start));
      }
      return free_intervals;
    }
  
    vector<Interval> mergeIntervals(vector<vector<Interval>>& schedule) {
      if (schedule.empty()) return {};
      
      vector<Interval> flatten;
      for(const auto& row : schedule) {
        for (const auto& iv : row) {
          flatten.push_back(iv);
        }
      }
      
      // sort by start time, then by end time
      std::sort(flatten.begin(), flatten.end(), [](const auto& iv1, const auto& iv2) -> bool{
        if (iv1.start == iv2.start) return iv1.end < iv2.end;
        return iv1.start < iv2.start;
      });
      
      vector<Interval> merged;
      Interval iv = flatten[0];
      int j = 0;
      while (j < flatten.size()) {
        if (iv.end < flatten[j].start) {
          merged.push_back(iv);
          iv = flatten[j];
        } else {
          iv.end = max(iv.end, flatten[j].end);
        }
        j++;
      }
      merged.push_back(iv);
      // corn case to cover last interval
      // if (iv.end < schedule[schedule.size() - 1].start) {
      //  merged.push_back(schedule[schedule.size() - 1]);
      //}
      return merged;
    }
};

/*
#include <algorithm>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Interval
{
public:
	int start;
	int end;

	Interval() {}

	Interval(int _start, int _end)
	{
		start = _start;
		end = _end;
	}
};

vector<Interval> mergeIntervals(vector<vector < Interval>> &schedule)
{
	if (schedule.empty()) return {};

	vector<Interval> flatten;
	for (const auto &row: schedule)
	{
		for (const auto &iv: row)
		{
			flatten.push_back(iv);
		}
	}

	// sort by start time, then by end time
	std::sort(flatten.begin(), flatten.end(), [](const auto &iv1, const auto &iv2)->bool
	{
		if (iv1.start == iv2.start) return iv1.end < iv2.end;
		return iv1.start < iv2.start;
	});

	std::cout << "---\n";  
	for (const Interval& iv : flatten) {
		std::cout << iv.start << " " << iv.end << std::endl;
	}
	
	vector<Interval> merged;
	Interval iv = flatten[0];
	int j = 0;
	while (j < flatten.size())
	{
		if (iv.end < flatten[j].start)
		{
			merged.push_back(iv);
			iv = flatten[j];
		}
		else
		{
			iv.end = max(iv.end, flatten[j].end);
		}
		j++;
	}
	merged.push_back(iv);
	// corn case to cover last interval
	// if (iv.end < schedule[schedule.size() - 1].start) {
	//  merged.push_back(schedule[schedule.size() - 1]);
	//}
	return merged;
}

int main(void)
{
	vector<vector<Interval>> schedule;
	{
		vector<Interval> vi;
		vi.push_back(Interval(7, 24));
		vi.push_back(Interval(29,33));
		vi.push_back(Interval(45,57));
		vi.push_back(Interval(66,69));
		vi.push_back(Interval(94,99));
		schedule.push_back(vi);
	}
	{
		vector<Interval> vi;
		vi.push_back(Interval(6, 24));
		vi.push_back(Interval(43,49));
		vi.push_back(Interval(56,59));
		vi.push_back(Interval(61,75));
		vi.push_back(Interval(80,81));
		schedule.push_back(vi);
	}
	{
		vector<Interval> vi;
		vi.push_back(Interval(5,16));
		vi.push_back(Interval(18,26));
		vi.push_back(Interval(33,36));
		vi.push_back(Interval(39,57));
		vi.push_back(Interval(65,74));
		schedule.push_back(vi);
	}
	{
		vector<Interval> vi;
		vi.push_back(Interval(9,16));
		vi.push_back(Interval(27,35));
		vi.push_back(Interval(40,55));
		vi.push_back(Interval(68,71));
		vi.push_back(Interval(78,81));
		schedule.push_back(vi);
	}
	{
		vector<Interval> vi;
		vi.push_back(Interval(0,25));
		vi.push_back(Interval(29,31));
		vi.push_back(Interval(40,47));
		vi.push_back(Interval(57,87));
		vi.push_back(Interval(91,94));
		schedule.push_back(vi);
	}
	
	
	auto ivs = mergeIntervals(schedule);
	std::cout << "---\n";  
	for (const Interval& iv : ivs) {
		std::cout << iv.start << " " << iv.end << std::endl;
	}
	return 0;
}
*/