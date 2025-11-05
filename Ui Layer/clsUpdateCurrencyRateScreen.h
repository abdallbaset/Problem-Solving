#pragma once
#include  "clsScreen.h"
#include  "clsCurrency.h"
#include  "clsInputValidate.h"
class clsUpdateCurrencyRateScreen:protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency  Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n-------------------------";
		cout << "\nCountry      :" << Currency.Country;
		cout << "\nCurrencyCode :" << Currency.CurrencyCode;
		cout << "\nCurrencyName :" << Currency.CurrencyName;
		cout << "\nRate/(1$)    :" << Currency.Rate;
		cout << "\n-------------------------\n";
	}
	public:
		static void ShowUpdateCurrencyRateScreen()
		{
			_DrawScreenHeader("Update Currency Screen");

			string CurrencyCode = "";
			cout << "\nPleas Enter Currency Code : ";
			CurrencyCode = clsInputValidate::ReadString();

			while (!(clsCurrency::IsCurrencyExistbyCode(CurrencyCode)))
			{
				cout << "\nCurrency Code[" << CurrencyCode << "] Not Found, Please try again.";
				CurrencyCode = clsInputValidate::ReadString();
			}

			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_PrintCurrency(Currency);
			
				char Answer = 'Y';
			cout << "Are you sure you want to Update the Rate of this Currency? (Y/N) ?=> ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{
				cout << "\nUpdate Currency Rate :\n";
				cout << "_____________________________\n";
				cout << "Enter New Rate : ";
				float NewRate = clsInputValidate::ReadNumber<float>();
				Currency.UpdateRate(NewRate);

				cout << "\nCurrency Rate Updated Successfully :-)\n";
				_PrintCurrency(Currency);
			}
			else
			{
				cout << "\nThe Updation procedure has been cancelled.\n";
			}
		}

};

