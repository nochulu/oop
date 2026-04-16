#include <iostream>
#include "datetime.h"

using namespace std;

int main() {
    DateTime dt1, dt2;

    cout << "Enter first date (yyyy-MM-ddThh:mm:ss): ";
    cin >> dt1;

    cout << "Enter second date (yyyy-MM-ddThh:mm:ss): ";
    cin >> dt2;

    if (!dt1.isValid() || !dt2.isValid()) {
        cout << "Error: One of the dates is invalid!" << endl;
        system("pause");
        return 1;
    }

    cout << "Day of week: " << dt1.getDayOfWeek() << endl;
    cout << "Style 1: "; dt1.printFormatted(1);
    cout << "Style 2: "; dt1.printFormatted(2);
    cout << "Style 3: "; dt1.printFormatted(3);

    cout << "Difference: " << (dt1 - dt2) << " days" << endl;
    
    if (dt1 > dt2) cout << "Date 1 is later than Date 2" << endl;
    else if (dt1 < dt2) cout << "Date 1 is earlier than Date 2" << endl;
    else cout << "Dates are equal" << endl;

    cout << endl;
    system("pause");
    return 0;
}