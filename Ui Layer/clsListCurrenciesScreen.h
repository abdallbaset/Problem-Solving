#pragma once
#include <iomanip>
#include  "clsScreen.h"
#include  "clsCurrency.h"
class clsListCurrenciesScreen:protected clsScreen
{
	static void _PrintCurrenciesRecordLine(clsCurrency Currency)
	{
		cout << left;
		cout << "|" << setw(36)
			<< Currency.Country;

		cout << "|" << setw(10)
			<< Currency.CurrencyCode;

		cout << "|" << setw(40)
			<< Currency.CurrencyName;

		cout << "|" << setw(15)
			<< Currency.Rate
			<< "|\n";
	}
	static void _HeaderCurrencyList()
	{
		cout << left
			<< "----------------------------------------------------------------------------------------------------------\n";
		cout << "|" << setw(36)
			<< " Country ";

		cout << "|" << setw(10)
			<< " Code ";

		cout << "|" << setw(40)
			<< " Name";


		cout << "|" << setw(15)
			<< " Rate/(1$) "
			<< "|\n";

		cout << "----------------------------------------------------------------------------------------------------------\n";
	}
public:
	static void ShowCurrenciesListScreen()
	{
	
		vector<clsCurrency>vCurrencys = clsCurrency::GetCurrencysList();
		if (vCurrencys.size() > 0)
		{
			string Title = "\tCurrencies List Screen";
			string SubTitle = "\t" + to_string(vCurrencys.size()) + " Currencies(s)";
			_DrawScreenHeader(Title, SubTitle);
			_HeaderCurrencyList();
			for (clsCurrency & Currency : vCurrencys)
			{
				_PrintCurrenciesRecordLine(Currency);
			}

		}
		else
		{
			cout << "\t\t\t\t\tNo Currencies Available in the System :-(\n";
		}
		cout << "----------------------------------------------------------------------------------------------------------\n";

	}
};

