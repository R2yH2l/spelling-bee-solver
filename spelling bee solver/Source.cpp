#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <limits>
#include <unordered_map>

int main() {
	// check if wordlist exists
	std::filesystem::path path("data\\wordlist.csv");
	if (!std::filesystem::exists(path.parent_path())) {
		std::cout << "[+] adding missing directory \"data\\\"...";
		std::filesystem::create_directory(path.parent_path()); // create path if not found
		std::cout << " done!\n\n";
	}

	// validate wordlist.csv
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

	// open file to read
	std::fstream file(path, std::ios_base::in);

	// store file in string
	std::string line{};
	std::string string_file{};
	while (std::getline(file, line)) {
		string_file.append(line.append(","));
	}
	file.close();

	// parse file and separate words by letter
	std::unordered_map<int, std::string> words{};
	std::stringstream ss(string_file);
	std::string cell{};
	int count{};
	while (std::getline(ss, cell, ',')) {
		words[(int)cell[0]] += cell.append(",");
		count++;
	}
	std::cout << count << " words in " << path.filename() << ".\n\n";

	// main loop
	while (true) {
		// count of words found
		count = 0;

		// min and max size of words
		int min{}, max{};

		// user input
		std::string ltrs;
		std::cout << "Enter letters starting with the requried letter.\ninput: ";
		std::getline(std::cin, ltrs);

		// find words which can be spelled with only the letters from ltrs in them
		std::unordered_map<size_t, std::string> sort_words{};
		for (std::size_t t{}; t < ltrs.length(); t++) {
			ss.str(words[(int)ltrs[t]]);
			ss.clear();
			while (std::getline(ss, cell, ',')) {
				// make sure word is four letters or longer
				if (cell.length() >= 4) {
					bool mis = false; // missing a letter from ltrs
					bool req = false; // has required letter
					for (size_t c1{}; c1 < cell.length(); c1++) {
						for (size_t c2{}; c2 < ltrs.length(); c2++) {
							if (cell[c1] == ltrs[c2]) {
								mis = false;
								c2 == 0 ? req = true : req = req;
								break;
							}
							else mis = true;
						}
						if (mis) break;
					}
					// print word if it meets the criteria
					if ((!mis) && req) {
						sort_words[cell.length()] += cell.append(",");
						min == 0 ? min = cell.length() : min > cell.length() ? min = cell.length() : min = min;
						max < cell.length() ? max = cell.length() : max = max;
						count++;
					}
				}
			}
		}
		// print words by lenght
		for (size_t t = min; t < max; t++) {
			ss.str(sort_words[t]);
			ss.clear();
			while (getline(ss, cell, ',')) std::cout << cell << std::endl;
		}

		// print number of words found
		std::cout << count << std::endl << std::endl;
	}
	return 0;
}