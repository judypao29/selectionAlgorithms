#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<cmath>
#include<algorithm>
#include<utility>


int lazySelect(int k, std::vector<int>& input, unsigned long count);
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
    srand(time(NULL));
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

    //use lazy select to return k-th element
    int count = 1;
    int ret = lazySelect(k, vectorOfData, count);
    while (ret == -1)
    {
        ret = lazySelect(k, vectorOfData, ++count);
    }

    //stop timer
    auto stop = std::chrono::high_resolution_clock::now();

    //get duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "The k-th element where k is " << k << " is: " << ret << std::endl;
    std::cout << "Time taken by Lazy Select: "
             << duration.count() << " microseconds" << std::endl;
    return 0;
}

int lazySelect(int k, std::vector<int>& input, unsigned long count)
{
    // std::cout << "call " << count << "\n";
    std::vector<int> multiSubsetOfN;

    // choose n^{3/4} elements from input, put into subset.
    selectRandomElements(input, multiSubsetOfN);

    //sorts in n^{3/4}log n time
    std::sort(multiSubsetOfN.begin(), multiSubsetOfN.end());


    int x = floor((k * (pow(input.size(), -0.25))));
    int leftA = multiSubsetOfN[getA(x, input.size())];
    int rightB = multiSubsetOfN[getB(x, input.size())];

    std::vector<int> greaterThanA;
    std::vector<int> lessThanB;
    std::vector<int> betweenAandB;

    auto temp = getRankOfAandB(input, greaterThanA, lessThanB, betweenAandB, leftA, rightB, k);

    int rankA = temp.first;
    int rankB = temp.second;

    if (k < (pow(input.size(), 0.25)))
    {
        //get P leqB
        // if not in P, recursive call
        if ((k > rankB)||
        (lessThanB.size() > (4 * (pow(input.size(), 0.75)) + 2)))
        {
            return lazySelect(k, input, count);
        }
        else
        {
            std::sort(lessThanB.begin(), lessThanB.end());
            return lessThanB[k - 1];
        }
    }
    else if (k > ((input.size() - (pow(input.size(), 0.25)))))
    {
        //get P geqA
        // if not in P, recursive call
        if ((k < rankA )||
        (greaterThanA.size() > (4 * (pow(input.size(), 0.75)) + 2)))
        {
            return lazySelect(k, input, count);
        }
        else
        {
            std::sort(greaterThanA.begin(), greaterThanA.end());
            return greaterThanA[k - rankA];
        }
    }
    else if ((k >= (pow(input.size(), 0.25))) &&
    (k <= (input.size() - (pow(input.size(), 0.25)))))
    {
        //get P between A and B
        // if not in P, recursive call
        if (((k > rankB) || (k < rankA)) ||
        (betweenAandB.size() > (4 * (pow(input.size(), 0.75)) + 2)))
        {
            return lazySelect(k, input, count);
        }
        else
        {
            std::sort(betweenAandB.begin(), betweenAandB.end());
            return betweenAandB.at(k - rankA);
        }
    }
    return 0;
}

void selectRandomElements(std::vector<int>& inputData, std::vector<int>& subset)
{
    int numElementsInSubset = (int)std::floor(pow(inputData.size(), 0.75));

    for (int i = 0; i < numElementsInSubset; i++)
    {
        subset.push_back(inputData[rand() % inputData.size()]);
    }
}

int getA(int x, int inputSize)
{
    return std::max((int)std::floor(x - (pow(inputSize, 0.5))), 1);
}

int getB(int x, int inputSize)
{
    return std::min(std::ceil(x + (pow(inputSize, 0.5))), std::floor(pow(inputSize, 0.75)));
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
    int rankA = input.size() - greaterThanA.size() + 1;
    int rankB = lessThanB.size();

    return std::make_pair(rankA, rankB);
}
