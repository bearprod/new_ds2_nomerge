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

        int hash_number;

        string lower_key;

        lower_key = make_low(key_to_add);

        hash_number = hash_func(lower_key); 

        insert_key_at_index(lower_key, hash_number);

    }

int hashtable2::hash_func(string key){
        unsigned int hash_val = 0;

        unsigned int ret_val;

        for (char ch: key){
            ch = tolower(ch);
            hash_val = 2129 * hash_val + ch;
        }

        ret_val = hash_val % size_total;
        return ret_val;
    }



void hashtable2::insert_key_at_index(string key, int hash_val_index){

    unsigned int new_index;
    new_index = hash_val_index;        
    if(hash_array[hash_val_index] == "null"){
            hash_array[hash_val_index] = key;
            return;
        }
    else{
            for(int i = 0; i < size_total; i++){
                new_index = (new_index + (i * i)) % size_total;
                if(hash_array[new_index] == "null"){
                    hash_array[new_index] = key;
                    return;
                }                

            }
       }
       return;
            

    }


    
void hashtable2::search(string search_key){
        int hash_of_key;

        string lower_key;

        lower_key = make_low(search_key);

        hash_of_key = hash_func(lower_key);

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
        
    unsigned int new_index;
    new_index = hash_ind;        
    if(hash_array[hash_ind] == key){
            hash_array[hash_ind] = key;
            return true;
        }
    else{
            for(int i = 0; i < size_total; i++){
                new_index = (new_index + (i * i)) % size_total;
                if(hash_array[new_index] == key){
                    hash_array[new_index] = key;
                    return true;
                }                

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



