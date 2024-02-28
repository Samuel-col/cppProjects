#include <iostream>
#include <vector>

using namespace std;

int main(){
    // Project Euler problem 19

    /**
    * 1 Jan 1900 was a Monday.
    * Thirty days has September,
    April, June and November.
    All the rest have thirty-one,
    Saving February alone,
    Which has twenty-eight, rain or shine.
    * And on leap years, twenty-nine.
    * A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

    How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)? 
     */    

    /**
    0 : Sunday
    1 : Monday
    2 : Tuesday
    3 : Wendnesday
    4 : Thursday
    5 : Friday
    6 : Saturday
    */

    int jan_1_1900 = 1;
    int jan_1_1901 = (jan_1_1900 + 365)%7;
    int jan_1 = jan_1_1901;
    int sundays_1 = 0;
    vector<int> firsts;
    vector<int> months;
    for(int a = 1; a <= 100; a++){
        months = {31,28+(a%4 == 0 && (a%100 != 0 || a%400 == 0)),31,30,31,30,31,31,30,31,30,31};
        firsts.push_back(jan_1);
        for(int k = 0;k < 12; k++) firsts.push_back((firsts[k]+months[k])%7);
        for(int k = 0;k < 12; k++) sundays_1 += firsts[k]==0;
        jan_1 = (firsts[11] + 31)%7;
        firsts.clear();
    }

    cout << sundays_1 << endl;


    return 0;
}