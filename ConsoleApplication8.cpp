#include <iostream>
#include <windows.h>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void setCursorPosition(int x, int y){
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)((x*2)+1), (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

char pixel(int n) {
	char a[] = { ' ',' ','.',',',':',';','o','O','Q','#','@' };
	return a[(n / 10)];
}

struct point {
	float x = 0.0;
	float y = 0.0;
};

int circle(int x, int y, point p) {
	double s = sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
	if (s < 5) {
		return 100;
	}
	if (s >= 5) {
		if (s - 5 <= 0.8) {
			return (0.8 - (s - 5)) * 125;
		}
		else {
			return 0;
		}
	}
}

void colis(point *p, point *vect, float size, int n) {
	if (((p->x) + size) > n) {
		p->x -= 2*(((p->x) + size)-n);
		vect->x = 0-(vect->x);
	}
	if (((p->y) + size) > n) {
		p->y -= 2*(((p->y) + size)-n);
		vect->y = 0-(vect->y);
	}

	if (((p->x) - size) < 0) {
		p->x += 0-((p->x) - size);
		vect->x = -vect->x;
	}
	if (((p->y) - size) < 0) {
		p->y += 0-((p->y) - size);
		vect->y = -vect->y;
	}
}

void frame() {

}

BOOL ShowConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	return TRUE;
}

int main(){		
	srand(static_cast<unsigned int>(time(0)));
	ShowConsoleCursor(false);
	system("mode con cols=101 lines=52");
	const int n = 50;
	point p = {n/2, n/2};
	point pb = {n/2, n/2};
	point vect = {(rand()%100)*0.03, (rand()%100)*0.03};


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout.width(2);
			cout << pixel(circle(i,j,p));
		}
		cout << endl;
	}

	while (true) {
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (pixel(circle(i, j, pb)) != pixel(circle(i, j, p))){
					setCursorPosition(i, j);
					cout << pixel(circle(i, j, p));
				}
			}
		}
		pb.x = p.x;
		pb.y = p.y;

		p.x += vect.x;
		p.y += vect.y;

		vect.x/=1.01;
		vect.y/=1.01;

		colis(&p, &vect, 5.0, n-1);

		Sleep(33);
	}
	

	cin.get();
	return 0;
}