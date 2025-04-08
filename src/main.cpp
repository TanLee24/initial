#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "test/tc_dlinkedlist.h"
#include "test/tc_xarraylist.h"
#include "test/tc_inventory.h"

using namespace std;

void (*func_ptr[15])() = {
    dlistDemo1,
    dlistDemo2,
    dlistDemo3,
    dlistDemo4,
    dlistDemo5,
    dlistDemo6,
    xlistDemo1,
    xlistDemo2,
    xlistDemo3,
    xlistDemo4,
    tc_inventory1001,
    tc_inventory1002,
    tc_inventory1003,
    tc_inventory1004,
    tc_inventory1005
};

void run(int func_idx)
{
    func_ptr[func_idx]();
}

int main(int argc, char **argv)
{
    // cout << "Assignment-1" << endl;
    if (argc == 1) {
        //tc_inventory1001();
        dlistDemo1();
        cout << "ok\n";
        dlistDemo2();
        cout << "ok\n";
        dlistDemo3();
        cout << "ok\n";
        dlistDemo4();
        cout << "ok\n";
        dlistDemo5();
        cout << "ok\n";
        dlistDemo6();
        cout << "ok\n";
        xlistDemo1();
        cout << "ok\n";
        xlistDemo2();
        cout << "ok\n";
        xlistDemo3();
        cout << "ok\n";
        xlistDemo4();
        cout << "ok\n";
        tc_inventory1001();
        cout << "ok\n";
        tc_inventory1002();
        cout << "ok\n";
        tc_inventory1003();
        cout << "ok\n";
        tc_inventory1004();
        cout << "ok\n";
        tc_inventory1005();
    }
    
    return 0;
}