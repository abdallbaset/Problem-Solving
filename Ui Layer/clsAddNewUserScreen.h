#pragma once
#include "clsUser.h"
#include <iomanip>
#include  "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsAddNewUserScreen:protected clsScreen
{
private:

	static int _ReadPermissionsToSet()
	{
		char GiveAccess = 'n';
		int Permission = 0;
		cout << "\nDo you Want to give Full Access ? Y/N ? ";
		cin >> GiveAccess;

		if (toupper(GiveAccess) == 'Y')
		{
			Permission = clsUser::enPermissions::eAll;
		}
		else
		{
			cout << "\nDo you went to give Access to:\n\n";
			cout << "Show Client List ? Y/N ? ";
			cin >> GiveAccess;
			if (toupper(GiveAccess) == 'Y')
			{
		       Permission +=clsUser::enPermissions::pListClients;
			}

			cout << "\nAdd New Client ? y/n ? ";
			cin >> GiveAccess;
			if (toupper(GiveAccess) == 'Y')
			{
				Permission += clsUser::enPermissions::pAddNewClient;
			}

			cout << "\nDelete Client ? Y/N ? ";
			cin >> GiveAccess;
			if (toupper(GiveAccess) == 'Y')
			{
				Permission += clsUser::enPermissions::pDeleteClient;
			}

			cout << "\nUpdate Client ? Y/N ? ";
			cin >> GiveAccess;
			if (toupper(GiveAccess) == 'Y')
			{
				Permission += clsUser::enPermissions::pUpdateClients;
			}

			cout << "\nFind Client ? Y/N ? ";
			cin >> GiveAccess;
			if (toupper(GiveAccess) == 'Y')
			{
				Permission += clsUser::enPermissions::pFindClient;
			}


			cout << "\nTransactions ? Y/N ? ";
			cin >> GiveAccess;
			if (toupper(GiveAccess) == 'Y')
			{
				Permission += clsUser::enPermissions::pTranactions;
			}

			cout << "\nManage User ? Y/N ? ";
			cin >> GiveAccess;
			if (toupper(GiveAccess) == 'Y')
			{
				Permission += clsUser::enPermissions::pManageUsers;
			}

			cout << "\nShow Login Register ? Y/N ? ";
			cin >> GiveAccess;
			if (toupper(GiveAccess) == 'Y')
			{
				Permission += clsUser::enPermissions::pLoginRegister;
			}
		}
			return Permission;
	}
	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter your Firs Name:";
		User.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter your Last Name:";
		User.LastName = clsInputValidate::ReadString();
		cout << "\nEnter your Email:";
		User.Email = clsInputValidate::ReadString();
		cout << "\nEnter your Phone:";
		User.Phone = clsInputValidate::ReadString();
		cout << "\nEnter your PassWord:";
		User.PassWord = clsInputValidate::ReadString();
		cout << "\nEnter your Permission:\n";
		User.Permission = _ReadPermissionsToSet();
	}
	static void _PrintUser(clsUser  User)
	{
		cout << "\nUser Card:";
		cout << "\n-------------------------";
		cout << "\nFirstName   :" << User.FirstName;
		cout << "\nLastName    :" << User.LastName;
		cout << "\nFullName    :" << User.FullName;
		cout << "\nEmail       :" << User.Email;
		cout << "\nPhone       :" << User.Phone;
		cout << "\nUserName    :" << User.UserName;
		cout << "\nPassWord    :" << User.PassWord;
		cout << "\nPermission  :" << User.Permission;
		cout << "\n-------------------------\n";
	}
public:
	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\tAdd Users Screen");

		string UserName = "";
		cout << "\nPleas Enter your User Name : ";
		UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name is Used, Please try again.";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);


		clsUser::enSaveResult SaveResult;
		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case clsUser::enSaveResult::svSucceeded:
			cout << "\nUser added Successfully :-)\n";
			_PrintUser(NewUser); break;

		case clsUser::enSaveResult::svFaildEmptyObject:
			cout << "Error UserName was not saved because it’s Empaty\n"; break;

		case clsUser::enSaveResult::svFaildAccountNumberExists:
			cout << "User Name failed to use :-(\n"; break;
		default:
			cout << "Not among the expected cases !!\n";
		}
	}
};

