#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;

struct wordCount
{
	string word;
	int count = 1;

	bool operator==(const wordCount& right)
	{
		return word == right.word;
	}

	friend ostream& operator<<(ostream& stream, const wordCount& i)
	{
		cout << i.word << " " << i.count;
		return stream;
	}
};

bool CompareWordCount(const wordCount& a, const wordCount& b)
{
	return a.count > b.count;
}

int main()
{
    //local variables
    ifstream inputFile;
    list<wordCount> wordStorage;
    string stringStorage;
    bool goodRead = false;
	bool added = false;

    //Open the file.
	inputFile.open("MobyDick.txt");
	if (inputFile.is_open())
	{
		cout << "File opened." << endl;
		goodRead = true;
	}
	else
	{
		cout << "File failed to open." << endl;
	}

    //Reads the book.
    while (goodRead == true)
	{
		if (inputFile >> stringStorage)
		{
			added = false;
			//Remove end punctuation.
			stringStorage.erase(remove_if(stringStorage.begin(), stringStorage.end(), ::ispunct), stringStorage.end());

            //Convert to lowercase.
			for (char &i : stringStorage)
			{
				i = tolower(i);
			}
                        
			wordCount word;
			word.word = stringStorage;
			stringStorage.clear();

			for (wordCount &i : wordStorage)
			{
				if (i == word && added == false)
				{
					i.count = i.count + 1;
					added = true;
				}
			}
			if (added == false)
			{
				wordStorage.push_front(word);
			}
		}
		else
		{
			goodRead = false;
		}
    }
	inputFile.close();
	cout << "File closed." << endl << endl;

	//sort.
	wordStorage.sort(CompareWordCount);

	//print first 25.
	int numberPrinted = 0;
	for (const auto& v : wordStorage)
	{
		cout << v << endl;
		++numberPrinted;
		if (numberPrinted == 25)
		{
			break;
		}
	}
}

