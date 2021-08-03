/*
	록 페스티벌
	작성일: 2021년 8월 3일(화)
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int C;
	cin >> C;
	while (C--) {
		int N, L;
		cin >> N >> L;
		vector<int> cost(N);
		for (int i = 0; i < N; ++i)
			cin >> cost[i];
		double answer = -1.0;
		for (int i = L; i <= N; ++i) {
			int t = 0;
			while (t + i <= N) {
				int sum = 0;
				for (int j = 0; j < i; ++j)
					sum += cost[t + j];
				double temp = sum / (double)i;
				if (temp < answer || answer < 0.0) answer = temp;
				++t;
			}
		}
		cout << fixed;
		cout.precision(10);
		cout << answer << '\n';
	}
	return 0;
}

// O(N2), 기존 풀이는 아마 O(N3)
/*
	double answer = 1e20;
	for (int i = 0; i < N; ++i) {
		int sum = 0;
		int j, count = 1;
		for (j = i; j < L + i - 1 && j < N; ++j, ++count)
			sum += cost[j];
		for (; j < N; ++j, ++count) {
			sum += cost[j];
			double temp = sum / (double)count;
			if (temp < answer) answer = temp;
		}
	}
*/