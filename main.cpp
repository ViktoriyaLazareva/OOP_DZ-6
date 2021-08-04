#include <iostream>
#include <cstdlib>
using namespace std;

#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>

using namespace std;

   ostream& endll(ostream& os) {
       cout.clear();
    return os << "\n" << "\n";
}

int main()
{
//Task 1 (variant 1)---------------------------------------
int integer_number;
    cout << "Input integer number:" << endl;
    cin >> integer_number;
    while(!(cin >> integer_number)) {
        cout << "Error!" << endl;
    cin.clear();
    fflush(stdin);
    cout << "Input integer number:" << endl;

   }
    cout << endll;

//Task 1 (varint 2)-----------------------------------------
    /*string str;
    getline(cin,str);

    for(int i = 0; i < str.length(); i++){
        if(isdigit(str[i])){}
        else{
            cout << "Error! ";
            break;
        }
    }
    cout << "Your input: " << str << endl;
    cout << endll;*/

    //-------------------------------------------------------

    system ("Pause");
    return 0;
}

