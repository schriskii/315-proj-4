#include "MinimumOverlap.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>

MinimumOverlap::MinimumOverlap(const std::string &setFile) {
	std::string line;
	std::ifstream file(setFile);
	int next_num;
	
	if (file.is_open()){
		
		while(getline(file, line)){
			
			std::vector<int> new_row;
			
			std::istringstream iss(line);
			
			while (iss >> next_num){
				new_row.push_back(next_num);
			}
			
			file_contents.push_back(new_row);
		}
	}
}

unsigned int MinimumOverlap::FMO_rec(
		std::vector<bool> used,
		std::vector<int> sofar,
		std::vector<int> input,	// ultimate goal
		const bool &print
		) const {
	
	unsigned int min = -1;
	
	for (int j = 0; j < file_contents.size() - 1; j++) if (!used[j]){
		std::vector<int> result;
		set_difference(input.begin(), input.end(), file_contents[j].begin(), file_contents[j].end(), back_inserter(result));
		
		if (result.empty()){
			int combined = sofar.size() + file_contents[j].size();
			if (combined < min){
				min = combined;
			}
		}
		else{
			for (auto h : file_contents[j]){
				sofar.push_back(h);
			}
			used[j] = true;
			
			int cmin = FMO_rec(used, sofar, result, j+1);
			
			if (cmin < min){
				min = cmin;
			}
			
			for (auto h : file_contents[j]){
				sofar.pop_back();
			}
			used[j] = false;
		}

	}
	
	return min;
}



unsigned int MinimumOverlap::findMinimumOverlap(const std::vector<int> &cover, const bool &print) const {
	
	std::vector<int> sofar;
	std::vector<bool> used(file_contents.size(), false);
	
	return FMO_rec(used, sofar, cover, print);
}




