#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

using namespace std;

int getNumberEndedWithComma(std::istream &ins) {
	std::string numString;

	getline(ins, numString, ',');
	std::istringstream iss(numString);

	int num;
	iss >> num;

	return num;
}

void cmdD(std::istream &ins, std::ostream &outs) {
	int lspeed, rspeed, ldir, rdir;
	lspeed = getNumberEndedWithComma(ins);
	rspeed = getNumberEndedWithComma(ins);
	ldir = getNumberEndedWithComma(ins);
	rdir = getNumberEndedWithComma(ins);

	outs << 'D' << lspeed << ',' << rspeed << ",\n";

        cout << "In/out: " << lspeed << ',' << rspeed << ',' << ldir << ',' << rdir << endl;
}

void cmdB(std::istream &ins, std::ostream &outs) {
	ins.ignore();
	ins.ignore();
}

void loop(std::istream &ins, std::ostream &outs) {
	string line;
	while (true) {
		int ch = ins.get();
                if (ins.fail()) continue;
		cout << "ch=" << (char)ch << endl;
		switch (ch) {
		case 'D':
			cmdD(ins, outs);
			break;
		case 'B':
			cmdB(ins, outs);
			break;
		}
	}
}

int main(int argc, char **argv) {
	if (argc > 1) {
		shared_ptr<std::fstream> fs(new std::fstream(argv[1]));
		if (!fs->is_open()) {
			std::cout << "Unable to open file" << std::endl << std::endl;
			exit(-1);
		}
		loop(*fs, *fs);
		fs->close();
	} else {
		loop(std::cin, std::cout);
	}

	return 0;
}
