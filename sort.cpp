#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<chrono>

// format: ./run file.csv <int k>
int main(int argc, char* argv[])
{
    // std::vector<int> vectorOfData((int)inputSize);
    std::vector<int> vectorOfData;

  int k = atoi(argv[2]);
  std::fstream inputData;
  inputData.open(argv[1]);
  std::string stringNum;

  while (std::getline(inputData, stringNum, ','))
  {
    int num = stoi(stringNum);
    vectorOfData.push_back(num);
  }
  inputData.close();

  //start timer
  auto start = std::chrono::high_resolution_clock::now();

  //sort and return the k-th element
  std::sort(vectorOfData.begin(), vectorOfData.end());

  //stop timer
  auto stop = std::chrono::high_resolution_clock::now();

  //get duration
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "vecSize: " <<vectorOfData.size() << '\n';

  // std::cout << "The k-th element where k is " << k << " is: " << vectorOfData[k - 1] << std::endl;
  std::cout << "Time taken by Sorting: "
           << duration.count() << " microseconds" << std::endl;
  return 0;
}
