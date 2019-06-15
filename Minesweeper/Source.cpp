#include <iostream>
#include <vector>
#include <Windows.h>
#include <random>
#include <locale>
using namespace std;
enum MineData {
	BLANK,
	MINE,

};
struct gameplate {
	unsigned int xsize;
	unsigned int ysize;
	int mineNum;
	vector<vector<int>> mineData;
	vector<vector<int>> outputData;
	int flagNum;
};

void gameover(bool);
bool reveal(vector<vector<int>>&, vector<vector<int>>&, pair<int, int>);
void output(vector<vector<int>>&, vector<vector<int>>&);
int getNearbyFlag(vector<vector<int>>&, pair<int, int>);
bool revealNearby(vector<vector<int>>&, vector<vector<int>>&, pair<int, int>);
int main() {
	//SetConsoleOutputCP(65001);
	setlocale(LC_ALL, "");
	//Set Game
	gameplate plate;
	do {
		wcout << L"판의 가로 길이:";
		cin >> plate.xsize;
	} while (plate.xsize < 1);
	do {
		wcout << L"판의 세로 길이:";
		cin >> plate.ysize;
	} while (plate.ysize < 1);
	plate.mineData = vector<vector<int>>(plate.ysize, vector<int>(plate.xsize, BLANK));
	plate.outputData = vector<vector<int>>(plate.ysize, vector<int>(plate.xsize, -1));
	do {
		wcout << L"지뢰의 개수 (1 미만의 값 입력 시 자동):";
		cin >> plate.mineNum;
	} while (plate.mineNum > plate.xsize * plate.ysize);
	if (plate.mineNum < 1) {
		plate.mineNum = plate.xsize * plate.ysize / 2;
	}
	plate.flagNum = 0;
	output(plate.outputData, plate.mineData);
	int turn = 0;
	bool isFirstOpen = true;
	while (true) {

		wchar_t mode = L'가';
		int ix = 0;
		int iy = 0;
		wchar_t ixc = L'가';
		wchar_t iyc = L'가';
		cout << "========모드========\nㄹ: 열기\nㅍ: 깃발\n====================\n남은 지뢰 수: " << plate.mineNum - plate.flagNum << "/" << plate.mineNum << "\n입력: 모드 x y\n";
		wcin.clear();
		wcin >> mode >> ixc >> iyc;

		ix = (int)ixc - 44032;
		iy = (int)iyc - 44032;
		cout << ix << "," << iy;
		if (ix >= 0 && iy >= 0 && ix % 56 == 0 && iy % 56 == 0) {

			ix = ix / 56;
			iy = iy / 56;

			switch (mode) {
			case L'ㄹ':
				if (isFirstOpen) {
					//Mine Placement
					std::random_device rd;
					std::mt19937 mersenne(rd());
					std::uniform_int_distribution<> randY(0, plate.ysize - 1);
					std::uniform_int_distribution<> randX(0, plate.xsize - 1);
					int mineCount = 0;
					do {
						int x = randX(mersenne);
						int y = randY(mersenne);
						if (plate.mineData[y][x] != MINE && sqrt(pow((double)x - (double)(ix + 1), 2) + pow((double)y - (double)(iy + 1), 1)) > sqrt(2)) {
							mineCount++;
							plate.mineData[y][x] = MINE;
						}
					} while (mineCount < plate.mineNum);
					isFirstOpen = false;
				}
				if (plate.outputData[iy][ix] == getNearbyFlag(plate.outputData, make_pair(ix, iy))) {
					gameover(!revealNearby(plate.mineData, plate.outputData, make_pair(ix, iy)));
				}
				else {
					gameover(!reveal(plate.mineData, plate.outputData, make_pair(ix, iy)));
				}
				turn++;
				break;
			case L'ㅍ':
				if (ix < 0 || iy < 0 || iy >= plate.mineData.size() || ix >= plate.mineData[iy].size()) {
					cout << "WTF?";
					break;
				}
				if (plate.outputData[iy][ix] == -1) {
					plate.outputData[iy][ix] = 9;
					plate.flagNum++;
				}
				else if (plate.outputData[iy][ix] == 9) {
					plate.outputData[iy][ix] = -1;
					plate.flagNum--;
				}
				turn++;
				break;
			default:
				cout << "WTF?";
				break;
			}

		}
		output(plate.outputData, plate.mineData);

	}




	output(plate.outputData, plate.mineData);
}

void output(vector<vector<int>>& outputData, vector<vector<int>>& mineData) {
	const wchar_t arr[] = L"○①②③④⑤⑥⑦⑧";
	const wchar_t arr2[] = L"１２３４５６７８９";
	system("cls");

	wcout << L"○";
	for (int i = 0; i < outputData[0].size(); i++) {

		wcout << wchar_t(44032 + i * 56);


	}
	cout << "\n";
	for (int i = 0; i < outputData.size(); i++) {
		wcout << wchar_t(44032 + i * 56);
		for (int j = 0; j < outputData[i].size(); j++) {

			int dat = outputData[i][j];
			if (dat == -1) {
				wcout << L"ㅁ";
			}
			else if (dat == 9) {
				wcout << L"깃";
			}
			else {
				wcout << arr[dat];
			}
		}
		cout << endl;
	}
}

bool reveal(vector<vector<int>>& mineData, vector<vector<int>>& outputData, pair<int, int> coord) {
	if (coord.first < 0 || coord.second < 0 || coord.second >= mineData.size() || coord.first >= mineData[coord.second].size())return false;
	if (outputData[coord.second][coord.first] != -1) return false;

	if (mineData[coord.second][coord.first] == MINE) {
		return true;
	}

	int count = 0;

	for (int y = coord.second - 1; y <= coord.second + 1; y++) {
		for (int x = coord.first - 1; x <= coord.first + 1; x++) {
			if (x == coord.first && y == coord.second)continue;
			if (x < 0 || y < 0 || y >= mineData.size() || x >= mineData[y].size())continue;
			if (mineData[y][x] == MINE)count++;
		}
	}
	outputData[coord.second][coord.first] = count;
	if (count == 0) {
		return revealNearby(mineData, outputData, coord);
	}
	return false;

}
bool revealNearby(vector<vector<int>>& mineData, vector<vector<int>>& outputData, pair<int, int> coord) {
	bool touchedMine = false;
	for (int y = coord.second - 1; y <= coord.second + 1; y++) {
		for (int x = coord.first - 1; x <= coord.first + 1; x++) {

			if (x == coord.first && y == coord.second)continue;
			if (x < 0 || y < 0 || y >= mineData.size() || x >= mineData[y].size())continue;
			if (outputData[y][x] == 9)continue;
			touchedMine = reveal(mineData, outputData, make_pair(x, y));
		}
	}
	return touchedMine;
}
int getNearbyFlag(vector<vector<int>>& outputData, pair<int, int> coord) {
	int count = 0;
	for (int y = coord.second - 1; y <= coord.second + 1; y++) {
		for (int x = coord.first - 1; x <= coord.first + 1; x++) {

			if (x == coord.first && y == coord.second)continue;
			if (x < 0 || y < 0 || y >= outputData.size() || x >= outputData[y].size())continue;

			if (outputData[y][x] == 9)count++;
		}
	}
	return count;
}
void gameover(bool win) {
	//TODO impl
	if (!win)
		wcout << L"게임 오버";
}
