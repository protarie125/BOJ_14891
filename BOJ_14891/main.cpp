#include <algorithm>
#include <bit>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using vs = vector<string>;

vs gs;
int k;

void rollRight(int g) {
	const auto& t = gs[g];
	gs[g] = t[7] + t.substr(0, 7);
}

void rollLeft(int g) {
	const auto& t = gs[g];
	gs[g] = t.substr(1) + t[0];
}

void roll(int g, int r) {
	auto doRoll = vector<pair<bool, int>>(4);
	doRoll[g] = { true, r };

	auto p = g;
	auto q = g - 1;
	while (0 <= q) {
		if (gs[p][6] != gs[q][2]) {
			doRoll[q] = { true, doRoll[p].second * -1 };
		}
		else {
			doRoll[q] = { false, 0 };
		}

		p = q;
		--q;
	}

	p = g;
	q = g + 1;
	while (q < 4) {
		if (gs[p][2] != gs[q][6]) {
			doRoll[q] = { true, doRoll[p].second * -1 };
		}
		else {
			doRoll[q] = { false, 0 };
		}

		p = q;
		++q;
	}

	for (auto i = 0; i < 4; ++i) {
		if (!doRoll[i].first) {
			continue;
		}

		if (1 == doRoll[i].second) {
			rollRight(i);
		}
		else if (-1 == doRoll[i].second) {
			rollLeft(i);
		}
	}
}

int calcPt() {
	auto ans = 0;
	for (auto i = 0; i < 4; ++i) {
		if ('1' == gs[i][0]) {
			ans += 1 << i;
		}
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	gs = vs(4);
	for (auto&& s : gs) {
		cin >> s;
	}

	cin >> k;
	while (0 < (k--)) {
		int g, r;
		cin >> g >> r;

		roll(g - 1, r);
	}

	cout << calcPt();

	return 0;
}