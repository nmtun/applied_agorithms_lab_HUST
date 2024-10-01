//Write a C program to perform some queries on a telco data (comming from stdin) with the following format:
//The first block of data consists of lines (terminated by a line containing #), each line (number of lines can be up to 100000) is under the form: 
//        call <from_number> <to_number> <date> <from_time> <end_time> 
//which is a call from the phone number <from_number> to a phone number <to_number> on <date>, and starting at time-point <from_time>, terminating at time-point <end_time>
//<from_number> and <to_number> are string of 10 characters (a phone number is correct if it contains only digits 0,1,...,9, otherwise, the phone number is incorrect)
//<date> is under the form YYYY-MM-DD (for example 2022-10-21)
//<from_time> and <to_time> are under the form hh:mm:ss (for example, 10:07:23)
 
//The second block consists of queries (terminated by a line containing #), each query in a line (number of lines can be up to 100000) and belongs to one of the following types:
//?check_phone_number: print to stdout (in a new line) value 1 if no phone number is incorrect
//?number_calls_from <phone_number>: print to stdout (in a new line) the number of times a call is made from <phone_number>
//?number_total_calls: print to stdout (in a new line) the total number of calls of the data
//?count_time_calls_from <phone_number>: print to stdout (in a new line) the total time duration (in seconds) the calls are made from <phone_number>

//Example
//Input
//call 0912345678 0132465789 2022-07-12 10:30:23 10:32:00
//call 0912345678 0945324545 2022-07-13 11:30:10 11:35:11
//call 0132465789 0945324545 2022-07-13 11:30:23 11:32:23
//call 0945324545 0912345678 2022-07-13 07:30:23 07:48:30
//#
//?check_phone_number
//?number_calls_from 0912345678
//?number_total_calls
//?count_time_calls_from 0912345678
//?count_time_calls_from 0132465789
//#

//Output
//1
//2
//4
//398
//120
//==================================================================================================================================================================================
#include <bits/stdc++.h>

using namespace std;

bool checkPhoneNumber(string number) {
    int check=0;
    for(int i=0; i<number.length(); i++){
        if(number[i] < '0' || number[i] > '9') check++;
    }
    if(number.length() != 10){
        return false;
    } else if (check>0) {
        return false;
    } else return true;
}

int timeToSeconds(const string& time){
    int h, m, s;
    sscanf(time.c_str(), "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    string option;
    int totalCalls = 0;
    int incorectPhone = 0;
    map<string, int> callsFrom;
    map<string, int> countTimeCalls;

    while(cin >> option && option != "#"){
        string fnum, tnum, date, ftime, etime;
        cin >> fnum >> tnum >> date >> ftime >> etime;
        totalCalls++;
        if(checkPhoneNumber(fnum) == false || checkPhoneNumber(tnum) == false ) incorectPhone++;

        int f_seconds = timeToSeconds(ftime);
        int e_seconds = timeToSeconds(etime);

        int coutCallsFrom = callsFrom[fnum]++;
        countTimeCalls[fnum] += (e_seconds - f_seconds);
    }

    while(cin >> option && option != "#"){
        if(option == "?check_phone_number"){
            if(incorectPhone == 0) {
                cout<<1<<endl;
            } else {
                cout<<0<<endl;
            }
        }
        if(option == "?number_total_calls"){
            cout<<totalCalls<<endl;
        }
        if(option == "?number_calls_from") {
            string phone_num;
            cin>>phone_num;
            cout<<callsFrom[phone_num]<<endl;
        }
        if(option == "?count_time_calls_from"){
            string phone_num;
            cin>>phone_num;
            cout<<countTimeCalls[phone_num]<<endl;
        }
    }

    return 0;
}
