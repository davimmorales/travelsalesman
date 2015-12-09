#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

char nameRead[] = "berlin52.tsp";//instance name

typedef struct{
  int id;
  int visited;
  float x;
  float y;
}cityType;

vector<cityType> cities;
int count;
float **distances;

/************************************************************************************
*** Method: readFile()                                                           ***
*** Function: reads instance file and attributes data                            ***
*************************************************************************************/
void readFile()
{
  count = 0;
  cityType dummy;

  ifstream instaceFile;
  instaceFile.open(nameRead, ios::in);

  if (!instaceFile) {
    printf("Wasn't able to open file.\n");
    //     getchar();
    exit(1);
  }

  if(instaceFile.is_open()){
    while(!instaceFile.eof()){
      instaceFile >> dummy.id;
      instaceFile >> dummy.x;
      instaceFile >> dummy.y;
      dummy.visited = 0;
      cities.push_back(dummy);
      count++;
    }
  }

  instaceFile.close();
}



/************************************************************************************
*** Method: preProcessing()                                                      ***
*** Function: processes data and creates distances matrix                        ***
*************************************************************************************/
void preProcessing(){
  distances = new float*[count];
  for (size_t i = 0; i < count; i++) {
    distances[i] = new float[count];
    for (size_t j = 0; j < count; j++) {
      distances[i][j] = calculateDistance(cities[i].x, cities[i].y,
      cities[j].x, cities[j].y);
    }
  }


}

int main(int argc, char const *argv[]) {
  readFile();
  return 0;
}
