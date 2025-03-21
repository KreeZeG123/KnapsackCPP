#include "kpSolverHeurDP.hpp"
#include <chrono>

using namespace std;

void testSolver( KpSolver * kp,  bool verboseMode = false){
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;


    //if (verboseMode) kp.printKnapsackInstance();

    start = std::chrono::steady_clock::now();
    kp->solve();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

    kp->printKnapsackSolution(verboseMode);
}

int main(int argc, char** argv){

    const char* instanceFile;
    string cheminDefaut =  "../instances/courseExample.in";
   // cheminDefaut ="../instances/kp_1000_2.in";
    cheminDefaut ="../instances/kp_10000_2.in";

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


    KpSolver * kp;

cout << "\ntest KpSolverGreedy :" <<endl;
    kp = new KpSolverGreedy(instanceFile);
    testSolver(kp);
    delete kp;

            cout << "\ntest KpSolverHeurDP (10,20):" <<endl;
    kp = new KpSolverHeurDP(instanceFile,10,20);
    testSolver(kp);
    delete kp;

            cout << "\ntest KpSolverHeurDP (50,50):" <<endl;
    kp = new KpSolverHeurDP(instanceFile,50,50);
    testSolver(kp);
    delete kp;

    cout << "\ntest KpSolverHeurDP basique (20, 60):" <<endl;
kp = new KpSolverHeurDP(instanceFile);
testSolver(kp);
delete kp;


        cout << "\ntest KpSolverHeurDP (50,100):" <<endl;
    kp = new KpSolverHeurDP(instanceFile,50,100);
    testSolver(kp);
    delete kp;



    return 0;
}
