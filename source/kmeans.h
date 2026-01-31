#ifndef KMEANS_H
#define KMEANS_H

/**
 * @file kmeans.h
 * @brief Declaration of KMeans class.
 */

#include <vector>
#include <string>
#include "point.h"

using namespace std;

/**
 * @struct Centroid
 * @brief Represents a centroid in K-Means clustering.
 */
struct Centroid {
    /// Coordinates of centroid
    vector<double> coords;
};

/**
 * @class KMeans
 * @brief Implements the K-Means clustering algorithm.
 *
 * This class loads data, performs clustering,
 * and saves the results to a file.
 */
class KMeans {
public:

    /**
     * @brief Constructor.
     * @param k Number of clusters.
     */
    KMeans(int k);

    /**
     * @brief Loads dataset from CSV file.
     * @param filename Path to input file.
     */
    void loadData(const string& filename);

    /**
     * @brief Runs the clustering algorithm.
     */
    void run();

    /**
     * @brief Saves clustering results to file.
     * @param filename Path to output file.
     */
    void saveResults(const string& filename);

private:
    int k; ///< Number of clusters
    int dimensions = 0; ///< Number of features (dimensions)

    vector<Point> points; ///< Dataset points
    vector<Centroid> centroids; ///< Cluster centroids

    /// Initializes centroids randomly
    void initCentroids();

    /// Assigns each point to nearest centroid
    void assignClusters();

    /// Updates centroid positions
    void updateCentroids();

    /**
     * @brief Computes squared Euclidean distance.
     */
    double distance(const Point& p, const Centroid& c);

    /**
     * @brief Checks convergence condition.
     * @param oldCentroids Previous centroid positions
     * @param tol Tolerance threshold
     * @return true if converged
     */
    bool hasConverged(const vector<Centroid>& oldCentroids, double tol);
};

#endif

