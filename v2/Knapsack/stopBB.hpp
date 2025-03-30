//********* stopBB.hpp *********

#pragma once

#include "kpDefs.hpp"
#include <chrono>


//TODO: rajouter limite de temps? epagap, eprgap,
class StopCriterionBB{

//protected:
//    KpSolver* kp;

public:
    virtual ~StopCriterionBB();
    virtual bool continueBB(size_t nbNod, size_t nbNodMem)=0;
};

/*
class MemLim : public StopCriterionBB {
private:
    size_t nbMaxNodeInMemory;

public:
    ~MemLim()=default;
     bool continueBB(size_t nbNod, size_t nbNodMem) override{return nbNodMem < nbMaxNodeInMemory ;};
     MemLim(size_t n): nbMaxNodeInMemory(n) {};
};

class NodeLim : public StopCriterionBB {
private:
    size_t nbMaxNodeBB;

public:
     bool continueBB(size_t nbNod, size_t nbNodMem) override{return nbNod < nbMaxNodeBB ;};
     NodeLim(size_t n): nbMaxNodeBB(n) {};
};
*/
/*
class NodeMemLim : public StopCriterionBB {
private:
    size_t nbMaxNodeBB;
    size_t nbMaxNodeInMemory;
public:
     bool continueBB(size_t nbNod, size_t nbNodMem) override{return nbNod < nbMaxNodeBB && nbNodMem < nbMaxNodeInMemory;};
     NodeMemLim(size_t n1,size_t n2): nbMaxNodeBB(n1),nbMaxNodeInMemory(n2) {};
};
*/

class TimeLimit : public StopCriterionBB {
    private:
        std::chrono::duration<double> limiteTemps;
    public:
         bool continueBB(std::chrono::duration<double> temps) override{return limiteTemps <  temps;};
         TimeLimit(std::chrono::duration<double> limite): limiteTemps(limite) {};
    };

class RelativeCode : public StopCriterionBB {
    private:
        float limGapPourcentage;
    public:
            bool continueBB(double upperBound, double lowerBound) override{return lowerBound/upperBound <= limGapPourcentage;};
            RelativeCode(float g): limGapPourcentage(g) {};
    };

class AbsoluteCode : public StopCriterionBB {
    private:
        float limGapAbsolute;
    public:
            bool continueBB(double upperBound, double lowerBound) override{return upperBound-lowerBound <= limGapAbsolute;};
            AbsoluteCode(float g): limGapAbsolute(g) {};
    };
