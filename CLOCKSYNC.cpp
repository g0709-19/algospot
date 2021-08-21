/*
	Synchronizing Clocks
	작성일: 2021년 8월 20일(금)
*/

#include <iostream>
#include <vector>

#define CLOCK_AMOUNT		16
#define SWITCH_AMOUNT		10
#define TWELVE_CLOCK		3
#define TIME_TYPE_AMOUNT	4
#define INF					99999

#define FOR(i, from, n) for (int i=(from), LIMIT=(n); i<LIMIT; ++i)
#define min(first, second) first <= second ? first : second;

using namespace std;

typedef int Time[CLOCK_AMOUNT];
typedef const vector<vector<int>> Switch;

Switch SWITCH_WITH_LINKED_CLOCK = {
	{0, 1, 2},
	{3, 7, 9, 11},
	{4, 10, 14, 15},
	{0, 4, 5, 6, 7},
	{6, 7, 8, 10, 12},
	{0, 2, 14, 15},
	{3, 14, 15},
	{4, 5, 7, 14, 15},
	{1, 2, 3, 4, 5},
	{3, 4, 5, 9, 13}
};

void setTimeByKeyboard(Time& time) {
	FOR(i, 0, CLOCK_AMOUNT) {
		int temp;
		cin >> temp;
		time[i] = temp / 3 - 1;
	}
}

void clickSwitch(Time& clockTime, int switchIndex) {
	FOR(i, 0, SWITCH_WITH_LINKED_CLOCK[switchIndex].size()) {
		int clockIndex = SWITCH_WITH_LINKED_CLOCK[switchIndex][i];
		clockTime[clockIndex] += 1;
		clockTime[clockIndex] %= TIME_TYPE_AMOUNT;
	}
}

bool checkAllTwelveClock(Time& time) {
	FOR(clock, 0, CLOCK_AMOUNT)
		if (time[clock] != TWELVE_CLOCK) {
			return false;
		}
	return true;
}

int getMinCount(Time& clockTime, int switchIndex) {
	if (switchIndex == SWITCH_AMOUNT)
		return checkAllTwelveClock(clockTime) ? 0 : INF;

	int minCount = INF;
	FOR(clickCount, 0, TIME_TYPE_AMOUNT) {
		minCount = min(minCount, clickCount + getMinCount(clockTime, switchIndex + 1));
		clickSwitch(clockTime, switchIndex);
	}
	return minCount;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int C;
	cin >> C;
	while (C--) {
		Time time;
		setTimeByKeyboard(time);
		int minCount = getMinCount(time, 0);
		cout << (minCount == INF ? -1 : minCount) << '\n';
	}
	return 0;
}
