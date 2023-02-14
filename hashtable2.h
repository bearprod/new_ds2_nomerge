#ifndef hashtable2_H
#define hashtable2_H

#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;


class hashtable2{
    
    public: 

    int size_fill; 
    int size_total;
    int misspelled_count = 0; 
    string* hash_array; 
    bool check_mode = true; 

    hashtable2(int size){
        
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

        insert_key_at_index(key_to_add, hash_number);

    }

    int hash_func(string key){
        unsigned int hash_val = 0;

        for (char ch: key){
            ch = tolower(ch);
            hash_val = 2129 * hash_val + ch;
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
                int quad_return;
                quad_return = quad_probe(hash_val_index);

                if(quad_return != -1)
                {
                    insert_key_at_index(key, quad_return);
                }
                else{
                    cout << "looped through array, i*i > size_total, could not find " << endl;
                    return;
                }
            }
        }
        else {
            throw out_of_range("in insert key call, hash func index out of bounds");
        }
    }
   
    int quad_probe(int last_index_checked){
        int cur_ind = last_index_checked;
        int room;
        int ind_to_start;
        int search_index_step;
        int last_index = size_total - 1;
        for(int i = 1; i * i < size_total; i++){
            search_index_step = i * i;
            if(cur_ind + i > last_index){
                room = last_index - cur_ind;
                ind_to_start = search_index_step - room - 1;
                cur_ind = ind_to_start;
            }
            else{
                cur_ind = cur_ind + search_index_step;
            }
            if(hash_array[cur_ind] == "null"){
                return cur_ind; 
            }
          
        }
        return -1;
    }

    // search for string - this is spell check, if cant find, add to array of misspeled, loading
    // maybe bool, idk, or return of soemthign def, add to misspelled cout
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
                return quad_search(key, hash_ind);
            }

        }
        else{
            throw out_of_range("hash func returned bad index");
        }
    }

    bool quad_search(string key, int last_ind){
        int cur_ind = last_ind;
        int room;
        int ind_to_start;
        int search_index_step;
        int last_index = size_total - 1;
        for(int i = 1; i * i < size_total; i++){
            search_index_step = i * i;
            if(cur_ind + search_index_step > last_index){
                room = last_index - cur_ind;
                ind_to_start = search_index_step - room - 1;
                cur_ind = ind_to_start;
            }
            else{
                cur_ind = cur_ind + search_index_step;
            }
            if(hash_array[cur_ind] == key){
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


};


#endif