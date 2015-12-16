simulatedAnnealingSolution:
	clang++ --std=c++11 ${@}.cpp -o bin/${@}

simulatedAnnealingSolution-berlin52: simulatedAnnealingSolution
	bin/simulatedAnnealingSolution instances/berlin52.tsp

naiveSolution:
	clang++ --std=c++11 ${@}.cpp -o bin/${@}

naiveSolution-berlin52: naiveSolution
	bin/naiveSolution instances/berlin52.tsp

naiveSolution-littleboy: naiveSolution
	bin/naiveSolution instances/littleboy.tsp
