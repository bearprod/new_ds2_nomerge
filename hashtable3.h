#ifndef hashtable3_H
#define hashtable3_H

#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

// this is double, make a second has function, and that hash value is the step factor 

// is h′(k) = q − (k mod q), for some prime number q < N


class hashtable3{
    
    public: 

    int size_fill; 
    int size_total;
    int misspelled_count = 0; 
    string* hash_array; 
    bool check_mode = false; 
    int hash_cof;

    hashtable3(int size){
        
        size_total = size * 2; 

        if(isPrime(size_total) == true){
            hash_array = new string[size_total];
            
            if(check_mode){
                cout << "initial size fond to be prime, init array of size:" << size_total << endl;
            }
        }
        else{
            size_total = findnextPrime(size_total);

            hash_array = new string[size_total];
            
            if(check_mode){
                cout << "found next prime number, init array of size:" << size_total << endl;
            }
        }

        for(int i = 0; i < size_total; i++){
            hash_array[i] = "null";
        }
        if(check_mode){
            cout << "init hash array of size size:" << size_total << endl;
        }
    }

    void print(){
        for(int i = 0; i < size_total; i++){
            cout << hash_array[i] << endl;
        }
    }


    void add_key(string key_to_add){

        int hash_number = hash_func(key_to_add); 

        string lower_key;

        lower_key = make_low(key_to_add);
        
        insert_key_at_index(lower_key, hash_number);

        return;

    }

    unsigned int hash_func(string key){
        unsigned int hash_val = 0;

        for (char ch: key){
            hash_val = 37 * hash_val + ch;
        }

        return hash_val % size_total;
    }



    void insert_key_at_index(string key, int hash_val_index){

        if(hash_val_index >= 0 && hash_val_index < size_total)
        {
            if(hash_array[hash_val_index] == "null"){
                hash_array[hash_val_index] = key;
                return;
        }
            else{

                int second_hash_result;
                second_hash_result = new_find_second_open(hash_val_index, key);
                
                if(second_hash_result != -1)
                {
                    hash_array[second_hash_result] = key;
                }
                else{

                    return;
                }
            }
        }
        else {
            throw out_of_range("in insert key call, hash func index out of bounds");
        }
    }
   

    int find_open_second(int last_index, string key){
        
        int sec_hash_val = second_hash(key);
        int step;
        int cur_ind = last_index;
        int room;
        int ind_to_start;
        int last_ind_array = size_total - 1;

        for(int i = 1; i * sec_hash_val < size_total; i++){
            step = i * sec_hash_val;
            if(cur_ind + step > last_ind_array){
                room = last_ind_array - cur_ind;
                ind_to_start = step - room - 1;
                cur_ind = ind_to_start;
            }
            else{
                cur_ind = cur_ind + step;
            }
            if(hash_array[cur_ind] == "null"){
                return cur_ind; 
            }
        }
        return -1;
    }

    int new_find_second_open(int last_index, string key){
        
        int sec_hash_val = second_hash(key);
        int step;
        int init_index = last_index;
        int ind_to_search;
        for(int i = 1; i < 100; i++){
            step = i * sec_hash_val;
            ind_to_search = (init_index + step) % size_total;
            if(hash_array[ind_to_search] == "null"){
                return ind_to_search; 
            }
        }
        return -1;
    }
    
    // need to change this 
    // i think u should just hash the index 
    // legit take indexd and step + and mod it, this will be way easier 
    // change paramter
    int second_hash(string key_to_hash){

        hash_cof = findlastprime(size_total);

        unsigned int hash_val = 0;

        for (char ch: key_to_hash){
            ch = tolower(ch);
            hash_val = 37 * hash_val + ch;  // these 3 functions could def be wrong
        }

        return hash_cof - (hash_val % hash_cof);

    }


    void search(string search_key){
        int hash_of_key;

        string lower_key;

        lower_key = make_low(search_key);

        if(lower_key != "empty bad string"){
           
            hash_of_key = hash_func(lower_key);

            if(search_for_hash_key_pair(lower_key, hash_of_key)){
                // cout << "found:" << lower_key << endl;
                return;
            }
            else{
                misspelled_count = misspelled_count + 1;
                // cout << "did not find: " << lower_key << endl;
                return;
            }
        }
        else{
            return;
        }

    }

    string make_low(string key){
        if(key.length() > 0)
            {
            for (int i = 0; i < key.length(); i++){
                key[i] = tolower(key[i]);
            }
            return key;
            }
        else{
            return "empty bad string";
            }
        }

    bool search_for_hash_key_pair(string key, int hash_ind){
        if(hash_ind >= 0 && hash_ind < size_total)
        {
            if(hash_array[hash_ind] == key){
                return true;
            }
            else{
                return new_second_search(hash_ind, key);
            }

        }
        else{
            throw out_of_range("hash func returned bad index");
        }
    }

    bool second_search(int last_index, string key){
        
        int sec_hash_val = second_hash(key);
        int step;
        int cur_ind = last_index;
        int room;
        int ind_to_start;
        int last_ind_array = size_total - 1;

        for(int i = 1; i * sec_hash_val < size_total; i++){
            step = i * sec_hash_val;
            if(cur_ind + step > last_ind_array){
                room = last_ind_array - cur_ind;
                ind_to_start = step - room - 1;
                cur_ind = ind_to_start;
            }
            else{
                cur_ind = cur_ind + step;
            }
            if(hash_array[cur_ind] == key){
                return true; 
            }
        }
        return false;
    }

    bool new_second_search(int last_index, string key){
        int sec_hash_val = second_hash(key);
        int step;
        int ind_to_search;
        int init_index = last_index;

        for(int i = 1; i < 100; i++){
            step = i * sec_hash_val;
            ind_to_search = (init_index + step) % size_total;
            if(hash_array[ind_to_search] == key){
                return true; 
            }
        }
        return false;
    }

    


    bool isPrime(int number){
        for(int i = 2; i < number; i++){
            if(number % i == 0){
                return false;
            }
        }
        return true;
    }

    int findnextPrime(int number){
        int cur_number = number;
        while(isPrime(cur_number) != true)
        {
            cur_number = cur_number + 1;
        }
        return cur_number;
    }

    int findlastprime(int number){
        int cur_number = number;
        while(isPrime(cur_number) != true)
        {
            cur_number = cur_number - 1;
        }
        return cur_number;
    }


};

#endif