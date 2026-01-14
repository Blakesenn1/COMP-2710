/**
* File Name: project1_Senn_abs0113.cpp
* Author: Blake Senn (abs0113)
*
* Compiled with MinGW GCC C++ compiler.
*
* I watched a Youtube video by Computer Time
* to understand the basics of c++.
* I used the hints.pdf in Canvas and previous
* coding knowledge as other sources.
*/

#include <iostream>
#include <limits>
using namespace std;

int main() {
    // Define variables
    int currentMonth = 0;
    double monthlyPaid;
    double interestTotal = 0;
    double interestRate;
    double interestRateC;
    double loan;
    double monthlyInterestAmount;
 
    // Currency formatting
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
 
    // User input
    cout << "\nLoan Amount: ";
    cin >> loan;

    while (cin.fail() || loan <= 0) {
        cout << "(Invalid Loan): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> loan;
    }

    cout << "Interest Rate (% per year): ";
    cin >> interestRate;

    while (cin.fail() || interestRate < 0) {
        cout << "(Invalid Interest Rate): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> interestRate;
    }

    // Interest rates for calculations
    interestRate /= 12;
    interestRateC = interestRate / 100;

    cout << "Monthly Payments: ";
    cin >> monthlyPaid;

    while (cin.fail() || monthlyPaid <= 0) {
        cout << "(Invalid Payment): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> monthlyPaid;
    }

    while (monthlyPaid <= loan * interestRateC) {
        cout << "(Insufficient Payment): ";
        cin >> monthlyPaid;
    }

    cout << endl;
 
    //Amortization table
    cout << "*****************************************************************\n"
         << "\tAmortization Table\n"
         << "*****************************************************************\n"
         << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";
    while (loan > 0) {
        if (currentMonth == 0) {
            cout << currentMonth++ << "\t$" << loan;
            if (loan < 1000) cout << "\t";
                cout << "\t" << "N/A\tN/A\tN/A\t\tN/A\n";
        }
        else {
            monthlyInterestAmount = loan * interestRateC;
            interestTotal += monthlyInterestAmount;
            loan = (loan * (1 + interestRateC) - monthlyPaid);
            if (loan < 0) {
                monthlyPaid += loan;
                loan = 0;
            }
            cout << currentMonth++
                 << "\t$" << loan << "\t";
            if (loan < 1000) {
                cout << "\t";
            }
            cout << "$" << monthlyPaid << "\t"
                 << interestRate << "\t"
                 << "$" << monthlyInterestAmount << "\t\t"
                 << "$" << monthlyPaid - monthlyInterestAmount << endl;
        }
    }

    // Loop to fill table
    cout << "****************************************************************\n";
    cout << "\nIt takes " << --currentMonth << " months to pay off "
         << "the loan.\n"
         << "Total interest paid is: $" << interestTotal;
    cout << endl << endl;
    return 0;
}