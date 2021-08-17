/*
	소풍
	작성일: 2021년 8월 17일(화)
*/

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<bool>> Graph;
typedef vector<bool> Paired;

int n = 0;

int countPairCase(const Graph& graph, Paired paired) {
	int toPair = -1;
	for (int i = 0; i < n; ++i)
		if (!paired[i]) {
			toPair = i;
			break;
		}
	if (toPair == -1) return 1;
	int caseCount = 0;
	for (int i = toPair + 1; i < n; ++i) {
		if (graph[toPair][i] && !paired[i]) {
			paired[toPair] = paired[i] = true;
			caseCount += countPairCase(graph, paired);
			paired[toPair] = paired[i] = false;
		}
	}
	return caseCount;
}

void linkNodeByKeyboard(Graph& graph) {
	int from, to;
	cin >> from >> to;
	graph[from][to] = 1;
	graph[to][from] = 1;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int C;
	cin >> C;
	while (C--) {
		int m;
		cin >> n >> m;
		Graph graph(n, vector<bool>(n));
		Paired paired = vector<bool>(n);
		for (int i = 0; i < m; ++i)
			linkNodeByKeyboard(graph);
		cout << countPairCase(graph, paired) << '\n';
	}
	return 0;
}
