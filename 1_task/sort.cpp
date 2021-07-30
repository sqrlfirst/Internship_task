#include <vector>
#include <sorting.h>

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