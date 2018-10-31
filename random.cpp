#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<time.h>


int quickSelect(int k, std::vector<int> input);
// int getRank(int e, std::vector<int> input);
int getRandomElement(int sizeOfData);

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

  int ret = quickSelect(k, vectorOfData);

  std::cout << "The k-th element where k is " << k << " is: " << ret << std::endl;

  return 0;
}

int quickSelect(int k, std::vector<int> input)
{
  std::vector<int> lessThan;
  std::vector<int> greaterThan;

  int randomE = input[getRandomElement(input.size())];

  //getRank
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] < randomE)
    {
      lessThan.push_back(input[i]);
    }
    else if (input[i] > randomE)
    {
      greaterThan.push_back(input[i]);
    }
  }
  int rankOfE = lessThan.size();

  //recursive calls
  if (rankOfE == k)
  {
    return randomE;
  }
  else if (k < rankOfE)
  {
    return quickSelect(k, lessThan);
  }
  else
  {
    return quickSelect(k - rankOfE, greaterThan);
  }
}

int getRandomElement(int sizeOfData)
{
  srand(time(NULL));
  // return 2;
  int temp = rand() % sizeOfData;
  std::cout << temp << std::endl;

  return temp;
}
