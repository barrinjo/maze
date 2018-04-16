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

location maze[20][20];
std::vector<coordinate> stack;

void addStack(int currentY, int currentX) {
	stack.push_back(coordinate(currentY, currentX));
	maze[currentY][currentX].visited = true;
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	unsigned int randomStartY, currentY = (rand() % m);
	unsigned int randomStartX, currentX = (rand() % n);
	location dummy;

	addStack(currentY, currentX);
	while (true) {
		int randDir = rand() % 4;

		if(randDir == 0) {
			if(!(currentY - 1)) {
				maze[currentY][currentX].n = true;
				maze[currentY - 1][currentX].s = true;
				currentY--;
				addStack(currentY, currentX);
				break;
			}		}
		else if(randDir == 1) {
			if(!(currentX + 1 >= n)) {
				maze[currentY][currentX].e = true;
				maze[currentY][currentX + 1].w = true;
				currentX++;
				addStack(currentY, currentX);
				break;
			}
		}
		else if(randDir == 2) {
			if(!(currentY + 1 >= m)) {
				maze[currentY][currentX].s = true;
				maze[currentY + 1][currentX].n = true;
				currentY++;
				addStack(currentY, currentX);
				break;
			}
		}
		else if(randDir == 3) {
			if (!(currentX - 1)) {
				maze[currentY][currentX].w = true;
				maze[currentY][currentX - 1].e = true;
				currentX--;
				addStack(currentY, currentX);
				break;
			}
		}
	}
}