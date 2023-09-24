#ifndef INC_3VRYAD_BOARD_H
#define INC_3VRYAD_BOARD_H
#include "bonus.h"
#include <iostream>
#include <vector>
#include <set>

class Board {
public:
    Board(int size = 5) {
        this->size = size;
        board_cells.resize(size, std::vector<Cell*>(size));
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                Cell* p = create_new_cell();
                std::swap(p, board_cells[x][y]);
            }
        }
    }
    ~Board() {
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                delete board_cells[x][y];
            }
        }
        board_cells.clear();
    }

    void print(std::pair<int, int> touch1, std::pair<int, int> touch2);
    void CheckDelete();
    void Gravity();
    void DrawBlackCells();
    void DeleteCells();
    void Activation();
    void ChangePlaces(std::pair<int, int> t1, std::pair<int, int> t2);
    std::set<std::pair<int, int>> to_delete;
    std::set<std::pair<int, int>> to_activate;

private:
    int size;
    Cell* create_new_cell();
    std::vector<std::vector<Cell*>> board_cells;
    void FindComp(std::pair<int, int> pair);
    void ActivateBomb(std::pair<int, int> pair);
    void ActivateBonus(std::pair<int, int> pair);

};




#endif 