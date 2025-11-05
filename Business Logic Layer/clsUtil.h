
#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

class clsUtil
{

   public:
    enum enCharType {
        SamallLetter = 1, CapitalLetter = 2,
        Digit = 3, MixChars = 4, SpecialCharacter = 5
    };

    static void  Srand()
    {
        //Seeds the random number generator in C++, called only once
        srand((unsigned)time(NULL));
    }

    static  int RandomNumber(int From, int To)
    {
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    static char GetRandomCharacter(enCharType CharType)
    {

        if (CharType == MixChars)
        {
            CharType = (enCharType)RandomNumber(1, 3);

        }

        switch (CharType)
        {

        case enCharType::SamallLetter:
        {
            return char(RandomNumber(97, 122));
        }
        case enCharType::CapitalLetter:
        {
            return char(RandomNumber(65, 90));
        }
        case enCharType::SpecialCharacter:
        {
            return char(RandomNumber(33, 47));
        }
        case enCharType::Digit:
        {
            return char(RandomNumber(48, 57));
        }
    defualt:
        {
            return char(RandomNumber(65, 90));
        }
        }
    }

    static  string GenerateWord(enCharType CharType, short Length)

    {
        string Word;

        for (int i = 1; i <= Length; i++)

        {

            Word = Word + GetRandomCharacter(CharType);

        }
        return Word;
    }

    static string  GenerateKey(enCharType CharType = CapitalLetter)
    {

        string Key = "";


        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);


        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {

        for (int i = 1; i <= NumberOfKeys; i++)

        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }

    }

    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = RandomNumber(From, To);
    }

    static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateWord(CharType, Wordlength);

    }

    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateKey(CharType);
    }

    static  void Swap(int& Number1, int& Number2)
    {
        int Temp;

        Temp = Number1;
        Number1 = Number2;
        Number2 = Temp;
    }

    static  void Swap(double& Number1, double& Number2)
    {
        double Temp;

        Temp = Number1;
        Number1 = Number2;
        Number2 = Temp;
    }

    static  void Swap(bool& A, bool& B)
    {
        bool Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(char& char1, char& char2)
    {
        char Temp;

        Temp = char1;
        char1 = char2;
        char2 = Temp;
    }

    static  void Swap(string& String1, string& String2)
    {
        string Temp;

        Temp = String1;
        String1 = String2;
        String2 = Temp;
    }

    static  void Swap(clsDate& Date1, clsDate& Date2)
    {
        clsDate::SwapDates(Date1, Date2);
    }

    static  void ShuffleArray(int arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }

    }

    static void setArray(int number[], int length)
    {
        for (int i = 0; i < length; i++)
        {
            number[i] = i + 1;
        }
    }
    static void getArray(int number[], int lenight)
    {

        for (int i = 0; i < lenight; i++)
        {
            cout << number[i] << " ";
        }
        cout << endl;
    }
    static void setArray(string number[], int length)
    {
        for (int i = 0; i < length; i++)
        {
            number[i] = i + 1;
        }
    }

    static void getArray(string number[], int lenight)
    {

        for (int i = 0; i < lenight; i++)
        {
            cout << number[i] << " ";
        }
        cout << endl;
    }

    static  void ShuffleArray(string arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }

    }

    static string  Tabs(short NumberOfTabs,string Space="")
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t"+ Space;
            cout << t;
        }
        return t;

    }
    static void Endl(short endlNumber)
    {
        for (int i = 1; i <= endlNumber; i++)
        {
            cout << endl;
        }
    }

    static string  EncryptText(string Text, short EncryptionKey= 2)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] + EncryptionKey);

        }

        return Text;

    }

    static string  DecryptText(string Text, short EncryptionKey=2)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] - EncryptionKey);

        }
        return Text;

    }


    static string NumberToText(int Number)
    {

        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
        "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
          "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

            return  arr[Number] + " ";

        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
            return  arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return  "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return  "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return  "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return  "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }


    }


};













