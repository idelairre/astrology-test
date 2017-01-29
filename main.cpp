#include "constellation.h"
#include "astrology.h"
#include <iostream>
#include <math.h>
#include <ctime>

int angle(int x1, int x2, int y1, int y2) {
  float angle = atan2(y1 - y2, x1 - x2);
  int degree = (angle * 180) / M_PI;
  return abs(degree);
}

int angle(Point& point1, Point& point2) {
  return angle(point1.y, point2.y, point1.x, point2.x);
}

int angle(Planet& planet1, Planet& planet2) {
  return angle(planet1.y, planet1.y, planet1.x, planet2.x);
}

std::vector<Point> getSkyCircumferencePoints(int radius) {
  int xCenter = 0;
  int yCenter = 0;
  int x, y;
  std::vector<Point> points;
  for (int i = 0; i < 360; i++) {
    y = radius * cos(i);
    x = radius * sin(i);
    Point point(xCenter + x, yCenter + y, i);
    points.push_back(point);
  }
  return points;
}

void calculateDegrees(Sky &sky) {
  sky.degsPerSign = (360 / sky.constellations.size());
  std::cout << "symbolic degrees " << sky.degsPerSign;
}

void checkAspect(Point point1, Point point2) {
  int degree = angle(point1, point2);
  for (int i = 0; i < AspectsArray.size(); i++) {
    Aspect aspect = AspectsArray[i];
    if (aspect.angle - aspect.orb <= degree && aspect.angle + aspect.orb >= degree) {
      std::cout << aspect.type << "\n";
    }
  }
}

void checkAspect(Planet planet1, Planet planet2) {
  int degree = angle(planet1, planet2);
  std::cout << degree << "\n";
  for (int i = 0; i < AspectsArray.size(); i++) {
    Aspect aspect = AspectsArray[i];
    if (aspect.angle - aspect.orb <= degree && aspect.angle + aspect.orb >= degree) {
      std::cout << degree << "\n";
      std::cout << aspect.type << " between " << planet1.name << " and " << planet2.name << "\n";
    }
  }
}

int main() {
  Sky sky;
  Constellation *pisces = new Constellation("pisces");
  Constellation *aries = new Constellation("aries");
  sky.constellations.push_back(*pisces);
  sky.constellations.push_back(*aries);

  // for (int i = 0; i < sky.planets.size(); i++) {
  //   std::cout << "\n";
  //   std::cout << sky.planets[i].degree;
  // }

  calculateDegrees(sky);
  std::vector<Point> points = getSkyCircumferencePoints(18);

  // put planets in a random position along sky circumference

  for (int i = 0; i < sky.planets.size(); i++) {
    srand(i + time(NULL));

    int index = rand() % points.size();
    std::cout << index << "\n";

    Planet planet = sky.planets[i];
    Point point = points[index];
    planet.x = point.x;
    planet.y = point.y;
    sky.planets[i] = planet;
  }

  for (int i = 0; i < sky.planets.size(); i++) {
    Planet planet1 = sky.planets[i];
    if (i + 1 < sky.planets.size()) {
      Planet planet2 = sky.planets[i + 1];
      std::cout << "\n";
      std::cout << planet1.x << ", " << planet1.y << "\n";
      std::cout << planet2.x << ", " << planet2.y << "\n";
      checkAspect(planet1, planet2);
    }
  }

  return 0;
}
