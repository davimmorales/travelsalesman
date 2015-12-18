simulatedAnnealingSolution:
	clang++ --std=c++11 ${@}.cpp -o bin/${@}

simulatedAnnealingSolution-berlin52: simulatedAnnealingSolution
	bin/simulatedAnnealingSolution instances/berlin52.tsp

simulatedAnnealingSolution2:
	clang++ --std=c++11 ${@}.cpp -o bin/${@}

simulatedAnnealingSolution2-berlin52: simulatedAnnealingSolution2
	bin/simulatedAnnealingSolution2 instances/berlin52.tsp


naiveSolution:
	clang++ --std=c++11 ${@}.cpp -o bin/${@}

naiveSolution-berlin52: naiveSolution
	bin/naiveSolution instances/berlin52.tsp

naiveSolution-littleboy: naiveSolution
	bin/naiveSolution instances/littleboy.tsp

backtrackSolution:
	clang++ --std=c++11 ${@}.cpp -o bin/${@}

backtrackSolution-berlin52: backtrackSolution
	bin/backtrackSolution instances/berlin52.tsp

backtrackSolution-littleboy: backtrackSolution
	bin/naiveSolution instances/littleboy.tsp
