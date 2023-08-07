#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include <QPushButton>
#include <vector>

class Board {

public:
  Board();
  int mapSize = 8;
  int cellSize = 80;
  std::vector<std::vector<int>> map;
  std::vector<std::vector<QString>> mapOfSymbols;
  void SetFiguresOnBoard();
  void FillMap();
  QList<QList<QPushButton *>> buttonsOnBoard;
};

#endif // BOARD_H
