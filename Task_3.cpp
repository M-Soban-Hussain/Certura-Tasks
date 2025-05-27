#include <iostream>
#include<iomanip>
#include <string>
#include <fstream>
using namespace std;

//the structure to replace 7 parallel arrays  
struct account_details {
    int account;// max number of accounts
    int password;
    int saving;
    string transaction[100];
    string names;
    string email;
    int transaction_count_array;

};


//implmenting file system 
//the funtions
int  menu();
void deposit_menu();
void withdrawal_menu();
void creating_account(account_details[], int&); //to check the account number 
int account_finder(account_details[], int&);
int length_finder(int);//for password
void depositing_the_money(account_details[], int&);
void checking_savings_in_the_account(account_details[], int&);
void withdrawing_the_money(account_details[], int&);
void change_password(account_details[], int&);
void  transferring_money(account_details[], int&);
string printing_transcript(account_details[], int&);
void admin_access(account_details[], int&);
string hangman();//to add some life in the ATM
void save_all_accounts_to_file(account_details[]);


int main() {
    account_details array[100] = {};
    int pin = 0;
    string email_1 = "";
    string name_1 = "";
    int entry = 0;
    int jumper = 0;
    int total_money = 0;

    int account_number = 0;
    int account_password = 0;
    int finder = -1;
    int money_to_be_deposited = 0;
    int money_to_be_withdrawn = 0;
    int option = 0;
    int new_password = 0;
    int length = 0;
    int transfer_account = 0;
    int locator = 0;       string x;


    option = menu();


    while (option != 8) {
        if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6 && option != 7 && option != 8 && option != 9 && option != 10 && option != 0) {
            option = menu(); //default case if the inut is invalid;

        }
        else {
            switch (option) {
                //displaying menu
            case 0:
                option = menu();
                break;



                //making an account 
            case 1:
                creating_account(array, finder);//here finder is passed as a  refrence so it updates in real time as no copy  is made
                option = 0;
                break;


                // depositing money
            case 2:
                depositing_the_money(array, finder);//here finder is passed as a  refrence so it updates in real time as no copy  is made
                option = 0;
                break;



            case 3:
                checking_savings_in_the_account(array, finder);//here finder is passed as a  refrence so it updates in real time as no copy  is made
                //I only used the three arrays in the  declartuion in the  opassing as tghey  were the only ones being used in this program.
                option = 0;
                break;

                //withdrawl
            case 4:
                withdrawing_the_money(array, finder);//here finder is passed as a  refrence so it updates in real time as no copy  is made
                option = 0;
                break;


            case 5:
                change_password(array, finder);
                option = 0;
                break;



                //printing the transripts 
            case 6:
                cout << "Input your account number \n";
                cin >> account_number;
                cout << "Input your account password \n";
                cin >> account_password;
                finder = account_finder(array, account_number);
                if (finder == -1) {
                    cout << "Account not found!" << endl;
                    option = 0;
                    break;
                }
                else {
                    printing_transcript(array, finder);
                }
                option = 0;
                break;



                //transfreing money
            case 7:
                transferring_money(array, finder);
                option = 0;
                break;


            case 8:
                cout << "\nThe program has terminated\n";
                break;



                //admin control
            case 9:
                admin_access(array, total_money);
                option = 0;
                break;

                //to play hangman
            case 10:
                hangman();
                option = 0;
                break;





            }
        }
    }
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //menu
int menu() {
    int option;
    cout << "\n\nEnter the following for each task\n\n";
    cout << setw(60) << "To view menu " << setw(15) << "0\n\n";
    cout << setw(60) << "To make an account press " << setw(15) << "1\n\n";
    cout << setw(60) << "To deposit money press " << setw(15) << "2\n\n";
    cout << setw(60) << "To view your bank balance " << setw(15) << "3\n\n";
    cout << setw(60) << "To withdraw your money " << setw(15) << "4\n\n";
    cout << setw(60) << "To change password " << setw(15) << "5\n\n";
    cout << setw(60) << "To view your billing history " << setw(15) << "6\n\n";
    cout << setw(60) << "To tranfer money in another account  " << setw(15) << "7\n\n";
    cout << setw(60) << "To exit " << setw(15) << "8\n\n";
    cout << setw(60) << "To login as admin " << setw(15) << "9\n\n";
    cout << setw(60) << "To play hang man " << setw(15) << "10\n\n";
    cin >> option;
    return option;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//deposit menu
void deposit_menu() {
    cout << "Enter the amount of money you want to deposit = \n";
    cout << setw(40) << "For 5000 " << setw(40) << "press 1\n";
    cout << setw(40) << "For 2500 " << setw(40) << "press 2\n";
    cout << setw(40) << "For 1000 " << setw(40) << "press 3\n";
    cout << setw(40) << "For 500  " << setw(40) << "press 4\n";
    cout << setw(65) << "For custom just enter the amount \n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //withdrawal menu
void withdrawal_menu() {
    cout << "Enter the amount of money you want to withdraw = \n";
    cout << setw(40) << "For 5000 " << setw(40) << "press 1\n";
    cout << setw(40) << "For 2500 " << setw(40) << "press 2\n";
    cout << setw(40) << "For 1000 " << setw(40) << "press 3\n";
    cout << setw(40) << "For 500  " << setw(40) << "press 4\n";
    cout << setw(65) << "For custom just enter the amount \n";
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int account_finder(account_details array[], int& account_number) {
    for (int i = 0; i < 100; i++) {
        if (array[i].account == account_number) {
            return i;
        }
    }
    return -1; // not found
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int length_finder(int number) {
    int length = 0;
    if (number == 0) return 1;
    while (number > 0) {
        length++;
        number /= 10;
    }
    return length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void creating_account(account_details array[], int& finder) {
    string email_1 = "";
    string name_1 = "";
    int account_number = 0;
    int account_password = 0;
    int money_to_be_deposited = 0;
    int length = 0;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name_1);

    cout << "Enter your email: ";
    getline(cin, email_1);

    cout << "Input your account number: ";
    cin >> account_number;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Account number must be numeric.\n";
        return; // back to menu
    }

    if (account_number <= 0) {
        cout << "The account number must be positive.\n";
        return;
    }

    finder = account_finder(array, account_number);
    if (finder != -1) {
        cout << "This account number is already being used.\n";
        return;
    }

    cout << "Input your 4-digit numeric password: ";
    cin >> account_password;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Password must be numeric.\n";
        return;
    }

    length = length_finder(account_password);
    if (length != 4) {
        cout << "Password must be exactly 4 digits.\n";
        return;
    }

    // Find the first empty slot
    for (int i = 0; i < 100; i++) {
        if (array[i].account == 0) {
            array[i].account = account_number;
            array[i].password = account_password;
            array[i].email = email_1;
            array[i].names = name_1;
            array[i].transaction_count_array = 0;

            cout << "Congrats " << array[i].names << " on making an account in our branch.\n";
            cout << "Enter the amount of money you want to deposit at the start: ";
            cin >> money_to_be_deposited;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Amount must be numeric.\n";
                return;
            }

            array[i].saving = money_to_be_deposited;

            if (array[i].transaction_count_array < 100) {
                array[i].transaction[array[i].transaction_count_array] = "Money deposited " + to_string(money_to_be_deposited);
                array[i].transaction_count_array++;
            }
            else {
                cout << "Transaction history full. This transaction won't be recorded.\n";
            }
            save_all_accounts_to_file(array);
            ;
            cout << "Your money has been deposited.\n";
            finder = i;
            break;

        }
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void depositing_the_money(account_details array[], int& finder) {
    int account_number = 0;
    int account_password = 0;
    int deposit_option = 0;

    cout << "Input your account number: ";
    cin >> account_number;

    cout << "Input your account password: ";
    cin >> account_password;

    finder = account_finder(array, account_number);

    if (finder == -1) {
        cout << "Account not found!\n";
        return;
    }

    if (array[finder].password != account_password) {
        cout << "Either the account or password is incorrect.\n";
        return;
    }

    deposit_menu();
    cin >> deposit_option;
    int amount = 0;

    switch (deposit_option) {
    case 1: amount = 5000; break;
    case 2: amount = 2500; break;
    case 3: amount = 1000; break;
    case 4: amount = 500; break;
    default:
        if (deposit_option > 4) {
            amount = deposit_option;
        }
        else {
            cout << "Invalid input.\n";
            return;
        }
    }

    array[finder].saving += amount;
    cout << array[finder].names << ", your money has been deposited.\n";

    if (array[finder].transaction_count_array < 100) {
        array[finder].transaction[array[finder].transaction_count_array] = "Money deposited: " + to_string(amount);
        array[finder].transaction_count_array++;
        save_all_accounts_to_file(array);

    }
    else {
        cout << "Transaction history full. This transaction won't be recorded.\n";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bank balance
void checking_savings_in_the_account(account_details array[], int& finder) {
    int account_number = 0;
    int account_password = 0;
    int deposit_option = 0;
    cout << "Input your account number \n";
    cin >> account_number;
    cout << "Input your account password \n";
    cin >> account_password;
    finder = account_finder(array, account_number);
    if (finder != -1) {
        if (array[finder].password == account_password) {
            cout << "The current savings in your account is " << array[finder].saving << endl;
        }

        else {
            cout << "Either the account you have entered or your password is incorrect";
        }
    }
    else {
        cout << "Account does not exist ";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void withdrawing_the_money(account_details array[], int& finder) {
    int  account_number = 0;
    int account_password = 0;
    int money_to_be_withdrawn = 0;
    cout << "Input your account number \n";
    cin >> account_number;
    cout << "Input your account password \n";
    cin >> account_password;
    finder = account_finder(array, account_number);
    if (finder == -1) {
        cout << "Account not found! " << endl;

    }
    else if (array[finder].password == account_password) {
        withdrawal_menu();
        cin >> money_to_be_withdrawn;
        if (money_to_be_withdrawn == 1)
        {
            if (array[finder].saving >= 5000) {
                array[finder].saving -= 5000;
                cout << array[finder].names << " your money has been withdrawn\n";
                cout << "The current savings in your account is " << array[finder].saving << endl;
                if (array[finder].transaction_count_array < 100) {
                    array[finder].transaction[array[finder].transaction_count_array] = "Money withdrawn " + to_string(5000);
                    array[finder].transaction_count_array++;
                    save_all_accounts_to_file(array);

                }
                else {
                    cout << "Transaction history full. This transaction won't be recorded.\n";
                }

            }
            else {
                cout << "You don't have enough money";
            }
        }
        else if (money_to_be_withdrawn == 2)
        {
            if (array[finder].saving >= 2500) {
                array[finder].saving -= 2500;
                cout << array[finder].names << " your money has been withdrawn\n";
                cout << "The current savings in your account is " << array[finder].saving << endl;
                if (array[finder].transaction_count_array < 100) {
                    array[finder].transaction[array[finder].transaction_count_array] = "Money withdrawn " + to_string(2500);
                    array[finder].transaction_count_array++;
                    save_all_accounts_to_file(array);

                }
                else {
                    cout << "Transaction history full. This transaction won't be recorded.\n";
                }

            }
            else {
                cout << "You don't have enough money";
            }
        }
        else if (money_to_be_withdrawn == 3)
        {
            if (array[finder].saving >= 1000) {
                array[finder].saving -= 1000;
                cout << array[finder].names << " your money has been withdrawn\n";
                cout << "The current savings in your account is " << array[finder].saving << endl;
                if (array[finder].transaction_count_array < 100) {
                    array[finder].transaction[array[finder].transaction_count_array] = "Money withdrawn " + to_string(1000);
                    array[finder].transaction_count_array++;
                    save_all_accounts_to_file(array);

                }
                else {
                    cout << "Transaction history full. This transaction won't be recorded.\n";
                }

            }
            else {
                cout << "You don't have enough money";
            }
        }
        else if (money_to_be_withdrawn == 4)
        {
            if (array[finder].saving >= 500) {
                array[finder].saving -= 500;
                cout << array[finder].names << " your money has been withdrawn\n";
                cout << "The current savings in your account is " << array[finder].saving << endl;
                if (array[finder].transaction_count_array < 100) {
                    array[finder].transaction[array[finder].transaction_count_array] = "Money withdrawn " + to_string(500);
                    array[finder].transaction_count_array++;
                }
                else {
                    cout << "Transaction history full. This transaction won't be recorded.\n";
                }

            }
            else {
                cout << "You don't have enough money";
            }
        }
        else if (money_to_be_withdrawn <= array[finder].saving) {
            if (money_to_be_withdrawn > 0) {
                array[finder].saving -= money_to_be_withdrawn;
                cout << array[finder].names << " your money has been withdrawn\n";
                cout << "The current savings in your account is " << array[finder].saving << endl;
                if (array[finder].transaction_count_array < 100) {
                    array[finder].transaction[array[finder].transaction_count_array] = "Money withdrawn " + to_string(money_to_be_withdrawn);
                    array[finder].transaction_count_array++;
                    save_all_accounts_to_file(array);

                }
                else {
                    cout << "Transaction history full. This transaction won't be recorded.\n";
                }

            }
            else {
                cout << " The input is invalid \n";

            }
        }
        else {
            cout << "Your account does not have this much to withdraw\n";
        }

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//chanhing password
void change_password(account_details array[], int& finder) {
    int account_number = 0;
    int account_password = 0;
    string email_1;
    int new_password;
    int  length;
    cout << "Input your account number \n";
    cin >> account_number;
    cout << "Input your account password \n";
    cin >> account_password;
    finder = account_finder(array, account_number);
    cout << "Enter your email = ";
    cin.ignore();
    getline(cin, email_1);
    if (finder != -1) {
        if (array[finder].password == account_password) {

            cout << endl << array[finder].names << " enter your new password = ";
            cin >> new_password;
            length = length_finder(new_password);


            if (length == 4 && array[finder].email == email_1) {
                array[finder].password = new_password;
                cout << "Your password has been changed \n";
                save_all_accounts_to_file(array);


            }
            else if (length < 4) {
                cout << "Your password is too small \n";

            }
            else if (length > 4) {
                cout << "Your password is too large \n";
            }
        }
        else {
            cout << "Your password is incorrect \n";
        }
    }
    else {
        cout << "The account does not exist";
    }

}



//transferring money
void  transferring_money(account_details array[], int& finder) {

    int account_number;
    int account_password = 0;
    int money_to_be_withdrawn = 0;
    int transfer_money = 0;
    int transfer_account = 0;
    int locator = 0;
    cout << "Input your account number \n";
    cin >> account_number;
    cout << "Input your account password \n";
    cin >> account_password;
    finder = account_finder(array, account_number);
    if (finder == -1) {
        cout << "Your account has not been found!" << endl;

    }
    else {
        if (array[finder].password != account_password) {
            cout << "Incorrect password!\n";


        }
        cout << "Input reciepents account number \n";
        cin >> transfer_account;
        locator = account_finder(array, transfer_account);
        if (locator == -1) {
            cout << "Your account has not been found!" << endl;

        }
        else {
            cout << "Enter the amount of money you want to transfer \n";
            cin >> transfer_money;
            if (transfer_money > array[finder].saving || transfer_money <= 0) {
                cout << "Your input is incorrect \n";

            }
            else {
                array[locator].saving += transfer_money;
                array[finder].saving -= transfer_money;
                cout << "Congrats " << array[finder].names << " " << transfer_money << " has been transfered to  " << array[locator].names << "\n";
                if (array[finder].transaction_count_array < 100) {
                    array[finder].transaction[array[finder].transaction_count_array] = "Money transferred " + to_string(transfer_money) + " to account " + to_string(transfer_account);
                    array[finder].transaction_count_array++;
                    save_all_accounts_to_file(array);

                }
                else {
                    cout << "Sender transaction history full. Transfer not logged.\n";
                }
                if (array[locator].transaction_count_array < 100) {
                    array[locator].transaction[array[locator].transaction_count_array] = "Money received " + to_string(transfer_money) + " from account " + to_string(account_number);
                    array[locator].transaction_count_array++;
                }
                else {
                    cout << "Receiver transaction history full. Transfer not logged.\n";
                }

            }
        }

    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string printing_transcript(account_details array[], int& index)
{
    string out = "\n";
    if (index == -1) {
        out = "The account does not exist";
        cout << out;
        return out;
    }
    else if (array[index].transaction_count_array >= 100) {
        out = "The transaction history is more than 100";
        cout << out;
        return out;
    }
    else {
        cout << array[index].names << " your billing history is \n";
        for (int i = 0; i < array[index].transaction_count_array; i++) {
            cout << array[index].transaction[i] << endl;
        }
        return out;
    }
}


//admin access
void admin_access(account_details array[], int& total_money) {
    int pin, entry, jumper;
    cout << "\nEnter the pin for amdin access = ";//it is 9181
    total_money = 0;
    cin >> pin;
    if (pin == 9181) {
        cout << "You have logged in as an administrator \n";
        cout << setw(100) << "If you want to view all the  account details  in the bank system = " << setw(5) << "press 1\n";
        cout << setw(100) << "If you want to view the total money in the bank system = " << setw(5) << "press 2\n";
        cin >> entry;
        if (entry == 1) {
            cout << setw(20) << "Name of Account" << setw(20) << "Account Number" << setw(20) << "Current balance" << endl;
            jumper = 0;
            while (jumper < 100 && array[jumper].account>0) {
                cout << setw(20) << array[jumper].names << setw(20) << array[jumper].account << setw(20) << array[jumper].saving << endl;
                jumper++;


            }
        }
        else if (entry == 2) {
            cout << setw(20) << "The total money in the banking  system is  ==  ";
            jumper = 0;
            while (jumper < 100 && array[jumper].account>0) {
                total_money += array[jumper].saving;
                jumper++;


            }
            cout << total_money;
            cout << endl;

        }
        else {
            cout << "Thanks for logging in \n";
        }
    }

    else {
        cout << "Your password is incorrect";
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string hangman() {
    string word_to_be_guessed;
    word_to_be_guessed = "ragnar";
    int lentgh = word_to_be_guessed.length();
    char aplhabet;
    string checker(lentgh, '*');
    int lives = 7;
    string out = "Thank for choosing to play";

    while (lives > 0) {
        int live_counter = 0;
        cout << "enter alphabet you want to guess \n";
        cin >> aplhabet;
        aplhabet = tolower(aplhabet);
        //checking the word
        for (int i = 0; i < lentgh; i++) {
            if (aplhabet == word_to_be_guessed[i]) {
                checker[i] = aplhabet;
                live_counter = 1;

            }
        }
        //displying results after every aplahbbet 
        cout << "the word you have guessed until now = ";
        for (int i = 0; i < lentgh; i++) {
            cout << checker[i];
        }
        cout << "\t\t\t";
        //calculating the lives

        if (live_counter != 1)
        {
            lives--;
        }
        cout << "Your lives now  are " << lives << endl;
        if (checker == word_to_be_guessed) {
            break;
        }
    }

    if (checker == word_to_be_guessed) {
        cout << "Congrats you have won !!!!!!!!!!!!!!!!!!!!";
    }
    else
    {
        cout << "Well try try again is the motto for success ";
    }
    return out;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void save_all_accounts_to_file(account_details array[]) {
    ofstream outFile("accounts_information.txt");
    if (!outFile) {
        cerr << "Error opening file!\n";
        return;
    }

    for (int i = 0; i < 100; ++i) {
        if (array[i].account == 0) {
            continue; // Skip empty accounts
        }

        outFile << "Account Number: " << array[i].account << "\n";
        outFile << "Password: " << array[i].password << "\n";
        outFile << "Name: " << array[i].names << "\n";
        outFile << "Email: " << array[i].email << "\n";
        outFile << "Balance: " << array[i].saving << "\n";
        outFile << "Transactions:\n";

        for (int j = 0; j < array[i].transaction_count_array; ++j) {
            outFile << array[i].transaction[j] << "\n";
        }
        outFile << "\n\n";

    }
    outFile.close();
    int option = 0;
}