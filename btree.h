// Copyright (c) 2019, Matthew Chalifoux.

#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include <iomanip>
using namespace std;
template<typename T>
class BTree{
public:
    BTree(bool dups_ok = false);
    BTree<T>& operator =(const BTree<T> rhs);
    ~BTree();
    bool check_Dups(T item);
    void clear_tree();
    void make_twins(BTree<T> *twin, BTree<T> *twin2, int i, int num);
    void insert_item(const T item, BTree<T> *ptr);
    void split_Node(int i);
    void copy_tree(BTree<T>* left,const BTree<T>* right);
    void insert(const T& item);
    void erase(const T& target);
    void print_tree(int level = 0, ostream& outs = cout) const;
    void print_tree_sub();
    void print_tree_two(int level = 0, ostream& outs = cout) const;
    template<typename U>
    friend ostream& operator <<(ostream& outs, const BTree<U>& print_me);

private:
    bool is_leaf() const {return child_count==0;}
    bool dups_ok;
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;
    T data[MAXIMUM + 1];
    BTree *subset[MAXIMUM + 2];
    unsigned int child_count;
    unsigned int data_count;
    void fix_excess_first(int i);
    void fix_excess_root(int i);
    void fix_excess(int i);
    void enter_Data(T item);
    void loose_erase(const T& target);
    void shift_data(int i);
    void fix_shortage(int i);
    void remove_biggest(T& removed_entry);
    void case_one(int i);
    void case_two(int i);
    void case_three(int i);
    void case_four(int i);
    void fix_erase_root(int i);
};
#endif // BTREE_H
