#ifndef INC_3VRYAD_ELEMENT_H
#define INC_3VRYAD_ELEMENT_H

#include <cmath>
#include <iostream>
#include <vector>


enum class Color {
    forest_green,
    dark_blue,
    lilac,
    blue_green,
    baby_blue,
    black
};

class Cell {
public:
    Cell() :color{ rand() % 5 } {
        board_size = 5;
    }
    virtual void PrintCell(int x, int y, bool frame);
    void ChangeColor(Color color) {
        this->color = color;
    }
    Color GetColor() {
        return this->color;
    }

    virtual int GetRadius() {
        return 0;
    }

    virtual std::vector<std::vector<int> > GetToChange() {
        std::vector<std::vector<int> > f;
        return f;
    }

protected:
    int board_size;
private:
    void color_analysis();
    Color color;
};


#endif 