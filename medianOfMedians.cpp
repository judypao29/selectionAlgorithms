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
int select(int k, std::vector<int> setOfElements);
int getRank(int medianOfMedians, std::vector<int> originalInput, std::vector<int>& greaterThan, std::vector<int>& lessThan);
int medOfMedRecur(std::vector<int> medians, int sizeOfGroups);
// format: ./run file.csv <int k> <int sizeOfGroups>
int main(int argc, char* argv[])
{
  int k = atoi(argv[2]);
  int sizeOfGroups = atoi(argv[3]);
  std::fstream inputData;

  inputData.open(argv[1]);
  std::string stringNum;
  std::vector<int> originalInput;
  //get original input
  while (std::getline(inputData, stringNum, ','))
  {
      int num = stoi(stringNum);
      originalInput.push_back(num);
  }
  inputData.close();

  int selectWoAh = select(k, originalInput)
  std::cout << selectWoAh << '\n';
  return select;


  return 0;
}

int select(int k, std::vector<int> setOfElements)
{
    std::vector<int> greaterThan;
    std::vector<int> lessThan;

    //recursive call to find median of medians
    int medianOfMedians = medOfMedRecur(originalInput, sizeOfGroups);

    //get rank of the medianOfMedians
    int rankOfMedian = getRank(medianOfMedians, originalInput, greaterThan, lessThan);

    //compare rank to k
    if (rankOfMedian == k)
    {
        return medianOfMedians;
    }
    else if (rankOfMedian > k)
    {
        return select(k, greaterThan);
    }
    else
    {
        return select(k, lessThan);
    }
}

int medOfMedRecur(std::vector<int> elements, int sizeOfGroups)
{
    int counter = 0;
    std::vector<int> mediansVector;
    std::vector<int> heap;
    for (int i = 0; i < elements.size(); i++)
    {
        if (counter != sizeOfGroups)
        {
            heap.push_back(elements[i]);
            counter++;
        }
        else
        {
            counter = 0;
            make_heap(heap.begin(), heap.end());
            for (int i = 0; i < (sizeOfGroups / 2); i++)
            {
                pop_heap(heap.begin(), heap.end());
                heap.pop_back();
            }
            pop_heap(heap.begin(), heap.end());
            mediansVector.push_back(heap.back());

            while(!heap.empty())
            {
                heap.pop_back();
            }

            heap.push_back(elements[i]);
            counter++;
        }
    }
    if (heap.size() == sizeOfGroups)
    {
        counter = 0;
        make_heap(heap.begin(), heap.end());
        for (int i = 0; i < (sizeOfGroups / 2); i++)
        {
            pop_heap(heap.begin(), heap.end());
            heap.pop_back();
        }
        pop_heap(heap.begin(), heap.end());
        mediansVector.push_back(heap.back());
    }
    if (mediansVector.empty())
    {
        for (int i = 0; i < heap.size(); i++)
        {
            mediansVector.push_back(heap[i]);
        }
    }
    if (mediansVector.size() <= sizeOfGroups)
    {
        return findMedian();
    }
    else
    {
        if (mediansVector.size() == 0)
        {
            std::cout << "uh oh" << '\n';
            return -123;
        }
        return medOfMedRecur(mediansVector, sizeOfGroups);
    }
}

int getRank(int medianOfMedians, std::vector<int> originalInput, std::vector<int>& greaterThan, std::vector<int>& lessThan)
{
    for (int i = 0; i < originalInput.size(); i++)
    {
        if (originalInput[i] > medianOfMedians)
        {
            greaterThan.push_back(input[i]);
        }
        else if (input[i] < rightB)
        {
            lessThan.push_back(input[i]);
        }
    }
    int rank = lessThan.size();
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
