#include <vector>
#include <iostream>
#include <chrono>

using namespace std;
constexpr int pcount = 200000;
vector<vector<float>> phash;
vector<float> phash2;

int main() {
	srand(static_cast <unsigned> (time(0)));
	auto start = chrono::steady_clock::now();
	phash.resize(pcount);
	phash2.resize(pcount);
	for (int i = 0; i < pcount; ++i) {
		phash[i].resize(42);
		for (int h = 0; h < 42; ++h) {
			phash[i][h] = rand() / static_cast <float> (RAND_MAX) * 10;
			phash2[i] += phash[i][h];
		}
	}
	cout << "Generated hash in: "
		<< chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count()
		<< " ms" << endl;
	start = chrono::steady_clock::now();
	float min_dist = 100000000;
	int best_i = 0;
	for (int i = 1; i < pcount; ++i) {
		//if (abs(phash2[0] - phash2[i]) > 200) continue;
		float dist = 0;
		for (int h = 0; h < 42; ++h) {
			dist += pow(phash[0][h] - phash[i][h], 2);
			//if (dist > min_dist) break;
		}
		//dist = pow(dist, 0.5);
		if (dist < min_dist) {
			min_dist = dist;
			best_i = i;
		}
	}
	cout << "Best i " << best_i << " with dist " << pow(min_dist, 0.5) << ": " << phash2[0] << "/" << phash2[best_i] << endl;
	cout << "Best i in: "
		<< chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count()
		<< " ms" << endl;
}
