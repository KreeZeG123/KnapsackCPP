#include "kpSolverGreedy.hpp"
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

    ofstream outfile("../csv/resultatQ4.csv", ios::out | ios::trunc);
    if (!outfile) {
        cerr << "Erreur à l'ouverture du fichier CSV !" << endl;
        return 1;
    }

    outfile << "Instance,N,M,Densite,VariancePoids,TauxRemplissage,TempsBB,OptimumBB" << endl;

    for (const auto &file : files) {
        KpSolverBB kpBB;
        
        kpBB.importInstance(file.c_str());
        
        int N = kpBB.getNbItems();

        if (N > MAX_ITEM) {
            kpBB.extractSubInstance(0,MAX_ITEM);
            N = kpBB.getNbItems();
        }

        int M = kpBB.getKnapsackBound();
        vector<int> values = kpBB.getValues();
        vector<int> weights = kpBB.getWeights();

        double density = calculateDensity(values, weights);
        double weightVariance = calculateWeightVariance(weights);
        double fillRate = calculateFillRate(weights, M);

        auto start = chrono::steady_clock::now();
        kpBB.solve();
        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        
        int optimalCost = kpBB.getSolutionCost();
        
        outfile << file << "," << N << "," << M << "," << density << "," << weightVariance << "," 
                << fillRate << "," << elapsed_seconds.count() << "," << optimalCost << endl;
    }

    outfile.close();
    return 0;
}
