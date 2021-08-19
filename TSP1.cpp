/*
	Traveling Salesman Problem 1
	작성일: 2021년 8월 19일(목)
*/

#include <iostream>
#include <vector>

#define FOR(i, from, n) for (int i=(from), LIMIT=(n); i<LIMIT; ++i)
#define min(first, second) first <= second ? first : second;

using namespace std;

typedef vector<vector<double>> Distance;
typedef vector<bool> Visit;

int startNode = 0;

Visit visited;

double findFastestRouteDistance(Distance & distance, int toTraverse, int remains) {
	if (remains == 0)
		return 0.0;
	visited[toTraverse] = true;
	double minDistance = 123456789.0;
	FOR(i, 0, distance.size()) {
		if (visited[i]) continue;
		double temp = distance[toTraverse][i] + findFastestRouteDistance(distance, i, remains - 1);
		minDistance = min(minDistance, temp);
	}
	visited[toTraverse] = false;
	return minDistance;
}

void setDistanceForNByKeyboard(Distance & distance, int n) {
	FOR(i, 0, n)
		FOR(j, 0, n)
			cin >> distance[i][j];
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int C;
	cin >> C;
	while (C--) {
		int N;
		cin >> N;
		Distance distance = vector<vector<double>>(N, vector<double>(N));
		visited = vector<bool>(N);
		setDistanceForNByKeyboard(distance, N);
		
		double fastestDistance = 1e20;
		for (startNode = 0; startNode < N; ++startNode)
			fastestDistance = min(fastestDistance, findFastestRouteDistance(distance, startNode, N - 1));
		
		cout << fixed;
		cout.precision(10);
		cout << fastestDistance << '\n';
	}
	return 0;
}
