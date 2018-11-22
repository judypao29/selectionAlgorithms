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
int select(int k, std::vector<int> setOfElements, std::vector<int> originalInput,int sizeOfGroups);
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

  //call selection algorithm and return k-th element
  int solution = select(k, originalInput, originalInput, sizeOfGroups);

  std::cout << "The k-th element where k is " << k << " is: " << solution << std::endl;

  return 0;
}

int select(int k, std::vector<int> setOfElements, std::vector<int> originalInput, int sizeOfGroups)
{
    std::vector<int> greaterThan;
    std::vector<int> lessThan;

    //recursive call to find median of medians
    int medianOfMedians = medOfMedRecur(setOfElements, sizeOfGroups);

    //get rank of the medianOfMedians
    int rankOfMedian = getRank(medianOfMedians, originalInput, greaterThan, lessThan);

    //compare rank to k
    if (rankOfMedian == k)
    {
        return medianOfMedians;
    }
    else if (rankOfMedian < k)
    {
        return select(k, greaterThan, originalInput, sizeOfGroups);
    }
    else
    {
        return select(k, lessThan, originalInput, sizeOfGroups);
    }
}

int medOfMedRecur(std::vector<int> elements, int sizeOfGroups)
{
    if (elements.empty())
    {
        std::cout << "this should never happen" << '\n';
        return -1;
    }
    if (elements.size() == 1)
    {
        return elements[0];
    }

    int counter = 0;
    std::vector<int> mediansVector;
    std::vector<int> heap;

    //split into groups of specified size, push median of each group into the mediansVector
    for (int i = 0; i < elements.size(); i++)
    {
        if (counter != sizeOfGroups)
        {
            heap.push_back(elements[i]);
            counter++;
        }
        else
        {
            make_heap(heap.begin(), heap.end());
            for (int i = 0; i < (sizeOfGroups / 2); i++)
            {
                pop_heap(heap.begin(), heap.end());
                heap.pop_back();
            }
            pop_heap(heap.begin(), heap.end());
            mediansVector.push_back(heap.back());

            //empty the heap
            while(!heap.empty())
            {
                heap.pop_back();
            }
            heap.push_back(elements[i]);
            counter = 1;
        }
    }

    //if there is another median, push it into mediansVector
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

    //if there's nothing in the mediansVector, push all elements in the heap to mediansVector
    if (mediansVector.empty())
    {
        for (int i = 0; i < heap.size(); i++)
        {
            mediansVector.push_back(heap[i]);
        }
    }

    if (mediansVector.size() <= sizeOfGroups)
    {
        sort(mediansVector.begin(), mediansVector.end());
        return mediansVector[mediansVector.size() / 2];
    }
    else
    {
        return medOfMedRecur(mediansVector, sizeOfGroups);
    }
}

int getRank(int medianOfMedians, std::vector<int> originalInput, std::vector<int>& greaterThan, std::vector<int>& lessThan)
{
    for (int i = 0; i < originalInput.size(); i++)
    {
        if (originalInput[i] > medianOfMedians)
        {
            greaterThan.push_back(originalInput[i]);
        }
        else if (originalInput[i] < medianOfMedians)
        {
            lessThan.push_back(originalInput[i]);
        }
    }
    return (lessThan.size() + 1);
}
