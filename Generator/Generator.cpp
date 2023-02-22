#include "Generator.h"
#include <Windows.h>
#include <algorithm>

Generator::Generator(int j, int k, long long modVal, string seed, int length) 
{
	this->j = j;
	this->k = k;
	this->modVal = modVal;
	this->length = length;
	if (length / 240 == 0) 
	{
		this->pages = 1;
	}
	else 
	{
		this->pages = (length / 240) + 1;
	}
	seedToArray(seed);
}

void Generator::generateMatrix()
{
	int counter = length;
	unsigned long num;
	numbersMatrix.clear();
	numbersMatrix.resize(this->pages);
	int indexOfGeneratedElement = arrSeed.size();
	for (int i = 0; i < pages; i++) {
		for (int f = 0; f < 240; f++) {
			if (counter == 0)
				break;
			num = (arrSeed[indexOfGeneratedElement - j] + arrSeed[indexOfGeneratedElement - k]) % modVal;
			numbersMatrix[i].push_back(num);
			for (int t = 0; t < indexOfGeneratedElement - 1; t++) {
				arrSeed[t] = arrSeed[t + 1];
			}
			arrSeed[indexOfGeneratedElement - 1] = num;
			counter--;
		}
	}
}

vector<vector<unsigned long>> & Generator::get_numbersMatrix()
{
	return numbersMatrix;
}

void Generator::seedToArray(string seed)
{
	int n = seed.size();
	for (int i = 0; i < n; i++) {
        arrSeed.push_back(seed[i] - '0');
    }
}

void Generator::sortPage(int page) 
{
	sort(numbersMatrix[page].begin(), numbersMatrix[page].end());
}

void Generator::sortAll() 
{
	int counter = length;
	unsigned long num;
	vector<unsigned long> temp;
	for (int i = 0; i < pages; i++) 
	{
		for (int j = 0; j < 240; j++) 
		{
			if (counter == 0)
				break;
			num = numbersMatrix[i][j];
			temp.push_back(num);
			counter--;
		}
	}

	sort(temp.begin(), temp.end());

	counter = length;
	int tempCounter = 0;
	numbersMatrix.clear();
	numbersMatrix.resize(this->pages);

	for (int i = 0; i < pages; i++)
	{
		for (int j = 0; j < 240; j++)
		{
			if (counter == 0)
				break;
			numbersMatrix[i].push_back(temp[tempCounter]);
			counter--;
			tempCounter++;
		}
	}
}

int Generator::get_pages() 
{
	return this->pages;
}

int Generator::get_length() 
{
	return this->length;
}






