#include <iostream>
#include <vector>
using namespace std;
struct gameplate {
	int xsize;
	int ysize;
	int mineNum;
	vector<vector<int>> mapData;
};
void output(vector<vector<int>> mapData);
int main() {
	//Set Game
	gameplate plate;
	cout << "���� ���� ����:";
	cin >> plate.xsize;
	cout << "���� ���� ����:";
	cin >> plate.ysize;
	plate.mapData = vector<vector<int>>(plate.ysize, vector<int>(plate.xsize,0));

	cout << "������ ���� (1 �̸��� �� �Է� �� �ڵ�):";
	cin >> plate.mineNum;
	if (plate.mineNum < 1) {
		plate.mineNum = plate.xsize * plate.ysize / 2;
	}


	output(plate.mapData);
}

void output(vector<vector<int>> mapData) {
	for (int i = 0; i < mapData.size(); i++) {
		for (int j = 0; j < mapData[i].size(); j++) {
			cout << mapData[i][j];
		}
		cout<<endl;
	}
}