#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <map>
#include <set>

int main() {
	// path to wordlist.csv
	std::filesystem::path path("data\\wordlist.csv");

	// open and parse wordlist.csv
	std::fstream file(path, std::ios_base::in);
	std::map<int, std::set<std::string>> word_list{};
	std::string cell{};
	while (std::getline(file, cell, ',')) { word_list[(int)cell[0]].insert(cell); }
	file.close();

	// main loop
	while (true) {
		// user input
		std::cout << "Enter letters starting with the requried letter.\ninput: ";
		std::string letters{};
		std::getline(std::cin, letters);
		std::cout << std::endl;

		// loop through letters in letters
		std::set<std::string> match_list{};
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		for (size_t ltr{}; ltr < letters.length(); ltr++) {
			// test if word is valid
			auto search_set = [letters, &match_list](const std::string& str) {
				if (str.length() >= 4 &&
					str.find_first_not_of(letters.c_str()) == std::string::npos &&
					str.find_first_of(letters[0]) != std::string::npos) {
					match_list.insert(str);
				}
			};

			// iterate through sets by letter
			std::for_each(word_list[letters[ltr]].begin(), word_list[letters[ltr]].end(), search_set);
		}
		// time taken to find words in secounds
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		// print words in match_list
		std::for_each(match_list.begin(), match_list.end(), [](const std::string& str) { std::cout << str << std::endl; });
		std::cout << match_list.size() << " words found in " << time_span.count() << " secounds.\n\n";
	}
	return 0;
}