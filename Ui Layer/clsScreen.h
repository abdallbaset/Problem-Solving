#pragma once
#include <iostream>
#include "clsUtil.h"
#include "Global.h"

using namespace std;

class clsScreen
{
protected:
	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout<< "\t\t\t\t----------------------------------------------------";
		clsUtil::Endl(1);
		cout <<clsUtil::Tabs(3,"       ") << Title;
		clsUtil::Endl(1);
		if (SubTitle != "")
		{
			cout << clsUtil::Tabs(3, "   ") << SubTitle;
			clsUtil::Endl(2);
		}
		cout << "\t\t\t\t----------------------------------------------------\n\n";
		cout << "\t\t\t\tUser:" << CurrentUser.UserName<<endl;
		cout << "\t\t\t\tDate:" << clsDate::DateToString(clsDate::GetSystemDate()) <<endl<<endl;
	}

	static bool CheckAccsessRights(clsUser::enPermissions Permissions)
	{
		if (!CurrentUser.CheckAccessPermission(Permissions))
		{
			cout << "\t\t\t\t\t------------------------------------------\n";
			cout << clsUtil::Tabs(3, "    ") << "Access Denied! Contact your Admin\n";
			cout << "\t\t\t\t\t------------------------------------------\n";
			return false;
		}
		else
			return true;
	}
};

