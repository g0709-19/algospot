/*
	보글 게임(완전 탐색)
	작성일: 2021년 8월 16일(월)
*/

#include <iostream>
#include <vector>

#define BOARD_SIZE	5

using namespace std;

typedef vector<vector<char>> GameBoard;

bool isStartFrom(GameBoard& gameBoard, int x, int y, string& word) {
	return gameBoard[x][y] == word[0];
}

string getRidofFirstCharacter(string& word) {
	return word.substr(1);
}

bool hasWord(GameBoard& gameBoard, int x, int y, string& word) {
	if (word.size() == 0) return true;
	if (x < 0 || y < 0) return false;
	if (!isStartFrom(gameBoard, x, y, word)) return false;
	string seperatedWord = getRidofFirstCharacter(word);
	for (int newX = x - 1; newX <= x + 1 && newX < BOARD_SIZE; ++newX) {
		for (int newY = y - 1; newY <= y + 1 && newY < BOARD_SIZE; ++newY) {
			if (newX == x && newY == y) continue;
			if (hasWord(gameBoard, newX, newY, seperatedWord))
				return true;
		}
	}
	return false;
}

bool findWord(GameBoard& gameBoard, string& word) {
	for (int x = 0; x < BOARD_SIZE; ++x) {
		for (int y = 0; y < BOARD_SIZE; ++y) {
			if (hasWord(gameBoard, x, y, word))
				return true;
		}
	}
	return false;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int C;
	cin >> C;
	while (C--) {
		GameBoard gameBoard(BOARD_SIZE, vector<char>(BOARD_SIZE));
		for (int i = 0; i < BOARD_SIZE; ++i)
			for (int j = 0; j < BOARD_SIZE; ++j)
				cin >> gameBoard[i][j];
		int N;
		cin >> N;
		while (N--) {
			string word;
			cin >> word;
			cout << word << " " << (findWord(gameBoard, word) ? "YES" : "NO");
			cout << '\n';
		}
	}
	return 0;
}
