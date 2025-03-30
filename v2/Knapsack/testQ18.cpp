#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include "kpSolverGreedy.hpp"
#include "kpSolverHeurDP.hpp"

using namespace std;

const vector<string> genInstanceFilesList() {
  vector<string> list;
  vector<string> nList;
  nList = {
    "00050","00100","00200","00500","01000"
  };
  for (auto & n : nList) {
    for (int i = 0; i < 25; i++) {
      stringstream ss;
      ss.width(3);
      ss.fill('0');
      ss << i;
      string s = ss.str();
      string path = "../../instances/00Uncorrelated/n" + n + "/R01000/s" + s + ".in";
      list.push_back(path);
    }
  }

  return list;
}

struct resultat_t {
  double costGlouton;
  double costKernel;
  double tempsGlouton;
  double tempsKernel;
};


int main(int argc, char** argv) {

  vector<string> instanceFiles = genInstanceFilesList();

  vector<resultat_t> resultats;
  for (auto & instanceFile : instanceFiles) {
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    // Test Glouton
    KpSolver * kpGlouton = new KpSolverGreedy(instanceFile);
    start = std::chrono::steady_clock::now();
    kpGlouton->solve();
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_glouton = end - start;

    // Test Kernel Search
    uint nbSelectedReopt;
    uint nbUnselectedReopt;
    KpSolver * kpKernel = new KpSolverHeurDP(instanceFile, 50, 50);
    start = std::chrono::steady_clock::now();
    kpKernel->solve();
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_kernel = end - start;

    // Initialisaiton du resultat
    resultat_t result;
    result.tempsGlouton = elapsed_seconds_glouton.count();
    result.tempsKernel = elapsed_seconds_kernel.count();
    result.costGlouton = kpGlouton->getSolutionCost();
    result.costKernel = kpKernel->getSolutionCost();

    resultats.push_back(result);
  }

  int nbFoisGloutonMeilleursTemps = 0;
  int nbFoisGloutonMeilleursValeurs = 0;
  int nbFoisKernelMeilleursTemps = 0;
  int nbFoisKernelMeilleursValeurs = 0;
  int nbFoisValeurKernelEtGloutonEgales = 0;
  for (auto & r : resultats) {
    if ( r.tempsGlouton < r.tempsKernel ) {
      nbFoisGloutonMeilleursTemps++;
    }
    else if ( r.tempsKernel < r.tempsGlouton ) {
      nbFoisKernelMeilleursTemps++;
    }

    if ( r.costGlouton > r.costKernel ) {
      nbFoisGloutonMeilleursValeurs++;
    } else if ( r.costKernel > r.costGlouton ) {
      nbFoisKernelMeilleursValeurs++;
    } else {
      nbFoisValeurKernelEtGloutonEgales++;
    }
  }

  cout << "==================================================" << endl;
  cout << "Nb Fois Glouton Meilleurs Que Kernel (Temps) : " << nbFoisGloutonMeilleursTemps << endl;
  cout << "Nb Fois Glouton Meilleurs Que Kernel (Valeurs) : " << nbFoisGloutonMeilleursValeurs << endl;
  cout << "Nb Fois Kernel Meilleurs Que Glouton (Temps) : " << nbFoisKernelMeilleursTemps << endl;
  cout << "Nb Fois Kernel Meilleurs Que Glouton (Valeurs) : " << nbFoisKernelMeilleursValeurs << endl;
  cout << "Nb Fois Valeurs Glouton Et Kernel Egales : " << nbFoisValeurKernelEtGloutonEgales << endl;

  return 0;
}