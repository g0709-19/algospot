/*
	외발 뛰기
	작성일: 2021년 9월 5일(일)
*/

#include <iostream>
#include <vector>

#define NOT_CACHED -2
#define INF -1
#define END 0

#define min(x, y) ((x) > (y) ? (y) : (x))

using namespace std;

typedef vector<vector<int>> Board;

Board cache;
int boardLength;

void insertBoardCostByKeyboard(Board& board);
int jumpTo(Board& board, int x, int y);
bool isEndPoint(Board& board, int x, int y);

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int caseAmount;
	cin >> caseAmount;
	while (caseAmount--) {
		cin >> boardLength;
		Board board(boardLength, vector<int>(boardLength));
		cache = Board(boardLength, vector<int>(boardLength, NOT_CACHED));
		insertBoardCostByKeyboard(board);

		int costForArrival = jumpTo(board, 0, 0);
		cout << (costForArrival == INF ? "NO" : "YES") << '\n';
	}
	return 0;
}

void insertBoardCostByKeyboard(Board& board) {
	for (int i = 0; i < boardLength; ++i)
		for (int j = 0; j < boardLength; ++j)
			cin >> board[i][j];
}

int jumpTo(Board &board, int x, int y) {
	if (x >= boardLength || y >= boardLength)
		return INF;
	if (isEndPoint(board, x, y))
		return END;
	const int COST = board[x][y];
	if (y + COST >= boardLength &&
		x + COST >= boardLength)
		return INF;
	int& cachedCost = cache[x][y];
	if (cachedCost != NOT_CACHED)
		return cachedCost;

	int costForArrivalToRight = INF;
	int costForArrivalToBottom = INF;
	if (y + COST < boardLength)
		costForArrivalToRight = jumpTo(board, x, y + COST);
	if (x + COST < boardLength)
		costForArrivalToBottom = jumpTo(board, x + COST, y);

	if (costForArrivalToRight != INF && costForArrivalToBottom != INF)
		return cachedCost = COST + min(costForArrivalToRight, costForArrivalToBottom);
	else if (costForArrivalToRight != INF)
		return cachedCost = COST + costForArrivalToRight;
	else if (costForArrivalToBottom != INF)
		return cachedCost = COST + costForArrivalToBottom;
	else
		return cachedCost = INF;
}

bool isEndPoint(Board& board, int x, int y) {
	return board[x][y] == END;
}
