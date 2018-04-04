#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main () {
	string line;
	//int y = 0;
	vector<string> lines;

	ifstream file ("floorplan");
	if (file.is_open()) {

		while(getline(file, line)) {
			lines.push_back (line);
		}
		file.close();

		for (int y = 0; y < lines.size(); ++y)
		{
			for (int x = 0; x < lines[y].length(); ++x)
			{
				if (lines[y][x] == 'W') {
					cout << "█";
				}
				else if (lines[y][x] == 'S') {
					cout << "☺";
				}
				else if (lines[y][x] == 'F') {
					cout << " ";
				}
				else {
					cout << lines[y][x];
				}
			}
			cout << endl;
		}

	}

	else {
	cout << "floorplan not found\n";
	}
}