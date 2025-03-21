#include <chrono>
#include "kpSolverDPsparseV2.hpp"
#include "kpSolverBB.hpp"


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
    kp.printKnapsackSolution(false);

}

//TODO:1 sortie sur une instance tous les calculs possibles par matrice et solverus differents

//TODO:calcul sur toutes les instances (sauf trop grandes), sortir tableau .csv avec temps de calculs et valeurs obtenues
// kp_10000_1_0.03.in a 10000 objets passe, pas l'instance originale



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
};
}

void testBBSolvers(const char* instanceFile){



    vector<BranchingStrategies> bStrategies = { BranchingStrategies::BestBound,  BranchingStrategies::DFS10, BranchingStrategies::DFS01}; // BranchingStrategies::BFS
    // BranchingStrategies::Random};


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


int main(int argc, char** argv){

    const char* instanceFile;
    string cheminDefaut =  "../instances/courseExample.in";
    cheminDefaut ="../instances/kp_100_2.in";
    //cheminDefaut ="../instances/kp_10000_1_0.1.in";

    if (argc < 2) {
        //cerr << "Usage: knapsack inputFile [heuristicMode] [verbosity]" << endl;
        //cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        //cerr << "A third parameter enable verbosity, useful for debugging" << endl;
        //return 1;

        instanceFile = cheminDefaut.c_str();

    }
    else     instanceFile = argv[1];


    //bool verboseMode = true;
    //if (argc < 3) verboseMode = false;
/*
    cout << "______________________________" <<endl
         << "Instance :" << cheminDefaut << endl
         << "______________________________" << endl;
*/

    testBBSolvers(instanceFile);

    return 0;
}
