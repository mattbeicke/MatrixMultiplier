#include "Matrix.cpp"
#include <vector>
#include <stdexcept>
#include <limits>

void help() {
	std::cout << "\nEnter: " << std::endl;
	std::cout << " help     | to print this" << std::endl;
	std::cout << " new x    | to make a new matrix with # rows = # cols = x" << std::endl;
	std::cout << " new x y  | to make a new matrix with # rows = x and # cols = y" << std::endl;
	std::cout << " list     | list matrices" << std::endl;
	std::cout << " print x  | to print matrix with id x" << std::endl;
	std::cout << " edit x   | to edit an existing matrix based on id x" << std::endl;
	std::cout << " mult x y | to multiply matrix with id x by matrix with id y" << std::endl;
	std::cout << " quit     | to quit" << std::endl;
}

int main() {
	std::vector<Matrix> matrices;
	help();
	std::string s;
	while (true) {
		std::cout << "\n> ";
		std::getline(std::cin, s);
		std::cout << std::endl;
		if (s.compare("quit") == 0 || s.compare("q") == 0) {
			for (int i = 0;i < matrices.size();i++) {
				matrices[i].destroyMatrix();
			}
			return 0;
		} else if (s.compare("help") == 0) {
			help();
		} else if (s.compare("list") == 0) {
			if (matrices.size() == 0) {
				std::cout << "no matrices to print" << std::endl;
			}
			for (int i = 0;i < matrices.size();i++) {
				std::cout << "id = " << i << std::endl;
				matrices[i].printMatrix();
				std::cout << std::endl;
			}
		} else if (s.substr(0, 4).compare("new ") == 0) {
			int rows = std::stoi(s.substr(4, s.find_last_of(" ") - 4));
			int cols = std::stoi(s.substr(s.find_last_of(" ")));
			if (rows < 1 || cols < 1) {
				std::cout << "Invalid rows/cols";
			} else {
				Matrix m1(rows, cols);
				m1.fill();
				matrices.push_back(m1);
				std::cout << "New matrix stored at id = " << (matrices.size() - 1) << std::endl;
			}
		} else if (s.substr(0, 6).compare("print ") == 0) {
			int id = std::stoi(s.substr(6));
			if (!(id < 0 || id >= matrices.size())) {
				matrices[id].printMatrix();
			} else {
				std::cout << "Invalid id" << std::endl;
			}
		} else if (s.substr(0, 5).compare("edit ") == 0) {
			int id = std::stoi(s.substr(5));
			if (id<0 || id>matrices.size() - 1) {
				std::cout << "Invalid id" << std::endl;
			} else {
				int choice = -1;
				while (choice != 3) {
					std::cout << "\nEnter: " << std::endl;
					std::cout << " 1 to delete matrix" << std::endl;
					std::cout << " 2 to edit a cell" << std::endl;
					std::cout << " 3 to quit editing" << std::endl;
					std::cout << " All operations are done on matrix with id = " << id << std::endl << "> ";
					std::string sh;
					std::getline(std::cin, sh);
					choice = stoi(sh);
					if (choice == 1) {
						matrices.erase(matrices.begin() + id);
						std::cout << "Removed matrix at id = " << id << ". Matrix id's have now been updated. Run 'list' command to see them" << std::endl;
						choice = 3;
					} else if (choice == 2) {
						std::cout << "Enter row of cell to edit" << std::endl;
						std::getline(std::cin, sh);
						int row = stoi(sh);
						std::cout << "Enter column of cell to edit" << std::endl;
						std::getline(std::cin, sh);
						int col = stoi(sh);
						std::cout << "Enter new value of cell" << std::endl;
						std::getline(std::cin, sh);
						int val = stoi(sh);
						if (row < 1 || col < 1 || row > matrices[id].getRows() || col > matrices[id].getCols()) {
							std::cout << "Invalid cell" << std::endl;
						} else {
							matrices[id].setCell(row, col, val);
						}
					} else if (choice != 3) {
						std::cout << "Invalid selection, quitting editing" << std::endl;
						choice = 3;
					}
				}
			}
		}
		else if (s.substr(0, 5).compare("mult ") == 0) {
			if (s.find_first_of(" ") == s.find_last_of(" ")) {
				std::cout << "Invalid input" << std::endl;
			} else {
				int id1 = std::stoi(s.substr(5, s.find_last_of(" ") - 5));
				int id2 = std::stoi(s.substr(s.find_last_of(" ")));
				if (id1<0 || id2<0 || id1 > matrices.size() - 1 || id2 > matrices.size() - 1) {
					std::cout << "Invalid ids" << std::endl;
				} else {
					Matrix mult = matrices[id1].multiply(matrices[id2]);
					if (mult.isNull()) {
						std::cout << "failed to multply matrix " << id1 << " and " << id2 << std::endl;
					} else {
						matrices.push_back(mult);
						std::cout << "Multiplied matrix " << id1 << " and " << id2 << ". Its been saved under id = " << (matrices.size() - 1) << std::endl;
					}
				}
			}
		}
	}
}