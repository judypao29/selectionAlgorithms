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
  std::vector<int> heap;
  std::vector<int> medians;


  int counter = 0;
  while (std::getline(inputData, stringNum, ','))
  {
      int num = stoi(stringNum);
      if (counter != sizeOfGroups)
      {
          heap.push_back(num);
          counter++;
      }
      else
      {
          std::cout << "HEAP CONTENTS" << std::endl;

          for (int i = 0; i < heap.size(); i++)
          {
              std::cout << heap.at(i) << std::endl;
          }

          counter = 0;
          make_heap(heap.begin(), heap.end());
          for (int i = 0; i < (sizeOfGroups / 2); i++)
          {
              pop_heap(heap.begin(), heap.end());
              heap.pop_back();
          }
          pop_heap(heap.begin(), heap.end());
          medians.push_back(heap.back());

          while(!heap.empty())
          {
              heap.pop_back();
          }
          heap.push_back(num);
          counter++;
      }
  }
  inputData.close();
  // for (int i = 0; i < medians.size(); i++)
  // {
  //     std::cout << medians.at(i) << std::endl;
  // }


  return 0;
}
//
// void make_heapTest()
// {
//     std::vector<int> heap = {2, 3, 1, 10};
//
//     make_heap(heap.begin(), heap.end());
//
//     // std::cout << heap.at(0) << std::endl;
//     // std::cout << heap.at(1) << std::endl;
//     // std::cout << heap.at(2) << std::endl;
//     // std::cout << heap.at(3) << std::endl;
//     // std::cout << heap.at(4) << std::endl;
//     //
//     //
//
//
//     pop_heap(heap.begin(), heap.end());
//     std::cout << heap.back() << std::endl;
//     heap.pop_back();
//
//     pop_heap(heap.begin(), heap.end());
//     std::cout << heap.back() << std::endl;
//     heap.pop_back();
//
//     pop_heap(heap.begin(), heap.end());
//     std::cout << heap.back() << std::endl;
//     heap.pop_back();
//
//     pop_heap(heap.begin(), heap.end());
//     std::cout << heap.back() << std::endl;
//     heap.pop_back();
//     //
//     // pop_heap(heap.begin(), heap.end());
//     // std::cout << heap.back() << std::endl;
//     // heap.pop_back();
//
//     std::cout << heap.back() << std::endl;
//     std::cout << heap.size() << std::endl;
//
//
// }
