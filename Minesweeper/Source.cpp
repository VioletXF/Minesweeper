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
	plate.outputData = vector<vector<int>>(plate.ysize, vector<int>(plate.xsize, -1));
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

	
	output(plate.outputData);
}

void output(vector<vector<int>>&outputData) {
char_w arr[]="○①②③④⑤⑥⑦⑧●◐Ⓧ";
	system("cls");
	for (int i = 0; i < outputData.size(); i++) {
		for (int j = 0; j < outputData[i].size(); j++) {
			int dat = outputData[i][j];
cout<<arr[dat];
		}
		cout<<endl;
	}
}

void reveal(vector<vector<int>>&mineData, vector<vector<int>> &outputData, pair<int,int> coord){
if(mineData[coord.second][coord.first]==MINE){
gameover(false);
}
int count=0;
for(int y=coord.second-1;y<=coord.second+1;y++){
for(int x=coord.first-1;x<=coord.first+1;x++){
if(x==coord.first&&y==coord.second)continue;
if(mineData[y][x]==MINE)count++;
}
}
if(count==0){
for(int y=coord.second-1;y<=coord.second+1;y++){
for(int x=coord.first-1;x<=coord.first+1;x++){
if(x==coord.first&&y==coord.second)continue;
reveal(mineData,outputData,make_pair(x,y);
}
}
}
outputData[coord.second][coord.first]=count;
}

void gameover(bool win){
//TODO impl
}
