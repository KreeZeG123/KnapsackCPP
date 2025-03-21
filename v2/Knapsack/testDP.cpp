#include <chrono>
#include "kpSolverDP.hpp"
#include "kpSolverHeurDP.hpp"
#include "kpSolverDPsparseV2.hpp"


void testSolver(std::string const &instanceFile, bool verboseMode, MatDPType matrixType){
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    KpSolverDPv2 kp(instanceFile,matrixType);
    //KpSolverDPv1bis kp(instanceFile,matrixType);
    //KpSolverDPv1 kp(instanceFile,matrixType);
    //KpSolverDPv0 kp(instanceFile,matrixType);

    //if (verboseMode) kp.printKnapsackInstance();
    cout << endl
         << "Dynamic Programming with matrix of type " << tostring(matrixType) << " :" << endl
         << endl;
    start = std::chrono::steady_clock::now();
    kp.solve();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

    kp.printKnapsackSolution(verboseMode);
    //if (verboseMode) kp.printFirstLineDP();
    if (verboseMode) kp.printMatrixDP();
}


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

//TODO:1 sortie sur une instance tous les calculs possibles par matrice et solverus differents

//TODO:calcul sur toutes les instances (sauf trop grandes), sortir tableau .csv avec temps de calculs et valeurs obtenues
// kp_10000_1_0.03.in a 10000 objets passe, pas l'instance originale

void testDPSolvers(std::string const &instanceFile)
{

    vector<MatDPType> v = {
        //MatDPType::MatDPvectVect,
        //MatDPType::MatDPvect,
        //MatDPType::MatDPtabTab,
        MatDPType::MatDPtab
    };

    KpSolver * kp;

    for(auto matrixType : v){

        cout << endl
             << "DP v0 with matrix of type " << tostring(matrixType) << " :" << endl
             << endl;
        kp = new KpSolverDPv0(instanceFile,matrixType);
        testSolver( kp);
        delete kp;

        cout << endl
             << "DP v1 with matrix of type " << tostring(matrixType) << " :" << endl
             << endl;
        kp = new KpSolverDPv1(instanceFile,matrixType);
        testSolver( kp);
        delete kp;

        cout << endl
             << "DP v1bis with matrix of type " << tostring(matrixType) << " :" << endl
             << endl;
        kp = new KpSolverDPv1bis(instanceFile,matrixType);
        testSolver( kp);
        delete kp;

        cout << endl
             << "DP v2 with matrix of type " << tostring(matrixType) << " :" << endl
             << endl;
        kp = new KpSolverDPv2(instanceFile,matrixType);
        testSolver( kp);
        delete kp;

    }


    //KpSolverDP * kpDP;

    cout << "\ntest kpSolverDPsparseV2 :" <<endl;


    kp = new kpSolverDPsparseV2(instanceFile);
    testSolver(kp);
    delete kp;


    cout << "\ntest KpSolverGreedy :" <<endl;
    kp = new KpSolverGreedy(instanceFile);
    testSolver(kp);
    delete kp;

    cout << "\ntest KpSolverHeurDP :" <<endl;
    kp = new KpSolverHeurDP(instanceFile);
    testSolver(kp);
    delete kp;


/*
    cout << "\ntest KpSolverDPv2 :" <<endl;

    kpDP = new KpSolverDPv2(instanceFile);
    testSolver(kpDP);
    //kpDP->printMatrixDP();
    delete kpDP;

    cout << "\ntest KpSolverDP2 :" <<endl;

    kp = new KpSolverDP2(instanceFile);
    testSolver(kp);
    delete kp;
*/


}

int main(int argc, char** argv){

    const char* instanceFile;
    string cheminDefaut =  "../instances/courseExample.in";
    cheminDefaut ="../instances/kp_1000_2.in";
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

    testDPSolvers(instanceFile);

/*
    kp = new KpSolverHeurDP(instanceFile,10,10);
    testSolver(kp);
    delete kp;

    kp = new KpSolverHeurDP(instanceFile);
    testSolver(kp);
    delete kp;
*/

/*
    //testDP(instanceFile, verboseMode);
    testDP(instanceFile, verboseMode,MatDPType::MatDPtabTab);
    testDP(instanceFile, verboseMode, MatDPType::MatDPvectVect);
    testDP(instanceFile, verboseMode,MatDPType::MatDPvect);
    testDP(instanceFile, verboseMode,MatDPType::MatDPtab);

    cheminDefaut = "../instances/kp_100_1.in";
    instanceFile = cheminDefaut.c_str();

    cout << "______________________________" <<endl
         << "Instance :" << cheminDefaut << endl
         << "______________________________" << endl;

    testDP(instanceFile, verboseMode,MatDPType::MatDPtabTab);
    testDP(instanceFile, verboseMode, MatDPType::MatDPvectVect);
    testDP(instanceFile, verboseMode,MatDPType::MatDPvect);
    testDP(instanceFile, verynamique peuvent être utilisées pour trouver des solutions optimales ou proches de l'optimal.




    cheminDefaut = "../instances/kp_100_2.in";
    instanceFile = cheminDefaut.c_str();
    cout << "______________________________" <<endl
         << "Instance :" << cheminDefaut << endl
         << "______________________________" << endl;

    testDP(instanceFile, verboseMode,MatDPType::MatDPtabTab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPtab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPvect);
    testDP(instanceFile, verboseMode, MatDPType::MatDPvectVect);

    cheminDefaut = "../instances/kp_1000_1.in";
    instanceFile = cheminDefaut.c_str();

    cout << "______________________________" <<endl
         << "Instance :" << cheminDefaut << endl
         << "______________________________" << endl;

    testDP(instanceFile, verboseMode,MatDPType::MatDPtabTab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPtab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPvect);
    testDP(instanceFile, verboseMode, MatDPType::MatDPvectVect);


    cheminDefaut = "../instances/kp_1000_2.in";
    instanceFile = cheminDefaut.c_str();
    cout << "______________________________" <<endl
         << "Instance :" << cheminDefaut << endl
         << "______________________________" << endl;

    testDP(instanceFile, verboseMode,MatDPType::MatDPtabTab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPtab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPvect);
    testDP(instanceFile, verboseMode, MatDPType::MatDPvectVect);
*/
    return 0;
}
