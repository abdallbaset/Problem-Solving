#pragma once
#include <iomanip>
#include  "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;
class clsCurrencyExchangeMainScreen:protected clsScreen
{
private:
	enum enCurrenciesMainMenuOptions { eListCurrency = 1, eFindCurrency = 2, eUpdateCurrencyRate = 3, eCurrencyCalculator = 4, MainMenu = 5 };
	static short _ReadCurrencyExchangeMenuOptions()
	{
		short NumberOfOption = 0;
		cout << "Chose what do you want to do? [1 to 5]?";
		NumberOfOption = clsInputValidate::ReadNumberBetween<short>(1, 5);
		return NumberOfOption;
	}
	static void _GoBackToCurrenciesMenu()
	{
		cout << "\nPress any key to go back to Currency Exchange Menu...";
		system("pause > nul");
		ShowCurrencysMenue();
	}

	static void _ShowListCurrenciesScreen()
	{
		clsListCurrenciesScreen::ShowCurrenciesListScreen();
	}
	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateCurrencyRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}
	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PreformCurrenciesMainMenu(enCurrenciesMainMenuOptions UserOption)
	{
		switch (UserOption)
		{
		case enCurrenciesMainMenuOptions::eListCurrency:
		{
			  system("cls");
			 _ShowListCurrenciesScreen();
			_GoBackToCurrenciesMenu();
		}; break;
		case enCurrenciesMainMenuOptions::eFindCurrency:
		{
			 system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrenciesMenu();
		}; break;
		case enCurrenciesMainMenuOptions::eUpdateCurrencyRate:
		{
			 system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrenciesMenu();

		}; break;
		case enCurrenciesMainMenuOptions::eCurrencyCalculator:
		{
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrenciesMenu();

		}; break;
		
		case enCurrenciesMainMenuOptions::MainMenu:
		{
		}; break;
		default:
			cout << "This option Not Bounds the Option Menu :-(\n";
		}
	}
public:
	static void ShowCurrencysMenue()
	{
		/*if (!CheckAccsessRights(clsUser::enPermissions::pManageUsers))
		{
			return;
		}*/

	 	system("cls");
		_DrawScreenHeader("Currency Exchange Main Screen");
		cout << "-----------------------------------------------------\n";
		cout << "\t\tCurrency Exchange Menue\t\t    |\n";
		cout << "-----------------------------------------------------\n";
		cout << "\t[1] List Currency.\t\t\t    |\n";
		cout << "\t[2] Find Currency.\t\t\t    |\n";
		cout << "\t[3] Update Rate.\t\t\t    |\n";
		cout << "\t[4] Currency Calculator.\t\t    |\n";
		cout << "\t[5] Main Menu.\t\t\t\t    |\n";
		cout << "-----------------------------------------------------\n";
		_PreformCurrenciesMainMenu((enCurrenciesMainMenuOptions)_ReadCurrencyExchangeMenuOptions());
	}
};

