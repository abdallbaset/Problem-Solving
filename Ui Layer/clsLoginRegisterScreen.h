#pragma once
#include "clsUser.h"
#include <iomanip>
#include  "clsScreen.h"
using namespace std;
class clsLoginRegisterScreen:protected clsScreen
{

private:
	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord loginRegister)
	{
		cout << left;
		cout << "|" << setw(36)
			<< loginRegister.DateTime;

		cout << "|" << setw(20)
			<< loginRegister.UserName;

		cout << "|" << setw(20)
			<< loginRegister.PassWord;

		cout << "|" << setw(15)
			<< loginRegister.Permission
			<< "|\n";
	}
	static void _HeaderLoginRegisterList()
	{
		cout << left
			<< "------------------------------------------------------------------------------------------------\n";
		cout << "|" << setw(36)
			<< "Date/Time ";

		cout << "|" << setw(20)
			<< "UserName ";

		cout << "|" << setw(20)
			<< "PassWord ";

		cout << "|" << setw(15)
			<< "Permission "
			<< "|\n";

		cout << "------------------------------------------------------------------------------------------------\n";
	}
public:
	static void ShowLoginRegisterList()
	{
		if (!CheckAccsessRights(clsUser::enPermissions::pLoginRegister))
		{
			return;
		}


		vector<clsUser::stLoginRegisterRecord>vLoginRegisters = clsUser::GetLoginRegister();
		if (vLoginRegisters.size() > 0)
		{
			string Title = "\tLogin Register Screen";
			string SubTitle ="\t   "+to_string(vLoginRegisters.size()) + " Records(s)";
			_DrawScreenHeader(Title, SubTitle);
			_HeaderLoginRegisterList();
			for (clsUser::stLoginRegisterRecord & Record : vLoginRegisters)
			{
				_PrintLoginRegisterRecordLine(Record);
				cout << "------------------------------------------------------------------------------------------------\n";
			}

		}
		else
		{
			cout << "\t\t\t\t\tNo Login Register Available in the System :-(\n";
		}
	}
};

