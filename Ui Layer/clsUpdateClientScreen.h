#pragma once
#include "clsBankClient.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsUpdateClientScreen:protected clsScreen
{
private:
	enum enUpdateOptions
	{
		eFirstName = 1, eLastName = 2, eEmail = 3, ePhone = 4, ePinCode = 5, eBalance = 6, eAll = 7
	};
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
	static void _SpecificUpdate(clsBankClient &client)
	{
		short NumberofOption = 0;
		cout << "Enter Your number of the option you want to modify\n[FirstName = 1,LastName = 2,Email = 3, Phone = 4,Pincode = 5 ,Balance = 6,All =7] => ";
		NumberofOption = clsInputValidate::ReadNumberBetween<short>(1, 7);

		switch (NumberofOption)
		{
		case enUpdateOptions::eFirstName:_ReadFirstName(client); break;
		case enUpdateOptions::eLastName:_ReadLastName(client); break;
		case enUpdateOptions::eEmail:_ReadEmail(client); break;
		case enUpdateOptions::ePhone:_ReadPhone(client); break;
		case enUpdateOptions::ePinCode:_ReadPinCode(client); break;
		case enUpdateOptions::eBalance:_ReadBalance(client); break;
		case enUpdateOptions::eAll:_ReadClientInfo(client); break;
		default:
			cout << "This option Not Bounds the Option :-(\n";
		}
	}
	static void _ReadEmail(clsBankClient& Client)
	{
		cout << "\nEnter your new Email:";
		Client.Email = clsInputValidate::ReadString();
	}
	static void _ReadFirstName(clsBankClient& Client)
	{
		cout << "\nEnter your new Firs Name:";
		Client.FirstName = clsInputValidate::ReadString();
	}
	static void _ReadLastName(clsBankClient& Client)
	{
		cout << "\nEnter your new Last Name:";
		Client.LastName = clsInputValidate::ReadString();
	}
	static void _ReadPhone(clsBankClient& Client)
	{
		cout << "\nEnter your new Phone:";
		Client.Phone = clsInputValidate::ReadString();
	}
	static void _ReadPinCode(clsBankClient& Client)
	{
		cout << "\nEnter your new PinCode:";
		Client.PinCode = clsInputValidate::ReadString();
	}
	static void _ReadBalance(clsBankClient& Client)
	{
		cout << "\nEnter your new Balance:";
		Client.AccountBalance = clsInputValidate::ReadNumber<int>();
	}

public:
	static void showUpdateClientScreen()
	{
		if (!CheckAccsessRights(clsUser::enPermissions::pUpdateClients))
		{
			return;
		}
		_DrawScreenHeader("   Update client Screen");

		string AccountNumber = "";
		cout << "\nPleas Enter your Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\nAccount number [" << AccountNumber << "] Not Found, Please try again.";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(AccountNumber);
		_PrintClient(client);
		char Answer = 'Y';
		cout << "Are you sure you want to Update this client? (Y/N) ?=> ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			cout << "\nUpdate Client Info :\n";
			cout << "_____________________________\n";
			_SpecificUpdate(client);

			clsBankClient::enSaveResult SaveResult;
			SaveResult = client.Save();

			switch (SaveResult)
			{
			case clsBankClient::enSaveResult::svSucceeded:
				cout << "\nAccount Updated Successfully :-)\n";
				_PrintClient(client); break;

			case clsBankClient::enSaveResult::svFaildEmptyObject:
				cout << "Error Account was not saved because it’s Empaty\n"; break;
			default:
				cout << "Not among the expected cases !!\n";
			}
			
		
		}
		else
		{
			cout << "\nThe Updation procedure has been cancelled.\n";
		}
	
	}
};

