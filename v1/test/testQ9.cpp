#include "kpSolverGreedy.hpp"
#include "kpSolverGreedyFractional.hpp"
#include "kpSolverBB.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#define MAX_ITEM 10000

using namespace std;

// Fonction pour calculer le ratio valeur/poids moyen
double calculateAvgValueWeightRatio(const vector<int> &values, const vector<int> &weights) {
    double sumValueWeightRatio = 0.0;
    for (size_t i = 0; i < values.size(); ++i) {
        sumValueWeightRatio += static_cast<double>(values[i]) / weights[i];
    }
    return sumValueWeightRatio / values.size();
}

// Fonction pour calculer la densité (valeur totale / poids total)
double calculateDensity(const vector<int> &values, const vector<int> &weights) {
    int totalValue = 0;
    int totalWeight = 0;
    for (size_t i = 0; i < values.size(); ++i) {
        totalValue += values[i];
        totalWeight += weights[i];
    }
    return static_cast<double>(totalValue) / totalWeight;
}

// Fonction pour calculer la variance des poids
double calculateWeightVariance(const vector<int> &weights) {
    double meanWeight = 0.0;
    for (int weight : weights) {
        meanWeight += weight;
    }
    meanWeight /= weights.size();
    
    double variance = 0.0;
    for (int weight : weights) {
        variance += std::pow(weight - meanWeight, 2);
    }
    return variance / weights.size();
}

// Fonction pour calculer le taux de remplissage (totalWeight / M)
double calculateFillRate(const vector<int> &weights, int capacity) {
    int totalWeight = 0;
    for (int weight : weights) {
        totalWeight += weight;
    }
    return static_cast<double>(totalWeight) / capacity;
}

int main(int argc, char **argv) {
    vector<string> files {
        "../instances/kp_100_1.in",
        "../instances/kp_100_2.in",
        "../instances/kp_1000_1.in",
        "../instances/kp_1000_2.in",
        "../instances/kp_10000_1.in",
        "../instances/kp_10000_1_0.1.in",
        "../instances/kp_10000_1_0.01.in",
        "../instances/kp_10000_1_0.02.in",
        "../instances/kp_10000_1_0.03.in",
        "../instances/kp_10000_1_0.04.in",
        "../instances/kp_10000_1_0.05.in",
        "../instances/kp_10000_2.in",
        "../instances/kp_100000_1.in",
        "../instances/kp_100000_2.in"
    };

    ofstream outfile("../csv/resultatsQ9.csv", ios::out | ios::trunc);
    if (!outfile) {
        cerr << "Erreur à l'ouverture du fichier CSV !" << endl;
        return 1;
    }

    outfile << "Instance,Optimum,upperBound,lowerBound,gapGreedy,TempsGreedy,lowerBoundFractional,gapFractional,gapOptimumLower,gapOptimumLowerFractionalTempsGreedyFractional" << endl;

    for (const auto &file : files) {
        KpSolverGreedy kpGreedy;
        KpSolverGreedyFractional kpGreedyFractional;
        kpGreedy.importInstance(file.c_str());
        kpGreedyFractional.importInstance(file.c_str());

        auto start = chrono::steady_clock::now();
        kpGreedy.solve();
        auto end = chrono::steady_clock::now();
        chrono::duration<double> tempsGreedy = end - start;

        start = chrono::steady_clock::now();
        kpGreedyFractional.solve();
        end = chrono::steady_clock::now();
        chrono::duration<double> tempsGreedyFractional = end - start;

        
        float lowerBound = kpGreedy.getSolutionCost();
        float lowerBoundFractional = kpGreedyFractional.getSolutionCost();

        float upperBound = kpGreedy.getUpperBound();
        float upperBoundFractional = kpGreedyFractional.getUpperBound();

        float gapGreedy = (floor(kpGreedy.getUpperBound()) - (double)kpGreedy.getSolutionCost()) / ((double)kpGreedy.getSolutionCost()) * 100;
        float gapFractional = (floor(kpGreedyFractional.getUpperBound()) - (double)kpGreedyFractional.getSolutionCost()) / ((double)kpGreedyFractional.getSolutionCost()) * 100;
        float gapOptimumUpper = (floor(kpGreedyFractional.getUpperBound()) - (double)kpGreedyFractional.getSolutionCost()) / ((double)kpGreedyFractional.getSolutionCost()) * 100;

        outfile << file << "," << " " << "," << upperBound << "," << lowerBound << "," << gapGreedy << "," << tempsGreedy.count() << "," 
                << upperBoundFractional << "," << lowerBoundFractional << "," << gapFractional << "," << tempsGreedyFractional.count() << endl;
    }

    outfile.close();
    return 0;
}
