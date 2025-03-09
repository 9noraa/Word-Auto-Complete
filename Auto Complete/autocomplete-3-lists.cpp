/*Name: Aaron Cohen
fsuid: ajc17d */

			//includes for the 3 list program
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

			//function declarations
void PrintLists(vector<list<string> > V1, list<string> L1, int sub_length, int max_length);

void PrintResults(string input, list<string> L1, int max_length);

bool ValidSearch(string input, vector<list<string> > V1, int sub_length);

			//My main function takes in arguments for file and sub string length
int main(int argc, char* argv[])
{
			//variable initialization
  string occurences, word, sub, input;
  int result_length = atoi(argv[2]);
  int sub_length = atoi(argv[3]);
			//initializing a vector lists that will hold the substrings of each length
  vector<list<string> > L1(sub_length, list<string>());
			//Next list holds the values taken from the file
  list<string> L2;
			//opening a file for input
  ifstream input_file;
  input_file.open(argv[1]);
			//file error checking
  if(!input_file)
  {
    cerr << "Failed." << endl;
    exit(1);
  }
			//reading until the end of the file and taking values as input
  while(!input_file.eof())
  {
    input_file.ignore();
    input_file >> occurences >> word;
    for(int i = 0; i < sub_length; i++)
    {
			//getting sub strings 
      sub = word.substr(0, (i+1));
      L1[i].push_back(sub);
    }
    L2.push_back(word);
    L2.push_back(occurences);    
  }
			//closing file 
  input_file.close();
  cout << "Search Terms: " << endl;
			//prints the available search terms
  PrintLists(L1, L2, sub_length, result_length);
			//a do while loop that gets user input and prints the results
  do
  {
    cout << "Ask me for an autocomplete (type 'quit' to exit)" << endl;
    cin >> input;
    while(!ValidSearch(input, L1, sub_length))
    {
      if(input == "quit")
      {
        exit(1);
      }
      cout << "Invalid search term. Try again: " << endl;
      cin >> input;
    }
    PrintResults(input, L2, result_length);
  }while(input != "quit");
}

			//a function that goes through the vector list and prints each possible search term
void PrintLists(vector<list<string> > V1, list<string> L1, int sub_length, int max_length)
{
  for(int i = 0; i < sub_length; i++)
  {
    cout << "st[" << (i+1) << "]: " << endl;
    for(list<string>::iterator j = V1[i].begin(); j != V1[i].end(); ++j)
    {
      cout << "\tsearch term = '" << *j << "'" << endl;
      PrintResults(*j, L1, max_length);
    }
  }
  
}

void PrintResults(string input, list<string> L1, int max_length)
{
			//used an indicator variable to print the correct word and occurences 
  int indicator = 0;
  string temp;
			//iterating through the list
  for(list<string>::iterator i = L1.begin(); i != L1.end(); ++i)
  {
    if(indicator == 1)
    {
      cout << "\t\t(occurence,word) pair = (" << *i << ",'";
      cout << temp << "')" << endl;
      indicator = 0;
    }
    if((*i).find(input) == 0 && (*i).length() <= max_length)
    {
      temp = *i;
      indicator = 1;
    }
  }
}

			//function that makes sure the user inputs a valid search term from the matrix
bool ValidSearch(string input, vector<list<string> > V1, int sub_length)
{
  for(int i = 0; i < sub_length; i++)
  {
			//iterating through the vector of search terms
    for(list<string>::iterator j = V1[i].begin(); j != V1[i].end(); ++j)
    {
      if(input == *j)
      {
        return true;
      }
    }
  }
  return false;
}
