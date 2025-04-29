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

    static clsBankClient _ConvertLineToClientObj(string& Line, string Separetor = "#//#")
    {
        vector <string> vClientData = clsString::Split(Line,Separtor);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], vClientData[6], vClientData[7]);
    }
    
    static clsBankClient _GetEmptyClientObj()
    {
        clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", "", "");
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

