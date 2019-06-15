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
};

void gameover(bool);
bool reveal(vector<vector<int>>&, vector<vector<int>>&, pair<int, int>);
void output(vector<vector<int>>&);
int main() {
	locale::global(locale("kor"));
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

	int turn = 0;
	while (true) {

		char mode;
		int ix;
		int iy;
		cout << "R 1 8";
		cin.clear();
		cin >> mode >> ix >> iy;
		
		switch (mode) {
		case 'R':
		case 'r':
			if (turn == 0) {
				//Mine Placement
				std::random_device rd;
				std::mt19937 mersenne(rd());
				std::uniform_int_distribution<> randY(0, plate.ysize - 1);
				std::uniform_int_distribution<> randX(0, plate.xsize - 1);
				int mineCount = 0;
				do {
					int x = randX(mersenne);
					int y = randY(mersenne);
					if (plate.mineData[y][x] != MINE||sqrt(pow((double)(x-ix), 2) + pow((double)(y-iy),1))>sqrt(2)) {
						
						
						mineCount++;
						plate.mineData[y][x] = MINE;
					}
				} while (mineCount < plate.mineNum);
			}
			if (reveal(plate.mineData, plate.outputData, make_pair(ix, iy))) {
				gameover(false);
			}
			break;
		case 'F':
		case 'f':
			//TODO impl
			break;
		default:
			cout << "WTF?";
			break;
		}
		output(plate.outputData);
	}




	output(plate.outputData);
}

void output(vector<vector<int>>& outputData) {
	const wchar_t arr[] = L"○①②③④⑤⑥⑦⑧●◐Ⓧ";
	system("cls");
	for (int i = 0; i < outputData.size(); i++) {
		for (int j = 0; j < outputData[i].size(); j++) {
			int dat = outputData[i][j];
			wcout << arr[dat];
		}
		cout << endl;
	}
}

bool reveal(vector<vector<int>>& mineData, vector<vector<int>>& outputData, pair<int, int> coord) {
	if (mineData[coord.second][coord.first] == MINE) {
		return true;
	}
	int count = 0;
	for (int y = coord.second - 1; y <= coord.second + 1; y++) {
		for (int x = coord.first - 1; x <= coord.first + 1; x++) {
			if (x == coord.first && y == coord.second)continue;
			if (x < 0 || y < 0||y > mineData.size()|| x > mineData[y].size() )continue;
			if (mineData[y][x] == MINE)count++;
		}
	}
	if (count == 0) {
		for (int y = coord.second - 1; y <= coord.second + 1; y++) {
			for (int x = coord.first - 1; x <= coord.first + 1; x++) {

				if (x == coord.first && y == coord.second)continue;
				if (x > mineData[y].size() || y > mineData.size() || x < 0 || y < 0)continue;
				return reveal(mineData, outputData, make_pair(x, y));
			}
		}
	}
	outputData[coord.second][coord.first] = count;
	return false;
}

void gameover(bool win) {
	//TODO impl
}
