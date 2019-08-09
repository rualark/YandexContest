#include <iostream>
#include <vector>

using namespace std;

int main() {
	std::vector <bool> v(2);
	v[0] = true;
	v[1] = false;
	std::cout << v[0] << v[1] << std::endl;
	std::swap(v[0], v[1]);
	std::cout << v[0] << v[1] << std::endl;
	return 0;
}