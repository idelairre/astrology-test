#ifndef ASTROLOGY_H
#define ASTROLOGY_H

#include "constellation.h"
#include <functional>
#include <string>
#include <vector>
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 360);
auto genDegree = std::bind(distribution, generator);

struct Aspect {
  std::string type;
  int angle;
  int orb;
  Aspect(std::string type, int angle, int orb = 5) : type(type), angle(angle), orb(orb) { };
};

struct Planet {
  std::string name;
  int degree;
  int speed;
  int x;
  int y;
  // std::vector<Aspect> aspects;
  Planet(std::string name, int x = 0, int y = 0, int speed = 0) : name(name), x(x), y(y), speed(speed) {
    degree = genDegree();
  };
} Mercury("Mercury"), Venus("Venus"), Earth("Earth"), Mars("Mars"), Jupiter("Jupiter");

struct Point {
  int x;
  int y;
  int degree;
  Point(int x, int y, int degree) : x(x), y(y), degree(degree) { };
};

struct Sky {
  std::vector<Constellation> constellations;
  std::vector<Planet> planets = { Mercury, Venus, Earth, Mars, Jupiter };
  int degsPerSign;
} sky;

std::vector<Aspect> AspectsArray = {
  Aspect("conjunction", 0, 12),
  Aspect("sextile", 60, 5),
  Aspect("square", 90, 8)
};

class Astrology {
  public:
    static Sky ASky;
};

#endif
