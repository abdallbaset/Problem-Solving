#pragma once
#include "clsBankClient.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;
class clsAddNewClientsScreen:protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter your Firs Name:";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter your Last Name:";
		Client.LastName = clsInputValidate::ReadString();
		cout << "\nEnter your Email:";
		Client.Email = clsInputValidate::ReadString();
		cout << "\nEnter your Phone:";
		Client.Phone = clsInputValidate::ReadString();
		cout << "\nEnter your PinCode:";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "\nEnter your Balance:";
		Client.AccountBalance = clsInputValidate::ReadNumber<int>();
	}
	static void _PrintClient(clsBankClient  Client)
	{
		cout << "\nClient Card:";
		cout << "\n-------------------------";
		cout << "\nFirstName   :" <<Client.FirstName;
		cout << "\nLastName    :" <<Client.LastName;
		cout << "\nFullName    :" <<Client.FullName;
		cout << "\nEmail       :" <<Client.Email;
		cout << "\nPhone       :" <<Client.Phone;
		cout << "\nAcco. Number:" <<Client.AccountNumber;
		cout << "\nPassWord    :" <<Client.PinCode;
		cout << "\nBalance     :" <<Client.AccountBalance;
		cout << "\n-------------------------\n";
	}
public:
	static void ShowAddNewClientScreen()
	{

		if (!CheckAccsessRights(clsUser::enPermissions::pAddNewClient))
		{
			return ;
		}


		_DrawScreenHeader("\tAdd clients Screen");

		string AccountNumber = "";
		cout << "\nPleas Enter your Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is Used, Please try again.";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);


		clsBankClient::enSaveResult SaveResult;
		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResult::svSucceeded:
			cout << "\nClient added Successfully :-)\n";
			_PrintClient(NewClient); break;

		case clsBankClient::enSaveResult::svFaildEmptyObject:
			cout << "Error Account was not saved because it’s Empaty\n"; break;

		case clsBankClient::enSaveResult::svFaildAccountNumberExists:
			cout << "Account number failed to use :-(\n"; break;
		default:
			cout << "Not among the expected cases !!\n";
		}
	}
};

