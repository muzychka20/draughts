#include "checker.h"
#include "AdditionalFunctions.h"

void Checker::setType(int t) { this->type = t; }

int Checker::getType() { return this->type; }

void Checker::DefineType(int position) {
  switch (position) {
  case 1:
    setType(1);
    break;
  case 2:
    setType(2);
    break;
  case 3:
    setType(3);
    break;
  case 4:
    setType(4);
    break;
  default:
    setType(0);
  }
}

void Checker::SetEndPostion(int y, int x) {
  this->endPositionX = x;
  this->endPositionY = y;
}

void Checker::SetStartPostion(int y, int x) {
  this->startPositionX = x;
  this->startPositionY = y;
}

void Checker::fillPossibleMoves() {
  if (type == 1) {
    possibleMoves = {{-1, -1}, {-1, +1}};
  } else if (type == 2) {
    possibleMoves = {{+1, -1}, {+1, +1}};
  } else if (type == 3 || type == 4) {
    possibleMoves = {{+1, -1}, {+1, +1}, {-1, -1}, {-1, +1}};
  }
}

void Checker::CheckStrikeFigure(int sizeOfMap, int currentPLayer,
                                std::vector<std::vector<int>> map) {
  std::vector<std::pair<int, int>> oneVariantOfStrike;
  possibleStrikes.clear();
  for (int i = 0; i < sizeOfMap; i++) {
    for (int j = 0; j < sizeOfMap; j++) {
      oneVariantOfStrike.push_back({i, j});
      for (auto move : directionsStock.directions) {
        int dx = move.second, dy = move.first;
        if (isInBoard(i + dy, j + dx, sizeOfMap) &&
            isInBoard(i + 2 * dy, j + 2 * dx, sizeOfMap) &&
            (map[i][j] == currentPLayer || map[i][j] == currentPLayer + 2) &&
            (map[i + dy][j + dx] == (currentPLayer == 1 ? 2 : 1) ||
             map[i + dy][j + dx] == (currentPLayer == 1 ? 4 : 3)) &&
            !map[i + 2 * dy][j + 2 * dx]) {
          oneVariantOfStrike.push_back({i + 2 * dy, j + 2 * dx});
        }
      }
      if (oneVariantOfStrike.size() == 1) {
        oneVariantOfStrike.clear();
      } else {
        possibleStrikes.push_back(oneVariantOfStrike);
      }
      oneVariantOfStrike.clear();
    }
  }
}

bool Checker::CheckContinueStrike(int i, int j, int sizeOfMap,
                                  int currentPLayer,
                                  std::vector<std::vector<int>> map,
                                  std::vector<std::pair<int, int>> pass,
                                  std::pair<int, int> dr) {
  strikesForOne.clear();
  for (auto move : directionsStock.directions) {
    int dx = move.second, dy = move.first;
    if (isInBoard(i + dy, j + dx, sizeOfMap) &&
        isInBoard(i + 2 * dy, j + 2 * dx, sizeOfMap) &&
        NotIn(pass, {i + dy, j + dx}) &&
        (map[i][j] == currentPLayer || map[i][j] == currentPLayer + 2) &&
        (map[i + dy][j + dx] == (currentPLayer == 1 ? 2 : 1) ||
         map[i + dy][j + dx] == (currentPLayer == 1 ? 4 : 3)) &&
        !map[i + 2 * dy][j + 2 * dx]) {
      strikesForOne.push_back({i + 2 * dy, j + 2 * dx});
    }
  }
  return strikesForOne.empty() ? false : true;
}
