#include <iostream>
using namespace std;
struct gameplate {
	int xsize;
	int ysize;
	int mineNum;
};
int main() {
	gameplate plate;
	cout << "판의 가로 길이:";
	cin >> plate.xsize;
	cout << "판의 세로 길이:";
	cin >> plate.ysize;
	cout << "지뢰의 개수 (1 미만의 값 입력 시 자동):";
	cin >> plate.mineNum;
	if (plate.mineNum < 1) {
		plate.mineNum = plate.xsize * plate.ysize / 2;
	}
}