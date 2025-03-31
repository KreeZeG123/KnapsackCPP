//********* stopBB.hpp *********
#pragma once

#include "kpDefs.hpp"
#include <chrono>
#include <cmath>
#include <vector>

class StopCriterionBB {
public:
    virtual ~StopCriterionBB() = default;
    virtual bool continueBB(size_t nbNod, size_t nbNodMem, NodeManagement * nodes) = 0;
};

class MemLim : public StopCriterionBB {
private:
    size_t nbMaxNodeInMemory;

public:
    explicit MemLim(size_t n) : nbMaxNodeInMemory(n) {}
    bool continueBB(size_t nbNod, size_t nbNodMem, NodeManagement * nodes) override {
        return nbNodMem < nbMaxNodeInMemory;
    }
};

class NodeLim : public StopCriterionBB {
private:
    size_t nbMaxNodeBB;
    
public:
    explicit NodeLim(size_t n) : nbMaxNodeBB(n) {}
    bool continueBB(size_t nbNod, size_t nbNodMem, NodeManagement * nodes) override {
        return nbNod < nbMaxNodeBB;
    }
};

class AbsGapLim : public StopCriterionBB {
private:
    double absGap;

public:
    explicit AbsGapLim(double gap) : absGap(gap) {}
    bool continueBB(size_t nbNod, size_t nbNodMem, NodeManagement * nodes) override {
        double upperBound = nodes->getUpperBound();
        double lowerBound = nodes->getLowerBound();
        return (upperBound - lowerBound) > absGap;
    }
};

class RelGapLim : public StopCriterionBB {
private:
    double relGap;

public:
    explicit RelGapLim(double gap) : relGap(gap) {}
    bool continueBB(size_t nbNod, size_t nbNodMem, NodeManagement * nodes) override {
        double upperBound = nodes->getUpperBound();
        double lowerBound = nodes->getLowerBound();
        if (upperBound == 0) return false;

        double gap = (upperBound - lowerBound) / upperBound;
        return gap > relGap;
    }
};


class TimeLimit : public StopCriterionBB {
private:
    std::chrono::duration<double> limiteTemps;
    std::chrono::time_point<std::chrono::steady_clock> start;

public:
    explicit TimeLimit(std::chrono::duration<double> limite) 
        : limiteTemps(limite), start(std::chrono::steady_clock::now()) {}

    bool continueBB(size_t nbNod, size_t nbNodMem, NodeManagement* nodes) override {
        return (std::chrono::steady_clock::now() - start) < limiteTemps;
    }
};

class CombinedStopCriterion : public StopCriterionBB {
private:
    std::vector<StopCriterionBB*> criteria;

public:
    void addCriterion(StopCriterionBB* criterion) {
        criteria.push_back(criterion);
    }

    bool continueBB(size_t nbNod, size_t nbNodMem, NodeManagement * nodes) override {
        for (const auto& criterion : criteria) {
            if (!criterion->continueBB(nbNod, nbNodMem, nodes)) {
                return false; 
            }
        }
        return true;
    }
};
