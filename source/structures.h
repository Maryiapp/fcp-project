#ifndef POINT_H
#define POINT_H

/**
 * @file point.h
 * @brief Defines the Point structure.
 */

#include <vector>

 /**
  * @struct Point
  * @brief Represents a data point in multidimensional space.
  */
struct Point {

    /// Coordinates of the point
    std::vector<double> coords;

    /// Cluster assignment
    int cluster = -1;
};

#endif
