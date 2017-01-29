#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include <string>

class Constellation {
  public:
    Constellation(std::string _name);
    std::string name;
    int startDegree;
    int endDegree;
};

#endif
