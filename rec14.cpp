//@file: rec14.cpp
//@author: Michael Chen
//@date: 12/8/2022


#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;


// Task 9
void print_list(const list<int>& ls){
    for(list<int>::const_iterator const_iter = ls.begin(); const_iter != ls.end(); ++const_iter){
        cout << *const_iter << "    ";
    }
}

// Task 10
void rangedFor_print_list(const list<int>& ls){
    for(int i: ls){
        cout << i << "  ";
    }
}


//Task 11
void auto_print_otherLs(const list<int>& ls){
    for(auto const_iter = ls.begin(); const_iter != ls.end();++ ++const_iter){
        cout << *const_iter << "    ";
    }
    
}

// Task 12
list<int>::const_iterator find_list(const list<int>& ls, int val){
    for(list<int>::const_iterator const_iter = ls.begin(); const_iter != ls.end(); ++const_iter){
        if(*const_iter == val){
            return const_iter;
        }
    }
    return ls.end();
}

// Task 13
auto find_list_auto(const list<int>& ls, int val){
    for(auto const_iter = ls.begin(); const_iter != ls.end();++const_iter){
        if(*const_iter == val){
            return const_iter;
        }
    }
    return ls.end();
}

// Task 15
bool isEven(int num){ return (num%2 == 0);}

// Task 16
struct EvenFunctor{
    bool operator()(int num) const {
        return (num%2 == 0);
    }
};

// Task 19
list<int>::const_iterator ourFind(list<int>::const_iterator begin, list<int>::const_iterator end, int num){
    cout << "this is ourFind func" << endl;
    for(list<int>::const_iterator const_iter = begin; const_iter != end; ++const_iter){
        if(*const_iter == num){
            return const_iter;
        }
    }
    return end;
}

// Task 20
template<typename T, typename U>
T ourFind(T begin, T end, U num){
    cout << "this is ourFind template" << endl;
    for(T const_iter = begin; const_iter != end; ++const_iter){
        if(*const_iter == num){
            return const_iter;
        }
    }
    return end;
}





int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    
    vector<int> vec = {21,12,56,33,87,57,43,89};
    for(int ele: vec){
        cout << ele << "  ";
    }
    
    cout << "\n=======\n";
    
    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    
    list<int> ls(vec.begin(),vec.end());
    for(int ele: ls){
        cout << ele << "    ";
    }
    
    cout << endl;
    cout << "\n=======\n";
    
    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    
    sort(vec.begin(),vec.end());
    for(int ele: vec){
        cout << ele << "    ";
    }
    cout << endl;
    for(int ele: ls){
        cout << ele << "    ";
    }
    
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    
    
    for(size_t i = 0; i<vec.size();i+=2){
        cout << vec[i] << "   ";
    }
    

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";

//    for(size_t i = 0; i<ls.size();i+=2){
//        cout << ls[i] << "   ";
//    }
//
    
    
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";

    for(vector<int>::const_iterator const_iter = vec.begin();const_iter != vec.end();const_iter+=2){
        cout << *const_iter << "    ";
    }
    
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    
    for(list<int>::const_iterator const_iter = ls.begin(); const_iter != ls.end();++ ++const_iter){
        cout << *const_iter << "    ";
    }
    
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";

    ls.sort();
    for(int ele: ls){
        cout << ele << "    ";
    }
    
    
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";

    print_list(ls);
    
    cout << endl;
    cout << "=======\n";
    
    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    
    rangedFor_print_list(ls);
    
    cout << endl;
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";

    auto_print_otherLs(ls);
    
    cout << endl;
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    
    
    cout << "Finding 34" << endl;
    cout << *find_list(ls, 34)<< endl;
    
    cout << "Finding 87" <<  endl;
    cout << *find_list(ls, 87) << endl;
    

    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    
    
    cout << "auto Finding 34" << endl;
    cout << *find_list_auto(ls, 34)<< endl;
    
    cout << "auto Finding 87" <<  endl;
    cout << *find_list_auto(ls, 87) << endl;
    
    
    
    
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";

    
    cout << "generic Finding 34" << endl;
    
    list<int>::const_iterator const_iter1 = find(ls.begin(),ls.end(),34);
    if(const_iter1 == ls.end()){
        cout << "34 is not found in this list" << endl;
    } else {
        cout << *const_iter1 << endl;
    }
    
    cout << "generic Finding 87" <<  endl;
    
    list<int>::const_iterator const_iter2 = find(ls.begin(),ls.end(),87);
    if(const_iter2 == ls.end()){
        cout << "87 is not found in this list" << endl;
    } else {
        cout << *const_iter2 << endl;
    }
    
    
    
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    
    
    list<int>::const_iterator const_iter_if = find_if(ls.begin(),ls.end(),isEven);
    
    if(const_iter_if == ls.end()){
        cout << "no even int in this list" << endl;
    } else{
        cout << *const_iter_if << endl;
    }
    
    
    

    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    
    
    list<int>::const_iterator const_iterator_functor = find_if(ls.begin(),ls.end(),EvenFunctor());
    if(const_iterator_functor == ls.end()){
        cout << "no even int in this list" << endl;
    } else{
        cout << *const_iterator_functor<< endl;
    }
    

    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";

    list<int>::const_iterator const_iter_lambda = find_if(ls.begin(), ls.end(), [](int num)->bool{return num%2==0;});
    if(const_iter_lambda == ls.end()){
        cout << "no even int in this list" << endl;
    } else{
        cout << *const_iter_lambda<< endl;
    }
    
    
    
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    
    
    int* int_array = new int[ls.size()];
    copy(ls.begin(),ls.end(),int_array);
    for(size_t i = 0; i<ls.size();++i){
        cout << int_array[i] << "   ";
    }
    
    cout << "dynamic Finding 34" << endl;

    int* iterator_dyn1= find(int_array,int_array+ls.size(),34);
    if(iterator_dyn1 == int_array+ls.size()){
        cout << "34 is not found in this dynamic array" << endl;
    } else {
        cout << *iterator_dyn1 << endl;
    }

    cout << "generic Finding 87" <<  endl;
    
    int* iterator_dyn2= find(int_array,int_array+ls.size(),87);
    if(iterator_dyn2== int_array+ls.size()){
        cout << "87 is not found in this dynamic array" << endl;
    } else {
        cout << *iterator_dyn2 << endl;
    }
    
    
    delete [] int_array;
    
    cout << endl;
    
    

    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";

    cout << "ourFind Finding 34" << endl;
    
    list<int>::const_iterator const_iter_ourFind1 = ourFind(ls.begin(),ls.end(),34);
    if(const_iter_ourFind1 == ls.end()){
        cout << "34 is not found in this list" << endl;
    } else {
        cout << *const_iter_ourFind1 << endl;
    }
    
    cout << "generic Finding 87" <<  endl;
    
    list<int>::const_iterator const_iter_ourFind2 = ourFind(ls.begin(),ls.end(),87);
    if(const_iter_ourFind2 == ls.end()){
        cout << "87 is not found in this list" << endl;
    } else {
        cout << *const_iter_ourFind2 << endl;
    }
    
    
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";

    cout << "ourFind template vector Finding 34" << endl;
    vector<int>::const_iterator const_iter_temp1 = ourFind(vec.begin(),vec.end(),34);
    if(const_iter_temp1 == vec.end()){
        cout << "34 is not found in this list" << endl;
    } else {
        cout << *const_iter_temp1 << endl;
    }
    
    cout << "ourFind template vector Finding 87" << endl;
    vector<int>::const_iterator const_iter_temp2 = ourFind(vec.begin(),vec.end(),87);
    if(const_iter_temp2 == vec.end()){
        cout << "34 is not found in this list" << endl;
    } else {
        cout << *const_iter_temp2 << endl;
    }
    
    
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    
    //open file
    ifstream ifs("pooh-nopunc.txt");
    if(!ifs){
        cerr << "the file cannot be found" << endl;
        exit(1);
    }
    // create a vector of strings that take each word
    vector<string> words;
    string word;
    while(ifs>>word){
        vector<string>::const_iterator const_iter_word = find(words.begin(),words.end(),word);
        if(const_iter_word == words.end()){// if distinct
            words.push_back(word);
        }
    }
    ifs.close();
    //display size and contents
    cout << "the vector size is " << words.size() << endl;
    for(const string& item: words){
        cout << item << "   ";
    }

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    
    //open file
    ifstream ifs_set("pooh-nopunc.txt");
    if(!ifs_set){
        cerr << "the file cannot be found" << endl;
        exit(1);
    }
    
    set<string> words_set;
    string word_set;
    while(ifs_set >> word_set){
        if(words_set.find(word_set) == words_set.end()){
            words_set.insert(word_set);
        }
    }
    ifs_set.close();
    
    // display size and contents
    cout << "the set size is " << words_set.size() << endl;
    for(const string& item: words_set){
        cout << item << "   ";
    }
    
    
    

    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";

    
    ifstream ifs_map("pooh-nopunc.txt");
    if(!ifs_map){
        cerr << "the file cannot be found" << endl;
        exit(1);
    }
    
    map<string, vector<int>> words_map;
    string word_map;
    int counter = 0;
    while(ifs_map >> word_map){
        if(words_map.find(word_map)==words_map.end()){
            ++counter;
            words_map[word_map].push_back(counter);
        }
    }
    ifs_map.close();
    
//    string key;
//    int val;
    for(auto pair: words_map){
        cout << pair.first <<" is in the position of ";
        for(int ele: pair.second){
            cout << ele << "    ";
        }
    }
    
    cout << endl;
    
    cout << "=======\n";
}
