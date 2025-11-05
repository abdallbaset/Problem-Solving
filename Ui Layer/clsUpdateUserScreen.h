#pragma once
#include "clsUser.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsUpdateUserScreen:protected clsScreen
{
private:
	enum enUpdateOptions
	{
		eFirstName = 1, eLastName = 2, eEmail = 3, ePhone = 4, ePassWord = 5, ePermission = 6, eAll = 7
	};
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
				Permission += clsUser::enPermissions::pListClients;
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
	static void _ReadEmail(clsUser & User)
	{
		cout << "\nEnter your new Email:";
		User.Email = clsInputValidate::ReadString();
	}
	static void _ReadFirstName(clsUser& User)
	{
		cout << "\nEnter your new Firs Name:";
		User.FirstName = clsInputValidate::ReadString();
	}
	static void _ReadLastName(clsUser& User)
	{
		cout << "\nEnter your new Last Name:";
		User.LastName = clsInputValidate::ReadString();
	}
	static void _ReadPhone(clsUser& User)
	{
		cout << "\nEnter your new Phone:";
		User.Phone = clsInputValidate::ReadString();
	}

	static void _ReadPassWord(clsUser& User)
	{
		cout << "\nEnter your new PassWord:";
		User.PassWord = clsInputValidate::ReadString();
	}
	static void _ReadPermission(clsUser& User)
	{
		cout << "\nEnter your new Permission:";
		User.Permission = _ReadPermissionsToSet();
	}
	static void _SpecificUpdate(clsUser& User)
	{
		short NumberofOption = 0;
		cout << "Enter Your number of the option you want to modify\n[FirstName = 1 , LastName = 2 , Email = 3 , Phone = 4 , PassWord = 5 , Permission = 6 , All = 7] => ";
		NumberofOption = clsInputValidate::ReadNumberBetween<short>(1, 7);

		switch (NumberofOption)
		{
		case enUpdateOptions::eFirstName:_ReadFirstName(User); break;
		case enUpdateOptions::eLastName:_ReadLastName(User); break;
		case enUpdateOptions::eEmail:_ReadEmail(User); break;
		case enUpdateOptions::ePhone:_ReadPhone(User); break;
		case enUpdateOptions::ePassWord:_ReadPassWord(User); break;
		case enUpdateOptions::ePermission:_ReadPermission(User); break;
		case enUpdateOptions::eAll:_ReadUserInfo(User); break;
		default:
			cout << "This option Not Bounds the Option :-(\n";
		}
	}

public:
	static void ShowUpdateUserScreen()
	{
	   _DrawScreenHeader("Update User Screen");

		string UserName = "";
		cout << "\nPleas Enter your User Name : ";
		UserName = clsInputValidate::ReadString();

		while (!(clsUser::IsUserExist(UserName)))
		{
			cout << "\nUser Name [" << UserName << "] Not Found, Please try again.";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'Y';
		cout << "Are you sure you want to Update this User? (Y/N) ?=> ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			cout << "\nUpdate User Info :\n";
			cout << "_____________________________\n";
			_SpecificUpdate(User);

			clsUser::enSaveResult SaveResult;
			SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsUser::enSaveResult::svSucceeded:
				cout << "\n User Updated Successfully :-)\n";
				_PrintUser(User); break;

			case clsUser::enSaveResult::svFaildEmptyObject:
				cout << "Error User was not saved because it’s Empaty\n"; break;
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

