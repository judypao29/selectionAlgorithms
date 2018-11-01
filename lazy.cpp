#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<cmath>
#include<algorithm>
#include<utility>


int lazySelect(int k, std::vector<int>& input);
void selectRandomElements(std::vector<int>& inputData, std::vector<int>& subset);
int getA(int x, int inputSize);
int getB(int x, int inputSize);
std::pair<int, int> getRankOfAandB(std::vector<int>& input,
    std::vector<int>& greaterThanA, std::vector<int>& lessThanB,
    std::vector<int>& betweenAandB, int leftA, int rightB, int k);
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

  std::vector<int> greaterThanA;
  std::vector<int> lessThanB;
  std::vector<int> betweenAandB;

  auto temp = getRankOfAandB(input, greaterThanA, lessThanB, betweenAandB, leftA, rightB, k);

  int rankA = temp.first;
  int rankB = temp.second;

  if (k < std::floor(pow(input.size(), 0.25)))
  {
    //get P leqB
    // if not in P, recursive call
    if ((k > rankB)||
    (lessThanB.size() > (4 * std::floor(pow(input.size(), 0.75)) + 2)))
    {
        std::cout << "if: 2 \n";

      return lazySelect(k, input);
    }
    else
    {
        std::sort(lessThanB.begin(), lessThanB.end());
        return lessThanB[k - rankA + 1];
    }
  }
  else if (k > ((input.size() - std::floor(pow(input.size(), 0.25)))))
  {
    //get P geqA
    // if not in P, recursive call
    if ((k < rankA )||
        (greaterThanA.size() > (4 * std::floor(pow(input.size(), 0.75)) + 2)))
    {
        std::cout << "if: 3\n";

      return lazySelect(k, input);
    }
    else
    {
        std::sort(greaterThanA.begin(), greaterThanA.end());
        return greaterThanA[k - rankA + 1];
    }
  }
  else if ((k >= std::floor(pow(input.size(), 0.25))) &&
            (k <= (input.size() - floor(pow(input.size(), 0.25)))))
  {
    //get P between A and B
    // if not in P, recursive call
    if (((k > rankB) || (k < rankA)) ||
        (betweenAandB.size() > (4 * std::floor(pow(input.size(), 0.75)) + 2)))
    {
        std::cout << "if: 1 \n";

      return lazySelect(k, input);
    }
    else
    {
        std::sort(betweenAandB.begin(), betweenAandB.end());
        return betweenAandB[k - rankA + 1];
    }
  }
  return 0;
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

std::pair<int, int> getRankOfAandB(std::vector<int>& input,
    std::vector<int>& greaterThanA, std::vector<int>& lessThanB,
    std::vector<int>& betweenAandB, int leftA, int rightB, int k)
{
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] >= leftA && input[i] <= rightB)
        {
            greaterThanA.push_back(input[i]);
            lessThanB.push_back(input[i]);
            betweenAandB.push_back(input[i]);
        }
        else if (input[i] >= leftA)
        {
            greaterThanA.push_back(input[i]);
        }
        else if (input[i] <= rightB)
        {
            lessThanB.push_back(input[i]);
        }
    }
    int rankA = input.size() - greaterThanA.size();
    int rankB = lessThanB.size();

    return std::make_pair(rankA, rankB);
}
