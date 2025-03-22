#include "kpSolverDP.hpp"
#include "kpSolverDPsparseV2.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>

// Fonction pour calculer le temps d'exécution d'un solveur
double testSolver(KpSolver* kp) {
    auto start = std::chrono::steady_clock::now();
    kp->solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    return elapsed_seconds.count();  // Retourner le temps de calcul en secondes
}

std::unique_ptr<KpSolver> createSolver(const std::string& instanceFile, const std::string& solverType) {
  MatDPType matType = MatDPType::MatDPtab;

  if (solverType == "KpSolverDPv0") {
    return std::make_unique<KpSolverDPv0>(instanceFile, matType);
  }
  else if (solverType == "KpSolverDPv1") {
      return std::make_unique<KpSolverDPv1>(instanceFile, matType);
  } 
  else if (solverType == "KpSolverDPv1bis") {
      return std::make_unique<KpSolverDPv1bis>(instanceFile, matType);
  }
  else if (solverType == "KpSolverDPv2") {
    return std::make_unique<KpSolverDPv2>(instanceFile, matType);
  }
  else if (solverType == "kpSolverDPsparseV2") {
    return std::make_unique<kpSolverDPsparseV2>(instanceFile);
  }
  else {
      throw std::invalid_argument("Unknown solver type");
  }
}


// Comparer deux solveurs sur une liste d'instances
void compareTwoSolvers(const vector<string>& instanceFiles, string solverType1, string solverType2) {
    double totalIndicatorSolver1 = 0.0;
    double totalIndicatorSolver2 = 0.0;
    int significantlyBetterCountSolver1 = 0;
    int significantlyBetterCountSolver2 = 0;

    // Parcourir toutes les instances et comparer les deux solveurs
    for (const auto& instanceFile : instanceFiles) {
        cout << "Testing solvers on instance: " << instanceFile << endl;

        // Créer une nouvelle instance du solveur pour chaque nouvelle instance de test
        auto solver1 = createSolver(instanceFile, solverType1);
        auto solver2 = createSolver(instanceFile, solverType2);

        // Mesurer les temps de calcul pour les deux solveurs
        double timeSolver1 = testSolver(solver1.get());
        double timeSolver2 = testSolver(solver2.get());

        // Calcul du meilleur temps parmi les deux solveurs
        double bestTime = std::min(timeSolver1, timeSolver2);

        // Calcul des indicateurs (ratios) pour chaque solveur
        double indicatorSolver1 = timeSolver1 / bestTime;
        double indicatorSolver2 = timeSolver2 / bestTime;
        
        totalIndicatorSolver1 += indicatorSolver1;
        totalIndicatorSolver2 += indicatorSolver2;

        // Comptabiliser les instances où l'écart de temps est significatif (> 10%)
        if (timeSolver1 < 0.9 * timeSolver2) {
          significantlyBetterCountSolver1++;
        }
        if (timeSolver2 < 0.9 * timeSolver1) {
            significantlyBetterCountSolver2++;
        }
    }

    // Calcul des moyennes des indicateurs pour les deux solveurs
    double averageIndicatorSolver1 = totalIndicatorSolver1 / instanceFiles.size();
    double averageIndicatorSolver2 = totalIndicatorSolver2 / instanceFiles.size();

    // Affichage des résultats pour les deux solveurs
    cout << "Results for Solver 1 (" << solverType1 << "):" << endl;
    cout << "Average Indicator: " << averageIndicatorSolver1 << endl;
    cout << "Number of instances where Solver 1 was significantly better: " << significantlyBetterCountSolver1 << endl;

    cout << "Results for Solver 2 (" << solverType2 << "):" << endl;
    cout << "Average Indicator: " << averageIndicatorSolver2 << endl;
    cout << "Number of instances where Solver 2 was significantly better: " << significantlyBetterCountSolver2 << endl;
}

// Fonction principale pour comparer les solveurs
int main(int argc, char** argv) {
    vector<string> instanceFiles;

    instanceFiles = {
      "../instances/kp_100_1.in",
      "../instances/kp_100_2.in",
      "../instances/kp_1000_1.in",
      "../instances/kp_1000_2.in"
    };

    // Vérifier si des fichiers d'instances sont passés en argument
    if (argc < 3) {
        printf("testQ11 <solver1> <solver2> :\n");
        printf(" - KpSolverDPv0\n - KpSolverDPv1\n - KpSolverDPv1bis\n - KpSolverDPv2\n");
        return 1;
    }

    string typeSolver1 = argv[1];
    string typeSolver2 = argv[2];

    // Choisir les types de solveurs à comparer (par exemple, v1 et v2)
    MatDPType type1 = MatDPType::MatDPvectVect; // Type du premier solveur
    MatDPType type2 = MatDPType::MatDPvect;     // Type du deuxième solveur

    // Comparer les deux solveurs avec les types choisis
    compareTwoSolvers(instanceFiles, typeSolver1, typeSolver2);

    return 0;
}
