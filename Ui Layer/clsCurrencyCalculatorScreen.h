#pragma once
#include  "clsScreen.h"
#include  "clsCurrency.h"
#include  "clsInputValidate.h"
class clsCurrencyCalculatorScreen :protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency  Currency,string Title = "\nCurrency Card:")
	{
		cout << "\n" << Title;
		cout << "\n-------------------------";
		cout << "\nCountry      :" << Currency.Country;
		cout << "\nCurrencyCode :" << Currency.CurrencyCode;
		cout << "\nCurrencyName :" << Currency.CurrencyName;
		cout << "\nRate/(1$)    :" << Currency.Rate;
		cout << "\n-------------------------\n";
	}
	static clsCurrency _GetCurrency(string Message)
	{
		cout << Message;
		string CurrencyCode = "";
		CurrencyCode = clsInputValidate::ReadString();

		while (!(clsCurrency::IsCurrencyExistbyCode(CurrencyCode)))
		{
			cout << "\nCurrency Code[" << CurrencyCode << "] Not Found, Please try again.";
			CurrencyCode = clsInputValidate::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return Currency;
	}

	static float _ReadAmount()
	{
		float Amount = 0.0;
		cout << "\nEnter Amount to Exchange :";
		Amount = clsInputValidate::ReadNumber<float>();
		return Amount;
	}

	static void _PrintacCalculationsResults(float Amount, clsCurrency  Currency1,clsCurrency Currency2)
	{
		 float AmountInUSD = Currency1.ConvertToUSD(Amount);
		_PrintCurrency(Currency1, "Convert From :");
		cout << Amount << " " << Currency1.CurrencyCode << " = " << AmountInUSD << " USD" << endl;

		if (Currency2.CurrencyCode == "USD")
		{
			return;
		}
		cout << "\nConvert From :\n";
		_PrintCurrency(Currency2, "To:");
		float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);
		cout << Amount << " " << Currency1.CurrencyCode << " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode << endl;

	}
public:
	static void ShowCurrencyCalculatorScreen()
	{
	    char Continue = 'N';
		
		do {
			 system("cls");
			_DrawScreenHeader("Currency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPleas Enter Currency From : ");
			clsCurrency CurrencyTo   = _GetCurrency("\nPleas Enter Currency To : ");
			float Amount = _ReadAmount();

			_PrintacCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

			cout << "\nDo you want perform another Calculator ? (Y/N) ? ";
			cin >> Continue;

		} while (toupper(Continue) == 'Y');
	
		
	}

};

