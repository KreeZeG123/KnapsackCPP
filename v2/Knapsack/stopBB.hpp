//********* stopBB.hpp *********

#pragma once

#include "kpDefs.hpp"
#include <chrono>
#include <cmath>

class StopCriterionBB {
public:
    virtual ~StopCriterionBB() {}
    virtual bool continueBB(size_t nbNod, size_t nbNodMem, double lowerBound = 0, double upperBound  = 0, std::chrono::duration<double> temps = std::chrono::duration<double>::zero())= 0;
};

class MemLim : public StopCriterionBB {
private:
    size_t nbMaxNodeInMemory;

public:
    MemLim(size_t n) : nbMaxNodeInMemory(n) {}
    bool continueBB(size_t nbNod, size_t nbNodMem, double lowerBound, double upperBound, std::chrono::duration<double> temps) override {
        return nbNodMem < nbMaxNodeInMemory;
    }
};

class NodeLim : public StopCriterionBB {
private:
    size_t nbMaxNodeBB;

public:
    NodeLim(size_t n) : nbMaxNodeBB(n) {}
    bool continueBB(size_t nbNod, size_t nbNodMem, double lowerBound, double upperBound, std::chrono::duration<double> temps) override {
        return nbNod < nbMaxNodeBB;
    }
};

class AbsGapLim : public StopCriterionBB {
private:
    double absGap;

public:
    AbsGapLim(double gap) : absGap(gap) {}
    bool continueBB(size_t nbNod, size_t nbNodMem, double lowerBound, double upperBound, std::chrono::duration<double> temps) override {
        return (upperBound - lowerBound) > absGap;
    }
};

class RelGapLim : public StopCriterionBB {
private:
    double relGap;

public:
    RelGapLim(double gap) : relGap(gap) {}
    bool continueBB(size_t nbNod, size_t nbNodMem, double lowerBound, double upperBound, std::chrono::duration<double> temps) override {
        if (upperBound == 0) return false;
        double gap = (upperBound - lowerBound) / upperBound;
        return gap > relGap;
    }
};

class TimeLimit : public StopCriterionBB {
    private:
        std::chrono::duration<double> limiteTemps;
    public:
        bool continueBB(size_t nbNod, size_t nbNodMem, double lowerBound, double upperBound, std::chrono::duration<double> temps) override{return limiteTemps <  temps;};
        TimeLimit(std::chrono::duration<double> limite): limiteTemps(limite) {};
    };

class CombinedStopCriterion : public StopCriterionBB {
private:
    std::vector<StopCriterionBB*> criteria;

public:
    void addCriterion(StopCriterionBB* criterion) {
        criteria.push_back(criterion);
    }

    bool continueBB(size_t nbNod, size_t nbNodMem, double lowerBound, double upperBound, std::chrono::duration<double> temps) override {
        for (auto& criterion : criteria) {
            if (!criterion->continueBB(nbNod, nbNodMem, lowerBound, upperBound, temps)) {
                return false; 
            }
        }
        return true;
    }
};
