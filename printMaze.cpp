#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <termios.h>
#include <sstream>
#include <ctime>
using namespace std;

string line;
string input;
//int y = 0;
vector<string> mazeInit;
vector<string> lines;
int coordX, coordY;

void printMaze();
void printMazeSlow();
void printMazeFast();
void refreshMaze();
char getch();
bool computerRandomSolve();
bool computerSolve();

int main (int argc, char const *argv[]) {
	srand(time(NULL));

	ifstream file (argv[1]);
	if (file.is_open()) {

		while(getline(file, line)) {
			mazeInit.push_back (line);
			lines.push_back (line);
		}
		file.close();
	}

	else {
	cout << "floorplan not found\n";
	return 0;
	}

	for (int y = 0; y < mazeInit.size(); ++y)
	{
		for (int x = 0; x < mazeInit[y].length(); ++x)
		{
			lines[y][x] = ' ';
		}
	}
	
	for (int y = 0; y < mazeInit.size(); ++y)
	{
		lines[y][0] = 'W';
		lines[y][lines[y].length() / 2] = 'W';

		int z = 1;

		for (int x = 1; x < mazeInit[y].length() - 1; x += 2)
		{
			if (mazeInit[y][x] == 'W') {
				lines[y][z] = 'W';
			}
			else if (mazeInit[y][x] == ' '){
				lines[y][z] = ' ';
			}

			z++;
		}

	}

	printMazeSlow();

	int choice;
	cout << "enter 0 to try the maze or 1 for random solve and 2 for quick solve: ";
	cin >> choice;

	if (choice == 1) {
		int begin = clock();

		choice = computerRandomSolve();

		int finish = clock();
		double elapsed_secs = double(finish - begin) / CLOCKS_PER_SEC;
		cout << "Finished in " << elapsed_secs << " seconds" << endl;
		if (choice == 0) {
			return 0;
		}
	}

	if (choice == 2) {
		int begin = clock();

		choice = computerSolve();
		printMaze();

		int finish = clock();
		double elapsed_secs = double(finish - begin) / CLOCKS_PER_SEC;
		cout << "Finished in " << elapsed_secs << " seconds" << endl;
		if (choice == 0) {
			return 0;
		}
	}
	
	for (;;) {
		cout << "move with wasd" << endl;
		input = getch();
		if (input == "w") { 
			if (lines[coordY - 1][coordX] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY - 1][coordX] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY - 1][coordX] = 'S';
			}
		}
		if (input == "a") { 
			if (lines[coordY][coordX - 1] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY][coordX - 1] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY][coordX - 1] = 'S';
			}
		}
		if (input == "s") { 
			if (lines[coordY + 1][coordX] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY + 1][coordX] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY + 1][coordX] = 'S';
			}
		}
		if (input == "d") { 
			if (lines[coordY][coordX + 1] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY][coordX + 1] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY][coordX + 1] = 'S';
			}
		}
		printMaze();
	}
}

void printMaze() {
	if (lines.size() > 31) {
		printMazeFast();
	}
	else {
		printMazeSlow();
	}
}

void printMazeSlow() {
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

void printMazeFast() {
	cout << "\033[2J\033[1;1H";
	for (int y = 0; y < lines.size(); ++y) {
		{
			for (int x = 0; x < lines[y].length(); ++x)
			{
				if (lines[y][x] == 'W') {
					cout << "#";
				}
				else if (lines[y][x] == 'S') {
					cout << "o";
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

void refreshMaze() {
	for (int y = 0; y < lines.size(); ++y) {
		for (int x = 0; x < lines[y].length(); ++x)
		{
			if (lines[y][x] == 'S') {
				coordY = y;
				coordX = x;
			}
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

bool computerRandomSolve () {
	for (;;) {
		int inputInt;
		inputInt = (rand() % 4);
		if (inputInt == 1) { 
			if (lines[coordY - 1][coordX] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY - 1][coordX] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY - 1][coordX] = 'S';
			}
		}
		if (inputInt == 2) { 
			if (lines[coordY][coordX - 1] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY][coordX - 1] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY][coordX - 1] = 'S';
			}
		}
		if (inputInt == 3) { 
			if (lines[coordY + 1][coordX] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY + 1][coordX] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY + 1][coordX] = 'S';
			}
		}
		if (inputInt == 0) { 
			if (lines[coordY][coordX + 1] == 'F') {
				cout << "YOU WIN!!!" << endl;
				return 0;
			}
			if (lines[coordY][coordX + 1] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY][coordX + 1] = 'S';
			}
		}
		printMaze();
	}
}

bool computerSolve() {
	int inputInt = 0;
	for (;;) {
		while (inputInt == 0) { 
			if (lines[coordY][coordX + 1] == 'F') {
				return 0;
			}
			else if (lines[coordY + 1][coordX] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY + 1][coordX] = 'S';
				refreshMaze();
				inputInt = 1;
			}
			else if (lines[coordY][coordX + 1] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY][coordX + 1] = 'S';
				refreshMaze();
			}
			else if (lines[coordY - 1][coordX] != 'W') {
				inputInt = 3;
			}
			else {
				inputInt = 2;
			}
		}
		while (inputInt == 1) { 
			if (lines[coordY + 1][coordX] == 'F') {
				return 0;
			}
			else if (lines[coordY][coordX - 1] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY][coordX - 1] = 'S';
				refreshMaze();
				inputInt = 2;
			}
			else if (lines[coordY + 1][coordX] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY + 1][coordX] = 'S';
				refreshMaze();
			}
			else if (lines[coordY][coordX + 1] != 'W') {
				inputInt = 0;
			}
			else {
				inputInt = 3;
			}
		}
		while (inputInt == 2) { 
			if (lines[coordY][coordX - 1] == 'F') {
				return 0;
			}
			else if (lines[coordY - 1][coordX] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY - 1][coordX] = 'S';
				refreshMaze();
				inputInt = 3;
			}
			else if (lines[coordY][coordX - 1] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY][coordX - 1] = 'S';
				refreshMaze();
			}
			else if (lines[coordY + 1][coordX] != 'W') {
				inputInt = 1;
			}
			else {
				inputInt = 0;
			}
		}
		while (inputInt == 3) { 
			if (lines[coordY - 1][coordX] == 'F') {
				return 0;
			}
			else if (lines[coordY][coordX + 1] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY][coordX + 1] = 'S';
				refreshMaze();
				inputInt = 0;
			}
			else if (lines[coordY - 1][coordX] != 'W') {
				lines[coordY][coordX] = '+';
				lines[coordY - 1][coordX] = 'S';
				refreshMaze();
			}
			else if (lines[coordY][coordX - 1] != 'W') {
				inputInt = 2;
			}
			else {
				inputInt = 1;
			}
		}
	}
}