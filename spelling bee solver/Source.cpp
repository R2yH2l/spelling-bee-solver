#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int main() {
	// open file to read
	constexpr const char* filename = "data\\wordlist.csv";
	std::fstream file(filename, std::ios_base::in);
	// read file
	std::string line{};
	std::string strfile{};
	while (std::getline(file, line)) {
		strfile.append(line.append(","));
	}
	file.close();
	// parse file
	std::stringstream ss(strfile);
	std::string cell{};
	constexpr const char* ltrs = "ilvteum";
	int count{};
	while (std::getline(ss, cell, ',')) {
		// check word length
		if (cell.length() >= 4) {
			bool req = false;
			// check if word starts with one of the letters
			for (std::size_t c = 0; c < 7; c++) {
				if (cell[0] == ltrs[c]) req = true;
			}
			// check for requried letter
			if (req) {
				for (std::size_t c{}; c < cell.length(); c++) {
					if (cell[c] == ltrs[0]) {
						req = true;
						break;
					}
					else req = false;
				}
			}
			// check word spelling
			if (req) {
				bool mis = false;
				// for each letter check that its from the list
				for (std::size_t c{}; c < cell.length(); c++) {
					for (std::size_t t = 0; t < 7; t++) {
						if (cell[c] == ltrs[t]) {
							mis = false;
							break;
						}
						else mis = true;
					}
					if (mis) {
						break;
					}
				}
				// print word
				if (mis == false) {
					std::cout << cell << std::endl;
					count++;
				}
			}
		}
	}
	// word count
	std::cout << count << std::endl;
	return 0;
}