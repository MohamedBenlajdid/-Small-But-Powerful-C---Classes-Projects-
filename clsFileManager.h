#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class clsFileManager
{
public:
    static void CreateNewFile(string& FileName)
    {
        fstream NewFile;
        NewFile.open(FileName, ios::out); // use ios::out for creating/writing
        if (NewFile.is_open())
        {
            cout << "\nFile Created Successfully.";
            NewFile.close(); // always close the file
        }
        else
        {
            cout << "\nFailed to Create the File!";
        }
    }
    static bool IsExistFile(string& FileName)
    {
        fstream File(FileName, ios::in);
        bool IsFound = File.is_open();
        File.close();
        return IsFound;
    }
    static void DeleteExistingFile(string& FileName)
    {
        if (IsExistFile(FileName))
        {
            if (remove(FileName.c_str()) == 0)
                cout << "\nFile Deleted Successfully.";
            else
                cout << "\nError Deleting the File!";
        }
        else
        {
            cout << "\nFile Not Found!";
        }
    }
    static void AddTextToFile(string& FileName, string& Text)
    {
        if (!IsExistFile(FileName))
        {
            cout << "\nFile not found!";
            return;
        }

        fstream File(FileName, ios::app);
        if (File.is_open())
        {
            File << Text << endl;
            File.close();
        }
        else
        {
            cout << "\nFailed to open the file!";
        }
    }
    static void ReplaceTextInFile(string& FileName,string& OldText,string& NewText)
    {
        if (!IsExistFile(FileName))
        {
            cout << "\nFile not found!";
            return;
        }

        fstream File(FileName, ios::in);
        string FileContent = "", Line;

        if (File.is_open())
        {
            while (getline(File, Line))
            {
                while (Line.find(OldText) != string::npos)
                {
                    Line.replace(Line.find(OldText), OldText.length(), NewText);
                }
                FileContent += Line + "\n";
            }
            File.close();
        }
        else
        {
            cout << "\nFailed to open the file for reading!";
            return;
        }

        File.open(FileName, ios::out | ios::trunc);
        if (File.is_open())
        {
            File << FileContent;
            File.close();
        }
        else
        {
            cout << "\nFailed to open the file for writing!";
        }
    }
    static void ReadFileContent(string& FileName)
    {
        if (!IsExistFile(FileName))
        {
            cout << "\nFile not found!";
            return;
        }

        fstream File(FileName, ios::in);
        if (File.is_open())
        {
            cout << "\n--- File Content ---\n";
            string Line;
            while (getline(File, Line))
            {
                cout << Line << endl;
            }
            File.close();
        }
        else
        {
            cout << "\nFailed to open the file!";
        }
    }
    static void SearchWordInFile(string& FileName,string& Word, bool ShowLineNumber = false)
    {
        if (!IsExistFile(FileName))
        {
            cout << "\nFile not found!" << endl;
            return;
        }

        fstream File(FileName, ios::in);
        if (File.is_open())
        {
            string Line;
            short LineNumber = 0;
            bool Found = false;

            while (getline(File, Line))
            {
                LineNumber++;
                if (Line.find(Word) != string::npos)
                {
                    Found = true;
                    if (ShowLineNumber)
                        cout << "\nWord \"" << Word << "\" found in line " << LineNumber << "." << endl;
                    else
                        cout << "\nWord \"" << Word << "\" found in the file." << endl;

                    break;
                }
            }
            File.close();

            if (!Found)
                cout << "\nWord \"" << Word << "\" not found in the file." << endl;
        }
        else
        {
            cout << "\nFailed to open the file!" << endl;
        }
    }
    static void ReplaceWordInFile(string& FileName,string& OldWord, const string& NewWord)
    {
        if (!IsExistFile(FileName))
        {
            cout << "\nFile not found!" << endl;
            return;
        }

        fstream File(FileName, ios::in);
        if (File.is_open())
        {
            string FileContent = "";
            string Line;

            while (getline(File, Line))
            {
                size_t Pos = Line.find(OldWord);
                while (Pos != string::npos)
                {
                    Line.replace(Pos, OldWord.length(), NewWord);
                    Pos = Line.find(OldWord, Pos + NewWord.length()); // search after the new word
                }

                FileContent += Line + "\n"; // add back the line + new line
            }
            File.close();

            // Now write back to the file (overwrite)
            File.open(FileName, ios::out | ios::trunc);
            if (File.is_open())
            {
                File << FileContent;
                File.close();
                cout << "\nAll occurrences of \"" << OldWord << "\" have been replaced with \"" << NewWord << "\"." << endl;
            }
            else
            {
                cout << "\nFailed to write to the file!" << endl;
            }
        }
        else
        {
            cout << "\nFailed to open the file!" << endl;
        }
    }
    static int CountWordInFile(string& FileName, const string& Word)
    {
        if (!IsExistFile(FileName))
        {
            cout << "\nFile not found!" << endl;
            return 0;
        }

        fstream File(FileName, ios::in);
        if (!File.is_open())
        {
            cout << "\nFailed to open the file!" << endl;
            return 0;
        }

        string Line;
        int Count = 0;

        while (getline(File, Line))
        {
            size_t Pos = Line.find(Word);
            while (Pos != string::npos)
            {
                Count++;
                Pos = Line.find(Word, Pos + Word.length());
            }
        }

        File.close();

        return Count;
    }

};

