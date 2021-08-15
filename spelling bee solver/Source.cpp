#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <limits>
#include <chrono>
#include <map>
#include <set>
#include <algorithm>

int main() {
	// check if wordlist exists
	std::filesystem::path path("data\\wordlist.csv");
	/*
	if (!std::filesystem::exists(path.parent_path())) {
		std::cout << "[+] adding missing directory \"\\data\"...";
		std::filesystem::create_directory(path.parent_path()); // create path if not found
		std::cout << " done!\n\n";
	}
	*/
	// validate wordlist.csv
	/*
	while (true) {
		// check if file exists
		if (!std::filesystem::exists(path)) {
			std::cout << "[!] " << path.filename() << " is missing please download the file from:\n"
				<< "https://github.com/R2yH2l/spelling-bee-solver/tree/master/spelling%20bee%20solver/data\n"
				<< "then place " << path.filename() << " into the directory:\n";
		}
		// check if file is empty
		else if (std::filesystem::file_size(path) == 0) {
			std::cout << "[!] " << path.filename() << " is empty please download the file from:\n"
				<< "https://github.com/R2yH2l/spelling-bee-solver/tree/master/spelling%20bee%20solver/data\n"
				<< "then replace the existing " << path.filename() << " in the directory:\n";
		}
		// check if file is missing data
		// todo: allow for custom wordlists and validate csv format
		else if (std::filesystem::file_size(std::filesystem::current_path() / path) != 1763167) {
			std::cout << "[!] " << path.filename() << " has invalid data please download the file from:\n"
				<< "https://github.com/R2yH2l/spelling-bee-solver/tree/master/spelling%20bee%20solver/data\n"
				<< "then replace the existing " << path.filename() << " in the directory:\n";
		}
		else break;
		std::cout << std::filesystem::current_path() / path.parent_path() << std::endl << "press enter when done...\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl;
	}
	*/
	// open and parse wordlist.csv
	std::fstream file(path, std::ios_base::in);
	std::string cell{};
	std::map<int, std::set<std::string>> word_list{};
	while (std::getline(file, cell, ',')) { word_list[(int)cell[0]].insert(cell); }
	file.close();

	// main loop
	while (true) {
		// min and max size of words
		// int min{}, max{};

		// user input
		std::cout << "Enter letters starting with the requried letter.\ninput: ";
		std::string letters{};
		std::getline(std::cin, letters);
		std::cout << std::endl;

		// find words which can be spelled with only the letters from letters in them
		std::set<std::string> matches{};
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		for (size_t ltr{}; ltr < letters.length(); ltr++) {
			// lambda func
			auto search_set = [letters, &matches](const std::string& str) {
				if (!(str.length() >= 4)) {
					bool missing = false, required = false;
					for (size_t chr1{}; chr1 < str.length(); chr1++) {
						for (size_t chr2{}; chr2 < letters.length(); chr2++) {
							if (str[chr1] == letters[chr2]) {
								missing = false;
								if (chr2 == 0 && (!required)) required = true;
								break;
							}
							else missing = true;
						}
						if (missing) break;
					}
					if ((!missing) && required) matches.insert(str);
				}
			};

			std::for_each(word_list[letters[ltr]].begin(), word_list[letters[ltr]].end(), search_set);
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		std::cout << "words found in " << time_span.count() << " secounds.\n\n";
	}

		// sort words by alpha order
		/*
		std::unordered_map<int, std::string> sort_words_ch{};
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		for (size_t t = min; t < max; t++) {
			ss.str(sort_words[t]);
			ss.clear();
			while (getline(ss, cell, ',')) sort_words_ch[(int)cell[0]] += cell.append(",");
		}
		*/
		// print words
	/*
		for (size_t t{}; t < ltrs.length(); t++) {
			ss.str(sort_words_ch[(int)ltrs[t]]);
			ss.clear();
			while (getline(ss, cell, ',')) std::cout << cell << std::endl;
		}
		*/
		// print number of words found and time it took to find them
		/*
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		std::cout << count << " words found in " << time_span.count() << " secounds.\n\n";
		*/
	return 0;
}