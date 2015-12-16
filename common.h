#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

char nameRead[ 256 ]; /* instance name */

class CityType {
public:
  int id;
  float x;
  float y;
  bool operator<( const CityType &other ) const {
    return( id < other.id );
  }
  void print( ) {
    cout << id << " ";
  }
};

typedef struct {
  float of = 0.0;
  vector< CityType > route;
}solutionType;

vector< CityType > cities;
size_t counter;
float **distances;

/************************************************************************************
 *** Method: calculateOF(solutionType solution)                                     ***
 *** Function: calculates objective function of a certain solution                  ***
 *************************************************************************************/
float calculateOF( const vector< CityType > &route ) {
  float total = 0; /* total distance of route */
  for( size_t i = 1; i < route.size( ); i++ ) {
    total += distances[ route[ i ].id ][ route[ i - 1 ].id ];
  }
  total += distances[ route[ 0 ].id ][ route.back( ).id ];
  return( total );
}

/************************************************************************************
 *** Method: generateInitial()                                                    ***
 *** Function: generates initial solutionType                                     ***
 *************************************************************************************/
solutionType generateInitial( ) {
  solutionType sol;
  sol.route = cities;
  random_shuffle( sol.route.begin( ), sol.route.end( ) );
  sol.of = calculateOF( sol.route );
  return( sol );
}

/************************************************************************************
 *** Method: calculateDistance(float a, float b, float x, float y                 ***
 *** Function: calculates distance between two points                             ***
 *************************************************************************************/
float calculateDistance( float a, float b, float x, float y ) {
  float i = x - a, j = y - b;
  return( std::sqrt( ( i ) * ( i ) + ( j ) * ( j ) ) );
}

/************************************************************************************
 *** Method: readFile()                                                           ***
 *** Function: reads instance file and attributes data                            ***
 *************************************************************************************/
void readFile( ) {
  counter = 0;


  ifstream instanceFile;
  instanceFile.open( nameRead, ios::in );
  if( !instanceFile ) {
    printf( "File not found.\n" );
    /*     getchar(); */
    exit( 1 );
  }
  if( instanceFile.is_open( ) ) {
    while( !instanceFile.eof( ) ) {
      CityType dummy;
      instanceFile >> dummy.id;
      instanceFile >> dummy.x;
      instanceFile >> dummy.y;
      dummy.id--;
      cities.push_back( dummy );
      counter++;
    }
  }
  counter--;
  cities.pop_back( );
//  for( CityType c : cities ) {
//    c.print( );
//  }
//  cout << endl;

  instanceFile.close( );
}

/************************************************************************************
 *** Method: preProcessing()                                                      ***
 *** Function: processes data and creates distances matrix                        ***
 *************************************************************************************/
void preProcessing( ) {
  distances = new float*[ counter ];
  for( size_t i = 0; i < counter; i++ ) {
    distances[ i ] = new float[ counter ];
    for( size_t j = 0; j < counter; j++ ) {
      distances[ i ][ j ] = calculateDistance( cities[ i ].x, cities[ i ].y,
                                               cities[ j ].x, cities[ j ].y );
//      printf("%.8f ", distances[i][j]);
    }
//    cout << endl;
  }
}

/************************************************************************************
 *** Method: shiftCity(solutionType sol)                                          ***
 *** Function: shifts two random cities                                                  ***
 *************************************************************************************/
solutionType shiftCity( solutionType &sol ) {
  srand( time( NULL ) );
  CityType aux;
  int city_1 = rand( ) % ( sol.route.size( ) );
  int city_2;
  do {
    city_2 = rand( ) % ( sol.route.size( ) );
  } while( city_1 == city_2 );
  std::swap( sol.route[ city_1 ], sol.route[ city_2 ] );
  return( sol );
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

void printSolution( const solutionType &sol ) {
  cout << "Best solution found: " << endl;
  cout << "OF = " << sol.of << endl;
  cout << "Route: " << endl;
  for( size_t i = 0; i < sol.route.size( ); i++ ) {
    cout << sol.route[ i ].id << " ";
  }
  cout << endl;
}
