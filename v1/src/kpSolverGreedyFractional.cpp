//********* knapsackGreedyFractional.cpp *********

#include "kpSolverGreedyFractional.hpp"


void KpSolverGreedyFractional::solveUpperBound() {

	upperBoundOPT=0;
    float remaining = knapsackBound;
    int id = 0;
    bool b = true;

    while(b &&remaining >0 && id < nbItems){
    	//cout << " Item: " << id << " Weight : " << weights[id]  << " Value : " << values[id] << " remaining : "<< remaining << endl;
    	if (weights[id] <= remaining) {
    		remaining -= weights[id];
    		upperBoundOPT += values[id];
    		id++;
    	}
    	else b = false;
	}

    if (id< nbItems && (!b)) upperBoundOPT += ((float) values[id])  * remaining /  ((float) weights[id]);

    //if (id< nbItems)  cout << " additional cost : " << ((float) values[id])  * remaining /  ((float) weights[id]) << endl;

 }

void KpSolverGreedyFractional::solveLowerBound() {

    solution.resize(nbItems);
    for (int i = 0; i < nbItems; i++)  solution[i]=false;

	costSolution=0;
	int remaining = knapsackBound;
    bool rempli = false;
    int i=0;

    while(i < nbItems && !rempli){
        if(weights[i] <= remaining){
            solution[i]=true;
            costSolution += values[i];
            remaining -= weights[i];
            i++;
        }else{
            rempli=true;
        }
    }
}

void KpSolverGreedyFractional::solve() {
	solveUpperBound();
	solveLowerBound();
}
