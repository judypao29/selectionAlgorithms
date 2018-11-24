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

  //parsing
  while (std::getline(inputData, stringNum, ','))
  {
    int num = stoi(stringNum);
    vectorOfData.push_back(num);
  }
  inputData.close();

  //start timer
  auto start = std::chrono::high_resolution_clock::now();

  //call selection algorithm and return k-th element
  int ret = quickSelect(k, vectorOfData);

  //stop timer
  auto stop = std::chrono::high_resolution_clock::now();

  //get duration
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  std::cout << "The k-th element where k is " << k << " is: " << ret << std::endl;
  std::cout << "Time taken by Random Selection: "
           << duration.count() << " microseconds" << std::endl;
  return 0;
}

int quickSelect(int k, std::vector<int> input)
{
  std::vector<int> lessThan;
  std::vector<int> greaterThan;
  if (input.empty())
  {
    std::cout << "oh no! The input is empty!" << std::endl;
    return 1;
  }
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
  int rankOfE = lessThan.size() + 1;

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
  // std::cout << temp << std::endl;

  return temp;
}
