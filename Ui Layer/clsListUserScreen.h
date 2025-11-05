#pragma once
#include "clsUser.h"
#include <iomanip>
#include  "clsScreen.h"
using namespace std;
class clsListUserScreen:protected clsScreen
{
private:
	static void _PrintUserRecordLine(clsUser User)
	{
		cout << left;
		cout << "|" << setw(16)
			<< User.UserName;

		cout << "|" << setw(10)
			<< User.PassWord;

		cout << "|" << setw(36)
			<< User.FullName;

		cout << "|" << setw(20)
			<< User.Email;

		cout << "|" << setw(10)
			<< User.Phone;

		cout << "|" << setw(12)
			<< User.Permission
			<< "|\n";
	}
	static void _HeaderUserList()
	{
		cout << left
			<< "---------------------------------------------------------------------------------------------------------------\n";
		cout << "|" << setw(16)
			<< "User Name ";

		cout << "|" << setw(10)
			<< "PassWord ";

		cout << "|" << setw(36)
			<< "Full Name ";

		cout << "|" << setw(20)
			<< "Email ";

		cout << "|" << setw(10)
			<< "Phone ";

		cout << "|" << setw(12)
			<< "Permission "
			<< "|\n";

		cout << "---------------------------------------------------------------------------------------------------------------\n";
	}
public:
	static void ShowUsersList()
	{
		vector<clsUser>vUsers = clsUser::GetUsersList();
		if (vUsers.size() > 0)
		{
			string Title = "\tUser List Screen";
			string SubTitle = "\tUser list " + to_string(vUsers.size()) + " User(s)";
			_DrawScreenHeader(Title, SubTitle);
			_HeaderUserList();
			for (clsUser& User : vUsers)
			{
				_PrintUserRecordLine(User);
				cout << "---------------------------------------------------------------------------------------------------------------\n";
			}

		}
		else
		{
			cout << "\t\t\t\t\tNo Users Available in the System :-(\n";
		}
	}
};

