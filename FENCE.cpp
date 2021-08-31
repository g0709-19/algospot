/*
	울타리 잘라내기
	작성일: 2021년 9월 1일(수)
*/

#include <iostream>
#include <vector>

#define max(x, y) ((x) > (y)) ? (x) : (y)

using namespace std;

typedef vector<int> Fence;

int findWhereShortestFence(Fence& fences, int from, int to) {
	int shortestFence = from;
	for (int i = from + 1; i <= to; ++i)
		if (fences[shortestFence] > fences[i])
			shortestFence = i;
	return shortestFence;
}

int getAreaByFence(Fence& fences, int fenceLocation) {
	int shorterInLeft = fenceLocation - 1;
	int shorterInRight = fenceLocation + 1;
	while (shorterInLeft >= 0 && fences[shorterInLeft] >= fences[fenceLocation])
		--shorterInLeft;
	int size = fences.size();
	while (shorterInRight < size && fences[shorterInRight] >= fences[fenceLocation])
		++shorterInRight;
	return (shorterInRight - shorterInLeft - 1) * fences[fenceLocation];
}

vector<bool> visited;

int getBiggestRectangle(Fence& fences, int from, int to) {
	if (from > to) return 0;
	int shortestFence = findWhereShortestFence(fences, from, to);
	if (visited[shortestFence]) return 0;
	visited[shortestFence] = 1;
	int area = getAreaByFence(fences, shortestFence);
	int leftArea = getBiggestRectangle(fences, from, shortestFence - 1);
	int rightArea = getBiggestRectangle(fences, shortestFence + 1, to);
	return max(area, max(leftArea, rightArea));
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int caseAmount;
	cin >> caseAmount;
	while (caseAmount--) {
		int fenceAmount;
		cin >> fenceAmount;
		Fence fence(fenceAmount);
		visited = vector<bool>(fenceAmount);
		for (int i = 0; i < fenceAmount; ++i)
			cin >> fence[i];
		cout << getBiggestRectangle(fence, 0, fenceAmount - 1) << '\n';
	}
	return 0;
}
