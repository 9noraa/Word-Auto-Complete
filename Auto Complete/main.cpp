/*Name: Aaron Cohen
fsuid: ajc17d */

			//includes for the program
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>

using namespace std; 

			//Function initialization that prints the results of the search terms
void PrintResults(string user, int size, int max_length, list<string> word, list<string> inst);

			//My main function takes arguments for the file and result lengths
int main(int argc, char* argv[])
{

			//convert the character strings to integers
  int result_length = atoi(argv[2]);
  int complete_length = atoi(argv[3]);
  string response, instances, word;
			//opening a file for input with the command line argument
  ifstream WikFile;
  WikFile.open(argv[1]);
			//File opening error checking
  if(!WikFile)
    {
      cerr << "Failed\n";
      exit(1);
    }
			//Initializing the list
  list<string> WordList;
  list<string> InstList;
			//Reading the file into the list
  while(!WikFile.eof())
  {
    WikFile >> instances >> word;
			//getline for cities.txt (correctly reads in the cities)
    //getline(WikFile, word, '\n');
    //WikFile.ignore();
    WordList.push_back(word);
    InstList.push_back(instances);
  }
  WikFile.close();
			//code that would print the contents of the list
  /*for(list<string>::iterator i = WordList.begin(); i != WordList.end(); ++i)
  {
    cout << *i << endl; 
  }
  for(list<string>::iterator i = InstList.begin(); i != InstList.end(); ++i)
  {
    cout << *i << endl; 
  }*/
			//Asking the user for input and reading their response
  cout << "Ask me which is the most popular! " << endl;
  cin >> response;
			//Calling function to print the response 
  PrintResults(response, result_length, complete_length, WordList, InstList);
			//do while loop for multiple autocompletes
  do
  {
    cout << "Ask me for another autocomplete. " << endl;
    cin >> response;
    PrintResults(response, result_length, complete_length, WordList, InstList);
  }while(response != "quit");
}


void PrintResults(string user, int size, int max_length, list<string> word, list<string> inst)
{
			//Making temp variables to store the index of the list
  int count = 0, temp = 0, temp_arr[size];
  string word_arr[size], inst_arr[size];
  cout << "Top answers for" << " '" << user << "' " << endl;
			//Finding the user input matches in the list
  for(list<string>::iterator i = word.begin(); i != word.end(); ++i)
  {
    if((*i).find(user) == 0 && (*i).length() < max_length)
    {
      word_arr[temp] = *i;
      temp_arr[temp] = count;
      temp++;
    }
    if(temp == size)
    {
      break;
    }
    count++;
  }
  temp = 0;
  count = 0;
			//finding and printing the corresponding amount of instances
  for(list<string>::iterator i = inst.begin(); i != inst.end(); ++i)
   {
    if(temp_arr[temp] == count)
    {
      inst_arr[temp] = *i;
      temp++;
    }
    count++;
  } 
  for(int i = 0; i < temp; i++)
  {
    cout << "\t " << (i+1) << " " << word_arr[i] << " (" << inst_arr[i] << " instances)" << endl; 
  }
}
