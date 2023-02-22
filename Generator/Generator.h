#include <string>
#include <vector>


using namespace std;

class Generator {
public:
	Generator(int j, int k, long long modVal, string seed, int length);
	void generateMatrix();
	void sortPage(int page);
	void sortAll();
	vector<vector<unsigned long>> & get_numbersMatrix();
	int get_pages();
	int get_length();
private:
	int j, k, pages, length;
	long long modVal;
	vector<unsigned long> arrSeed;
	vector<vector<unsigned long>> numbersMatrix;
	void seedToArray(string seed);
};