#include <iostream>
using namespace std;
struct gameplate {
	int xsize;
	int ysize;
	int mineNum;
};
int main() {
	gameplate plate;
	cout << "���� ���� ����:";
	cin >> plate.xsize;
	cout << "���� ���� ����:";
	cin >> plate.ysize;
	cout << "������ ���� (1 �̸��� �� �Է� �� �ڵ�):";
	cin >> plate.mineNum;
	if (plate.mineNum < 1) {
		plate.mineNum = plate.xsize * plate.ysize / 2;
	}
}