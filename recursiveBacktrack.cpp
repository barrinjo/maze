#include <iostream>
#include <thread>
#include <vector>

int m = 20;
int n = 20;

struct location {
	bool n, e, s, w, visited;
	location(): n(false), e(false), s(false), w(false), visited(false) {}
};

struct coordinate {
	double y, x;
	coordinate(double paramy, double paramx): y(paramy), x(paramx) {}
};

location maze[22][22];
std::vector<coordinate> stack;

void addStack(int currentY, int currentX) {
	//Add Stack
	//Takes the current location and adds it to the vector of visited coordinates
	//Joshua Barringer
	stack.push_back(coordinate(currentY, currentX));
	maze[currentY][currentX].visited = true;
}

void mazeBorder() {
	//Maze Border
	//sets the edges of the maze to visited spaces so we don't have to deal with leaving the maze on accident
	//acts like a buffer for the random movement
	//Joshua Barringer
	for(int y = 0; y < 22; y++) {
		for(int x = 0; x < 22; x++) {
			if(y == 21 || y == 0) {
				maze[y][x].visited = true;
			}
			if(x == 21 || x == 0) {
				maze[y][x].visited = true;
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	using std::cout;
	using std::endl;

	srand(time(NULL));

	mazeBorder();

	unsigned int randomStartY, currentY = (rand() % m) + 1;
	unsigned int randomStartX, currentX = (rand() % n) + 1;
	location dummy;

	addStack(currentY, currentX);
	do {
		cout << "first step" << endl;
		int randDir = rand() % 4;

		if(randDir == 0) {
			if(maze[currentY - 1][currentX].visited == false) {
				maze[currentY][currentX].n = true;
				maze[currentY - 1][currentX].s = true;
				currentY--;
				addStack(currentY, currentX);
			}
		}
		else if(randDir == 1) {
			if(maze[currentY][currentX + 1].visited == false) {
				maze[currentY][currentX].e = true;
				maze[currentY][currentX + 1].w = true;
				currentX++;
				addStack(currentY, currentX);
			}
		}
		else if(randDir == 2) {
			if(maze[currentY + 1][currentX].visited == false) {
				maze[currentY][currentX].s = true;
				maze[currentY + 1][currentX].n = true;
				currentY++;
				addStack(currentY, currentX);
			}
		}
		else if(randDir == 3) {
			if (maze[currentY][currentX - 1].visited == false) {
				maze[currentY][currentX].w = true;
				maze[currentY][currentX - 1].e = true;
				currentX--;
				addStack(currentY, currentX);
			}
		}
	} while (currentY == randomStartY && currentX == randomStartX);

	while(currentY != randomStartY && currentX != randomStartX) {
		cout << "X: " << currentX << endl;
		cout << "Y: " << currentY << endl;
		int randDir = rand() % 4;

		if(maze[currentY + 1][currentX].visited
		&& maze[currentY][currentX + 1].visited
		&& maze[currentY - 1][currentX].visited
		&& maze[currentY][currentX - 1].visited) {
			cout << "back" << endl;
			stack.pop_back();
			currentY = stack.back().y;
			currentX = stack.back().x;
		}
		else {
			if(randDir == 0) {
				cout << "N" << endl;
				if(maze[currentY - 1][currentX].visited == false) {
					maze[currentY][currentX].n = true;
					maze[currentY - 1][currentX].s = true;
					currentY--;
					addStack(currentY, currentX);
				}
			}
			else if(randDir == 1) {
				cout << "E" << endl;
				if(maze[currentY][currentX + 1].visited == false) {
					maze[currentY][currentX].e = true;
					maze[currentY][currentX + 1].w = true;
					currentX++;
					addStack(currentY, currentX);
				}
			}
			else if(randDir == 2) {
				cout << "S" << endl;
				if(maze[currentY + 1][currentX].visited == false) {
					maze[currentY][currentX].s = true;
					maze[currentY + 1][currentX].n = true;
					currentY++;
					addStack(currentY, currentX);
				}
			}
			else if(randDir == 3) {
				cout << "W" << endl;
				if (maze[currentY][currentX - 1].visited == false) {
					maze[currentY][currentX].w = true;
					maze[currentY][currentX - 1].e = true;
					currentX--;
					addStack(currentY, currentX);
				}
			}
		}
	}

	for (int y = 0; y < 22; ++y)
	{
		for (int x = 0; x < 22; ++x)
		{
			/*if (maze[y][x].n == true && maze[y][x].w == true) cout << " ";
			else*/ cout << "+";
			if (maze[y][x].n == true) cout << "  ";
			else cout << "--";
			/*if (maze[y][x].n == true && maze[y][x].e == true) cout << " ";
			else*/ cout << "+";
		}
		cout << endl;
		for (int x = 0; x < m; ++x)
		{
			if (maze[y][x].w == true) cout << " ";
			else cout << "|";
			if (maze[y][x].n == true || maze[y][x].e == true || maze[y][x].s == true || maze[y][x].w == true) cout << "  ";
			else cout << "++";
			if (maze[y][x].e == true) cout << " ";
			else cout << "|";
		}
		cout << endl;
		for (int x = 0; x < m; ++x)
		{
			/*if (maze[y][x].s == true && maze[y][x].w == true) cout << " ";
			else*/ cout << "+";
			if (maze[y][x].s == true) cout << "  ";
			else cout << "--";
			/*if (maze[y][x].s == true && maze[y][x].e == true) cout << " ";
			else*/ cout << "+";
		}
		cout << endl;
	}
}