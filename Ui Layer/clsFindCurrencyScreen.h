#pragma once
#include  "clsScreen.h"
#include  "clsCurrency.h"
#include  "clsInputValidate.h"

class clsFindCurrencyScreen:protected clsScreen
{
private:
	enum CurrencySearchOption{eByCurrencyCode = 1, eByCountryName= 2};
	static void _PrintCurrency(clsCurrency  Currency)
	{
		cout << "\Currency Card:";
		cout << "\n-------------------------";
		cout << "\nCountry      :" << Currency.Country;
		cout << "\nCurrencyCode :" << Currency.CurrencyCode;
		cout << "\nCurrencyName :" << Currency.CurrencyName;
		cout << "\nRate/(1$)    :" << Currency.Rate;
		cout << "\n-------------------------\n";
	}

	static CurrencySearchOption ReadCurrencySearchOption()
	{
		short NumberOfSearchOption = 0;
		cout << "Find By :[1] Code or [2] Country ? ";
		NumberOfSearchOption = clsInputValidate::ReadNumberBetween<short>(1, 2, "Wrong choice ,Please Find By :[1] Code or [2] Country ? ");
		return (CurrencySearchOption)NumberOfSearchOption;
	}
	static void _ShowResult(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Not Found :-(\n";
		}
	}
public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\tFind Currency Screen");
		CurrencySearchOption NumberOfSearchOption = ReadCurrencySearchOption();

		switch (NumberOfSearchOption)
		{
		  case CurrencySearchOption::eByCurrencyCode:
		  {
		    string CurrencyCode = "";
			cout << "\nPlease Enter CurrencyCode : ";
			CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			 _ShowResult(Currency);
		  }; break;

		  case CurrencySearchOption::eByCountryName:
		  {
			  string CountryName = "";
			cout << "\nPlease Enter Country Name : ";
			CountryName = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(CountryName);
			_ShowResult(Currency);
		
		  }; break;

		  default:
			cout << "This option Not Bounds the Option Menu :-(\n";
		}
	}
};

