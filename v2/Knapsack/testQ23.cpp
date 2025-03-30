#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include "kpSolverGreedy.hpp"
#include "kpSolverHeurDP.hpp"
#include "kpSolverBB.hpp"

using namespace std;

std::string name(  BranchingStrategies b){
    switch(b){
    case BranchingStrategies::BestBound:
        return "BestBound";
    case BranchingStrategies::Random:
        return "Random";
    case BranchingStrategies::DFS10:
         return "DFS10";
    case BranchingStrategies::DFS01:
        return "DFS01";/*
    case BranchingStrategies::BFS:
        return "BFS";*/
    default:
        throw std::invalid_argument( "testBB.cpp:29 : unexpected argurment for name()" );
    };
}

void testSolver(KpSolverBB & kp){
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    //if (verboseMode) kp.printKnapsackInstance();

    start = std::chrono::steady_clock::now();
    kp.solve();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
    std::cout << "number of BB nodes: " <<kp.getNbNodes()<< endl;
    //kp.printKnapsackSolution(false);

}


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

int main(int argc, char** argv) {
    vector<string> instanceFiles = genInstanceFilesList();

    vector<BranchingStrategies> bStrategies = { BranchingStrategies::BestBound,  BranchingStrategies::DFS10, BranchingStrategies::DFS01}; // BranchingStrategies::BFS
    // BranchingStrategies::Random};

    for (auto instanceFile : instanceFiles){

        cout << instanceFile <<endl;

        for(auto b : bStrategies){

            cout  << endl << "Mode de branchement : " << name(b)  << endl << endl;
            KpSolverBB kpBB (instanceFile,b);
            kpBB.setVerboseMode(0);

            cout  << "Resultats sans heuristique initiale:"  << endl << endl;
            kpBB.setInitialHeur(Heuristics::None);
            testSolver(kpBB);
            cout  << endl << "Resultats avec heuristique gloutonne initiale:"  << endl << endl;
            kpBB.setInitialHeur(Heuristics::Greedy);
            testSolver(kpBB);

            cout  << endl << "Resultats avec heuristique DP initiale:"  << endl << endl;
            kpBB.setInitialHeur(Heuristics::KernelSearch);
            testSolver(kpBB);

        }
    }
}
    