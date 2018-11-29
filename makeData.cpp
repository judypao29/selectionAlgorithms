#include<iostream>
#include<set>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>

//./run <size of file>
int main(int argc, char * argv[])
{
  long long int datasetSize = atoi(argv[1]);
  long long int randomNumber;
  auto set = new std::set<long long int>();

  srand (time(NULL));
  while (set->size() != datasetSize)

  {
    randomNumber = rand();
    if (randomNumber == 0)
    {
      continue;
    }
    auto ret = set->insert(randomNumber);
    if (ret.second == true)
    {
      std::cout << randomNumber << ",";
    }
  }

  delete set;
  
  return 0;
}
