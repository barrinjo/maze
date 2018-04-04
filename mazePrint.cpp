#include <iostream>
#include <fstream>
using namespace std;

int main () {
	string line;

	ifstream file ("floorplan");
	if (file.is_open()) {
		while(getline(file, line)) {
			for (int i = 0; i <= 30; i++) {
				if (line[i] == 'W') {
					cout << "█";
				}
				else if (line[i] == 'S') {
					cout << "☺";
				}
				else if (line[i] == 'F') {
					cout << " ";
				}
				else {
					cout << line[i];
				}
			}
			cout << endl;
		}
	}
	else {
	cout << "floorplan not found\n";
	}
}