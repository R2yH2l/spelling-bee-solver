#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <map>
#include <set>

int main() {
	// path to word_list.csv
	std::filesystem::path path("data\\word_list.csv");
	constexpr std::uintmax_t file_size = 1763167; // know valid file size

	// validate word_list.csv
	while (true) {
		if (!std::filesystem::exists(path)) {
			// create data dir if missing
			if (!std::filesystem::exists(path.relative_path())) std::filesystem::create_directory(path.parent_path());
			std::cout << "[!] " << path.string() << " is missing please download it from:\nhttps://github.com/R2yH2l/spelling-bee-solver/tree/master/spelling%20bee%20solver/data.\n\n";
		}
		else if (std::filesystem::is_empty(path)) {
			std::cout << "[!] " << path.string() << " is empty please redownload it from:\nhttps://github.com/R2yH2l/spelling-bee-solver/tree/master/spelling%20bee%20solver/data.\n\n";
		}
		else if (std::filesystem::file_size(path) != file_size) {
			std::cout << "[-] " << path.string() << " has been alterded and the program might not work as intended.\n\n";
			break;
		}
		else break;

		// user input
		std::cout << "Press enter when done.";
		std::string temp{};
		std::getline(std::cin, temp);
		std::cout << std::endl;
	}

	// open and parse word_list.csv
	std::fstream file(path, std::ios_base::in);
	std::map<int, std::set<std::string>> word_list{};
	std::string cell{};
	while (std::getline(file, cell, ',')) { word_list[(int)cell[0]].insert(cell); }
	file.close();

	// main loop
	while (true) {
		// user input
		std::cout << "Enter seven letters starting with the requried letter.\ninput: ";
		std::string letters{};
		std::getline(std::cin, letters);
		std::cout << std::endl;

		if (letters.length() == 7) {
			// loop through letters in letters
			std::map<int, std::set<std::string>> match_list{};

			// get first time point
			std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

			// iterate through sets by letter
			std::for_each(letters.begin(), letters.end(), [letters, &word_list, &match_list](const char ltr) {
				// test if word is valid
				std::for_each(word_list[ltr].begin(), word_list[ltr].end(), [letters, ltr, &match_list](const std::string& str) {
					if (str.length() >= 4 &&
						str.find_first_not_of(letters.c_str()) == std::string::npos &&
						str.find_first_of(letters[0]) != std::string::npos) {
						match_list[ltr].insert(str);
					}
					}
				);
				}
			);

			// time to find words in secounds
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

			// print words in match_list
			size_t word_count{};
			std::for_each(letters.begin(), letters.end(), [letters, &word_list, &word_count, &match_list](const char ltr) {
				std::for_each(match_list[ltr].begin(), match_list[ltr].end(), [](const std::string& str) { std::cout << str << std::endl; });
				word_count += match_list[ltr].size();
				});

			// print word_count and time_span
			std::cout << std::endl << word_count << " words found in " << time_span.count() << " secounds.\n\n";
		}
		else std::cout << "[-] you've entered " << (letters.length() < 7 ? "to few " : "to many ") << "letters seven are needed.\n\n";
	}
	return 0;
}