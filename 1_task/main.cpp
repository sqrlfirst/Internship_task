#include <iostream>
#include <vector>
#include <algo.h>

using namespace std;

unsigned int SIZE = 10000000;

int main(int argc, char **argv) {

    // initialization of numbers
    vector<int> numbers(size, 0);
    generate(numbers.begin(), numbers.end(), rand);
    
    vector<int> res1;
    vector<int> res2;
    vector<int> res3;

    // test 1st sort type
    res1 = threeWaysSort(numbers, NONPARITY_UP);
    // test 1st sort type
    res2 = threeWaysSort(numbers, PARITY_DOWN);
    // test 1st sort type
    res3 = threeWaysSort(numbers, MIXED);

    // check results
    // var1 : all elements are non-parity & placed in increasing order
    checkFirstSort(res1);
    // var2 : all elements are parity & placed in decreasing order
    checkSecondSort(res2);
    // var3 : first elements are parity & placed in increasing order     // развернуть var1 
    //        then elements are non-parity & placed in decreasing order  // развернуть var2
    checkThirdSort(res3);

}

typedef enum {
    NONPARITY_UP,
    PARITY_DOWN,
    MIXED
} sort_type_t;

vector<int> threeWaysSort(vector<int> &a, sort_type_t type) {
    int num_of_parity = 0;
    int num_of_non_parity = 0;
    // count number of parity and non-parity elements
    for (int i = 0; i < a.size(); i++) {
        if (a[i] % 2 == 0) {
            num_of_parity++;
        }
        else {
            num_of_non_parity++;
        }
    }
    
    vector<int> tmp;
    if (type == NONPARITY_UP) {
        tmp.reserve(num_of_non_parity);
    }
    else if (type == PARITY_DOWN) {
        tmp.reserve(num_of_parity);
    }
    else (type == MIXED) {
        tmp.reserve(a.size());
    }

    if (type == NONPARITY_UP) {
        // remove parity elements
        for (int i = 0; i < a.size(); i++) {
            if (a[i] % 2 != 0) {
                tmp.push_back(a[i]);
            }
        }
        // sort in increasing order
        sort(tmp.begin(), tmp.end());
    } 
    else if (type == PARITY_DOWN) { 
        // remove nonparity elements
        for (int i = 0; i < a.size(); i++) {
            if (tmp[i] % 2 == 0) {
                tmp.push_back(a[i]);
            }
        }
        // sort in decreasing order
        sort(tmp.rbegin(), tmp.rend() );

    }
    else if (type == MIXED) {
        // move parity elements into one vector, nonparity into another
        vector<int> tmp_par;\
        tmp_par.reserve(num_of_parity);
        vector<int> tmp_non_par;
        tmp_non_par.reserve(num_of_non_parity);
        for (int i = 0; i <a.size(); i++) {
            if (a[i] % 2 == 0) {
                tmp_par.push_back(a[i]);
            }
            else {
                tmp_non_par.push_back(a[i]);
            }
        }
        // sort parity into increasing order
        // sort nonparity in decreasing order
        sort(tmp_par.begin(), tmp_par.end() );
        sort(tmp_non_par.rbegin(), tmp_non_par.rend());

        // combine result
        tmp.insert(tmp.end(), tmp_par.begin(), tmp_par.end());
        tmp.insert(tmp.end(), tmp_non_par.begin(), tmp_non_par.end()); 

    }
    else {
        // Error
    }

} 


void checkFirstSort(vector<int> &vec) {
    int num_of_wrong_elem = 0;
    int num_of_wrong_elem_places = 0;

    for (int i = 0; i < vec.size(); i++) {
        if(i != 0) {
            if (vec[i] % 2 == 0) num_of_wrong_elem++;
            if (vec[i-1] > vec[i]) num_of_wrong_elem_places++;
        }
        else {
            if (vec[i] % 2 == 0) num_of_wrong_elem++;
        }
    }

    cout << "Test 1 done. Number of parity elements are: " << num_of_wrong_elem << '\n'
         << "             Number of elements in wrong places: " << num_of_wrong_elem_places << '\n';

    if ((num_of_wrong_elem == 0) && (num_of_wrong_elem_places == 0)) {
        cout << "TEST ENDED SUCCESFULL \n";
    }

}


void checkSecondSort(vector<int> &vec) {
    int num_of_wrong_elem = 0;
    int num_of_wrong_elem_places = 0;

    for (int i = 0; i < vec.size(); i++) {
        if(i != 0) {
            if (vec[i] % 2 != 0) num_of_wrong_elem++;
            if (vec[i-1] < vec[i]) num_of_wrong_elem_places++;
        }
        else {
            if (vec[i] % 2 != 0) num_of_wrong_elem++;
        }
    }

    cout << "Test 2 done. Number of non-parity elements are: " << num_of_wrong_elem << '\n'
         << "             Number of elements in wrong places: " << num_of_wrong_elem_places << '\n';

    if ((num_of_wrong_elem == 0) && (num_of_wrong_elem_places == 0)) {
        cout << "TEST ENDED SUCCESFULL\n";
    }
    else {
        cout << "TEST NOT PASSED\n";
    }
}


void checkThirdSort(vector<int> &vec) {
    int num_of_parity = 0;
    int num_of_non_parity = 0;
    // count number of parity and non-parity elements
    for (int i = 0; i < vec.size(); i++) {
        if (a[i] % 2 == 0) {
            num_of_parity++;
        }
        else {
            num_of_non_parity++;
        }
    }

    int wrong_par_elem = 0;
    int wrong_non_par_elem = 0;
    int wrong_par_elem_places = 0;
    int wrong_non_par_elem_places = 0;

    for (int i = 0; i < vec.size(); i++) {
        if ((i < num_of_parity) & (i != 0)) { // check parity elements
            if (vec[i] % 2 != 0) wrong_par_elem++;
            if (vec[i-1] > vec[i]) wrong_par_elem_places++;
        }
        else if ((i == 0) & (num_of_parity != 0)) { // check zero parity elements
            if (vec[i] % 2 != 0) wrong_par_elem++;
        }
        else if ((i == 0) & (num_of_parity == 0)) { // check zero non-parity elements
            if (vec[i] % 2 == 0) wrong_non_par_elem++;
        }
        else { // check non-parity elements
            // add special occasion for first element
            if (i == num_of_parity) {
                if(vec[i] % 2 == 0) wrong_non_par_elem++;
            }
            else {
                if(vec[i] % 2 == 0) wrong_non_par_elem++;
                if(vec[i-1] < vec[i]) wrong_non_par_elem_places++;
            }
        }
    }

    cout << "Test 3 done. Number of wrong parity elements are           : " << wrong_par_elem << '\n'
         << "             Number of parity elements in wrong places     : " << wrong_par_elem_places << '\n'
         << "             Number of wrong non-parity elements are       : " << wrong_non_par_elem << '\n'
         << "             Number of non-parity elements in wrong places : " << wrong_non_par_elem_places << '\n';

    int total_mistakes = wrong_par_elem + wrong_par_elem_places + wrong_non_par_elem + wrong_non_par_elem_places;

    if (total_mistakes == 0) {
        cout << "TEST ENDED SUCCESFULL\n";
    }
    else {
        cout << "TEST NOT PASSED\n";
    }
}



