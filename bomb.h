#include <ctime>
#include "element.h"

class bomb : public Cell {
public:
	bomb() :Cell() {
		radius = (rand() + time(NULL)) % 3 + 1;
	}
	virtual void PrintCell(int x, int y, bool frame);
	int GetRadius() {
		return this->radius;
	}
private:
	int radius;
};