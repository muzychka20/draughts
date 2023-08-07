#include "queen.h"
#include "AdditionalFunctions.h"
#include <algorithm>

Queen::Queen() {}

void Queen::CheckStrikeFigure(int sizeOfMap, int currentPLayer,
                              std::vector<std::vector<int>> map) {
  std::vector<std::pair<int, int>> oneVariantOfStrikeQueen;
  possibleStrikes.clear();
  possibleStrikesQueenTemp.clear();
  bool is;
  for (int i = 0; i < sizeOfMap; i++) {
    for (int j = 0; j < sizeOfMap; j++) {
      if (map[i][j] == currentPLayer + 2) {
        oneVariantOfStrikeQueen.push_back({i, j});
        for (auto &move : directionsStock.directions) {
          int dx = move.second, dy = move.first, ti = i, tj = j;
          is = true;
          while (isInBoard(ti + dy, tj + dx, sizeOfMap) && is) {
            if (isInBoard(ti + dy, tj + dx, sizeOfMap) &&
                isInBoard(ti + 2 * dy, tj + 2 * dx, sizeOfMap) &&
                (map[ti + dy][tj + dx] == (currentPLayer == 1 ? 2 : 1) ||
                 map[ti + dy][tj + dx] == (currentPLayer == 1 ? 4 : 3)) &&
                !map[ti + 2 * dy][tj + 2 * dx]) {
              ti += 2 * dy;
              tj += 2 * dx;
              while (isInBoard(ti, tj, sizeOfMap) && !map[ti][tj]) {
                oneVariantOfStrikeQueen.push_back({ti, tj});
                ti += dy;
                tj += dx;
              }
            }
            ti += dy;
            tj += dx;
            if (isInBoard(ti, tj, sizeOfMap) && map[ti][tj])
              is = false;
          }
        }
        if (oneVariantOfStrikeQueen.size() == 1)
          oneVariantOfStrikeQueen.clear();
        else
          possibleStrikesQueenTemp.push_back(oneVariantOfStrikeQueen);
        oneVariantOfStrikeQueen.clear();
      }
    }
  }
  DeleteExtraStrikesQueen(sizeOfMap, currentPLayer, map);
}

void Queen::DeleteExtraStrikesQueen(int sizeOfMap, int currentPLayer,
                                    std::vector<std::vector<int>> map) {
  std::vector<std::pair<int, int>> strikes;
  bool is;
  for (auto &diagonal : possibleStrikesQueenTemp) {
    directionsStock.d1.push_back(diagonal[0]);
    directionsStock.d2.push_back(diagonal[0]);
    directionsStock.d3.push_back(diagonal[0]);
    directionsStock.d4.push_back(diagonal[0]);
    for (int i = 1; i < (int)diagonal.size(); i++) {
      if (diagonal[0].first > diagonal[i].first &&
          diagonal[0].second > diagonal[i].second) {
        directionsStock.d1.push_back({diagonal[i].first, diagonal[i].second});
      } else if (diagonal[0].first > diagonal[i].first &&
                 diagonal[0].second < diagonal[i].second) {
        directionsStock.d2.push_back({diagonal[i].first, diagonal[i].second});
      } else if (diagonal[0].first < diagonal[i].first &&
                 diagonal[0].second > diagonal[i].second) {
        directionsStock.d3.push_back({diagonal[i].first, diagonal[i].second});
      } else if (diagonal[0].first < diagonal[i].first &&
                 diagonal[0].second < diagonal[i].second) {
        directionsStock.d4.push_back({diagonal[i].first, diagonal[i].second});
      }
    }

    if (directionsStock.d1.size() > 1)
      possibleStrikes.push_back(directionsStock.d1);
    directionsStock.d1.clear();

    if (directionsStock.d2.size() > 1)
      possibleStrikes.push_back(directionsStock.d2);
    directionsStock.d2.clear();

    if (directionsStock.d3.size() > 1)
      possibleStrikes.push_back(directionsStock.d3);
    directionsStock.d3.clear();

    if (directionsStock.d4.size() > 1)
      possibleStrikes.push_back(directionsStock.d4);
    directionsStock.d4.clear();
  }

  for (auto &line : possibleStrikes) {
    strikes.clear();
    strikes.push_back(line[0]);
    for (int index = 1; index < (int)line.size(); index++) {
      int i = line[index].first, j = line[index].second;

      int queenI = line[0].first, queenJ = line[0].second;
      if ((queenI > i && queenJ < j) || (queenI < i && queenJ > j)) {
        for (auto &move : directionsStock.dir1) {
          int dx = move.second, dy = move.first, ti = i, tj = j;
          is = true;
          while (isInBoard(ti + dy, tj + dx, sizeOfMap) && is) {
            if (isInBoard(ti + dy, tj + dx, sizeOfMap) &&
                isInBoard(ti + 2 * dy, tj + 2 * dx, sizeOfMap) &&
                (map[ti + dy][tj + dx] == (currentPLayer == 1 ? 2 : 1) ||
                 map[ti + dy][tj + dx] == (currentPLayer == 1 ? 4 : 3)) &&
                !map[ti + 2 * dy][tj + 2 * dx]) {
              strikes.push_back(line[index]);
              break;
            }
            ti += dy;
            tj += dx;
            if (isInBoard(ti, tj, sizeOfMap) && map[ti][tj])
              is = false;
          }
        }

      } else if ((queenI > i && queenJ > j) || (queenI < i && queenJ < j)) {
        for (auto &move : directionsStock.dir2) {
          int dx = move.second, dy = move.first;
          int ti = i;
          int tj = j;
          is = true;
          while (isInBoard(ti + dy, tj + dx, sizeOfMap) && is) {
            if (isInBoard(ti + dy, tj + dx, sizeOfMap) &&
                isInBoard(ti + 2 * dy, tj + 2 * dx, sizeOfMap) &&
                (map[ti + dy][tj + dx] == (currentPLayer == 1 ? 2 : 1) ||
                 map[ti + dy][tj + dx] == (currentPLayer == 1 ? 4 : 3)) &&
                !map[ti + 2 * dy][tj + 2 * dx]) {
              strikes.push_back(line[index]);
              break;
            }
            ti += dy;
            tj += dx;
            if (isInBoard(ti, tj, sizeOfMap) && map[ti][tj])
              is = false;
          }
        }
      }
    }
    if (strikes.size() != 1) {
      for (int count = 0; count < (int)strikes.size(); count++) {
        for (auto &place : line) {
          if (NotIn(strikes, {place.first, place.second}) && place != line[0]) {
            // delete
            auto it = std::remove(line.begin(), line.end(), place);
            line.erase(it, line.end());
          }
        }
      }
    }
  }
}

bool Queen::CheckContinueStrike(int pi, int pj, int sizeOfMap,
                                int currentPLayer,
                                std::vector<std::vector<int>> map,
                                std::vector<std::pair<int, int>> pass,
                                std::pair<int, int> dr) {
  strikesForOne.clear();
  for (int i = 0; i < sizeOfMap; i++) {
    for (int j = 0; j < sizeOfMap; j++) {
      if (i == pi && j == pj) {
        for (auto &move : directionsStock.directions) {
          int dx = move.second, dy = move.first, ti = i, tj = j;
          bool is = true;
          if (!SameCell(dr.first, dr.second, dy, dx)) {
            while (isInBoard(ti + dy, tj + dx, sizeOfMap) && is) {
              if (isInBoard(ti + dy, tj + dx, sizeOfMap) &&
                  isInBoard(ti + 2 * dy, tj + 2 * dx, sizeOfMap) &&
                  (map[ti + dy][tj + dx] == (currentPLayer == 1 ? 2 : 1) ||
                   map[ti + dy][tj + dx] == (currentPLayer == 1 ? 4 : 3)) &&
                  !map[ti + 2 * dy][tj + 2 * dx] &&
                  NotIn(pass, {ti + dy, tj + dx})) {
                ti += 2 * dy;
                tj += 2 * dx;
                while (isInBoard(ti, tj, sizeOfMap) && !map[ti][tj]) {
                  strikesForOne.push_back({ti, tj});
                  ti += dy;
                  tj += dx;
                }
              }
              ti += dy;
              tj += dx;
              if (isInBoard(ti, tj, sizeOfMap) && map[ti][tj])
                is = false;
            }
          }
        }
      }
    }
  }
  SplitIntoDirections(pi, pj);
  strikesForOne.clear();
  for (auto &row : strikesForOneNewFormat) {
    std::vector<std::pair<int, int>> strikes;
    for (auto &element : row) {
      int i = element.first, j = element.second, queenI = pi, queenJ = pj;
      if ((queenI > i && queenJ < j) || (queenI < i && queenJ > j)) {
        CheckLineForNextStrike(map, directionsStock.dir1, element, &strikes,
                               pass, sizeOfMap, currentPLayer, i, j);
      } else if ((queenI > i && queenJ > j) || (queenI < i && queenJ < j)) {
        CheckLineForNextStrike(map, directionsStock.dir2, element, &strikes,
                               pass, sizeOfMap, currentPLayer, i, j);
      }
    }
    if (!strikes.empty()) {
      for (int count = 0; count < (int)strikes.size(); count++) {
        for (auto &place : row) {
          if (NotIn(strikes, {place.first, place.second})) {
            // delete
            auto it = std::remove(row.begin(), row.end(), place);
            row.erase(it, row.end());
          }
        }
      }
    }
    for (auto &index : row)
      strikesForOne.push_back(index);
  }
  return strikesForOne.empty() ? false : true;
}

void Queen::CheckLineForNextStrike(std::vector<std::vector<int>> map,
                                   std::vector<std::pair<int, int>> dir,
                                   std::pair<int, int> element,
                                   std::vector<std::pair<int, int>> *strikes,
                                   std::vector<std::pair<int, int>> pass,
                                   int sizeOfMap, int currentPLayer, int ti,
                                   int tj) {
  for (auto &move : dir) {
    int dx = move.second, dy = move.first;
    bool is = true;
    while (isInBoard(ti + dy, tj + dx, sizeOfMap) && is) {
      if (isInBoard(ti + dy, tj + dx, sizeOfMap) &&
          isInBoard(ti + 2 * dy, tj + 2 * dx, sizeOfMap) &&
          (map[ti + dy][tj + dx] == (currentPLayer == 1 ? 2 : 1) ||
           map[ti + dy][tj + dx] == (currentPLayer == 1 ? 4 : 3)) &&
          !map[ti + 2 * dy][tj + 2 * dx] && NotIn(pass, {ti + dy, tj + dx})) {
        strikes->push_back(element);
        break;
      }
      ti += dy;
      tj += dx;
      if (isInBoard(ti, tj, sizeOfMap) && map[ti][tj])
        is = false;
    }
  }
}

void Queen::SplitIntoDirections(int pi, int pj) {
  strikesForOneNewFormat.clear();
  directionsStock.d1.clear();
  directionsStock.d2.clear();
  directionsStock.d3.clear();
  directionsStock.d4.clear();
  for (auto &diagonal : strikesForOne) {

    if (pi > diagonal.first && pj > diagonal.second) {
      directionsStock.d1.push_back({diagonal.first, diagonal.second});
    } else if (pi > diagonal.first && pj < diagonal.second) {
      directionsStock.d2.push_back({diagonal.first, diagonal.second});
    } else if (pi < diagonal.first && pj > diagonal.second) {
      directionsStock.d3.push_back({diagonal.first, diagonal.second});
    } else if (pi < diagonal.first && pj < diagonal.second) {
      directionsStock.d4.push_back({diagonal.first, diagonal.second});
    }
  }
  if (directionsStock.d1.size())
    strikesForOneNewFormat.push_back(directionsStock.d1);
  directionsStock.d1.clear();
  if (directionsStock.d2.size())
    strikesForOneNewFormat.push_back(directionsStock.d2);
  directionsStock.d2.clear();
  if (directionsStock.d3.size())
    strikesForOneNewFormat.push_back(directionsStock.d3);
  directionsStock.d3.clear();
  if (directionsStock.d4.size())
    strikesForOneNewFormat.push_back(directionsStock.d4);
  directionsStock.d4.clear();
}
