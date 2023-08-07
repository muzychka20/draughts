#ifndef DIRECTIONSSTORE_H
#define DIRECTIONSSTORE_H

#include <vector>

class DirectionsStore {
public:
  DirectionsStore();
  std::vector<std::pair<int, int>> directions;
  std::vector<std::pair<int, int>> dir1;
  std::vector<std::pair<int, int>> dir2;
  std::vector<std::pair<int, int>> d1;
  std::vector<std::pair<int, int>> d2;
  std::vector<std::pair<int, int>> d3;
  std::vector<std::pair<int, int>> d4;
  std::pair<int, int> dr;
};

#endif // DIRECTIONSSTORE_H
