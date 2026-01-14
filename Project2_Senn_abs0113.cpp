/**
* File Name: project2_Senn_abs0113.cpp
* Author: Blake Senn (abs0113)
*
* Compiled with MinGW GCC C++ compiler.
*
* I used the hints in Canvas and previous
* coding knowledge as sources.
*
* I watched a short youtube video by
* LearningLad to modify the srand(time(0))
* function since mine would not compile.
*/

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

// Methods
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void Press_any_key(void);
bool shoot_target_result(int probability);

// Tests
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

// Variables
const int duels = 10000, aaronHitChance = 33, bobHitChance = 50;
int aaronWins1 = 0, bobWins = 0, charlieWins = 0, aaronWins2 = 0;
bool aaronAlive = true, bobAlive = true, charlieAlive = true;

int main(void) {
    cout << "*** Welcome to Blake's Duel Simulator ***\n";
    srand(static_cast<unsigned int>(time(0)));
    test_at_least_two_alive();
    Press_any_key();
    test_Aaron_shoots1();
    Press_any_key();
    test_Bob_shoots();
    Press_any_key();
    test_Charlie_shoots();
    Press_any_key();
    test_Aaron_shoots2();
    Press_any_key();
    // Strategy 1
    cout << "Ready to test strategy 1 (run 10000 times):\n";
    Press_any_key();
    for(int i = 0; i < duels; i++) {
        aaronAlive = true;
        bobAlive = true;
        charlieAlive = true;
        while(at_least_two_alive(aaronAlive, bobAlive, charlieAlive)) {
            if (aaronAlive) {
                Aaron_shoots1(bobAlive, charlieAlive);
            }
            if (bobAlive) {
                Bob_shoots(aaronAlive, charlieAlive);
            }
            if (charlieAlive) {
                Charlie_shoots(aaronAlive, bobAlive);
            }
        }
        if (aaronAlive) {
            aaronWins1++;
        }
        if (bobAlive) {
            bobWins++;
        }
        if (charlieAlive) {
            charlieWins++;
        }
    }
    cout << "Aaron won " << aaronWins1 << "/10000 duels or " <<
static_cast<double>(aaronWins1)/duels * 100 << "%\n"
        << "Bob won " << bobWins << "/10000 duels or " <<
static_cast<double>(bobWins)/duels * 100 << "%\n"
        << "Charlie won " << charlieWins << "/10000 duels or " <<
static_cast<double>(charlieWins)/duels * 100 << "%\n"
        << endl;

    // Strategy 2
    cout << "Ready to test strategy 2 (run 10000 times):\n";
    bobWins = 0, charlieWins = 0;
    Press_any_key();
    for (int i = 0; i < duels; i++) {
        aaronAlive = true;
        bobAlive = true;
        charlieAlive = true;
        while(at_least_two_alive(aaronAlive, bobAlive, charlieAlive)) {
            if (aaronAlive) {
                Aaron_shoots2(bobAlive, charlieAlive);
            }
            if (bobAlive) {
                Bob_shoots(aaronAlive, charlieAlive);
            }
            if (charlieAlive) {
                Charlie_shoots(aaronAlive, bobAlive);
            }
        }
        if (aaronAlive) {
            aaronWins2++;
        }
        if (bobAlive) {
            bobWins++;
        }
        if (charlieAlive) {
            charlieWins++;
        }
    }
    cout << "Aaron won " << aaronWins2 << "/10000 duels or " <<
static_cast<double>(aaronWins2)/duels * 100 << "%\n"
        << "Bob won " << bobWins << "/10000 duels or " <<
static_cast<double>(bobWins)/duels * 100 << "%\n"
        << "Charlie won " << charlieWins << "/10000 duels or " <<
static_cast<double>(charlieWins)/duels * 100 << "%\n"
        << endl;

    if (aaronWins1 > aaronWins2) {
        cout << "Strategy 1 is better than strategy 2.\n";
    } 
    else {
        cout << "Strategy 2 is better than strategy 1.\n";
    }
    return 0;
}
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
    return ((A_alive && B_alive) || (B_alive && C_alive) || (A_alive &&
C_alive));
}
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
    assert(aaronAlive == true);
    bool hit = shoot_target_result(aaronHitChance);
    if (hit && C_alive) {
        C_alive = false;
        return;
    }
    if (hit && B_alive) {
        B_alive = false;
        return;
    }
}
void Bob_shoots(bool& A_alive, bool& C_alive) {
    assert(bobAlive == true);
    bool hit = shoot_target_result(bobHitChance);
    if (hit && C_alive) {
        C_alive = false;
        return;
    }
    if (hit && A_alive) {
        A_alive = false;
        return;
    }
}
void Charlie_shoots(bool& A_alive, bool& B_alive) {
    assert(charlieAlive == true);
    if (B_alive) {
        B_alive = false;
        return;
    }
    if (A_alive) {
        A_alive = false;
        return;
    }
}
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    bool hit;
    if (C_alive && B_alive){
        hit = false;
    } 
    else {
        hit = shoot_target_result(aaronHitChance);
    }
    if (hit && C_alive) {
        C_alive = false;
        return;
    }
    if (hit && B_alive) {
        B_alive = false;
        return;
    }
}

// Pause command for Linux terminal
void Press_any_key(void) {
    cout << "Press Enter to continue...";
    cin.ignore().get();
}

bool shoot_target_result(int probability) {
    int result = rand()%100;
    return result <= probability;
}

// Tests
void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";
    
    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";
    
    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";
    
    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n";
    
    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed ...\n";
}

void test_Aaron_shoots1() {
    cout << "\nUnit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\
n";
    bool bob_a = true, charlie_a = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(bob_a, charlie_a);
    assert(true == bob_a);

    bob_a = false, charlie_a = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(bob_a, charlie_a);

    bob_a = true, charlie_a = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n"
         << "\t\tAaron is shooting at Bob\n";
    Aaron_shoots1(bob_a, charlie_a);
}

void test_Bob_shoots() {
    cout << "\nUnit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\
n";
    bool aaron_a = true, charlie_a = true;
    cout << "\tCase 1: Aaron alive, Charlie alive\n"
         << "\t\tBob is shooting at Charlie\n";
    Bob_shoots(aaron_a, charlie_a);

    aaron_a = false, charlie_a = true;
    cout << "\tCase 1: Aaron dead, Charlie alive\n"
         << "\t\tBob is shooting at Charlie\n";
    Bob_shoots(aaron_a, charlie_a);

    aaron_a = true, charlie_a = false;
    cout << "\tCase 3: Aaron alive, Charlie dead\n"
         << "\t\tBob is shooting at Aaron\n";
    Bob_shoots(aaron_a, charlie_a);
}

void test_Charlie_shoots(){
    cout << "\nUnit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\
n";
    bool aaron_a = true, bob_a = true;
    cout << "\tCase 1: Aaron alive, Bob alive\n"
         << "\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(aaron_a, bob_a);
    assert(false == bob_a && true == aaron_a);

    aaron_a = false, bob_a = true;
    cout << "\tCase 1: Aaron dead, Bob alive\n"
         << "\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(aaron_a, bob_a);
    assert(false == bob_a && false == aaron_a);

    aaron_a = true, bob_a = false;
    cout << "\tCase 3: Aaron alive, Bob dead\n"
         << "\t\tCharlie is shooting at Aaron\n";
    Charlie_shoots(aaron_a, bob_a);
    assert(false == aaron_a && false == bob_a);
}

void test_Aaron_shoots2(){
    cout << "\nUnit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\
n";
    bool bob_a = true, charlie_a = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n"
         << "\t\tAaron intentionally misses his first shot\n"
         << "\t\tBoth Bob and Charlie are alive.\n";
    Aaron_shoots2(bob_a, charlie_a);
    assert(bob_a == true && charlie_a == true);

    bob_a = false, charlie_a = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots2(bob_a, charlie_a);

    bob_a = true, charlie_a = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n"
         << "\t\tAaron is shooting at Bob\n";
    
    Aaron_shoots2(bob_a, charlie_a);
}