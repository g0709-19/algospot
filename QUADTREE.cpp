/*
	쿼드 트리 뒤집기
	작성일: 2021년 9월 1일(수)
*/

#include <iostream>
#include <string>

#define COMPRESSED	'x'
#define WHITE		'w'
#define BLACK		'b'

#define shiftToNext(iterator) ++(iterator)

using namespace std;

string reverse(string::iterator& iterator) {
	char head = *iterator;
	shiftToNext(iterator);
	if (head == WHITE || head == BLACK)
		return string(1, head);
	else if (head == COMPRESSED) {
		string leftUp = reverse(iterator);
		string rightUp = reverse(iterator);
		string leftDown = reverse(iterator);
		string rightDown = reverse(iterator);
		string reversed = COMPRESSED + leftDown + rightDown + leftUp + rightUp;
		return reversed;
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int caseAmount;
	cin >> caseAmount;
	while (caseAmount--) {
		string toTest;
		cin >> toTest;
		string::iterator firstWord = toTest.begin();
		cout << reverse(firstWord) << '\n';
	}
	return 0;
}

