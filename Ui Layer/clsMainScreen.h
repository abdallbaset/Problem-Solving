#pragma once
#include <iostream>
#include  "clsScreen.h"
#include  "clsInputValidate.h"
#include  "clsClientListScreen.h"
#include  "clsAddNewClientsScreen.h"
#include  "clsDeleteClientScreen.h"
#include  "clsUpdateClientScreen.h"
#include  "clsFindClientScreen.h"
#include  "clsTransactionsScreen.h"
#include  "clsManageUserScreen.h"
#include  "Global.h"
#include  "clsLoginRegisterScreen.h"
#include  "clsCurrencyExchangeMainScreen.h"

using namespace std;

class clsMainScreen:protected clsScreen
{
private:
	enum _enMainMenuOptions {
		ShowClientList = 1, Add_NewClient = 2, DeleteClient = 3, Update_ClientInfo = 4, FindClient = 5, Transactions = 6,
		ManageUser = 7,LoginRegister = 8,CurrencyExchange = 9 ,Logout = 10
	};

	static void _GoBackMainMenu()
	{
		cout << "\nPress any key to go back to Main Menu...";
		system("pause > nul");
		ShowMainMenu();
	}
	static void _ShowAddNewClients()
	{
		clsAddNewClientsScreen::ShowAddNewClientScreen();
	}
	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}
	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::showUpdateClientScreen();
	}
	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientsList();
	}
	
	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}
	static void _ShowTransactionsMenue()
	{
		clsTransactionsScreen::ShowTransactionsMenu();
	}
	static void _ShowMangeUsersMenue()
	{
		clsManageUserScreen::ShowMangeUsersMenue();
	}
	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterList();
	}
	static void _ShowCurrencyExchangeScreen()
	{
		clsCurrencyExchangeMainScreen::ShowCurrencysMenue();
	}
	static void _LogOut()
	{
		CurrentUser = clsUser::Find("","");
	}

	static void _PreformMainMenu(_enMainMenuOptions ClientOption)
	{

		switch (ClientOption)
		{
		case _enMainMenuOptions::Add_NewClient:
		{
			system("cls");
			_ShowAddNewClients();
			_GoBackMainMenu();

		}; break;
		case _enMainMenuOptions::DeleteClient:
		{
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackMainMenu();

		}; break;
		case _enMainMenuOptions::Update_ClientInfo:
		{
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackMainMenu();

		}; break;
		case _enMainMenuOptions::ShowClientList:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackMainMenu();
		}; break;
		case _enMainMenuOptions::FindClient:
		{

			system("cls");
			_ShowFindClientScreen();
			_GoBackMainMenu();

		}; break;
		case _enMainMenuOptions::Transactions:
		{
			system("cls");
			_ShowTransactionsMenue();
			_GoBackMainMenu();
		}; break;
		case _enMainMenuOptions::ManageUser:
		{
			system("cls");
			_ShowMangeUsersMenue();
			_GoBackMainMenu();
		}; break;
		case _enMainMenuOptions::LoginRegister:
		{
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackMainMenu();
		}; break;

		case _enMainMenuOptions::CurrencyExchange:
		{
			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackMainMenu();
		}; break;
		case _enMainMenuOptions::Logout:
			system("cls");
			_LogOut();
			break;
		default:
			cout << "This option Not Bounds the Option Menu :-(\n";
		}
	}
	static short _ReadMenuOptions()
	{
		short NumberOfOption = 0;
		cout << "Chose what do you want to do? [1 to 10]?";
		 NumberOfOption =clsInputValidate::ReadNumberBetween<short>(1,10) ;
		return NumberOfOption;
	}
public:
	static void ShowMainMenu()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");
		cout << "-----------------------------------------------------\n";
		cout << "\t\tMain Menu Screen                    |\n";
		cout << "-----------------------------------------------------\n";
		cout << "\t[1] Show Client List.\t\t\t    |\n";
		cout << "\t[2] Add New Client.\t\t\t    |\n";
		cout << "\t[3] Delete Client.\t\t\t    |\n";
		cout << "\t[4] Update Client Info.\t\t\t    |\n";
		cout << "\t[5] Find Client.\t\t\t    |\n";
		cout << "\t[6] Transactions.\t\t\t    |\n";
		cout << "\t[7] Mange User.\t\t\t\t    |\n";
		cout << "\t[8] Login Register.\t\t\t    |\n";
		cout << "\t[9] Currency Exchange.\t\t\t    |\n";
		cout << "\t[10] LogOut.\t\t\t\t    |\n";
		cout << "-----------------------------------------------------\n";
		_PreformMainMenu((_enMainMenuOptions)_ReadMenuOptions());
	}
};

