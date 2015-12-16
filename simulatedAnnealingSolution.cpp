#include "common.h"
using namespace std;
solutionType SA( const solutionType &initial, float T0, float SAmax, float alpha );

int main(int argc, char const *argv[]) {
  if( argc != 2 ) {
    cout << "Usage " << argv[ 0 ] << " <instance file>" << endl;
    exit( 1 );
  }
  strcpy( nameRead, argv[ 1 ] );
  srand (time(NULL));
  float mean;
  float SAmax = 100000;
  float alpha = 0.99;
  float T0 = 10000000;
  solutionType s1;
  readFile();
  preProcessing();
  const clock_t begin_time = clock();
  s1 = generateInitial();
  s1 = SA(s1, T0, SAmax, alpha);
  std::cout << "TIME: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<endl;
  printSolution(s1);
  for (size_t i = 0; i < 1000; i++) {
    random_shuffle( s1.route.begin(), s1.route.end() );
    mean += calculateOF(s1.route);
  }

  cout << "Mean solution: " << mean/1000 << endl;

  return 0;
}


solutionType SA( const solutionType &initial, float T0, float SAmax, float alpha ) {
  float iterT = 0;
  float T = T0;
  float delta;
  solutionType neighbor;
  solutionType solution;
  solutionType best;
  int count = 0;
  solution = initial;
  best = solution;
  while( T > 0.0001 ) {
    while( iterT < SAmax ) {
      iterT++;
      count++;
      neighbor = solution;
      neighbor = shiftCity( neighbor );
      neighbor.of = calculateOF( neighbor.route );
      delta = solution.of - neighbor.of;
      /* cout << delta << endl; */
      if( delta >= 0 ) {
        solution = neighbor;
        if( solution.of < best.of ) {
          best = solution;
        }
      }
      else {
        float x = ( ( float ) ( rand( ) % 10000 ) / 10000.0 );
        float expoente = ( delta / T );
        if( x < ( exp( expoente ) ) ) {
          solution = neighbor;
        }
      }
    }
    T *= alpha;
    iterT = 0;
    // cout << "T = " << T << "\tOF = " << solution.of << "\tbestOF " << best.of << endl;
  }
  // cout << endl;
  return( best );
}
