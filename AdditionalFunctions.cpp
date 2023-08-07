#include "AdditionalFunctions.h"

bool isInBoard(int pi, int pj, int sizeOfMap) {
  return (pi >= sizeOfMap || pj >= sizeOfMap || pi < 0 || pj < 0) ? false
                                                                  : true;
}

bool SameCell(int i, int j, int y, int x) {
  return (i == y && x == j) ? true : false;
}

bool NotIn(std::vector<std::pair<int, int>> v, std::pair<int, int> p) {
  for (auto &i : v)
    if (i.first == p.first && i.second == p.second)
      return false;
  return true;
}

void TurnMove(int *currentPlayer, QLabel *currentPlayerLabel) {
  if (*currentPlayer == 1) {
    *currentPlayer = 2;
    currentPlayerLabel->setText("Current player: Black");
  } else if (*currentPlayer == 2) {
    *currentPlayer = 1;
    currentPlayerLabel->setText("Current player: White");
  }
}

void RemoveCheckers(std::vector<std::pair<int, int>> &pass,
                    std::vector<std::vector<int>> &map) {
  for (auto &p : pass)
    map[p.first][p.second] = 0;
  pass.clear();
}

void Swap(std::vector<std::vector<int>> &map, int i, int j, int y, int x) {
  int t = map[i][j];
  map[i][j] = map[y][x];
  map[y][x] = t;
}
