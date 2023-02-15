#include "hashtable2.h"

using namespace std;

 hashtable2::hashtable2(int size){
        
        size_total = size * 2; 

        if(isPrime(size_total) == true){
            hash_array = new string[size_total];
            
        }
        else{
            size_total = findnextPrime(size_total);

            hash_array = new string[size_total];
            
        
        }

        for(int i = 0; i < size_total; i++){
            hash_array[i] = "null";
        }
    }

void hashtable2::add_key(string key_to_add){

        int hash_number = hash_func(key_to_add); 

        insert_key_at_index(key_to_add, hash_number);

    }

int hashtable2::hash_func(string key){
        unsigned int hash_val = 0;

        for (char ch: key){
            ch = tolower(ch);
            hash_val = 2129 * hash_val + ch;
        }

        return hash_val % size_total;
    }



void hashtable2::insert_key_at_index(string key, int hash_val_index){

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

int hashtable2::quad_probe(int last_index){
        int init_ind = last_index;
        int check_ind;
        int quad_fact;
        for(int i = 1; i*i < size_total; i++){
            quad_fact = i*i;
            check_ind = (init_ind + quad_fact) % size_total;
            if(hash_array[check_ind] == "null"){
                return check_ind; 
            }

        }
        return -1;

    }

    
void hashtable2::search(string search_key){
        int hash_of_key;

        string lower_key;

        lower_key = make_low(search_key);

        if(lower_key != "empty bad string"){
           
            hash_of_key = hash_func(lower_key);

            if(search_for_hash_key_pair(lower_key, hash_of_key)){
                
                return;
            }
            else{
                misspelled_count = misspelled_count + 1;
    
                return;
            }
        }
        else{
            return;
        }

    }

string hashtable2::make_low(string key){
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

bool hashtable2::search_for_hash_key_pair(string key, int hash_ind){
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


int hashtable2::quad_search(string key, int last_ind){
        int init_ind = last_ind;
        int check_ind;
        int quad_fact;
        for(int i = 1; i*i < size_total; i++){
            quad_fact = i*i;
            check_ind = (init_ind + quad_fact) % size_total;
            if(hash_array[check_ind] == key){
                return true; 
            }

        }
        return false;

    }
    


bool hashtable2::isPrime(int number){
        for(int i = 2; i < number; i++){
            if(number % i == 0){
                return false;
            }
        }
        return true;
    }

int hashtable2::findnextPrime(int number){
        int cur_number = number;
        while(isPrime(cur_number) != true)
        {
            cur_number = cur_number + 1;
        }
        return cur_number;
    }



