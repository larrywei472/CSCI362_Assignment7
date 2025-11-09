#include <iostream>
#include <list>
#include <random>
#include <vector>



constexpr const size_t RANDOM_GENERATED_NUMBER_AMOUNT = 1000;



class Hashmap{

    private:

        const int _table_size;      // In this assignment, it will always be 10
        std::vector<std::list<int>> _data_table;

    public:

        Hashmap(const int t_size) : _table_size(t_size), _data_table(_table_size){ 
            for(int x = 0 ; x < t_size ; x++){
                _data_table.at(x) = std::list<int>();
            }
        }

        Hashmap() : _table_size(9), _data_table(_table_size){
            for(int x = 0 ; x < 9 ; x++){
                _data_table.at(x) = std::list<int>();
            }
        }


        // Hash function used - get number in the tens place of the number
        int hash_function(const int num){
            if(_table_size != 9){
                std::cout << "Error: Wrong table size must be size 10 to use this hash function" << std::endl;
                exit(1);
            }

            if(num < 10 || num > 99){
                std::cout << "Error: hash_function(const int num) - num '" << num << "' does not fit in range [10,99]" << std::endl;
                exit(1);
            }

            return ((num / 10) - 1);
        }


        
        // Add to linked list if linked list does not already have value
        void add(const int value){
            size_t insert_index = hash_function(value);
            auto& i_list = _data_table.at(insert_index);

            bool add_value = true;
            for(std::list<int>::iterator it = i_list.begin() ; it != i_list.end() ; it++){
                if(*it == value){
                    add_value = false;
                }
            }
            if(add_value){
                i_list.push_back(value);
            }
        }


        // return it as a const so you cannot directly edit 
        const std::list<int>& table_list_at(const int table_index){
            return const_cast<const std::list<int>&>(_data_table.at(table_index));
        }

        void print_hashmap(){

            int cnt = 1;
            for(auto list : _data_table){

                std::cout << cnt << " | ";
                for(auto it = list.begin() ; it != list.end() ; it++){
                    std::cout << *it << " ";
                }
                std::cout << '\n';
                cnt++;
            }
        }

        void print_table(int row){
            row--;

            if(row < 0 || row > 9){
                std::cout << "Error: print_table(int row) - invalid row number" << std::endl;
                exit(1); 
            }

            auto& list = _data_table.at(row);
            std::cout << "row " << (row + 1) << ": ";
            for(auto it = list.begin() ; it != list.end() ; it++){
                std::cout << *it << " ";
            }
            std::cout << '\n';
        }

};




int main(){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(10, 99);

    std::vector<int> nums(RANDOM_GENERATED_NUMBER_AMOUNT);

    for(auto it = nums.begin() ; it != nums.end() ; it++){
        *it = dist(gen);
    }

    Hashmap h;
    for(int num : nums){
        h.add(num);
    }

    std::cout << "======================================================\n";
    std::cout << "Auto generated hashmap with removed duplicates\n";
    std::cout << "------------------------------------------------------\n";
    h.print_hashmap();


    std::cout << "======================================================\n";

    int row;
    std::cout << "Enter a table slot to print [1,9]" << std::endl;
    std::cin >> row;

    if(row < 1 || row > 9){
        std::cout << "Invalid row num. Exiting..." << std::endl;
        exit(1);
    }

    h.print_table(row);
    


}