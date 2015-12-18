#include "common.h"
/*
 * 1) Consider city 1 as the starting and ending point.
 * 2) Generate all (n-1)! Permutations of cities.
 * 3) Calculate cost of every permutation and keep track of minimum cost permutation.
 * 4) Return the permutation with minimum cost.
 */
float minDist = std::numeric_limits<float>::max();
vector<CityType> best;
void permute(int l, int r, float dist){
  if(dist >= minDist){
    return;
  }
  if(l == r-1){
    dist += distances[r][0];
    if(dist < minDist){
      best = cities;
      best.push_back(best.front());
      minDist = dist;
    }
  }else {
    for (size_t i = l; i <= r; i++){
      swap(cities[l], cities[i]);
      float d2 = distances[cities[l].id][cities[l-1].id];
      permute(l+1, r, dist+d2);
      swap(cities[i], cities[l]);
    }
  }
}

using namespace std;
int main( int argc, char const *argv[] ) {
  if( argc != 2 ) {
    cout << "Usage " << argv[ 0 ] << " <instance file>" << endl;
    exit( 1 );
  }
  strcpy( nameRead, argv[ 1 ] );
  srand( time( NULL ) );
  solutionType s1;
  readFile( );
  preProcessing( );
  s1.route = cities;
  s1.of = std::numeric_limits< float >::max( );
  const clock_t begin_time = clock();
//   do {
//     float of = calculateOF( cities );
// //    for( CityType c : cities ) {
// //      c.print( );
// //    }
// //    cout << " : " << of << endl;
//     if( of < s1.of ) {
//       s1.of = of;
//       s1.route = cities;
//     }
//
//   } while( std::next_permutation( cities.begin( ), cities.end( ) ) );
  permute(0,counter-1,0.0);
  std::cout << "TIME: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<endl;
  printSolution( s1 );

  return( 0 );
}
