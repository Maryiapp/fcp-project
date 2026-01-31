/**
 * @file kmeans.cpp
 * @brief Implementation of KMeans class.
 */

#include "kmeans.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/**
 * @brief Constructor implementation.
 */
KMeans::KMeans(int k) : k(k) {}

/**
 * @brief Loads dataset from CSV file.
 */
void KMeans::loadData(const string& filename) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open input file: " << filename << "\n";
        exit(1);
    }

    string line;
    bool firstLine = true;

    while (getline(file, line)) {

        if (line.empty()) continue;

        if (firstLine) {
            firstLine = false;
            continue;
        }

        stringstream ss(line);
        string token;
        Point p;

        for (int i = 0; i < 4; i++) {
            if (!getline(ss, token, ',')) break;
            p.coords.push_back(stod(token));
        }

        if (points.empty())
            dimensions = p.coords.size();

        if (p.coords.size() == dimensions)
            points.push_back(p);
    }

    file.close();

    cout << "Loaded points: " << points.size() << "\n";
    cout << "Detected dimensions: " << dimensions << "\n";

    initCentroids();
}

/**
 * @brief Randomly initializes centroids.
 */
void KMeans::initCentroids() {

    if (points.size() < k) {
        cout << "Error: k > number of points\n";
        exit(1);
    }

    centroids.resize(k);

    for (int i = 0; i < k; i++) {
        int index = rand() % points.size();
        centroids[i].coords = points[index].coords;
    }
}

/**
 * @brief Computes squared Euclidean distance.
 */
double KMeans::distance(const Point& p, const Centroid& c) {

    double sum = 0.0;

    for (size_t i = 0; i < p.coords.size(); i++) {
        double diff = p.coords[i] - c.coords[i];
        sum += diff * diff;
    }

    return sum;
}

/**
 * @brief Assigns each point to the nearest centroid.
 */
void KMeans::assignClusters() {

    for (auto& p : points) {

        double bestDist = distance(p, centroids[0]);
        int bestCluster = 0;

        for (int i = 1; i < k; i++) {
            double d = distance(p, centroids[i]);
            if (d < bestDist) {
                bestDist = d;
                bestCluster = i;
            }
        }

        p.cluster = bestCluster;
    }
}

/**
 * @brief Updates centroid coordinates.
 */
void KMeans::updateCentroids() {

    vector<int> counts(k, 0);
    vector<vector<double>> newCoords(k, vector<double>(dimensions, 0.0));

    for (const auto& p : points) {

        int c = p.cluster;
        counts[c]++;

        for (int j = 0; j < dimensions; j++)
            newCoords[c][j] += p.coords[j];
    }

    for (int i = 0; i < k; i++) {

        if (counts[i] == 0) continue;

        for (int j = 0; j < dimensions; j++)
            centroids[i].coords[j] = newCoords[i][j] / counts[i];
    }
}

/**
 * @brief Checks if centroids have converged.
 */
bool KMeans::hasConverged(const vector<Centroid>& oldCentroids, double tol) {

    for (int i = 0; i < k; i++) {

        double dist = 0;

        for (int j = 0; j < dimensions; j++) {
            double diff = centroids[i].coords[j] - oldCentroids[i].coords[j];
            dist += diff * diff;
        }

        if (dist > tol)
            return false;
    }

    return true;
}

/**
 * @brief Executes the K-Means algorithm.
 */
void KMeans::run() {

    const int maxIter = 100;
    const double tol = 1e-4;

    for (int iter = 0; iter < maxIter; iter++) {

        vector<Centroid> oldCentroids = centroids;

        assignClusters();
        updateCentroids();

        if (hasConverged(oldCentroids, tol)) {
            cout << "Converged after " << iter + 1 << " iterations\n";
            break;
        }
    }
}

/**
 * @brief Saves clustering results to output file.
 */
void KMeans::saveResults(const string& filename) {

    ofstream out(filename);

    if (!out.is_open()) {
        cout << "Cannot open output file: " << filename << "\n";
        return;
    }

    out << "K-Means Clustering\nCentroids:\n";

    for (int i = 0; i < k; i++) {
        out << "Centroid " << i << ": ";
        for (double v : centroids[i].coords)
            out << v << " ";
        out << "\n";
    }

    out << "\nPoints and clusters:\n";

    for (size_t i = 0; i < points.size(); i++) {

        out << "Point " << i << ": (";

        for (size_t j = 0; j < points[i].coords.size(); j++) {
            out << points[i].coords[j];
            if (j + 1 < points[i].coords.size())
                out << ", ";
        }

        out << ") -> cluster " << points[i].cluster << "\n";
    }

    out.close();
}
