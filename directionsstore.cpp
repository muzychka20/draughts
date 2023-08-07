#include "directionsstore.h"

DirectionsStore::DirectionsStore() {
  this->directions = {{+1, -1}, {+1, +1}, {-1, -1}, {-1, +1}};
  this->dir1 = {{-1, -1}, {1, 1}};
  this->dir2 = {{-1, 1}, {1, -1}};
}
