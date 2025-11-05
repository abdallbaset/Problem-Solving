#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;
class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	 float  _Rate;

	static clsCurrency _ConvertLinetoCurrencyObject(string LineData, string Sepertor = "#//#")
	{
		vector<string> vWord = clsString::Split(LineData, Sepertor);
		return clsCurrency(enMode::UpdateMode, vWord[0], vWord[1], vWord[2], stof(vWord[3]));

	}
	static string _ConvertCurrencyObjectToline(clsCurrency CurrencyInfo, string Separator = "#//#")
	{
		string Line = "";
		Line +=CurrencyInfo.Country + Separator;
		Line +=CurrencyInfo.CurrencyCode + Separator;
		Line +=CurrencyInfo.CurrencyName + Separator;
		Line += to_string(CurrencyInfo.Rate);
		return Line;
	}

	void _Update()
	{
		vector<clsCurrency> vCurrencys;
		vCurrencys = _LoadCurrencyDataFromFaile();
		for (clsCurrency & Currency : vCurrencys)
		{
			if (Currency.CurrencyCode == CurrencyCode)
			{
				Currency = *this;
				break;
			}
		}
		_SaveCurrencysDataToFile(vCurrencys);
	}
	static void _SaveCurrencysDataToFile(vector<clsCurrency> vCurrencys)
	{
		string LineData = "";
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsCurrency & Currency : vCurrencys)
			{
					LineData = _ConvertCurrencyObjectToline(Currency);
					MyFile << LineData << endl;
			}
			MyFile.close();
		}
	}
	static vector<clsCurrency> _LoadCurrencyDataFromFaile()
	{
		vector<clsCurrency>vCurrencys;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		string line = "";
		if (MyFile.is_open())
		{
			while (getline(MyFile, line))
			{
				clsCurrency CurrencyInfo = _ConvertLinetoCurrencyObject(line);
				vCurrencys.push_back(CurrencyInfo);
			}
			MyFile.close();
		}
		return vCurrencys;
	}

  static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0.0);
	}

public:
	clsCurrency(enMode Mode, string Country,string CurrencyCode,string CurrencyName,float Rate)
	{
		_Mode = Mode;
		_Country= Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string GetCountry()
	{
		return _Country;
    }
	__declspec(property(get = GetCountry))string Country;

	string GetCurrencyCode()
	{
		return _CurrencyCode;
    }
	__declspec(property(get = GetCurrencyCode))string CurrencyCode;

	string GetCurrencyName()
	{
		return _CurrencyName;
    }
	__declspec(property(get = GetCurrencyName))string CurrencyName;

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}
     float GetRate()
	{
		return _Rate;

    }
	 __declspec(property(get = GetRate))float Rate;

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(line);
				if (clsString::UpperAllString(Currency.Country) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();

		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string Code)
	{
		Code = clsString::UpperAllString(Code);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(line);
				if (Currency.CurrencyCode == Code)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();

		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExistbyCode(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}
	
	static vector<clsCurrency> GetCurrencysList()
	{
		return _LoadCurrencyDataFromFaile();
	}

	 float ConvertToUSD(float Amount)
	{
		return  Amount / Rate;
	}
	 float ConvertToOtherCurrency( float Amount, clsCurrency Currency2 )
	{
		 float AmountInUSD = ConvertToUSD(Amount);
		 if (Currency2.CurrencyCode == "USD")
		 {
			 return AmountInUSD;
		 }

		return AmountInUSD * Currency2.Rate;
	}
};

