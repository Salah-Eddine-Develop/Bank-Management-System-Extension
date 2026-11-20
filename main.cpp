// Project2BankExtension.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";

void  ShowMainMenueScreen();

void ShowTransactionMenueScreen();

enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClientInfo = 4, eFindClient = 5, eTransactions = 6, eExit = 7
};

enum enTransactionMenueOptions
{
    eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue = 4
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

string ReadClineAccountNumber()
{
    string AccouN = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccouN;
    return AccouN;
}

string ConvertRecordToLine(stClient Cline, string Seperator = "#//#")
{
    string sClinetRecord = "";
    sClinetRecord += Cline.AccountNumber + Seperator;
    sClinetRecord += Cline.PinCode + Seperator;
    sClinetRecord += Cline.Name + Seperator;
    sClinetRecord += Cline.Phone + Seperator;
    sClinetRecord += to_string(Cline.AccountBalance);

    return sClinetRecord;
}

vector <string> SplitString(string S1, string Delim)
{
    vector <string> vWords;

    string sWord = "";

    short pos = 0;

    while ((pos = S1.find(Delim)) != S1.npos)
    {
        sWord = S1.substr(0, pos);

        if (sWord != "")
        {
            vWords.push_back(sWord);
        }


        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vWords.push_back(S1);
    }

    return vWords;
}

stClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    stClient Cline;

    vector <string> vClineData = SplitString(Line, Seperator);

    Cline.AccountNumber = vClineData.at(0);
    Cline.PinCode = vClineData.at(1);
    Cline.Name = vClineData.at(2);
    Cline.Phone = vClineData.at(3);
    Cline.AccountBalance = stod(vClineData.at(4));

    return Cline;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    fstream MyFile;


    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);

            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }

        MyFile.close();
    }

    return false;
}

stClient ReadNewCline()
{
    stClient Client;

    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber <<
            "] already exists, Enter another Account Number ? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewClient()
{

    stClient Client;
    Client = ReadNewCline();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

vector <stClient> LoadClientsDataFromFile(string FileName)
{
    fstream MyFile;

    vector<stClient> vClients;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

void PrintClientRecord(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List(" << vClients.size() << ") Client(s).";
    cout << "\n__________________________________________________________";
    cout << "_______________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n__________________________________________________________";
    cout << "_______________________________________\n" << endl;

    for (stClient Cline : vClients)
    {
        PrintClientRecord(Cline);
        cout << endl;
    }

    cout << "\n__________________________________________________________";
    cout << "_______________________________________\n" << endl;

}

void PrintClientCard(stClient Client)
{
    cout << "\nThe follwing are the client details:";
    cout << "\n\nAccount Number : " << Client.AccountNumber;
    cout << "\nPin Code       : " << Client.PinCode;
    cout << "\nName           : " << Client.Name;
    cout << "\nPhone          : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Cline)
{

    for (stClient& cline : vClients)
    {
        if (AccountNumber == cline.AccountNumber)
        {
            Cline = cline;
            return true;
        }
    }

    return false;

}

void AddClients()
{

    char AddMore = 'Y';

    do
    {
        cout << "Adding New Clinet:\n\n";

        AddNewClient();

        cout << "\nClinet Added Successfully, do you want to add more clients?[Y/N] ?";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

void SaveClientsDataToFile(string FileName, vector <stClient> vClients)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (stClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();

    }

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    stClient Client;
    char Answer = 'n';


    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure want delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;


        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!";
        return false;
    }


}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    stClient Client;
    char Answer = 'n';



    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure want update this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {

                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Update Successfully.";
            return true;


        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!";
        return false;
    }
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddClients();
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClineAccountNumber();

    DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Screen";
    cout << "\n-----------------------------------\n";

    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClineAccountNumber();

    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClineAccountNumber();
    stClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient with Account Number[" << AccountNumber
            << "] is not found!";
    }
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

short ReadTransactionMenueOption()
{
    short choise = 0;

    do
    {
        cout << "Choose what do you want to do? [1 to 4]? ";
        cin >> choise;

    } while (choise < 1 || choise > 4);
    

    return choise;
}

double Deposit(double clientBalance, double deposit)
{
    return clientBalance + deposit;
}

bool ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber;
    double deposit = 0;
    char isYes = 'Y';

    while (true) {
        AccountNumber = ReadClineAccountNumber();
        for (stClient& client : vClients)
        {
            if (client.AccountNumber == AccountNumber)
            {
                PrintClientCard(client);

                cout << "\n\nPlease enter deposit amount? ";
                cin >> deposit;

                cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
                cin >> isYes;

                if (isYes == 'y' || isYes == 'Y')
                {
                    client.AccountBalance = Deposit(client.AccountBalance, deposit);

                    cout << "\nThe new Balance is " << client.AccountBalance << endl;

                    SaveClientsDataToFile(ClientsFileName, vClients);

                    return true;

                }
                return false;

            }
        }

        cout << "\n\nClient with[" << AccountNumber << "] does not exit.\n";

    }

}

bool ShowWithdrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber;
    double withdraw = 0;
    char isYes = 'Y';

    while (true) {
        AccountNumber = ReadClineAccountNumber();
        for (stClient& client : vClients)
        {
            if (client.AccountNumber == AccountNumber)
            {
                PrintClientCard(client);

                cout << "\n\nPlease enter withdraw amount? ";
                cin >> withdraw;

                while (withdraw > client.AccountBalance)
                {
                    cout << "\n\nAmount Exceeds the balance, you can Withdraw up to : "
                        << client.AccountBalance;

                    cout << "\n\nPlease enter another amount? ";
                    cin >> withdraw;
                }
                

                cout << "\nAre you sure you want perfrom this transaction? y/n ? ";
                cin >> isYes;

                if (isYes == 'y' || isYes == 'Y')
                {
                    client.AccountBalance = Deposit(client.AccountBalance, (-1)*withdraw);

                    cout << "\n\nThe new Balance is " << client.AccountBalance << endl;

                    SaveClientsDataToFile(ClientsFileName, vClients);

                    return true;

                }

                return false;

            }
        }

        cout << "\n\nClient with[" << AccountNumber << "] does not exit.\n";

    }

}

void PrintClientRecordBalances(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowTotalBalances()
{
    double TotalBalances = 0;
    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List(" << vClients.size() << ") Client(s).";
    cout << "\n__________________________________________________________";
    cout << "_______________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n__________________________________________________________";
    cout << "_______________________________________\n" << endl;

    for (stClient Client : vClients)
    {
        TotalBalances += Client.AccountBalance;

        PrintClientRecordBalances(Client);
        cout << endl;
    }

    cout << "\n__________________________________________________________";
    cout << "_______________________________________\n" << endl;

    cout << "\n\t\t\t\t\tTotal Balances = " << TotalBalances << endl;

}

void GoBackToTransactionMenue()
{
    cout << "\n\nPress any key to go back to Transaction Menue...";
    system("pause>0");
    ShowTransactionMenueScreen();
}

void PerformTransactionMenueOption(enTransactionMenueOptions TransactionMenueOptions)
{
    switch (TransactionMenueOptions)
    {
    case enTransactionMenueOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionMenue();
        break;

    case enTransactionMenueOptions::eWithdraw:
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionMenue();
        break;

    case enTransactionMenueOptions::eTotalBalances:
        system("cls");
        ShowTotalBalances();
        GoBackToTransactionMenue();
        break;

    case enTransactionMenueOptions::eMainMenue:
        system("cls");
        ShowMainMenueScreen();
        break;
    }
}

void ShowTransactionMenueScreen()
{
    system("cls");
    cout << "============================================\n";
    cout << "\t\tTransaction Menue Screen\n";
    cout << "============================================\n";
    cout << "\t[1] Deposit." << endl;
    cout << "\t[2] Withdraw." << endl;
    cout << "\t[3] Total Balanses." << endl;
    cout << "\t[4] Main Menue." << endl;
    cout << "============================================\n";

    PerformTransactionMenueOption((enTransactionMenueOptions)ReadTransactionMenueOption());
}

short ReadMainMenueOption()
{
    short choise = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 7]? ";
        cin >> choise;

    } while (choise < 1 || choise > 7);
    

    return choise;
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenueScreen();
}

void PerformMainMenueOption(enMainMenueOptions MainMenueOptions)
{
    switch (MainMenueOptions)
    {
    case enMainMenueOptions::eListClients:
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClientInfo:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eTransactions:
        system("cls");
        ShowTransactionMenueScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
        break;

    }
}

void ShowMainMenueScreen()
{
    system("cls");
    cout << "============================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "============================================\n";
    cout << "\t[1] Show Client List." << endl;
    cout << "\t[2] Add New Client." << endl;
    cout << "\t[3] Delete Client." << endl;
    cout << "\t[4] Update Client Info." << endl;
    cout << "\t[5] Find Client." << endl;
    cout << "\t[6] Transaction." << endl;
    cout << "\t[7] Exit." << endl;
    cout << "============================================\n";

    PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}


int main()
{
    ShowMainMenueScreen();

    system("pause>0");


    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
