#pragma once
#include "clsBankClient.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsDepositScreen:protected clsScreen
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
	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\tDeposit Screen");
		cout << "\nPleas Enter your Account Number : ";
		string AccountNumber = _ReadAccountNumber();

		while (!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\nAccount number [" << AccountNumber << "] Not Found, Please try again.";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		int DepositAmount = 0;
		cout << "\nPlase Enter  Deposit Amount ? ";
		 DepositAmount = clsInputValidate::ReadNumber<int>();

		char Answer = 'y';
		cout << "\nAre you sure you want to Prefrom this transaction? (Y/N) ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Client.Deposit(DepositAmount);
			cout << "\nDeposit successful :-).\n\nNew Blances is " << Client.AccountBalance << endl;
		}
		else
		{
			cout << "\nThe Deposit has been cancelled.\n";
		}
	}
};

