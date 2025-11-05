#pragma once
#include "clsUser.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsFindUserScreen:protected clsScreen
{
private:
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
	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\tFind User Screen");

		string UserName = "";
		cout << "\nPleas Enter Your User Name : ";
		UserName = clsInputValidate::ReadString();

		while (!(clsUser::IsUserExist(UserName)))
		{
			cout << "\nUser Name [" << UserName << "] Not Found, Please try again.";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
			_PrintUser(User);
		}
		else
		{
			cout << "\nUser Not Found :-(\n";
		}
	}
};

