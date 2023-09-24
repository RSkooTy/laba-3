#include "board.h"
#include <set>
#include <queue>
#include<iostream>
#include <algorithm>
#define x first
#define y second

void Board::FindComp(std::pair<int, int> pair) {
    std::set<std::pair<int, int>>visited;
    std::queue<std::pair<int, int>>tovisit;
    std::pair<int, int>curr = pair;
    tovisit.push(curr);
    Color color = board_cells[pair.x][pair.y]->GetColor();
    while (!tovisit.empty()) {
        curr = tovisit.front();
        tovisit.pop();
        if (curr.x < 0 or curr.y < 0 or curr.x >= size or curr.y >= size) {
            continue;
        }
        if (color != board_cells[curr.x][curr.y]->GetColor()) {
            continue;
        }
        if (visited.find(curr) != visited.end()) {
            continue;
        }
        visited.insert(curr);
        tovisit.push({ curr.x + 1, curr.y });
        tovisit.push({ curr.x - 1, curr.y });
        tovisit.push({ curr.x, curr.y + 1 });
        tovisit.push({ curr.x, curr.y - 1 });
    }
 
    if (visited.size() > 2) {
        for (auto u : visited) {
            to_delete.insert(u);
        }
    }
}

void Board::Gravity() {
    for (int y = size - 2; y >= 0; y--) {
        for (int x = 0; x < size; x++) {
            int ycurr = y;
            while (ycurr < size - 1 && board_cells[x][ycurr]->GetColor() != Color::black &&
                board_cells[x][ycurr + 1]->GetColor() == Color::black) {
                std::swap(board_cells[x][ycurr], board_cells[x][ycurr + 1]);
                ycurr++;
            }
        }
    }
}

Cell* Board::create_new_cell() {
    Cell* p;
    int chance = (rand() + time(NULL)) % 100;
    if (chance < 2) {
        p = new bomb;
        return p;
    }

    if (chance < 4) {
        p = new bonus;
        return p;
    }

    p = new Cell;
    return p;
}

void Board::print(std::pair<int, int> touch1, std::pair<int, int> touch2) {
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            std::pair<int, int> t = { x, y };
            if (touch1 == t || touch2 == t) {
                board_cells[x][y]->PrintCell(x, y, true);
            }
            else {
                board_cells[x][y]->PrintCell(x, y, false);
            }

        }


}

void Board::CheckDelete() {
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++)
            if (to_delete.find({ x, y }) == to_delete.end()) {
                FindComp({ x, y });
            }
}

void Board::DrawBlackCells() {
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++)
            if (board_cells[x][y]->GetColor() == Color::black) {
                Cell* rand = create_new_cell();
                std::swap(rand, board_cells[x][y]);
                delete rand;
            }
}

void Board::DeleteCells() {
    for (auto u : to_delete) {
        Cell p;
        if (typeid(*board_cells[u.first][u.second]).name() != typeid(p).name()) {
            to_activate.insert(u);
        }
        else {
            board_cells[u.first][u.second]->ChangeColor(Color::black);
        }
    }
    to_delete.clear();
}

void Board::Activation() {
    for (auto u : to_activate) {
        bomb p;
        if (typeid(*board_cells[u.first][u.second]).name() == typeid(p).name()) {
            ActivateBomb(u);
        }
        else {
            ActivateBonus(u);
        }
        board_cells[u.first][u.second]->ChangeColor(Color::black);
    }
    to_activate.clear();
}

void Board::ActivateBonus(std::pair<int, int> pair) {
    std::vector<std::vector<int> > m = board_cells[pair.x][pair.y]->GetToChange();
    if (m.empty()) return;
    int count = 0;
    for (int i = 0; i < 2; i++) {
        int u = m[i][0];
        int v = m[i][1];
        if (pair.first + u >= 0 && pair.first + u < size
            && pair.second + v >= 0 && pair.second + v < size
            && board_cells[pair.first + u][pair.second + v]->GetColor() != Color::black && count < 2) {
            count++;
            board_cells[pair.first + u][pair.second + v]->ChangeColor(board_cells[pair.first][pair.second]->GetColor());
        }
    }
}

void Board::ActivateBomb(std::pair<int, int> pair) {
    int radius = board_cells[pair.x][pair.y]->GetRadius();
    for (int r = 1; r <= radius; r++) {
        for (int u = 0; u <= r; u++) {
            int v = r - u;
            int m[2] = { -1, 1 };
            for (auto i : m)
                for (auto j : m) {
                    if (pair.first + i * u >= 0 && pair.first + i * u < size
                        && pair.second + j * v >= 0 && pair.second + j * v < size
                        && board_cells[pair.first + i * u][pair.second + j * v]->GetColor() != Color::black) {
                        to_delete.insert({ pair.first + i * u, pair.second + j * v });
                    }
                }


        }
    }
}

void Board::ChangePlaces(std::pair<int, int> t1, std::pair<int, int> t2) {
    if (abs(t1.first - t2.first) + abs(t1.second - t2.second) == 1) {
        std::swap(board_cells[t1.first][t1.second], board_cells[t2.first][t2.second]);
    }
}