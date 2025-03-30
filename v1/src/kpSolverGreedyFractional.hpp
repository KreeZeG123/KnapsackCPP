//********* kpSolverGreedyFractional.hpp *********

#ifndef KPSOLVERGREEDYFRACTIONAL_HPP
#define KPSOLVERGREEDYFRACTIONAL_HPP

#include "kpSolver.hpp"

class  KpSolverGreedyFractional : public KpSolver {
public:

    void solveLowerBound();
    void solveUpperBound();
    void solve();


};


#endif
