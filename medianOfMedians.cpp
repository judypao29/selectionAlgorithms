/*
o	initialize heap.
o	read each item in csv and insert <size of groups> items into a heap.
o	Use heap to find median of the group by popping, then empty the heap.
o	Put each median into an array.
o	Repeat until everything is read in.
*/

#include<fstream>
#include<iostream>
#include<string>
#include<vector>

// format: ./run file.csv <int k> <int sizeOfGroups>
int main(int argc, char* argv[])
{
  int k = atoi(argv[2]);
  int sizeOfGroups = atoi(argv[3]);
  std::fstream inputData;

  inputData.open(argv[1]);
  std::string stringNum;
  std::vector<int> tempVec;


  while (std::getline(inputData, stringNum, ','))
  {
    int num = stoi(stringNum);
    vectorOfData.push_back(num);
  }
  inputData.close();

  std::sort(vectorOfData.begin(), vectorOfData.end());

  std::cout << "The k-th element where k is " << k << " is: " << vectorOfData[k - 1] << std::endl;

  return 0;
}
