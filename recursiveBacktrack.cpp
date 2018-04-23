#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

int m = 22;
int n = 22;

struct location {
	bool n, e, s, w, visited;
	location(): n(false), e(false), s(false), w(false), visited(false) {}
};

struct coordinate {
	double y, x;
	coordinate(double paramy, double paramx): y(paramy), x(paramx) {}
};

std::vector<coordinate> stack;

void addStack(int currentY, int currentX, std::vector< std::vector<location> > &maze) {
	//Add Stack
	//Takes the current location and adds it to the vector of visited coordinates
	//Joshua Barringer
	stack.push_back(coordinate(currentY, currentX));
	maze[currentY][currentX].visited = true;
}

void mazeBorder(std::vector< std::vector<location> > &maze) {
	//Maze Border
	//sets the edges of the maze to visited spaces so we don't have to deal with leaving the maze on accident
	//acts like a buffer for the random movement
	//Joshua Barringer
	for(int y = 0; y < m; y++) {
		for(int x = 0; x < n; x++) {
			if(y == m-1 || y == 0) {
				maze[y][x].visited = true;
			}
			if(x == n-1 || x == 0) {
				maze[y][x].visited = true;
			}
		}
	}
}

void printMaze(std::vector< std::vector<location> > &maze) {
	//Print Maze
	//Stolen from my old binary tree maze generator
	//prints in 3 x 4 squares of corners and walls for each location in the maze
	//Joshua Barringer
	using std::cout;
	using std::endl;
        using std::ofstream;
	for(int y = 1; y < m-1; ++y) {
		for(int x = 1; x < n-1; ++x) {
			/*if (maze[y][x].n == true && maze[y][x].w == true) cout << " ";
			else*/ cout << "+";
			if (maze[y][x].n == true) cout << "  ";
			else cout << "--";
			/*if (maze[y][x].n == true && maze[y][x].e == true) cout << " ";
			else*/ cout << "+";
		}
		cout << endl;
		for(int x = 1; x < n-1; ++x) {
			if (maze[y][x].w == true) cout << " ";
			else cout << "|";
			if (maze[y][x].n == true || maze[y][x].e == true || maze[y][x].s == true || maze[y][x].w == true) cout << "  ";
			else cout << "++";
			if (maze[y][x].e == true) cout << " ";
			else cout << "|";
		}
		cout << endl;
		for(int x = 1; x < n-1; ++x) {
			/*if (maze[y][x].s == true && maze[y][x].w == true) cout << " ";
			else*/ cout << "+";
			if (maze[y][x].s == true) cout << "  ";
			else cout << "--";
			/*if (maze[y][x].s == true && maze[y][x].e == true) cout << " ";
			else*/ cout << "+";
		}
		cout << endl;
	}

        ofstream file ("recursiveMaze");
        for(int y = 1; y < m-1; ++y) {
                for(int x = 1; x <  - 1; ++x) {
                        /*if (maze[y][x].n == true && maze[y][x].w == true) file << " ";
                        else*/ file << "W";
                        if (maze[y][x].n == true) file << "  ";
                        else file << "WW";
                        /*if (maze[y][x].n == true && maze[y][x].e == true) file << " ";
                        else*/ file << "W";
                }
                file << endl;
                for(int x = 1; x <  - 1; ++x) {
                        if (maze[y][x].w == true) file << " ";
                        else file << "W";
                        if (maze[y][x].n == true || maze[y][x].e == true || maze[y][x].s == true || maze[y][x].w == true) file << "  ";
                        else file << "WW";
                        if (maze[y][x].e == true) file << " ";
                        else file << "W";
                }
                file << endl;
                for(int x = 1; x <  - 1; ++x) {
                        /*if (maze[y][x].s == true && maze[y][x].w == true) file << " ";
                        else*/ file << "W";
                        if (maze[y][x].s == true) file << "  ";
                        else file << "WW";
                        /*if (maze[y][x].s == true && maze[y][x].e == true) file << " ";
                        else*/ file << "W";
                }
                file << endl;
        }
        file.close();
}

void clear () {
	//Clear Screen
	//john is dumb
	//Joshua Barringer
	std::cout << "\033[2J\033[1;1H";
}

int main(int argc, char const *argv[])
{
	using std::vector;
	using std::cout;
	using std::endl;
        using std::cin;

        cout << "WELCOME TO MAZE!!!!\nEnter length: ";
        cin >> n;
        n+=2;
        cout << "Enter a height: ";
        cin >> m;
        m+=2;

	vector< vector<location> > maze;
	for(int y = 0; y < m; y++) {
		vector<location> row;
		for(int x = 0; x < n; x++) {
			row.push_back(location());
		}
		maze.push_back(row);
	}

	srand(time(NULL));

	mazeBorder(maze);

	unsigned int randomStartY = (rand() % (m-2)) + 1;
	unsigned int randomStartX = (rand() % (n-2)) + 1;
	unsigned int currentY = randomStartY;
	unsigned int currentX = randomStartX;
	cout << "x:" << randomStartX << " y:" << randomStartY << " ";

	addStack(currentY, currentX, maze);
        cout << maze[currentY][currentX].visited << endl;

	do {
		//cout << "X: " << currentX << endl;
		//cout << "Y: " << currentY << endl;
		int randDir = rand() % 4;

		if(maze[currentY + 1][currentX].visited
		&& maze[currentY][currentX + 1].visited
		&& maze[currentY - 1][currentX].visited
		&& maze[currentY][currentX - 1].visited) {
			cout << "<";
			stack.pop_back();
			currentY = stack.back().y;
			currentX = stack.back().x;
		}
		else {
			if(randDir == 0) {
				if(maze[currentY - 1][currentX].visited == false) {
					cout << "N";
					maze[currentY][currentX].n = true;
					maze[currentY - 1][currentX].s = true;
					currentY--;
					addStack(currentY, currentX, maze);
				}
                                else randDir++;
			}
			else if(randDir == 1) {
				if(maze[currentY][currentX + 1].visited == false) {
					cout << "E";
					maze[currentY][currentX].e = true;
					maze[currentY][currentX + 1].w = true;
					currentX++;
					addStack(currentY, currentX, maze);
				}
                                else randDir++;
			}
			else if(randDir == 2) {
				if(maze[currentY + 1][currentX].visited == false) {
					cout << "S";
					maze[currentY][currentX].s = true;
					maze[currentY + 1][currentX].n = true;
					currentY++;
					addStack(currentY, currentX, maze);
				}
                                else randDir++;
			}
			else if(randDir == 3) {
				if (maze[currentY][currentX - 1].visited == false) {
					cout << "W";
					maze[currentY][currentX].w = true;
					maze[currentY][currentX - 1].e = true;
					currentX--;
					addStack(currentY, currentX, maze);
				}
                                else randDir = 0;
			}
		}
		//clear();
		//printMaze(maze);
		//getchar();
	} while(currentY != randomStartY || currentX != randomStartX);
	cout << endl;
	printMaze(maze);
	return 0;
}