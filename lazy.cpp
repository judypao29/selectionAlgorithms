#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<cmath>
#include<algorithm>


int lazySelect(int k, std::vector<int>& input);
void selectRandomElements(std::vector<int>& inputData, std::vector<int>& subset);
int getA(int x, int inputSize);
int getB(int x, int inputSize);
int getRank(int a, std::vector<int>& input);

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

  //parsing
  while (std::getline(inputData, stringNum, ','))
  {
    int num = stoi(stringNum);
    vectorOfData.push_back(num);
  }
  inputData.close();

  int ret = lazySelect(k, vectorOfData);

  std::cout << "The k-th element where k is " << k << " is: " << ret << std::endl;

  return 0;
}

int lazySelect(int k, std::vector<int>& input)
{
  std::vector<int> multiSubsetOfN;
  if (input.empty())
  {
    std::cout << "oh no! The input is empty!" << std::endl;
    return 1;
  }
  // choose n^{3/4} elements from input, put into subset.
  selectRandomElements(input, multiSubsetOfN);


  //sorts in n^{3/4}log n time
  std::sort(multiSubsetOfN.begin(), multiSubsetOfN.end());

  int x = (k * (floor(pow(input.size(), -.25))));
  int leftA = multiSubsetOfN[getA(x, input.size())];
  int rightB = multiSubsetOfN[getB(x, input.size())];

  std::vector<int> setP;
  if ((k > std::floor(pow(input.size(), 0.25))) &&
            (k < (input.size() - floor(pow(input.size(), 0.25)))))
  {
    //get P between A and B
    // if not in P, recursive call
    if (input[k] > rightB && input[k] < leftA)
    {
      return lazySelect(k, input);
    }
    for (int i = 0; i < input.size(); i++)
    {
      if (input[i] >= leftA && input[i] <= rightB)
      {
        setP.push_back(input[i]);
      }
    }
  }
  else if (k < std::floor(pow(input.size(), 0.25)))
  {
    //get P leqB
    // if not in P, recursive call
    if (input[k] > rightB)
    {
      return lazySelect(k, input);
    }
    for (int i = 0; i < input.size(); i++)
    {
      if (input[i] <= rightB)
      {
        setP.push_back(input[i]);
      }
    }
  }
  else if (k > (input.size() - std::floor(pow(input.size(), 0.25))))
  {
    //get P geqA
    // if not in P, recursive call
    if (input[k] < leftA)
    {
      return lazySelect(k, input);
    }
    for (int i = 0; i < input.size(); i++)
    {
      if (input[i] >= leftA)
      {
        setP.push_back(input[i]);
      }
    }
  }

  if (setP.size() > (4 * std::floor(pow(input.size(), 0.75)) + 2))
  {
    return lazySelect(k, input);
  }
  else
  {
      std::sort(setP.begin(), setP.end());
      int rankA = getRank(leftA, input);
      return setP[k - rankA + 1];
  }
}

void selectRandomElements(std::vector<int>& inputData, std::vector<int>& subset)
{
  srand(time(NULL));
  int numElementsInSubset = (int)std::floor(pow(inputData.size(), 0.75));

  for (int i = 0; i < numElementsInSubset; i++)
  {
    subset.push_back(inputData[rand() % inputData.size()]);
  }
}

int getA(int x, int inputSize)
{
  return std::max((int)std::floor(x - std::floor(pow(inputSize, 0.5))), 1);
}

int getB(int x, int inputSize)
{
  return std::min(std::ceil(x - std::floor(pow(inputSize, 0.5))), std::floor(pow(inputSize, 0.75)));
}

int getRank(int a, std::vector<int>& input)
{
  int count = 1;
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] < a)
    {
      count++;
    }
  }
  return count;
}
