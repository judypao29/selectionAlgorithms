#include<fstream>
#include<iostream>
#include<string>
#include<vector>

// format: ./run file.csv <int k>
int main(int argc, char* argv[])
{
  int k = atoi(argv[2]);
  std::fstream inputData;
  inputData.open(argv[1]);
  std::string stringNum;

  std::vector<int> vectorOfData;

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
