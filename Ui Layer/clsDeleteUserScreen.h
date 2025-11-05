#pragma once
#include "clsUser.h"
#include <iomanip>
#include  "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsDeleteUserScreen:protected clsScreen
{
private:
	static void _PrintUser(clsUser  User)
	{
		cout << "\nUser Card:";
		cout << "\n-------------------------";
		cout << "\nFirstName   :" <<User.FirstName;
		cout << "\nLastName    :" <<User.LastName;
		cout << "\nFullName    :" <<User.FullName;
		cout << "\nEmail       :" <<User.Email;
		cout << "\nPhone       :" <<User.Phone;
		cout << "\nUserName    :" <<User.UserName;
		cout << "\nPassWord    :" <<User.PassWord;
		cout << "\nPermission  :" <<User.Permission;
		cout << "\n-------------------------\n";
	}
public:
	static void ShowDeleteUserScreen()

	{
		_DrawScreenHeader("\tDelete User Screen");

		string UserName = "";
		cout << "\nPleas Enter Your User Name : ";
		UserName = clsInputValidate::ReadString();

		while (!(clsUser::IsUserExist(UserName)))
		{
			cout << "\nUser Name [" << UserName << "] Not Found, Please try again.";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'Y';
		cout << "Are you sure you want to delete this User? (Y/N) ?=> ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully :-)\n";
				_PrintUser(User);
			}
			else
			{
				cout << "\nError User was not  Deleted :-(\n";

			}
		}
		else
		{
			cout << "\nThe deletion procedure has been cancelled.\n";
		}
	}
};

