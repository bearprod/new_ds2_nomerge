#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <limits>
#include<regex>
#include <cctype>
#include <sstream> // dont need this 
#include "hashtable2.h"
#include "hashtable1.h"
#include "hashtable3.h"

using namespace std;
using namespace std::chrono;

// for each hash
// print time to construct
// print time to search
// print number of misspelled words


int main(int argc,  char **argv)
{

    regex regex("[A-Za-z-]+");
    
    bool main_check = false;

    string dict_file_name = "dictionaryFile2.txt";

    ifstream dict_file;

    int count_of_dict_words = 0;
    
    string iter_line;

    dict_file.open(dict_file_name);
    if(!dict_file.eof()){

        while(getline(dict_file, iter_line)){
            count_of_dict_words = count_of_dict_words + 1;
        }
    }

    dict_file.close();


    if(main_check){
        cout << "from main call, init hash table with size param:" << count_of_dict_words << endl;
    }

    hashtable2 second_hash(count_of_dict_words);

    string dict_line;

    int dict_test;

    dict_file.open(dict_file_name);
    if(!dict_file.eof()){

        while(getline(dict_file, dict_line)){

            smatch dict_result;
            
            for (sregex_iterator iter(dict_line.begin(), dict_line.end(), regex); iter != sregex_iterator(); ++iter){
                    
            
                    dict_result = *iter;

                    // cout << dict_result.str() << endl;

                    second_hash.add_key(dict_result.str());  

                    // cout << second_hash.hash_func(dict_result.str()) << endl;

            }

        }
    }

    cout << "ended foor loops" << endl;
  
    dict_file.close();


   // second_hash.print_index(5);
    


    if(main_check){
        cout << "hashed hash table:" << endl;
    }


    string input_file_name = "inputFile2.txt";


    ifstream input_file;

    input_file.open(input_file_name);

    if(!input_file.eof())
    {
        string reg_line;

        // cout << "about to read in input file shit" << endl;
        while(getline(input_file, reg_line)){

            smatch result;

            int reg_test;
        
            for (sregex_iterator iter(reg_line.begin(), reg_line.end(), regex); iter != sregex_iterator(); ++iter){
                    
                    result = *iter;

                    // cout << "last word before seg fault" << result.str() << endl;

                    second_hash.search(result.str());

            }
        }
    input_file.close();

    cout << "size of hash " << second_hash.size_total << endl;
    cout << "numer of misspelled words: " << second_hash.misspelled_count << endl;
    
    }
    return 1;
}


