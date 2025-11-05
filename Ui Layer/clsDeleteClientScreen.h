#pragma once
#include "clsBankClient.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;
class clsDeleteClientScreen:protected clsScreen
{
private:
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
public :
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccsessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}


		_DrawScreenHeader("\tDelete client Screen");

		string AccountNumber = "";
		cout << "\nPleas Enter your Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\nAccount number ["<< AccountNumber<<"] Not Found, Please try again.";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		char Answer = 'Y';
		cout << "Are you sure you want to delete this client? (Y/N) ?=> ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client);
			}
			else
			{
				cout << "\nError Client was not  Deleted :-(\n";

			}
		}
		else
		{
			cout << "\nThe deletion procedure has been cancelled.\n";
		}
	}
};

