#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _Mode;
    string _AccountNumber;
    string _PINcode;
    float  _AccountBalance;

    static clsBankClient _LoadClientDataFromFile(string& FileName)
    {
        vector<clsBankClient> vClientData;
        fstream File(FileName, ios::in);
        if (File.is_open())
        {
            string Line;
            clsBankClient Client;
            while (getline(File, Line))
            {
                Client = _ConvertLineToClientObj(Line);
                vClientData.push_back(Client);
            }
            File.close();
        }
        return  vClientData;
    }

    static void _SaveClientDataToFile(string& FileName,vector<clsBankClient>& vClientData)
    {
        fstream File(FileName, ios::out);
        if (File.is_open())
        {
            string Line;
            for (clsBankClient& C : vClientData)
            {
                Line = _ConvertClientDataToLine(C);
                File << Line << endl;
            }
            File.close();
        }
    }

    static clsBankClient _ConvertLineToClientObj(string& Line, string Separetor = "#//#")
    {
        vector <string> vClientData = clsString::Split(Line,Separtor);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], vClientData[6], vClientData[7]);
    }
    
    static string _ConvertClientDataToLine(clsBankClient& ClientData,string Separetor = "#//#")
    {
        string DataLine = "";
        DataLine += ClientData.FirstName + Separetor;
        DataLine += ClientData.LastName + Separetor;
        DataLine += ClientData.Email + Separetor;
        DataLine += ClientData.Phone + Separetor;
        DataLine += ClientData.AccountBalance + Separetor;
        DataLine += ClientData.PINcode + Separetor;
        DataLine += to_string(ClientData.AccountBalance);
        return DataLine;
    }

    static clsBankClient _GetEmptyClientObj()
    {
        clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", "", "");
    }

    void _Update()
    {
        vector<clsBankClient> _vClientData;
        _vClientData = _LoadClientDataFromFile("Client.txt");
        for (clsBankClient& C : _vClientData)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C = *this;
                break;
            }
        }
        _SaveClientDataToFile(_vClientData);
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }


public:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
        string AccountNumber, string PINcode, float AccountBalance) : clsPerson(FirstName, LastName,
            Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PINcode = PINcode;
        _AccountBalance = AccountBalance;
    }

    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPINcode(string PINcode)
    {
        _PINcode = PINcode;
    }
    string GetPINcode()
    {
        return _PINcode;
    }
    __declspec(property(get = GetPINcode, put = SetPINcode))string PINcode;

    void SetAccountBalance(float Balance)
    {
        _AccountBalance = Balance;
    }
    float GetAccountBalance() 
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    static clsBankClient Find(string& AccountNumber)
    {
        fstream File("Client.txt", ios::in); // FileName HardCode Right now , Mode : Reading.
        if (File.is_open())
        {
            string Line;
            clsBankClient Client;
            while (File, Line)
            {
                Client = _ConvertLineToClientObj(Line, "#//#");
                if (Client.AccountNumber == AccountNumber)
                {
                    File.close();
                    return Client;
                }
            }
            File.close();
        }
            return _GetEmptyClientObj();
    }
    static clsBankClient Find(string AccountNumber, string PinCode)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
            break;
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
            break;
        }

        }
    }

    static bool IsClientExist(string& AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty);
    }

    };

