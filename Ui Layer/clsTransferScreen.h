#pragma once
#include "clsBankClient.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
class clsTransferScreen:protected clsScreen
{
private:
	static void _PrintClient(clsBankClient  Client)
	{
		cout << "\nClient Card:";
		cout << "\n-------------------------";
		cout << "\nFullName    :" << Client.FullName;
		cout << "\nAcco. Number:" << Client.AccountNumber;
		cout << "\nBalance     :" << Client.AccountBalance;
		cout << "\n-------------------------\n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString();

		while (!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\nAccount number [" << AccountNumber << "] Not Found, Please try again.";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static int _ReadAmount(clsBankClient Client)
	{
		int TransferAmount = 0;
		cout << "Enter Transfer Amount ? ";
		TransferAmount = clsInputValidate::ReadNumberBetween<int>(1, Client.AccountBalance, "Amount Exceeds the available Balance ,Enter another Amount ? ");
		return TransferAmount;
	}
public:
	static void ShowTransferScreen()
	{

		_DrawScreenHeader("    Transfer Screen");

		cout << "\nPleas Enter your Account Number to Transfer From : ";
		string AccountNumberTransferFrom = _ReadAccountNumber();
		clsBankClient SourceClient = clsBankClient::Find(AccountNumberTransferFrom);
		_PrintClient(SourceClient);

		cout << "\nPleas Enter your Account Number to Transfer To : ";
		string AccountNumberTransferTo = _ReadAccountNumber();
		clsBankClient DestinationClinet = clsBankClient::Find(AccountNumberTransferTo);
		_PrintClient(DestinationClinet);

		int TransferAmount = _ReadAmount(SourceClient);

		char Answer = 'N';
		cout << "Are you sure you want to preform this Operation? (Y/N) ?=> ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			if (SourceClient.Transfer(TransferAmount, DestinationClinet,CurrentUser.UserName))
			{
				cout << "\nTransfer Successfully :-)\n";
				_PrintClient(SourceClient);
				_PrintClient(DestinationClinet);
				
			}
			else
			{
				cout << "Transfer Faild :-(\n";
			}
			
		}
		else
		{
			cout << "\nThe Transfertion procedure has been cancelled.\n";
		}
	}
};

