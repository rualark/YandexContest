#include <atomic>

using namespace std;

int main() {
	atomic<int> ai;
	ai.store(1);
}
