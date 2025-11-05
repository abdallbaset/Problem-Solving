#pragma once
#include "clsBankClient.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsFindClientScreen:protected clsScreen
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
public:

	static void ShowFindClientScreen()
	{

		if (!CheckAccsessRights(clsUser::enPermissions::pFindClient))
		{
			return;
		}

		_DrawScreenHeader("\tFind Client Screen");

		string AccountNumber = "";
		cout << "\nPleas Enter your Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\nAccount number [" << AccountNumber << "] Not Found, Please try again.";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		if (!Client.IsEmpty())
		{
			cout << "\nClient Found :-)\n";
			_PrintClient(Client);
		}
		else
		{
			cout << "\nClient Not Found :-(\n";
		}
	}
};

