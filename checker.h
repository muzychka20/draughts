#ifndef CHECKER_H
#define CHECKER_H

#include "directionsstore.h"

class Checker {
public:
  DirectionsStore directionsStock;

  void setType(int t);
  int getType();
  void DefineType(int position);

  int startPositionX;
  int startPositionY;
  int endPositionX;
  int endPositionY;

  void SetEndPostion(int y, int x);
  void SetStartPostion(int y, int x);

  std::vector<std::pair<int, int>> possibleMoves;
  std::vector<std::pair<int, int>> possibleMovesIndex;
  void fillPossibleMoves();

  virtual void CheckStrikeFigure(int sizeOfMap, int currentPLayer,
                                 std::vector<std::vector<int>> map);
  std::vector<std::vector<std::pair<int, int>>> possibleStrikes;

  virtual bool CheckContinueStrike(int i, int j, int sizeOfMap,
                                   int currentPLayer,
                                   std::vector<std::vector<int>> map,
                                   std::vector<std::pair<int, int>> pass,
                                   std::pair<int, int> dr);
  std::vector<std::pair<int, int>> strikesForOne;

private:
  int type;
};

#endif // CHECKER_H
