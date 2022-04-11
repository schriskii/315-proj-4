/*
Student Name: Chris Koenig
Program Name: Find Minimum Overlap
Creation Date: Spring 2021 (date unknown)
Last Modified Date: Spring 2021 (date unknown)
CSCI Course: CSCI 315
Grade Received: (unknown)
Design Comments: (n/a)
*/

#ifndef MinimumOverlap_HPP
#define MinimumOverlap_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class MinimumOverlap {
	private:
		std::vector<std::vector<int>> file_contents;
		
	public:

		// Passes in a string pointing to the set/group file.
		// Make sure you store all the sets/groups!
		MinimumOverlap(const std::string &setFile);


/*
		unsigned int FMO_rec(
				const std::vector<int> &cover,	// ultimate goal
				std::vector<int> &hunted,		// numbers not already found
				std::vector<bool> &used,		// sets already used
				const bool &print
				) const;
		
		*/

		unsigned int FMO_rec(
				std::vector<bool> used,
				std::vector<int> sofar,
				std::vector<int> input,	// ultimate goal
				const bool &print
				) const;
		
		/*
		
		unsigned int FMO_rec(
				std::vector<int> &found,
				std::vector<bool> &used,
				const std::vector<int> &input,	// ultimate goal
				const bool &print
				) const;
		
		*/
		
		// Returns the minimum number of overlaps possible given a cover.
		// If print is true, it prints the set(s).
		unsigned int findMinimumOverlap(const std::vector<int> &cover, const bool &print) const;
};

#endif
