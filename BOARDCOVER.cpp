/*
	게임판 덮기
	작성일: 2021년 8월 18일(수)
*/

#include <iostream>
#include <vector>

#define FOR(i, from, n) for (int i=(from), LIMIT=(n); i<LIMIT; ++i)

#define BLOCK_SPACE	3
#define NONE		-1
#define TYPE_AMOUNT	4
#define COVER		1
#define ERASE		-1
#define OVERLAP		1

using namespace std;

typedef vector<vector<int>> GameBoard;

typedef struct Point { int x, y; } Point;

const int COVER_TYPE[TYPE_AMOUNT][BLOCK_SPACE][2] = {
	{{0,0},{1,0},{0,1}},
	{{0,0},{0,1},{1,1}},
	{{0,0},{1,0},{1,1}},
	{{0,0},{1,0},{1,-1}},
};

Point findFirstWhite(GameBoard& gameBoard) {
	FOR(y, 0, gameBoard.size()) {
		FOR(x, 0, gameBoard[0].size()) {
			if (!gameBoard[y][x])
				return { x, y };
		}
	}
	return { NONE, NONE };
}

bool hasNoWhite(Point& whitePoint) {
	return whitePoint.x == NONE || whitePoint.y == NONE;
}

bool coverBoardWithCenterAndType(GameBoard& gameBoard, Point center, int type) {
	bool canCoverBoard = true;
	FOR(i, 0, BLOCK_SPACE) {
		const int COVERED_Y = center.y + COVER_TYPE[type][i][0];
		const int COVERED_X = center.x + COVER_TYPE[type][i][1];
		if (COVERED_Y < 0 || COVERED_X < 0 ||
			COVERED_Y >= gameBoard.size() || COVERED_X >= gameBoard[0].size())
			canCoverBoard = false;
		else if ((gameBoard[COVERED_Y][COVERED_X] += COVER) > OVERLAP)
			canCoverBoard = false;
	}
	return canCoverBoard;
}

bool eraseBoardWithCenterAndType(GameBoard& gameBoard, Point center, int type) {
	bool canCoverBoard = false;
	FOR(i, 0, 3) {
		const int COVERED_Y = center.y + COVER_TYPE[type][i][0];
		const int COVERED_X = center.x + COVER_TYPE[type][i][1];
		if (COVERED_Y < 0 || COVERED_X < 0 ||
			COVERED_Y >= gameBoard.size() || COVERED_X >= gameBoard[0].size())
			canCoverBoard = false;
		else if ((gameBoard[COVERED_Y][COVERED_X] += ERASE) > OVERLAP)
			canCoverBoard = false;
	}
	return canCoverBoard;
}

int countCoverCapacity(GameBoard& gameBoard) {
	Point firstWhite = findFirstWhite(gameBoard);
	if (hasNoWhite(firstWhite)) return 1;

	int capacity = 0;
	FOR(type, 0, TYPE_AMOUNT) {
		if (coverBoardWithCenterAndType(gameBoard, firstWhite, type))
			capacity += countCoverCapacity(gameBoard);
		eraseBoardWithCenterAndType(gameBoard, firstWhite, type);
	}
	return capacity;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int C;
	cin >> C;
	while (C--) {
		int H, W;
		cin >> H >> W;
		GameBoard gameBoard = vector<vector<int>>(H, vector<int>(W));
		int whiteAmount = 0;
		for (int y = 0; y < H; ++y) {
			for (int x = 0; x < W; ++x) {
				char temp;
				cin >> temp;
				whiteAmount += temp == '.' ? 1 : 0;
				gameBoard[y][x] = temp == '#' ? 1 : 0;
			}
		}
		if (whiteAmount % BLOCK_SPACE == 0)
			cout << countCoverCapacity(gameBoard) << '\n';
		else
			cout << "0\n";
	}
	return 0;
}
