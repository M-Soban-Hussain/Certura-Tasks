#include< iostream>//including basic liraries
#include< fstream>
using namespace std ;

class Account{
    //Im using alass for the first time, i havent studied this befire
    public:
     int  accNo ;
    char name[ 50 ] ;
    float balance;
    void create( ){
       cout << "Enter Account No:  "; cin >>accNo;//asking the user to enter acct no.
        cout<< "Enter Name: ";cin. ignore(); cin.getline(name ,50);//asking the user to enter his name
        //here i used cin.ignore which clears the previous values stored
        cout <<"Enter Initial Balance: "; cin   >>balance;//askin the user to enter his balance initials
    }
	void show() { cout << " Account No. : " << accNo << "\nName:" << name << "\nBalance: " << balance << endl; }//this function shows the account details
	void deposit(float amt) { balance = balance + amt; }//this funct depostist the  money entered  y the user
    void withdraw(float amt )  {//This funct withdraws the money enterd
        if(balance >= amt) balance -= amt;
        else cout << "Insufficient balance\n"; }};
int main() {
    int choice;

    do {//looping through the menu until user exits
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) {//creatin accout
            Account acc;
            acc.create();
            ofstream out("accounts.dat", ios::binary | ios::app);
            out.write((char*)&acc, sizeof(acc));
            out.close();
        }

        else if (choice == 2 || choice == 3) {//deposit/withdraw
            int num;
            cout << "Enter Account No: "; cin >> num;
            fstream file("accounts.dat", ios::binary | ios::in | ios::out);
            Account acc;
            bool found = false;

            while (!file.eof()) {
                int pos = file.tellg();
                file.read((char*)&acc, sizeof(acc));
                if (!file) break;

                if (acc.accNo == num) {
                    float amt;
                    cout << "Enter amount: "; cin >> amt;
                    if (choice == 2) acc.deposit(amt);
                    else acc.withdraw(amt);
                    file.seekp(pos);
                    file.write((char*)&acc, sizeof(acc));
                    cout << "Transaction successful.\n";
                    found = true;
                    break;
                }
            }

            file.close();
            if (!found) cout << "Account not found.\n";
        }

        else if (choice == 4) {//checking balance
            int num;
            cout << "Enter Account No: "; cin >> num;
            ifstream in("accounts.dat", ios::binary);
            Account acc;
            bool found = false;

            while (in.read((char*)&acc, sizeof(acc))) {
                if (acc.accNo == num) {
                    acc.show();
                    found = true;
                    break;
                }
            }

            in.close();
            if (!found) cout << "Account not found.\n";
        }

        else if (choice == 5) {//exit
            cout << "Goodbye!\n";
        }

        else {
            cout << "Invalid option.\n";
        }

    } while (choice != 5);

    return 0;
}
