/*
	문제: n개의 원소 중 m개를 고르는 모든 조합을 찾는 알고리즘을 재귀로 구현할 것
	작성일: 2021년 8월 15일(일)
*/

#include <iostream>
#include <vector>

using namespace std;

void printElements(vector<int>& elementsToPrint) {
	const int ELEMENT_SIZE = elementsToPrint.size();
	for (int i = 0; i < ELEMENT_SIZE; ++i)
		cout << elementsToPrint[i] << ' ';
	cout << '\n';
}

void printCombination(const int TOTAL_ELEMENT_AMOUNT, vector<int>& elementsToPrint, int remainedElement) {
	if (remainedElement == 0) {
		printElements(elementsToPrint);
		return;
	}

	int starting = elementsToPrint.size() == 0 ? 0 : elementsToPrint.back() + 1;

	for (int i = starting; i < TOTAL_ELEMENT_AMOUNT; ++i) {
		elementsToPrint.push_back(i);
		printCombination(TOTAL_ELEMENT_AMOUNT, elementsToPrint, remainedElement - 1);
		elementsToPrint.pop_back();
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> elementsToPrint;
	printCombination(n, elementsToPrint, m);
	return 0;
}