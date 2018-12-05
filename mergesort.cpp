#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<chrono>


void mergeSort(std::vector<int> data, int l, int r);
void merge(std::vector<int> data, int l, int m, int r);

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
  mergeSort(vectorOfData, 0, vectorOfData.size() - 1);


  //stop timer
  auto stop = std::chrono::high_resolution_clock::now();

  //get duration
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  std::cout << "The k-th element where k is " << k << " is: " << vectorOfData[k - 1] << std::endl;
  std::cout << "Time taken by Merge Sort: "
           << duration.count() << " microseconds" << std::endl;
  return 0;
}

void mergeSort(std::vector<int> data, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) /2;
        mergeSort(data, left, middle);
        mergeSort(data, middle+1, right);
        merge(data, left, middle, right);
    }
}

void merge(std::vector<int> data, int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 =  right - middle;

    /* create temp arrays */
    std::vector<int> temp1;
    std::vector<int> temp2;
    temp1.reserve(n1);
    temp2.reserve(n2);

    /* Copy data to temp arrays L[] and R[] */
    for (int i = 0; i < n1; i++)
    {
        temp1.push_back(data[left + i]);
    }
    for (int j = 0; j < n2; j++)
    {
        temp2.push_back(data[middle + 1 + j]);
    }

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (temp1[i] <= temp2[j])
        {
            data[k] = temp1[i];
            i++;
        }
        else
        {
            data[k] = temp2[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        data[k] = temp1[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        data[k] = temp2[j];
        j++;
        k++;
    }
}
