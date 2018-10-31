#include<iostream>
#include<set>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>

//./run <size of file>
int main(int argc, char * argv[])
{
  int datasetSize = atoi(argv[1]);
  int randomNumber;
  std::set<int> set;

  srand (time(NULL));
  while (set.size() != datasetSize)
  {
    randomNumber = rand();
    if (randomNumber == 0)
    {
      continue;
    }
    auto ret = set.insert(randomNumber);
    if (ret.second == true)
    {
      std::cout << randomNumber << ",";
    }
  }
  return 0;
}
