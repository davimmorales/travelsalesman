#include "common.h"
using namespace std;

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
  s1 = generateInitial();
  s1 = SA(s1, T0, SAmax, alpha);
  printSolution(s1);

  for (size_t i = 0; i < 1000; i++) {
    random_shuffle( s1.route.begin(), s1.route.end() );
    mean += calculateOF(s1.route);
  }
  cout << "Mean solution: " << mean/1000 << endl;

  return 0;
}
