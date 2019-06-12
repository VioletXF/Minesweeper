#include <iostream>
#include <vector>
#include <Windows.h>
#include <random>
using namespace std;
enum MineData{
	BLANK,
	MINE,

}
struct gameplate {
	unsigned int xsize;
	unsigned int ysize;
	int mineNum;
	vector<vector<int>> mineData;
	vector<vector<int>> outputData;
};
void output(vector<vector<int>>&mineData);
int main() {
	//Set Game
	gameplate plate;
	do {
		cout << "판의 가로 길이:";
		cin >> plate.xsize;
	} while (plate.xsize < 1);
	do {
		cout << "판의 세로 길이:";
		cin >> plate.ysize;
	} while (plate.ysize < 1);
	plate.mineData = vector<vector<int>>(plate.ysize, vector<int>(plate.xsize,BLANK));
	plate.outputData = vector<vector<int>>(plate.ysize, vector<int>(plate.xsize, 0));
	do {
		cout << "지뢰의 개수 (1 미만의 값 입력 시 자동):";
		cin >> plate.mineNum;
	} while (plate.mineNum > plate.xsize * plate.ysize);
	if (plate.mineNum < 1) {
		plate.mineNum = plate.xsize * plate.ysize / 2;
	}

	//Mine Placement
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> randY(0, plate.ysize - 1);
	std::uniform_int_distribution<> randX(0, plate.xsize - 1);
	int mineCount = 0;
	do {
		int x = randX(mersenne);
		int y = randY(mersenne);
		if (plate.mineData[y][x] != MINE) {
			mineCount++;
			plate.mineData[y][x] = MINE;
		}
	} while (mineCount < plate.mineNum);

	
	output(plate.mineData);
}

void output(vector<vector<int>>&mineData) {
	system("cls");
	for (int i = 0; i < mineData.size(); i++) {
		for (int j = 0; j < mineData[i].size(); j++) {
			int dat = mineData[i][j];
		}
		cout<<endl;
	}
}