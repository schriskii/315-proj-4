#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
#include "MinimumOverlap.hpp"

bool print = false;
bool validArguments(int argc, char *argv[]);
void createCover(char *arg, std::vector<int> &cover);
void printCover(std::vector<int> &cover);

int main(int argc, char *argv[]) {
	std::vector<int> vec;
	unsigned int count=0;
	clock_t start, end;
	double time, total=0;
	std::vector<float> timings;

	if (!validArguments(argc, argv)) {
		return 1;
	}

	printf("Arguments were validated, calling constructor...\n");
	// Now we will time the preprocessor/constructor phase
	start = clock();
	MinimumOverlap minoverlap(argv[1]);
	end = clock();
	printf("%s took %4.4f seconds preprocessing\n", argv[1],
			(end - start) / (float)CLOCKS_PER_SEC);

	// Now run test for each cover passed int
	std::vector<int> cover;
	for (int i = 3; i < argc; i++) {

		createCover(argv[i], cover);

		printf("Testing cover:");
		printCover(cover);
		fflush(stdout);

		start = clock();
		count = minoverlap.findMinimumOverlap(cover, print);
		end = clock();
		time = (end - start) / (float)CLOCKS_PER_SEC;
		total += time;

		printf("  found a minimum of %d elements in %4.4f seconds\n\n", count, time);
		timings.push_back(time);
	}

	std::sort(timings.begin(), timings.end());

	FILE *file = fopen("data/timings.dat", "w");
	if (file) {
		for (int i = 0; i < timings.size(); i++) {
			fprintf(file, "%d %f\n", i, timings[i]);
		}
		fclose(file);
		printf("Timing information written to 'data/timings.dat'\n");
	} else {
		printf("Unable to open 'data/timings.dat' for writting. No timing information written.\n");
	}

	return 0;
}

bool validArguments(int argc, char *argv[]) {

	// Check number of arguments
	if (argc <4) {
		printf("Error, not enough parameters.  Usage:\n");
		printf("%s <set file> <yes/no> <list of phrases>\n", argv[0]);
		return false;
	}

	// Check the yes/no argument
	if (strcmp(argv[2],"yes") == 0) {
		print=true;
	} else if (strcmp(argv[2],"no") == 0) {
		print=false;
	} else {
	  printf("error in 2nd parameter which must be yes or no, got %s\n",argv[2]);
	  return false;
	}

	// Ensure the set file can be opened.
	std::ifstream inTest;
	inTest.open(argv[1]);
	if (!inTest.is_open()) {
		printf ("File %s could not be opened\n", argv[1]);
		return false;
	}
	inTest.close();

	return true;
}

void createCover(char *arg, std::vector<int> &cover) {
	char *token;
	int len = 1;
	const char *delim = " ";

	// First get the number of spaces, which is used to compute the length.
	for (int i = 0; i < strlen(arg); i++) {
		if (arg[i] == ' ') {
			len++;
		}
	}

	// resize the vector
	cover.resize(len);

	// now grab each number and place into the vector
	cover[0] = atoi(strtok(arg, delim));
	for (int i = 1; i < cover.size(); i++) {
		cover[i] = atoi(strtok(NULL, delim));
	}
}

void printCover(std::vector<int> &cover) {
	printf("{ ");
	for (int i = 0; i < cover.size(); i++) {
		printf("%d ", cover[i]);
	}
	printf("}");
}
