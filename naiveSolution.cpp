#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <limits>
#include <time.h>

using namespace std;

char nameRead[] = "pr76.tsp";//instance name

class CityType{
public:
  int id;
  float x;
  float y;
  bool operator<( const CityType &other) const {
    return id < other.id;
  }
};

typedef struct{
  float of;
  vector<CityType> route;
}solutionType;

vector<CityType> cities;
int counter;
float **distances;

/************************************************************************************
*** Method: calculateOF(solutionType solution)                                     ***
*** Function: calculates objective function of a certain solution                  ***
*************************************************************************************/
float calculateOF(solutionType solution){
  float total = 0;//total distance of route
  for (size_t i = 1; i < solution.route.size(); i++) {
    total += distances[solution.route[i].id][solution.route[i-1].id];
  }
  return total;
}

/************************************************************************************
*** Method: generateInitial()                                                    ***
*** Function: generates initial solutionType                                     ***
*************************************************************************************/
solutionType generateInitial(){
  solutionType sol;
  sol.route = cities;
  random_shuffle( sol.route.begin(), sol.route.end() );
  sol.of = calculateOF(sol);
  return sol;
}

/************************************************************************************
*** Method: calculateDistance(float a, float b, float x, float y                 ***
*** Function: calculates distance between two points                             ***
*************************************************************************************/
float calculateDistance(float a, float b, float x, float y){
  return sqrt((a-x)*(a-x)+(b-y)*(b-y));
}

/************************************************************************************
*** Method: readFile()                                                           ***
*** Function: reads instance file and attributes data                            ***
*************************************************************************************/
void readFile()
{
  counter = 0;
  CityType dummy;

  ifstream instanceFile;
  instanceFile.open(nameRead, ios::in);

  if (!instanceFile) {
    printf("File not found.\n");
    //     getchar();
    exit(1);
  }

  if(instanceFile.is_open()){
    while(!instanceFile.eof()){
      instanceFile >> dummy.id;
      instanceFile >> dummy.x;
      instanceFile >> dummy.y;
      cities.push_back(dummy);
      counter++;
    }
  }
  instanceFile.close();
}

/************************************************************************************
*** Method: preProcessing()                                                      ***
*** Function: processes data and creates distances matrix                        ***
*************************************************************************************/
void preProcessing(){
  distances = new float*[counter];
  for (size_t i = 0; i < counter; i++) {
    distances[i] = new float[counter];
    for (size_t j = 0; j < counter; j++) {
      distances[i][j] = calculateDistance(cities[i].x, cities[i].y,
        cities[j].x, cities[j].y);
      }
    }
  }

/************************************************************************************
*** Method: shiftCity(solutionType sol)                                          ***
*** Function: shifts two random cities                                                  ***
*************************************************************************************/
solutionType shiftCity(solutionType sol){
  srand (time(NULL));
  CityType aux;
  int city_1 = rand()%(sol.route.size());
  int city_2;
  do{
    city_2 = rand() %(sol.route.size());
  }while(city_1==city_2);
  std::swap( sol.route[city_1], sol.route[city_2]);
  return sol;
}

solutionType SA(solutionType initial, float T0, float SAmax, float alpha) {
  float iterT = 0;
  float T = T0;
  float delta;
  solutionType neighbor;
  solutionType solution;
  solutionType best;
  int count = 0;
  solution = initial;
  best = solution;
  while (T>0.0001){
    while (iterT<SAmax) {
      iterT++;
      count ++;
      neighbor = solution;
      neighbor = shiftCity(neighbor);
      neighbor.of = calculateOF(neighbor);
      delta = solution.of - neighbor.of;
      // cout << delta << endl;
      if(delta>=0){
        solution = neighbor;
        if(solution.of<best.of)
          best = solution;
      }
      else{
        float x = ((float)(rand()%10000)/10000.0);
        float expoente = (delta/T);
        if(x<(exp(expoente)))
          solution = neighbor;
      }
    }
    T *= alpha;
    iterT = 0;
      cout << "T = " <<  T << "\tOF = " << solution.of << "\tbestOF " << best.of << endl;
  }
  cout << endl;
  return best;
}

void printSolution(solutionType sol){
  cout << "Best solution found: " << endl;
  cout << "OF = " << sol.of << endl;
  cout << "Route: " << endl;
  for (size_t i = 0; i < sol.route.size(); i++) {
    cout << sol.route[i].id << " ";
  }
  cout << endl;
}

// 1) Consider city 1 as the starting and ending point.
// 2) Generate all (n-1)! Permutations of cities.
// 3) Calculate cost of every permutation and keep track of minimum cost permutation.
// 4) Return the permutation with minimum cost.

int main(int argc, char const *argv[]) {
  srand (time(NULL));
  solutionType s1;
  readFile();
  preProcessing();
  s1.route = cities;
  float val = std::numeric_limits<float>::max();
  do {
    val = min( calculateOF( s1 ), val);
  } while ( std::next_permutation(s1.route.begin(), s1.route.end()) );
  printSolution(s1);
  return 0;
}
