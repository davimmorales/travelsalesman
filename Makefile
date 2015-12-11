dynamicSolution:
	clang++ ${@}.cpp -o bin/${@}

dynamicSolution-berlin52: dynamicSolution
	bin/dynamicSolution instances/berlin52.tsp
