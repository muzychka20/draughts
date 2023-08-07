#ifndef ADDITIONALFUNCTIONS_H
#define ADDITIONALFUNCTIONS_H

#include <QLabel>
#include <vector>

bool isInBoard(int pi, int pj, int sizeOfMap);
bool SameCell(int i, int j, int x, int y);
bool NotIn(std::vector<std::pair<int, int>> v, std::pair<int, int> p);
void TurnMove(int *currentPlayer, QLabel *currentPlayerLabel);
void RemoveCheckers(std::vector<std::pair<int, int>> &pass,
                    std::vector<std::vector<int>> &map);
void Swap(std::vector<std::vector<int>> &map, int i, int j, int y, int x);

#endif // ADDITIONALFUNCTIONS_H
