#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

struct informations
{
    string Account_Num;
    string Pin_Code;
    string FullName;
    string Phone_Num;
    string Account_Balance;
    bool MarForDelete = false;
};

// Split string
vector<string> split_string(string s, string delim)
{
    vector<string> store_words;

    int pos = 0;
    string sWord;

    while ((pos = s.find(delim)) != string::npos)
    {
        sWord = s.substr(0, pos);

        if (sWord != "")
        {
            store_words.push_back(sWord);
        }

        s.erase(0, pos + delim.length());
    }

    if (s != "")
    {
        store_words.push_back(s);
    }

    return store_words;
}

// Convert line from file to record
informations ConvertLineToRecord(string line, string separator = "#//#")
{
    informations client;

    vector<string> vClientData = split_string(line, separator);

    if (vClientData.size() >= 5)
    {
        client.Account_Num = vClientData[0];
        client.Pin_Code = vClientData[1];
        client.FullName = vClientData[2];
        client.Phone_Num = vClientData[3];
        client.Account_Balance = vClientData[4];
    }

    return client;
}

// Read clients from file
vector<informations> ReadFromFile(string FileName)
{
    vector<informations> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string line;

        while (getline(MyFile, line))
        {
            if (!line.empty())
            {
                informations client = ConvertLineToRecord(line);
                vClients.push_back(client);
            }
        }

        MyFile.close();
    }

    return vClients;
}

// Print client
void PrintClientRecord(informations Client)
{
    cout << "| " << setw(15) << left << Client.Account_Num;
    cout << "| " << setw(10) << left << Client.Pin_Code;
    cout << "| " << setw(40) << left << Client.FullName;
    cout << "| " << setw(12) << left << Client.Phone_Num;
    cout << "| " << setw(12) << left << Client.Account_Balance;
}

// Read account number
string ReadClientAccountNumber()
{
    string AccountNumber;

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;

    return AccountNumber;
}

// Convert record to line
string ConvertRecordToLine(informations Client, string Separator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.Account_Num + Separator;
    stClientRecord += Client.Pin_Code + Separator;
    stClientRecord += Client.FullName + Separator;
    stClientRecord += Client.Phone_Num + Separator;
    stClientRecord += Client.Account_Balance;

    return stClientRecord;
}

// Save clients to file
void SaveClientsDataToFile(string FileName, vector<informations>& vClients)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (informations& c : vClients)
        {
            if (c.MarForDelete == false)
            {
                MyFile << ConvertRecordToLine(c) << endl;
            }
        }

        MyFile.close();
    }
}

// Change client information
informations ChangeClientRecord(string AccountNumber)
{
    informations Client;

    Client.Account_Num = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.Pin_Code);

    cout << "Enter Name? ";
    getline(cin, Client.FullName);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone_Num);

    cout << "Enter AccountBalance? ";
    cin >> Client.Account_Balance;

    return Client;
}

// Update client
bool UpdateClientByAccountNumber(
    string AccountNumber,
    vector<informations>& vClients)
{
    char Answer = 'n';

    // Search inside the vector
    for (informations& Client : vClients)
    {
        if (Client.Account_Num == AccountNumber)
        {
            cout << "\n\nClient found:\n";
            PrintClientRecord(Client);

            cout << "\n\nAre you sure you want to update this client? y/n? ";
            cin >> Answer;

            if (Answer == 'Y' || Answer == 'y')
            {
                // Change the client in the vector
                Client = ChangeClientRecord(AccountNumber);

                // Save the updated vector to the file
                SaveClientsDataToFile("client.txt", vClients);

                cout << "\n\nClient Updated Successfully.";
                return true;
            }
            else
            {
                cout << "\nClient was not updated.";
                return false;
            }
        }
    }

    cout << "\nClient with Account Number ("
         << AccountNumber << ") is Not Found!";

    return false;
}

int main()
{
    vector<informations> vClients;

    // Load clients
    vClients = ReadFromFile("client.txt");

    // Get account number
    string AccountNumber = ReadClientAccountNumber();

    // Update client
    UpdateClientByAccountNumber(AccountNumber, vClients);

    return 0;
}
