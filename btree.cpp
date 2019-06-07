// Copyright (c) 2019, Matthew Chalifoux.

#include "btree.h"

// erases number from root and adjusts root
template<typename T>
void BTree<T>::shift_data(int i){
    // if target is in array i
    if(0 == i){
        T sub[data_count - 1];
        int l = 0;
        for(int p = 1; p < data_count ; ++p){
            sub[l] = data[p];
            ++l;
        }
        for(int p = 0; p < data_count - 1; ++p){
            data[p] = sub[p];
        }
        data_count -= 1;
//        cout << "11 data_count = " << data_count << endl;
//        for(int p = 0; p < data_count; ++p){
//            cout << "11 data[" << p << "] = " << data[p] << endl;
//        }
        return;
    }

    // if target is in last array
    if(i == data_count - 1){
        data[i] = T();
        data_count -= 1;
        //cout << "22 data_count = " << data_count << endl;
//        for(int p = 0; p < data_count; ++p){
//            cout << "22 data[" << p << "] = " << data[p] << endl;
//        }
        return;
    }

    // if target is in middle array
    T here[i], here2[data_count - (i + 1)];
    //cout << "here[j] (((((()))))) " << endl;
    for(int j = 0; j < i; ++j){
        here[j] = data[j];
        //cout << "here[" << j << "] = "  << here[j] << endl;
    }
    int p = 0;
    for(int j = i + 1; j < data_count ; ++j){
        here2[p] = data[j];
        ++p;
    }
    for(int j = 0; j < i; ++j){
        data[j] = here[j];
    }
    p = 0;
    for(int j = i; j < data_count - 1; ++j){
        data[j] = here2[p];
        ++p;
    }
    data_count -= 1;
//    cout << "33 data_count = " << data_count << endl;
//    for(int p = 0; p < data_count; ++p){
//        cout << "33 data[" << p << "] = " << data[p] << endl;
//    }
}
template<typename T>
void BTree<T>::case_three(int i){
    //cout << "case three in play" << endl;

    //Part A case 3
    T here;
    here = data[i - 1];
    subset[i - 1]->data[subset[i - 1]->data_count] = here;

    for(int p = i - 1; p < data_count - 1; ++p){
        data[p] = data[p + 1];
    }

    subset[i - 1]->data_count += 1;
    for(int p = 0; p < subset[i - 1]->data_count; ++p){
        cout << "subset[" << i - 1 << "] = " << subset[i - 1]->data[p];
    }
    data_count -= 1;

    //Part B case 3
    int u = subset[i - 1]->data_count;
    for(int p = 0; p < subset[i]->data_count; ++p){
        subset[i - 1]->data[u] = subset[i]->data[p];
        ++u;
        subset[i - 1]->data_count += 1;
    }
    //cout << "**" << endl;
    for(int p = 0; p < subset[i - 1]->data_count; ++p){
        cout << "subset[i - 1]->data[" << p << "] = " << subset[i - 1]->data[p] << endl;
    }

    int m = subset[i - 1]->child_count;
    for(int p = 0; p < subset[i]->child_count; ++p){
        subset[i - 1]->subset[m] = new BTree<T>;
        copy_tree(subset[i - 1]->subset[m], subset[i]->subset[p]);
        subset[i - 1]->data[m] = subset[i]->data[p];
        ++m;
        subset[i - 1]->child_count += 1;
    }
    subset[i]->data_count = 0;
    subset[i]->child_count = 0;

    // Part C

    subset[i]->clear_tree();
    for(int p = i; p < child_count - 1; ++p){
        copy_tree(subset[p], subset[p + 1]);
    }
//    for(int p = 0; p < child_count - 1; ++p) {
//        cout << "case_three !!@#@$#" << endl;
//        subset[p]->print_tree();
//    }



    child_count -= 1;


}
template<typename T>
void BTree<T>::case_four(int i){

    //cout << "case _four called" << endl;

    //Part A
    for(int p = subset[i + 1]->data_count; p > 0; --p){
        subset[i + 1]->data[p] = subset[i + 1]->data[p - 1];
        //cout << "11subset[i + 1]->data[p] = " <<subset[i + 1]->data[p] << endl;
    }

    subset[i + 1]->data[0] = data[data_count - 1];

    data_count -= 1;

    subset[i + 1]->data_count += 1;

    //Part B

    //cout << "subset[i].data_count = " << subset[i]->data_count << endl;
    int pol = subset[i]->data_count;
    int klp = subset[i + 1]->data_count + subset[i]->data_count;
    if(subset[i]->data_count > 0){
        //cout << "In here?" << endl;
        for(int p =  klp - 1; p > pol; --p){
            subset[i + 1]->data[p] = subset[i + 1]->data[p - pol];
        }

        for(int p = pol - 1; p >= 0; --p){

            subset[i + 1]->data[p] = subset[i]->data[p];
            subset[i + 1]->data_count += 1;
            //cout << "subset[i + 1]->data[" << p << "] = " << subset[i + 1]->data[p] << endl;
        }
        subset[i]->data_count = 0;
    }

    pol = subset[i]->child_count;
    klp = subset[i + 1]->child_count + subset[i]->child_count;
    if(subset[i]->child_count > 0){
        //cout << "here ???" << endl;
        for(int p = klp - 1; p >= pol; --p){
            subset[i + 1]->subset[p] = new BTree<T>;
            copy_tree(subset[i + 1]->subset[p],subset[i + 1]->subset[p - pol]);
            subset[i + 1]->subset[p]->print_tree();
        }

        for(int p = pol - 1; p >= 0; --p){
            copy_tree(subset[i + 1]->subset[p], subset[i]->subset[p]);
            subset[i + 1]->child_count += 1;
        }
        subset[i]->child_count = 0;
    }

    //Part C

    subset[i]->clear_tree();

    for(int p = 0; p < child_count - 1; ++p){
       copy_tree(subset[p], subset[p + 1]);
    }

    child_count -= 1;

}
template<typename T>
void BTree<T>::case_two(int i){
    //cout << "case two " << endl;

    // Part A

    T item = data[i];

    subset[i]->data[subset[i]->data_count] = item;

    for(int p = 0; p < data_count - 1; ++p){
        data[p] = data[p + 1];
    }

   //cout << "data_count = " << data_count << endl;
    data_count -= 1;
    //cout << "data_count = " << data_count << endl;

    for(int p = 0; p < data_count ; ++p){
        //cout << "data[" << p << "] = " << data[p] << endl;
    }

    subset[i]->data_count += 1;

    //Part B

    T plp = subset[i + 1]->data[0];

    data[data_count] = plp;

    data_count += 1;

    for(int p = 0; p < subset[i + 1]->data_count - 1; ++p){
        subset[i + 1]->data[p] = subset[i + 1]->data[p + 1];
    }

    subset[i + 1]->data_count -= 1;

    //Part C

    if(subset[i + 1]->child_count > 0){
        subset[i]->subset[subset[i]->child_count] = new BTree<T>;
        copy_tree(subset[i]->subset[subset[i]->child_count], subset[i + 1]->subset[0]);

        for(int p = 0; p < subset[i + 1]->child_count - 1; ++p){
            copy_tree(subset[i + 1]->subset[p], subset[i + 1]->subset[p + 1]);
        }

        subset[i]->child_count += 1;

        subset[i + 1]->child_count -= 1;
    }



}
template<typename T>
void BTree<T>::case_one(int i){
    //cout << "case one " << endl;
    //move subset[i]->data over to make room for data[i-1]
    //  then put data[i-1] in subset[i]->data[0]
    //  the add one to subset[i]->data_count
    T here;
    here = data[i -1];
    //cout << "here = " << here << endl;

    T sub[subset[i]->data_count];
    for(int p = 0; p < subset[i]->data_count ; ++p){
        sub[p] = subset[i]->data[p + 1];
        //cout << "sub[" << p << "] = " << sub[p] << endl;
    }
    //cout << "t " << endl;
    subset[i]->data[0] = here;
    //cout << "t " << endl;
    for(int p = 0; p < subset[i]->data_count; ++p){
        cout << "n " << endl;
        data[p + 1] = sub[p];
    }
    subset[i]->data_count += 1;
    //cout << "case one data_count = " << data_count << endl;
    for(int p = 0; p < subset[i]->data_count; ++p){
        cout << "case one subset[i]->data[" << p << "] = " << subset[i]->data[p] << endl;
    }

    // Transfer the final item of subset[i - 1]->data up to replace
    //      data[i-1] and subtract one from subset[i-1]->data_count

    T op;
    op = subset[i-1]->data[subset[i-1]->data_count - 1];
    //cout << "op = " << op  << endl;
    data[i-1] = op;
    subset[i-1]->data_count -= 1;

    // If subset[i -1] has children, transfer the final child of subset[i-1]
    //    over to the front of subset[i]
    //    add one to subset[i]->child_count
    //    subtract one from subset[i]->child_count


    if(subset[i -1]->child_count > 0){

        subset[i]->subset[subset[i]->child_count] = new BTree<T>;
        for(int p = subset[i]->child_count; p > 0; --p){
            subset[i]->subset[p]->clear_tree();
            copy_tree(subset[i]->subset[p],subset[i]->subset[p - 1]);
        }
        subset[i]->subset[0]->clear_tree();
        copy_tree(subset[i]->subset[0], subset[i -1]->subset[subset[i-1]->child_count - 1]);

        subset[i]->child_count += 1;
        subset[i - 1]->subset[subset[i - 1]->child_count - 1]->clear_tree();
        subset[i - 1]->child_count -= 1;
    }


    return;


}
template<typename T>
void BTree<T>::fix_shortage(int i){
    if(0 == i){
        if(subset[i + 1]->data_count > MINIMUM){
            case_two(i);
            return;
        }
        case_four(i);
        return;
    }
    if(i == child_count - 1){
        if(subset[i - 1]->data_count > MINIMUM){
            case_one(i);
            return;
        }
        case_three(i);
        return;
    }
    // Still need to set-up fix_shortage if in middle subset
    // Do this below
    if(subset[i + 1]->data_count > MINIMUM){
        case_two(i);
        return;
    }
    if(subset[i - 1]->data_count > MINIMUM){
        case_one(i);
        return;
    }
    if(subset[i + 1]->data_count == MINIMUM){
        case_four(i);
        return;
    }
    if(subset[i - 1]->data_count == MINIMUM){
        case_three(i);
    }
}
template<typename T>
void BTree<T>::remove_biggest(T& removed_entry){

    if(0 == child_count){
        removed_entry = data[data_count - 1];
        data_count -= 1;
    }

    if(0 != child_count){
        subset[child_count - 1]->remove_biggest(removed_entry);
        if(subset[child_count - 1]->data_count < MINIMUM){
            fix_shortage(child_count - 1);
            return;
        }
    }
}
template<typename T>
void BTree<T>::loose_erase(const T& target){
    // check if root has no children
    if(0 == child_count){
        // Check if target is in root
        for(int i = 0; i < data_count; ++i){
            // if target is IN root and has no children     B
            if(target == data[i]){
                shift_data(i);
                return;
            }
            // if target is NOT in root and has no children     A
            if(target < data[i]){
                return;
            }
        }
    }

    // check if root has children
    if(0 != child_count){
        // Check if target is in root
        for(int i = 0; i < data_count; ++i){
            // target is in root and has children     D
            if(target == data[i]){
                subset[i]->remove_biggest(data[i]);
                if(subset[i]->data_count < MINIMUM){
                    fix_shortage(i);
                    return;
                }
            }

            //target is not in root and has children     C
            if(target < data[0]){
                subset[0]->loose_erase(target);
                if(subset[0]->data_count < MINIMUM){
                    fix_shortage(0);
                }
                return;
            }

            if(target >= data[data_count - 1]){
                int cc = child_count - 1;
                subset[child_count - 1]->loose_erase(target);
                if(subset[cc]->data_count < MINIMUM){
                    fix_shortage(cc);
                }
                return;
            }

            int j = 0;
            bool stop = false;
            do{
                if(!(target >= data[j] && target <= data[j + 1])){
                    ++j;
                }
                else if(target >= data[j] && target <= data[j + 1]){
                    subset[j + 1]->loose_erase(target);
                    if(subset[j + 1]->data_count < MINIMUM){
                        fix_shortage(j + 1);
                    }
                    stop = true;
                    return;
                }
            }while(stop == false);
        }
    }
}
template<typename T>
void BTree<T>::fix_erase_root(int i){

    if(data_count < MINIMUM){

        //cout << "Hello" << endl;

        BTree<T> *here;
        here = new BTree<T>;
        copy_tree(here, subset[0]);


        clear_tree();

        for(int p = 0; p < here->data_count; ++p){

            data[p] = here->data[p];
            data_count += 1;
        }

        for(int p = 0; p < here->child_count; ++p){
            subset[p] = new BTree<T>;
            copy_tree(subset[p],here->subset[p]);
            child_count += 1;
        }

        here->clear_tree();
        here = NULL;

    }

}
template<typename T>
void BTree<T>::erase(const T& target){
    // check if root has no children
    if(0 == child_count){
        // Check if target is in root
        for(int i = 0; i < data_count; ++i){
            // if target is IN root and has no children     B
            if(target == data[i]){
                shift_data(i);
                return;
            }
            // if target is NOT in root and has no children     A
            if(target < data[i]){
                return;
            }
        }
    }

    // check if root has children
    if(0 != child_count){
        // Check if target is in root
        for(int i = 0; i < data_count; ++i){

            // target is in root and has children     D
            if(target == data[i]){
                subset[i]->remove_biggest(data[i]);
                if(subset[i]->data_count < MINIMUM){
                    fix_shortage(i);
                    return;
                }
                fix_erase_root(0);
                return;
            }
        }
        // target is not in root and has children     C
        if(target < data[0]){
            subset[0]->loose_erase(target);
            if(subset[0]->data_count < MINIMUM){
                fix_shortage(0);
            }
            fix_erase_root(0);
            return;
        }

        if(target >= data[data_count - 1]){
            int cc = child_count - 1;
            subset[child_count - 1]->loose_erase(target);
            if(subset[cc]->data_count < MINIMUM){
                fix_shortage(cc);
            }
            fix_erase_root(0);
            return;
        }

        int j = 0;
        bool stop = false;
        do{
            if(!(target >= data[j] && target <= data[j + 1])){
                ++j;
            }
            else if(target >= data[j] && target <= data[j + 1]){
                subset[j + 1]->loose_erase(target);
                if(subset[j + 1]->data_count < MINIMUM){
                    fix_shortage(j + 1);
                }
                fix_erase_root(0);
                stop = true;
                return;
            }
        }while(stop == false);
    }
}




//ALL FUCTIONS FOR INSERT BELOW
template<typename T>
void BTree<T>::insert(const T& item){
//    cout << "item = " << item << endl; // 190
//    cout << "data_count = " << data_count << endl; // 2
//    cout << "child_count = " << child_count << endl; // 3

    if(0 == child_count){
        if(check_Dups(item) == true){
            return;
        }
        enter_Data(item);
        fix_excess_root(0);
        return;
    }
    if(0 != child_count){
        if(item <= data[0]){
            insert_item(item,subset[0]);
            fix_excess(0);
            fix_excess_root(0);
            return;
        }
        if(item >= data[data_count - 1]){
            if(190 == item){
                //cout << "ITEM = " << item << endl;
            }
            int cc = child_count;
            insert_item(item,subset[cc - 1]);
            fix_excess(cc - 1);
            fix_excess_root(0);
            return;
        }

        int i = 0;
        bool stop = false;
        do{
            if(!(item >= data[i] && item <= data[i + 1])){
                ++i;
            }
            else if(item >= data[i] && item <= data[i + 1]){
                //cout << "ABOUT TO BE " << endl;
                insert_item(item,subset[i + 1]);
                fix_excess(i + 1);
                fix_excess_root(0);
                stop = true;
            }

        }while(stop == false);
    }
}
template<typename T>
void BTree<T>::insert_item(const T item, BTree<T> *ptr){
//    cout << "item = " << item << endl; // 190  190
//    cout << "ptr->data_count = " << ptr->data_count << endl; // 2  2
//    cout << "ptr->child_count = " << ptr->child_count << endl; // 3  0
//    cout << "child_count = " << child_count << endl; // 3  3
//    cout << "data_count = " << data_count << endl; // 2  2


    if(0 == ptr->child_count){
        if(ptr->check_Dups(item) == true){
            return;
        }
        ptr->enter_Data(item);
        return;
    }
    if(0 != ptr->child_count){
        if(item <= ptr->data[0]){
            ptr->insert_item(item,ptr->subset[0]);
            ptr->fix_excess(0);
            return;
        }
        if(item >= ptr->data[ptr->data_count - 1]){
            ptr->insert_item(item,ptr->subset[ptr->child_count - 1]);
            int cc = ptr->child_count;
            //cout << "going " << endl;
            ptr->fix_excess(ptr->child_count - 1);
            return;
        }
        int i = 0;
        bool stop = false;
        do{
            if(!(item >= ptr->data[i] && item <= ptr->data[i + 1])){
                ++i;
            }
            else if(item >= ptr->data[i] && item <= ptr->data[i + 1]){
                //cout << "GETTING HERE!!!!!!!!!!" << endl;
                 ptr->insert_item(item,ptr->subset[i + 1]);
                 //cout << "BACK HERE" << endl;
                ptr->fix_excess(i + 1);
                stop = true;
            }

        }while(stop == false);
    }
}
template<typename T>
void BTree<T>::make_twins(BTree<T> *twin, BTree<T> *twin2, int i, int num ){
//    cout << "FFFIIIXXX EXXCXCCEEESS" << endl;
//    cout << "data count = " << data_count << endl;
//    cout << "subset[i].child count = " << subset[i]->child_count << endl;
    int scc = subset[i]->child_count;

    BTree<T> *iop[subset[i]->child_count / 2], *iop2[subset[i]->child_count / 2];
    for(int p = 0; p < subset[i]->child_count / 2; ++p){
        iop[p] = new BTree<T>;
        copy_tree(iop[p],subset[i]->subset[p]);
    }
    int s = 0;
    for(int p = subset[i]->child_count / 2; p < subset[i]->child_count ; ++p){
        iop2[s] = new BTree<T>;
        copy_tree(iop2[s],subset[i]->subset[p]);
        ++s;
    }
    //cout << "WENT THROUGH " <<endl;





    T here[MINIMUM], here2[MINIMUM];
    //cout << "here[j] (((((()))))) " << endl;
    for(int j = 0; j < num; ++j){
        here[j] = subset[i]->data[j];
        //cout << "here[" << j << "] = "  << here[j] << endl;
    }
    int p = 0;
    for(int j = num + 1; j < MAXIMUM + 1; ++j){
        here2[p] = subset[i]->data[j];
        //cout << "here[" << p << "] = " << here2[p] << endl;
    }

    // NEED TO do this sometime
    //subset[i]->clear_tree();





    //cout << "FFFF twin = " << endl;
    for(int p = 0; p < MINIMUM; ++p){
        twin->enter_Data(here[p]);
        //cout << "twin[" << i << "] = " << twin->data[p] << endl;
        //subset[i]->data_count += 1;
    }




    //cout << "FFFF twin2 = " << endl;
    for(int p = 0; p < MINIMUM; ++p){
        twin2->enter_Data(here2[p]);
        //cout << "twin2[" << i + 1 << "] = " << twin2->data[p] << endl;
        //subset[i + 1]->data_count += 1;
    }


    for(int p = 0; p < scc / 2; ++p){
        twin->subset[p] = new BTree<T>;
        copy_tree(twin->subset[p],iop[p]);
        twin->child_count += 1;
    }

    for(int p = 0; p < scc / 2; ++p){
        twin2->subset[p] = new BTree<T>;
        copy_tree(twin2->subset[p],iop2[p]);
        twin2->child_count += 1;
    }
    //cout << "REALLY WENT THROUGH" << endl;
}
template<typename T>
void BTree<T>::split_Node(int i){
    //cout << "PRINT TREE subset[0]" << endl;
    //subset[i]->print_tree();

//    cout << "data count = " << data_count << endl;
//    cout << "subset[i].child count = " << subset[i]->child_count << endl;
    int scc = subset[i]->child_count;

    BTree<T> *iop[subset[i]->child_count / 2], *iop2[subset[i]->child_count / 2];
    for(int p = 0; p < subset[i]->child_count / 2; ++p){
        iop[p] = new BTree<T>;
        copy_tree(iop[p],subset[i]->subset[p]);
    }
    int s = 0;
    for(int p = subset[i]->child_count / 2; p < subset[i]->child_count ; ++p){
        iop2[s] = new BTree<T>;
        copy_tree(iop2[s],subset[i]->subset[p]);
        ++s;
    }


    int num;
    num = subset[i]->data_count / 2;
    //cout << "NUM = " << num << endl;

    enter_Data(subset[i]->data[num]);
    //cout << "DATA[0] = " << data[0] << endl;

    //MAYBE THIS WILL BE A FUTURE BUG!!!!!!!!!!!! i.e. child_count = 2;
    child_count = 2;


    T here[MINIMUM], here2[MINIMUM];
    //cout << "here[j] (((((()))))) " << endl;
    for(int j = 0; j < num; ++j){
        here[j] = subset[i]->data[j];
        //cout << "here[" << j << "] = "  << here[j] << endl;
    }
    int p = 0;
    for(int j = num + 1; j < MAXIMUM + 1; ++j){
        here2[p] = subset[i]->data[j];
        //cout << "here[" << p << "] = " << here[p] << endl;
    }


    subset[i]->clear_tree();
    subset[i] = new BTree<T>;
    //cout << "FFFF subset[i] = " << endl;
    for(int p = 0; p < MINIMUM; ++p){
        subset[i]->enter_Data(here[p]);
        //cout << "1111subset[" << i << "] = " << subset[i]->data[p] << endl;
        //subset[i]->data_count += 1;
    }

    subset[i + 1] = new BTree<T>;
    //cout << "FFFF subset[i + 1] = " << endl;
    for(int p = 0; p < MINIMUM; ++p){
        subset[i + 1]->enter_Data(here2[p]);
        //cout << "222subset[" << i + 1 << "] = " << subset[i + 1]->data[p] << endl;
        //subset[i + 1]->data_count += 1;
    }


    for(int p = 0; p < scc / 2; ++p){
        subset[i]->subset[p] = new BTree<T>;
        copy_tree(subset[i]->subset[p],iop[p]);
        subset[i]->child_count += 1;
    }



    for(int p = 0; p < scc / 2; ++p){
        subset[i + 1]->subset[p] = new BTree<T>;
        copy_tree(subset[i + 1]->subset[p],iop2[p]);
        subset[i + 1]->child_count += 1;
    }
}
template<typename T>
void BTree<T>:: fix_excess_root(int i){
    if(0 == i){
//        cout << "data count 0000 = " << data_count << endl;
//        cout << "child cout ---- = " << child_count << endl;

        if(MAXIMUM + 1 == data_count){

            if( MAXIMUM + 2 == child_count){
                //cout << "Hello World!" << endl;

                //cout << "check last Print Tree" << endl;
                //print_tree();
                BTree<T> *here;
                here = new BTree<T>;
                //cout << "child count = " << child_count << "  data count = " << data_count << endl;
                here->child_count = child_count;
                //cout << "HI" << endl;
                for(int i = 0; i < data_count; ++i){
                    //cout << "data[i] = " << data[i] << endl;
                    here->enter_Data(data[i]);
                    //cout << "here.data[i] = " << here->data[i] << endl;
                }
                int l = 0;
                for(int p = 0; p < here->child_count; ++p){
                    //cout << "not here" << endl;
                    here->subset[p] = new BTree<T>;
                    copy_tree(here->subset[p],subset[p]);
                }
                //cout << "HERE PRINT TREE" << endl;
                //here->print_tree();
                clear_tree();
//                cout << "Data count ccc = " << data_count << " child coutn ccc = " << child_count << endl;
//                cout << "sdfsdfdfdsf " << endl;
                //print_tree();
//                cout << "sdfgsgsdgsdgsg" << endl;
//                cout << "HERE PRINT TREE 2" << endl;
                //here->print_tree();
                subset[0] = new BTree<T>;
                copy_tree(subset[0],here);
                //cout << "TTTTTTTTTTTT" << endl;
                //subset[0]->print_tree();
                child_count = 1;
                fix_excess_root(0);



            }

            if(subset[i] == NULL ){
                //cout << "fix_excess_root" << endl;
                if(3 == data_count){
                    //cout << "check last Print Tree" << endl;
                    //print_tree();
                    BTree<T> *here;
                    here = new BTree<T>;
                    //cout << "child count = " << child_count << "  data count = " << data_count << endl;
                    here->child_count = child_count;
                    //cout << "HI" << endl;
                    for(int i = 0; i < data_count; ++i){
                        //cout << "data[i] = " << data[i] << endl;
                        here->enter_Data(data[i]);
                        //cout << "here.data[i] = " << here->data[i] << endl;
                    }
                    int l = 0;
                    for(int p = 0; p < here->child_count; ++p){
                        //cout << "not here" << endl;
                        here->subset[p] = new BTree<T>;
                        copy_tree(here->subset[p],subset[p]);
                    }
                    //cout << "HERE PRINT TREE" << endl;
                    //here->print_tree();
                    clear_tree();
                    //cout << "Data count ccc = " << data_count << " child coutn ccc = " << child_count << endl;
                    //cout << "sdfsdfdfdsf " << endl;
                    //print_tree();
                    //cout << "sdfgsgsdgsdgsg" << endl;
                    //cout << "HERE PRINT TREE 2" << endl;
                    //here->print_tree();
                    subset[0] = new BTree<T>;
                    copy_tree(subset[0],here);
                    child_count = 1;
                    fix_excess_root(0);
                    return;
                }
            }
        }
        if(1 == child_count){
            split_Node(i);
            return;
        }
    }
}
template<typename T>
void BTree<T>::fix_excess(int i){

//    cout << "FIX EXCESS subset[i]->data_count = " << subset[i]->data_count << endl; // 3  3
//    cout << "i = " << i << endl; // 0  0

    if(subset[i]->data_count != MAXIMUM + 1){
        //cout << "fix_excess   i = " << i << endl;
        return;
    }

    int num;
    num = (subset[i]->data_count) / 2;
    T item;
    item = subset[i]->data[num];
    enter_Data(item);
//    cout << "item = " << item << endl; // 3  5
//    cout << "num = " << num << endl; // 1  1
//    cout << "subset[i].data_count = " << subset[i]->data_count << endl; // 3  3
//    cout << "subset[i].child_count = " << subset[i]->child_count << endl; // 0  4
//    cout << "child_count = " << child_count << endl; // 3  2
//    cout << "data_count = " << data_count << endl; // 3  2
//    cout << "i = " << i << endl; // 0  0
    if(2 == subset[i]->data[0]){
        //cout << "2 is in fix_excess" << endl;
    }

    if(i == subset[i]->data_count - 1)
    {

        // Get the data values of root split in two
        T gub[num];
        T gub2[num];

        for(int j = 0; j < num; ++j){
            gub[j] = subset[i]->data[j];
        }
        for(int j = 0; j < num ; ++j){
            //cout << " gub[ " << j << " ] = " << gub[j] << endl; //23
         }

        int l = 0;
        for(int j = num + 1; j < subset[i]->data_count ; ++j){
            gub2[l] = subset[i]->data[j];
            //cout << "2222 gub2[" << l << "] = " << gub2[l] << endl;
            ++l;
        }
        l = 0;
        for(int j = num + 1; j < subset[i]->data_count ; ++j){
            //cout << "232323 gub2[" << l << "] = " << gub2[l] << endl; //180
            ++l;
        }




        BTree<T> *ptr[subset[i]->child_count / 2];
        BTree<T> *ptr2[subset[i]->child_count / 2];
        if(subset[i]->child_count > 0){
            for(int j = 0; j < subset[i]->child_count / 2; ++j){
                ptr[j] = new BTree<T>;
//                cout << "subset[i]->subset[j]->data[0] = "  << subset[i]->subset[j]->data[0] << endl;
//                cout << "subset[i]->subset[j]->data[0] = "  << subset[i]->subset[j + 1]->data[0] << endl;
//                cout << "subset[i]->subset[j]->data[0] = "  << subset[i]->subset[j + 2]->data[0] << endl;
//                cout << "subset[i]->subset[j]->data[0] = "  << subset[i]->subset[j + 3]->data[0] << endl;
                copy_tree(ptr[j],subset[i]->subset[j]);
//                cout << "printing ptr[j] tree " << endl;
//                ptr[j]->print_tree();
            }
            int l = 0;
            for(int j = subset[i]->child_count / 2; j < subset[i]->child_count; ++j){
                //cout << "got here" << endl;
//                cout << "subset[i]->subset[j]->data[0] = "  << subset[i]->subset[j]->data[0] << endl;
//                cout << "subset[i]->subset[j]->data[0] = "  << subset[i]->subset[j + 1]->data[0] << endl;
                ptr2[l] = new BTree<T>;
                copy_tree(ptr2[l],subset[i]->subset[j]);
//                cout << "printing ptr2[j] tree " << endl;
//                ptr2[l]->print_tree();
                ++l;
            }
        }
        //cout << "i = " << i << endl; //
        int scc2 = subset[i]->child_count / 2;
        bool turn = false;
        if(subset[i]->child_count > 0){
            turn = true;
        }
        else if(0 == subset[i]->child_count)
        {
            turn = false;
        }

        int y = subset[i]->data_count;
        //cout << "subset[i].printtree()" << endl;
        //subset[i]->print_tree();



        subset[i]->clear_tree();
        subset[i] = new BTree<T>;

        for(int j = 0; j < num; ++j){
            subset[i]->enter_Data(gub[j]);
            //cout << "subset[i]->data[j] = " << subset[i]->data[j] << endl;
        }

        subset[i + 1] = new BTree<T>;
        for(int j = 0; j < num; ++j){
            subset[i + 1]->enter_Data(gub2[j]);
            //cout << "0000subset[i + 1]->data[j] = " << subset[i + 1]->data[j] << endl;
        }




        if(turn == true){
//            cout  << "here" << endl;
//            cout << "scc2 = " << scc2 << endl;
            for(int j = 0; j < scc2; ++j){
                subset[i]->subset[j] = new BTree<T>;
                copy_tree(subset[i]->subset[j],ptr[j]);
                subset[i]->child_count += 1;
            }
        }
        if(turn == true){
            for(int j = 0; j < scc2; ++j){
                //cout << "here" << endl;
                subset[i + 1]->subset[j] = new BTree<T>;
                copy_tree(subset[i + 1]->subset[j],ptr2[j]);
                subset[i + 1]->child_count += 1;
            }
        }

        child_count += 1;
        return;

    }

    if(0 == i){
//        cout << "item = " << item << endl; // 3  5
//        cout << "num = " << num << endl; // 1  1
//        cout << "subset[i].data_count = " << subset[i]->data_count << endl; // 3  3
//        cout << "subset[i].child_count = " << subset[i]->child_count << endl; // 0  4
//        cout << "child_count = " << child_count << endl; // 3  2
//        cout << "data_count = " << data_count << endl; // 3  2
//        cout << "i = " << i << endl; // 0  0

        //Copies tree to the right of i
        BTree<T> *sub[child_count - (i + 1)];
        int p = 0;
        for(int j = i + 1; j <= child_count - 1; ++j){
            sub[p] = new BTree<T>;
            copy_tree(sub[p],subset[j]);
            ++p;
        }
        p = 0;
//        for(int j = i + 1; j <= child_count - 1; ++j){
//            //cout << "sub[p]***************" << endl;
//            sub[p]->print_tree();
//            ++p;
//            //cout << "********************" << endl;
//       }
       //for(int i = 1; i < child_count)
        p = 0;
        // Sets subset i + 2 to the correct position
        for(int j = i + 2; j <= child_count; ++j){
            subset[j] = new BTree<T>;
            copy_tree(subset[j],sub[p]);
            ++p;
        }
//            for(int j = i + 2; j <= child_count ; ++j){
//                //cout << "subset[j]***************" << endl;
//                subset[j]->print_tree();
//                //cout << "********************" << endl;
//            }

        // Get the data values of root split in two
        T gub[num ];
        T gub2[num];

        for(int j = 0; j < num; ++j){
            gub[j] = subset[i]->data[j];
        }
//            for(int j = 0; j < num ; ++j){
//                cout << " gub[j] = " << gub[j] << endl;
//             }

        int l = 0;
        for(int j = num + 1; j <= num * 2 ; ++j){
            gub2[l] = subset[i]->data[j];
            ++l;
        }
        l = 0;
//            for(int j = num + 1; j <= data_count ; ++j){
//                cout << " gub2[j] = " << gub2[l] << endl;
//                ++l;
//            }


        BTree<T> *ptr[subset[i]->child_count / 2];
        BTree<T> *ptr2[subset[i]->child_count / 2];
        if(subset[i]->child_count > 0){
            for(int j = 0; j < subset[i]->child_count / 2; ++j){
                ptr[j] = new BTree<T>;
                copy_tree(ptr[j],subset[i]->subset[j]);
                //ptr[j]->print_tree();
            }
            int l = 0;
            for(int j = subset[i]->child_count / 2; j < subset[i]->child_count; ++j){
                ptr2[l] = new BTree<T>;
                copy_tree(ptr2[l],subset[i]->subset[j]);
                ++l;
                //ptr[j]->print_tree();
            }
        }
//        cout << "item = " << item << endl; // 3  5
//        cout << "num = " << num << endl; // 1  1
//        cout << "subset[i].data_count = " << subset[i]->data_count << endl; // 3  3
//        cout << "subset[i].child_count = " << subset[i]->child_count << endl; // 0  4
//        cout << "child_count = " << child_count << endl; // 3  2
//        cout << "data_count = " << data_count << endl; // 3  2
//        cout << "i = " << i << endl; // 0  0
        //cout << "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH" << endl;
        int scc2 = subset[i]->child_count / 2;
        bool turn = false;
        if(subset[i]->child_count > 0){
            turn = true;
        }
        else if(0 == subset[i]->child_count)
        {
            turn = false;
        }

        int b = subset[i]->data_count -(num + 1); // b = 2


        subset[i]->clear_tree();
        subset[i] = new BTree<T>;
        for(int j = 0; j < num; ++j){
            subset[i]->enter_Data(gub[j]);
            //cout << "subset[i]->data[j] = " << subset[i]->data[j] << endl;
        }

        subset[i + 1]->clear_tree();
        subset[i + 1] = new BTree<T>;
        for(int j = 0; j < b; ++j){
            subset[i + 1]->enter_Data(gub2[j]);
            //cout << "subset[i + 1]->data[j] = " << subset[i + 1]->data[j] << endl;
        }

        if(turn == true){
            for(int j = 0; j < scc2; ++j){
                subset[i]->subset[j] = new BTree<T>;
                copy_tree(subset[i]->subset[j],ptr[j]);
                subset[i]->child_count += 1;
            }
        }
        if(turn == true){
            for(int j = 0; j < scc2; ++j){
                subset[i + 1]->subset[j] = new BTree<T>;
                copy_tree(subset[i + 1]->subset[j],ptr2[j]);
                subset[i + 1]->child_count += 1;
            }
        }


        child_count += 1;
//            subset[0]->data_count = num - i;
//            subset[0]->child_count = 0;
//            subset[1]->data_count = data_count - num;
//            subset[1]->child_count = 0;
        return;
    }


    BTree<T> *twin, *twin2;
    twin = new BTree<T>;
    twin2 = new BTree<T>;

    //cout << "going to make twins" << endl;
    make_twins(twin,twin2, i, num);
    //cout << "back from making twins" << endl;
    //cout << "print twin" << endl;
    //twin->print_tree();
    //cout << "print twin2" << endl;
    //twin2->print_tree();

//    cout << "Again" << endl;
//    cout << "item = " << item << endl; // 21
//    cout << "num = " << num << endl; // 1
//    cout << "subset[i].data_count = " << subset[i]->data_count << endl; // 3
//    cout << "subset[i].child_count = " << subset[i]->child_count << endl; // 0
//    cout << "child_count = " << child_count << endl; // 3
//    cout << "data_count = " << data_count << endl; // 3

    BTree<T> *ptr[i], *ptr2[i];

    for(int p = 0; p < i; ++p){
        ptr[p] = new BTree<T>;
        copy_tree(ptr[p],subset[p]);
    }
    int l = 0;
    for(int p = i + 1; p < child_count; ++p){
        ptr2[l] = new BTree<T>;
        copy_tree(ptr2[l],subset[p]);
    }
    //cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;




    for(int p = 0; p < child_count; ++p){
        subset[p]->clear_tree();
    }
    child_count += 1;
    //cout << "new child_count = " << child_count << endl;
    //cout << "NEVER GOT HERE " << endl;
    for(int p = 0; p < i; ++p){
        subset[p] = new BTree<T>;
        copy_tree(subset[p],ptr[p]);
    }
    subset[i] = new BTree<T>;
    copy_tree(subset[i],twin);
    subset[i + 1] = new BTree<T>;
    copy_tree(subset[i + 1], twin2);
    // << "i = " << i << endl;
    ///cout << "CHILDE COUNTTTTTT = " << child_count <<endl;
    l = 0;
    for(int p = i + 2; p < child_count; ++p){
        subset[p] = new BTree<T>;
        copy_tree(subset[p],ptr2[l]);
        ++l;
    }

    //cout << "THROUGH TO THE OD" << endl;


}
template<typename T>
void BTree<T>::enter_Data(T item){
    if(0 == data_count){
        if(190 == item){
            //cout << "190 has been entered for data" << endl;
        }
        data[0] = item;
        data_count += 1;
        //cout << "****DATA SET*****" << endl;
//        for(int i = 0; i < data_count; ++i){
//            //cout << "data[" << i << "] = " << data[i] << endl;
//        }
        return;
    }
    if(0 != data_count){

        if(item <= data[0]){
            T sub[data_count + 1];
            sub[0] = item;
            for(int i = 1; i < data_count + 1; ++i){
                sub[i] = data[i - 1];
            }
            for(int i = 0; i < data_count; ++i){
                data[i] = T();
            }
            data_count += 1;
            for(int i = 0; i < data_count; ++i){
                data[i] = sub[i];
            }
            //cout << "****DATA SET*****" << endl;
            for(int i = 0; i < data_count; ++i){
                //cout << "data[" << i << "] = " << data[i] << endl;
            }
            return;
        }
        if(item >= data[data_count - 1]){
            data_count += 1;
            data[data_count - 1] = item;
            //cout << "****DATA SET*****" << endl;
//            for(int i = 0; i < data_count; ++i){
//                //cout << "data[" << i << "] = " << data[i] << endl;
//            }
            return;
        }
        int i = 0;
        bool stop = false;
        do{
            if(!(item >= data[i] && item <= data[i + 1])){
                ++i;
            }
            else if(item >= data[i] && item <= data[i + 1]){

                T sub[data_count + 1];
                for(int p = 0; p <= i; ++p){
                    sub[p] = data[p];
                }
                sub[i + 1] = item;
                data_count += 1;
                for(int j = i + 2; j < data_count; ++j){
                    sub[j] = data[j - 1];
                }
                for(int l = 0; l < data_count; ++l){
                    data[l] = T();
                }
                for(int l = 0; l < data_count; ++l){
                    data[l] = sub[l];
                }

                stop = true;
                //cout << "****DATA SET*****" << endl;
                for(int i = 0; i < data_count; ++i){
                    //cout << "data[" << i << "] = " << data[i] << endl;
                }
            }
        } while (stop == false);

    }
}
template<typename T>
bool BTree<T>::check_Dups(T item){
    if(0 == data_count){
        return false;
    }
    for(int i = 0; i < data_count; ++i){
        if(dups_ok == false){
            if(item == data[i]){
                return true;
            }
            else if(item != data[i]){
                return false;
            }
        }
        else if(dups_ok == true){
            return false;
        }
    }
}
template<typename T>
void BTree<T>::copy_tree(BTree<T>* left,const BTree<T>* right){

    left->child_count = right->child_count;
    left->data_count = right->data_count;
//    cout << "COPY TREEEEEEEEEE" << endl;
//    cout << "left_childcout = " << left->child_count << "right CC = " << right->child_count << endl;
//    cout << "left_datacout = " << left->data_count << "right DC = " << right->data_count << endl;
    for(int i = 0; i < right->data_count; ++i){
        left->data[i] = right->data[i];
    }
    BTree<T> *ptr[MAXIMUM + 2], *rtptr[MAXIMUM + 2];

    if(0 != right->child_count){
        //cout << "Not in here" << endl;
        for(int i = 0; i < right->child_count; ++i){
            left->subset[i] = new BTree<T>;
            copy_tree(left->subset[i],right->subset[i]);
            //left->subset[i] = ptr[i];
        }
    }
    //cout << "CCCC left prtint tree" << endl;
}
template<typename T>
BTree<T>& BTree<T>::operator =(const BTree<T> rhs){
    child_count = rhs.child_count;
    for(int i = 0; i < rhs.data_count; ++i){
        enter_Data(rhs.data[i]);
    }
    BTree<T> *ptr[MAXIMUM + 2], *rtptr[MAXIMUM + 2];

    if(0 != child_count){
        //cout << "HEEEE" << endl;
//        for(int i = 0; i < child_count; ++i){
//            ptr[i] = new BTree<T>;
//            //rtptr[i] = rhs.subset[i];
//        }
        for(int i = 0; i < rhs.child_count; ++i){
            subset[i] = new BTree<T>;
            copy_tree(subset[i],rhs.subset[i]);   //rtptr[i]
            //subset[i] = ptr[i];

        }
    }
}
template<typename T>
BTree<T>::BTree(bool dups_ok){
    data_count = 0;
    child_count = 0;
    for(int i = 0; i < MAXIMUM + 2; ++i){
        subset[i] = NULL;
    }
}
template<typename T>
BTree<T>::~BTree(){
    clear_tree();
}
template<typename T>
void BTree<T>::print_tree_two(int level, ostream& outs) const{
    const int EXTRA_INDENTATION = 4;
    size_t i;
    outs << setw(level) << "";

    for(i = 0;i < data_count; ++i){
        outs << data[i] << " " ;
    }
    outs << endl;

    for(i = 0; i < child_count; ++i){
        subset[i]->print_tree(level + EXTRA_INDENTATION);
    }
}
template<typename T>
void BTree<T>::print_tree(int level, ostream& outs) const{
    //cout << "Here" << endl;
    int last_child = child_count - 1;
    if(child_count > 0){
        subset[last_child]->print_tree(level + 1);
    }
    int j = last_child - 1;
    for(int i = data_count - 1; i >= 0; --i){
        outs << setw(level*8) << data[i];
        if(child_count > 2){
            if(subset[j]->data_count - 1 >= i){
                outs << setw((level + 1)*6) << subset[j]->data[i];
            }
        }
        outs << endl;
        if(0 == i && child_count > 0){
            cout << endl;
            subset[0]->print_tree(level + 1);
        }
    }
    cout << endl;
}
template<typename T>
ostream& operator <<(ostream& outs, const BTree<T>& print_me) {
    //cout << "Here 2 Print" << endl;
    print_me.print_tree();
    outs << endl;
    outs << "****************************************************" << endl;
    outs << endl;
    print_me.print_tree_two();
    return outs;
}
template<typename T>
void BTree<T>::clear_tree(){
    for(int i = 0; i < data_count; ++i){
        data[i] = T();
    }
    data_count = 0;
    for(int i = 0; i < child_count; ++i){
        subset[i]->clear_tree();
        delete [] subset;
        subset[i] = NULL;
    }
    child_count = 0;
}
