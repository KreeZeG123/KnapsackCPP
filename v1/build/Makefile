all: testProgDyn testHeur testIterHeur testBB testQ4 testQ8 testQ9

testQ9: KpSolver.o KpSolverDP.o NodeBB.o KpSolverHeurDP.o KpSolverGreedy.o KpSolverBB.o KpSolverGreedyFractional.o ../test/testQ9.cpp
	g++ -O3 -W -I../src KpSolver.o KpSolverDP.o KpSolverGreedy.o NodeBB.o KpSolverHeurDP.o KpSolverBB.o KpSolverGreedyFractional.o ../test/testQ9.cpp -o testQ9

testQ8: KpSolver.o KpSolverDP.o NodeBB.o KpSolverHeurDP.o KpSolverGreedy.o KpSolverBB.o KpSolverGreedyFractional.o ../test/testQ8.cpp
	g++ -O3 -W -I../src KpSolver.o KpSolverDP.o KpSolverGreedy.o NodeBB.o KpSolverHeurDP.o KpSolverBB.o KpSolverGreedyFractional.o ../test/testQ8.cpp -o testQ8

testQ4: KpSolver.o KpSolverDP.o NodeBB.o KpSolverHeurDP.o KpSolverGreedy.o KpSolverBB.o ../test/testQ4.cpp
	g++ -O3 -W -I../src KpSolver.o KpSolverDP.o KpSolverGreedy.o NodeBB.o KpSolverHeurDP.o KpSolverBB.o ../test/testQ4.cpp -o testQ4
	
testBB: KpSolver.o KpSolverDP.o NodeBB.o KpSolverHeurDP.o KpSolverGreedy.o KpSolverBB.o ../test/testBB.cpp
	g++ -O3 -W -I../src KpSolver.o KpSolverDP.o KpSolverGreedy.o NodeBB.o KpSolverHeurDP.o KpSolverBB.o ../test/testBB.cpp -o testBB

testIterHeur: KpSolver.o KpSolverDP.o  KpSolverHeurDP.o KpSolverGreedy.o KpSolverGreedyFractional.o ../test/testIterHeur.cpp
	g++ -O3 -W -I../src KpSolver.o KpSolverDP.o KpSolverHeurDP.o KpSolverGreedy.o ../test/testIterHeur.cpp -o testIterHeur

testHeur: KpSolver.o KpSolverDP.o  KpSolverHeurDP.o KpSolverGreedy.o KpSolverGreedyFractional.o ../test/testHeur.cpp
	g++ -O3 -W -I../src KpSolver.o KpSolverDP.o KpSolverHeurDP.o KpSolverGreedy.o KpSolverGreedyFractional.o ../test/testHeur.cpp -o testHeur

testProgDyn:  KpSolver.o KpSolverDP.o ../test/testProgDyn.cpp
	g++ -O3 -W -I../src KpSolver.o KpSolverDP.o ../test/testProgDyn.cpp -o testProgDyn 

KpSolverBB.o: ../src/kpSolverBB.cpp
	g++ -o KpSolverBB.o -O3 -W -c -I../src ../src/kpSolverBB.cpp

NodeBB.o: ../src/nodeBB.cpp
	g++ -o NodeBB.o -O3 -W -c -I../src ../src/nodeBB.cpp

KpSolverHeurDP.o: ../src/kpSolverHeurDP.cpp
	g++ -o KpSolverHeurDP.o -O3 -W -c -I../src ../src/kpSolverHeurDP.cpp

KpSolverGreedy.o: ../src/kpSolverGreedy.cpp
	g++ -o KpSolverGreedy.o -O3 -W -c -I../src ../src/kpSolverGreedy.cpp

KpSolverDP.o: ../src/kpSolverDP.cpp
	g++ -o KpSolverDP.o -O3 -W -c -I../src ../src/kpSolverDP.cpp

KpSolver.o: ../src/kpSolver.cpp
	g++ -o KpSolver.o -O3 -W -c -I../src ../src/kpSolver.cpp

KpSolverGreedyFractional.o: ../src/kpSolverGreedyFractional.cpp
	g++ -o KpSolverGreedyFractional.o -O3 -W -c -I../src ../src/kpSolverGreedyFractional.cpp

clean:
	rm -rf *.o

