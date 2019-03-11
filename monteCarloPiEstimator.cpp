#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <thread>
#include <cmath>
const int MAX_POINTS = 8000000;

struct Point {
	Point(double _x, double _y): x(_x), y(_y) {}
	void print() {
		std::cout << "(" << x << "," << y << ")\n";
	}
	double x, y;
};

/* Return values between (-1,1);*/
double nextRand() {
	return (rand() / double(RAND_MAX)) * 2 - 1;
}

/* Check if points are in the circle */
bool inBounds(double x, double y) {
	return sqrt(x*x + y*y) <= 1.0;
}

void cntInQuad(std::vector<Point> points, int quad, int (&total)[4]) {
	double x;
	double y;
	for(auto iter = points.begin(); iter != points.end(); iter++) {
		x = iter->x;
		y = iter->y;
		switch (quad) {
			case 0: 
				if ( x > 0 && y > 0 && inBounds(x,y)) 
						total[quad] += 1;
				break;
			case 1:
				if ( x > 0 && y < 0 && inBounds(x,y))
						total[quad] += 1;
				break;
			case 2:
				if ( x < 0 && y < 0 && inBounds(x,y)) 
						total[quad] += 1;
				break;
			case 3:
				if ( x < 0 && y > 0 && inBounds(x,y)) 
						total[quad] += 1;
				break;
		}
	}
	std::cout << total[quad] << std::endl;
} 

void generateQuadPoints(std::vector<Point> &circle) {
	for(int i = 0 ; i < MAX_POINTS; i++) 
		circle.push_back(Point(nextRand(), nextRand()));
}

int main() {
	srand(getpid());
	std::vector<Point> circle;	 
	generateQuadPoints(circle);
	int inQuad[4] = {0};
	for(int i = 0; i < 4; i++ ) {
		std::thread t(cntInQuad, circle,i, std::ref(inQuad));
		t.join();
	}
	int inCircle = inQuad[0] + inQuad[1] + inQuad[2] + inQuad[3];
	std::cout << "π = " << double(inCircle) * double(4.0) / (double(MAX_POINTS) ) << std::endl;
	return 0;
}
