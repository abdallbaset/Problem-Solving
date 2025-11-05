#pragma once
#include "clsUser.h"
#include  "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsMainScreen.h"
using namespace std;
class clsLoginScreen:protected clsScreen
{
private:
	static bool  _Login()
	{
		bool LoginFaild = false;
		string UserName = "";
		string PassWord = "";
		short LoginFaildCount = 0;
		do
		{
			if (LoginFaild)
			{
				LoginFaildCount++;
				cout << "\nInvlaid UserName/PassWord!\n";
				cout << "You have " << (3 - LoginFaildCount) << " Trials to login.\n";
				
			}
			if (LoginFaildCount == 3)
			{
				cout << "\nYou are Locked after " << LoginFaildCount << " faild Trials.\n";
				return false;
			}

			cout << "\nEnter UserName ? ";
			cin >> UserName;
			cout << "Enter PassWord ? ";
			cin >> PassWord;
			CurrentUser = clsUser::Find(UserName, PassWord);
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenu();
		return true;
	}
public:
	static bool showLoginScreen()
	{
		 system("cls");
		_DrawScreenHeader("\t\tLogin Screen");
		return _Login();
		 
	}
};

