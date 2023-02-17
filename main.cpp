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

    duration<double, nano> hash1_add;
    duration<double, nano> hash1_search;

    duration<double, nano> hash2_add;
    duration<double, nano> hash2_search;

    regex regex("[A-Za-z]+(-[A-Za-z]+)?"); // regex tp search for words and include hyphen

    string dict_file_name = argv[1];

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

    hashtable3 first_hash(count_of_dict_words);

    hashtable2 second_hash(count_of_dict_words);

    string dict_line;

    int dict_test;

    auto hash1_add_start = steady_clock::now();

    dict_file.open(dict_file_name);
    if(!dict_file.eof()){

        while(getline(dict_file, dict_line)){

            smatch dict_result;
            
            for (sregex_iterator iter(dict_line.begin(), dict_line.end(), regex); iter != sregex_iterator(); ++iter){
                    
            
                    dict_result = *iter;

                    first_hash.add_key(dict_result.str());  

            }

        }
    }
  
    dict_file.close();

    auto hash1_add_stop = steady_clock::now();

    hash1_add = hash1_add_stop - hash1_add_start; 

    
    string input_file_name = argv[2];

    ifstream input_file;

    auto hash1_search_start = steady_clock::now();

    input_file.open(input_file_name);

    if(!input_file.eof())
    {
        string reg_line;

        while(getline(input_file, reg_line)){

            smatch result;

            int reg_test;
        
            // regex iterator that iterates from beginning to end of line and searches for words, assigns each result to smatch object, use str() to return string
            for (sregex_iterator iter(reg_line.begin(), reg_line.end(), regex); iter != sregex_iterator(); ++iter){
                    
                    result = *iter;

                    first_hash.search(result.str());

            }
        }
    input_file.close();

    auto hash1_search_stop = steady_clock::now();
    
    hash1_search = hash1_search_stop - hash1_search_start; 

    cout << "time for hash1 add " << hash1_add.count() << " nanoseconds"  << endl;

    cout << "time for hash1 search " << hash1_search.count()<< " nanoseconds"  << endl;

    cout << "number of misspelled words for hash1: " << first_hash.misspelled_count << endl;
    
    }

    return 1;

     // now we start second hash, which is quad probe 

    auto hash2_add_start = steady_clock::now();

    dict_file.open(dict_file_name);
    if(!dict_file.eof()){

        while(getline(dict_file, dict_line)){

            smatch dict_result;
            
            for (sregex_iterator iter(dict_line.begin(), dict_line.end(), regex); iter != sregex_iterator(); ++iter){
                    
            
                    dict_result = *iter;

                    second_hash.add_key(dict_result.str());  

            }

        }
    }

    dict_file.close();

    auto hash2_add_stop = steady_clock::now();

    hash2_add = hash2_add_stop - hash2_add_start; 


    auto hash2_search_start = steady_clock::now();

    input_file.open(input_file_name);

    if(!input_file.eof())
    {
        string reg_line;

        while(getline(input_file, reg_line)){

            smatch result;

            int reg_test;
        
            for (sregex_iterator iter(reg_line.begin(), reg_line.end(), regex); iter != sregex_iterator(); ++iter){
                    
                    result = *iter;

                    second_hash.search(result.str());

            }
        }
    input_file.close();

    auto hash2_search_stop = steady_clock::now();
    
    hash2_search = hash2_search_stop - hash2_search_start; 

    cout << "time for hash2 add " << hash2_add.count() << " nanoseconds" << endl;

    cout << "time for hash2 search " << hash2_search.count() << " nanoseconds" << endl;

    cout << "number of misspelled words for hash2: " << second_hash.misspelled_count << endl;
    
    }




    return 1;
}


