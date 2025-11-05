#pragma once
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;
class clsWithdrawScreen:protected clsScreen
{
private:
	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString();
		return AccountNumber;
	}
	static void _PrintClient(clsBankClient  Client)
	{
		cout << "\nClient Card:";
		cout << "\n-------------------------";
		cout << "\nFirstName   :" << Client.FirstName;
		cout << "\nLastName    :" << Client.LastName;
		cout << "\nFullName    :" << Client.FullName;
		cout << "\nEmail       :" << Client.Email;
		cout << "\nPhone       :" << Client.Phone;
		cout << "\nAcco. Number:" << Client.AccountNumber;
		cout << "\nPassWord    :" << Client.PinCode;
		cout << "\nBalance     :" << Client.AccountBalance;
		cout << "\n-------------------------\n";
	}
public:
	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("     Withdraw Screen");
		cout << "\nPleas Enter your Account Number : ";
		string AccountNumber = _ReadAccountNumber();

		while (!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\nAccount number [" << AccountNumber << "] Not Found, Please try again.";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		int WithdrawAmount = 0;
		cout << "\nPlase Enter  Withdraw Amount ? ";
		WithdrawAmount = clsInputValidate::ReadNumber<int>();

		if (WithdrawAmount > Client.AccountBalance)
		{
			cout << "\nYour current salary is " << Client.AccountBalance << endl;
			cout << "No withdrawal amount ["<< WithdrawAmount<<"] available in your account. ";
			return;
		}
		else
		{
			char Answer = 'y';
			cout << "\nAre you sure you want to Prefrom this transaction? (Y/N) ? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Client.Withdraw(WithdrawAmount);
				cout << "\nWithdraw successful :-).\n\nNew Blances is " << Client.AccountBalance << endl<<endl;
			}
			else
			{
				cout << "\nThe Withdraw has been cancelled.\n";
			}
		}
	}
};

