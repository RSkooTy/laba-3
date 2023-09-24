#include <ctime>
#include <vector>
#include "bomb.h"

class bonus : public Cell {
public:
	bonus() :Cell() {
		mix();
	}
	virtual void PrintCell(int x, int y, bool frame);

	std::vector<std::vector<int> > GetToChange() {
		std::vector<std::vector<int> > to_change(2, std::vector<int>(2));
		to_change[0][0] = opt[0][0];
		to_change[1][0] = opt[1][0];
		to_change[0][1] = opt[0][1];
		to_change[1][1] = opt[1][1];
		return to_change;
	}

private:
	int opt[4][2] = { {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };
	int to_change[2][2];
	void mix() {
		for (int i = 0; i < 4; i++) {
			int r = (rand() + time(NULL)) % 4;
			std::swap(opt[i], opt[r]);
		}
	}
};