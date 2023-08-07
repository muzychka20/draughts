#ifndef QUEEN_H
#define QUEEN_H

#include "checker.h"
#include "directionsstore.h"

class Queen : public Checker {
public:
  Queen();
  DirectionsStore directionsStock;
  void CheckStrikeFigure(int sizeOfMap, int currentPLayer,
                         std::vector<std::vector<int>> map) override;
  bool CheckContinueStrike(int i, int j, int sizeOfMap, int currentPLayer,
                           std::vector<std::vector<int>> map,
                           std::vector<std::pair<int, int>> pass,
                           std::pair<int, int> dr) override;

private:
  std::vector<std::vector<std::pair<int, int>>> possibleStrikesQueenTemp;
  std::vector<std::vector<std::pair<int, int>>> strikesForOneNewFormat;
  void DeleteExtraStrikesQueen(int sizeOfMap, int currentPLayer,
                               std::vector<std::vector<int>> map);
  void CheckLineForNextStrike(std::vector<std::vector<int>> map,
                              std::vector<std::pair<int, int>> dir,
                              std::pair<int, int> element,
                              std::vector<std::pair<int, int>> *strikes,
                              std::vector<std::pair<int, int>> pass,
                              int sizeOfMap, int currentPLayer, int ti, int tj);
  void SplitIntoDirections(int pi, int pj);
};

#endif // QUEEN_H
