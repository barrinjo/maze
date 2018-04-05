#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <termios.h>
#include <sstream>
using namespace std;

string line;
string input;
//int y = 0;
vector<string> lines;
int coordX, coordY;

void printMaze();
char getch();

int main () {
	srand(time(NULL));

	ifstream file ("floorplan");
	if (file.is_open()) {

		while(getline(file, line)) {
			lines.push_back (line);
		}
		printMaze();
		file.close();

	}

	else {
	cout << "floorplan not found\n";
	}

	bool choice;
	cout << "enter 1 to try the maze or 0 to let the computer try: ";
	cin >> choice;
	
	for (;;) {
		int inputInt;
		cout << "move with wasd" << endl;
		if (choice == 1) {
			input = getch();
		}
		else {
			inputInt = (rand() % 4);
		}
		if (input == "w" || inputInt == 1) { 
			if (lines[coordY - 1][coordX] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY - 1][coordX] != 'W') {
				lines[coordY][coordX] = ' ';
				lines[coordY - 1][coordX] = 'S';
			}
		}
		if (input == "a" || inputInt == 2) { 
			if (lines[coordY][coordX - 1] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY][coordX - 1] != 'W') {
				lines[coordY][coordX] = ' ';
				lines[coordY][coordX - 1] = 'S';
			}
		}
		if (input == "s" || inputInt == 3) { 
			if (lines[coordY + 1][coordX] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY + 1][coordX] != 'W') {
				lines[coordY][coordX] = ' ';
				lines[coordY + 1][coordX] = 'S';
			}
		}
		if (input == "d" || inputInt == 0) { 
			if (lines[coordY][coordX + 1] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY][coordX + 1] != 'W') {
				lines[coordY][coordX] = ' ';
				lines[coordY][coordX + 1] = 'S';
			}
		}
		printMaze();
	}
}

void printMaze() {
	cout << "\033[2J\033[1;1H";
	for (int y = 0; y < lines.size(); ++y) {
		{
			for (int x = 0; x < lines[y].length(); ++x)
			{
				if (lines[y][x] == 'W') {
					cout << "█";
				}
				else if (lines[y][x] == 'S') {
					cout << "☺";
					coordY = y;
					coordX = x;
				}
				else if (lines[y][x] == 'F') {
					cout << "->";
				}
				else {
					cout << lines[y][x];
				}
			}
			cout << endl;
		}
	}
}

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}