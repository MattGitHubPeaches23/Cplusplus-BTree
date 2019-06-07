// Copyright (c) 2019, Matthew Chalifoux.

#include "btree.cpp"

int main(int argc, char *argv[])
{
    BTree<int> test, test2;


//    test.insert(13);
//    test.insert(7);
//    test.insert(22);
//    test.insert(25);
//    test.insert(12);
//    test.insert(8);
//    test.insert(23);
//    test.insert(5);
//    test.insert(14);
//    test.insert(24);
//    test.insert(4);
//    test.insert(16);
//    test.insert(21);
//    test.insert(17);
////    cout << test.subset[1]->subset[0]->data[0] << endl;
////    cout << test.subset[1]->subset[1]->data[0] << endl;
//    test.insert(90);
//    test.insert(180);
//    test.insert(190);
//    test.insert(80);
//    test.insert(70);
//    test.insert(3);
//    test.insert(2);

//    cout << test.subset[0]->subset[1]->subset[0]->data[0] << endl;
//    cout << test.subset[0]->subset[1]->subset[1]->data[0] << endl;


    test.insert(50);
    test.insert(30);
    test.insert(40);
    test.insert(60);
    test.insert(70);
    test.insert(20);
    test.insert(10);
    test.insert(25);
    test.insert(80);
    test.insert(55);
    test.insert(53);
    test.insert(3);
    test.insert(4);
    test.insert(2);
    test.insert(45);
    test.insert(43);
    test.insert(35);
    test.insert(75);
    test.insert(1);
    test.insert(0);
    test.insert(99);
   // test.insert(41);
    cout << "************ TEST *********************" << endl;
    cout << test;
//    cout << "****************************************" << endl << endl;
    cout << "ERASING NUMBER 53" << endl;
    test.erase(53);

    cout << "************ TEST *********************" << endl;
    cout << test;

//    int num = 32;
//    if(test.erase(num)){
//        cout << num << " is found in tree" << endl;
//    }
//    else {
//        cout << num << " is not found in tree" << endl;
//    }


    return 0;
}

