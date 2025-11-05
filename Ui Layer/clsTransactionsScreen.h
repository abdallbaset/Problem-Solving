#pragma once
#include "clsBankClient.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
using namespace std;
class clsTransactionsScreen:clsScreen
{
	enum enTransactionsMenuOptions { eDeposit = 1, eWithdraw = 2, eTotalBlances = 3,eTransfer = 4, eTransferLog =5 ,eMainMenue = 6 };

	static short _ReadTransactionsMenuOptions( )
	{
		short NumberOfOption = 0;
		cout << "Chose what do you want to do? [1 to 6]?";
		NumberOfOption = clsInputValidate::ReadNumberBetween<short>(1, 6);
		return NumberOfOption;
	}
	
	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _showTotalBalancesOfScreen()
	{
		clsTotalBalanceScreen::ShowTotalBalancesScreen();
	}
	static void _ShowTransferScreen()
	{
	     clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}
	
	static void _GoBackTransactionsMenu()
	{
		cout << "\nPress any key to go back to Transactions Menu...";
		system("pause > nul");
		ShowTransactionsMenu();
	}
	static void _PreformTransactionsMenu(enTransactionsMenuOptions ClientOption)
	{
		switch (ClientOption)
		{
		case enTransactionsMenuOptions::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackTransactionsMenu();
		}; break;
		case enTransactionsMenuOptions::eWithdraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackTransactionsMenu();
		}; break;
		case enTransactionsMenuOptions::eTotalBlances:
		{
			system("cls");
			_showTotalBalancesOfScreen();
			_GoBackTransactionsMenu();

		}; break;

		case enTransactionsMenuOptions::eTransfer:
		{
			system("cls");
			_ShowTransferScreen();
			_GoBackTransactionsMenu();

		}; break;
		case enTransactionsMenuOptions::eTransferLog:
		{
			system("cls");
			_ShowTransferLogScreen();
			_GoBackTransactionsMenu();

		}; break;
		case enTransactionsMenuOptions::eMainMenue:
		{
			
		}; break;
		default:
			cout << "This option Not Bounds the Option Menu :-(\n";
		}
	}


public:
	static void ShowTransactionsMenu()
	{
		if (!CheckAccsessRights(clsUser::enPermissions::pTranactions))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("   Transactions Screen");
		cout << "-----------------------------------------------------\n";
		cout << "\t\tTransactions Menue Screen\t    |\n";
		cout << "-----------------------------------------------------\n";
		cout << "\t[1] Deposit.\t\t\t\t    |\n";
		cout << "\t[2] Withdraw.\t\t\t\t    |\n";
		cout << "\t[3] Total Blances.\t\t\t    |\n";
		cout << "\t[4] Transfer.\t\t\t\t    |\n";
		cout << "\t[5] Transfer Log.\t\t\t    |\n";
		cout << "\t[6] Main Menue.\t\t\t\t    |\n";
		cout << "-----------------------------------------------------\n";
		_PreformTransactionsMenu((enTransactionsMenuOptions)_ReadTransactionsMenuOptions());
	}
};

