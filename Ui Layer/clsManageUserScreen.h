#pragma once
#include <iomanip>
#include  "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;
class clsManageUserScreen:protected clsScreen
{
private:
	enum enManageUsersMenuOptions { eListUsers = 1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4, FindUser = 5, MainMenu = 6 };

	static short _ReadManageUserMenuOptions()
	{
		short NumberOfOption = 0;
		cout << "Chose what do you want to do? [1 to 6]?";
		NumberOfOption = clsInputValidate::ReadNumberBetween<short>(1, 6);
		return NumberOfOption;
	}
	static void _GoBackManageUsersMenu()
	{
		cout << "\nPress any key to go back to Manage Users Menu...";
		system("pause > nul");
		ShowMangeUsersMenue();
	}
	static void _ShowListUsersScreen()
	{
		clsListUserScreen::ShowUsersList();
	}
	static void _ShowAddNewUsersScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}
	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}
	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PreformManageUsersMenu(enManageUsersMenuOptions UserOption)
	{
		switch (UserOption)
		{
		case enManageUsersMenuOptions::eListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBackManageUsersMenu();
		}; break;
		case enManageUsersMenuOptions::eAddUser:
		{
			system("cls");
			_ShowAddNewUsersScreen();
			_GoBackManageUsersMenu();
		}; break;
		case enManageUsersMenuOptions::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackManageUsersMenu();

		}; break;
		case enManageUsersMenuOptions::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackManageUsersMenu();

		}; break;
		case enManageUsersMenuOptions::FindUser:
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBackManageUsersMenu();

		}; break;
		case enManageUsersMenuOptions::MainMenu:
		{
		}; break;
		default:
			cout << "This option Not Bounds the Option Menu :-(\n";
		}
	}
public :
	static void ShowMangeUsersMenue()
	{
		if (!CheckAccsessRights(clsUser::enPermissions::pManageUsers))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("   Mange Users Screen");
		cout << "-----------------------------------------------------\n";
		cout << "\t\tManage Users Menue Screen\t    |\n";
		cout << "-----------------------------------------------------\n";
		cout << "\t[1] List Users.\t\t\t\t    |\n";
		cout << "\t[2] Add New User.\t\t\t    |\n";
		cout << "\t[3] Delete User.\t\t\t    |\n";
		cout << "\t[4] Update User.\t\t\t    |\n";
		cout << "\t[5] Find User.\t\t\t\t    |\n";
		cout << "\t[6] Main Menu.\t\t\t\t    |\n";
		cout << "-----------------------------------------------------\n";
		_PreformManageUsersMenu((enManageUsersMenuOptions)_ReadManageUserMenuOptions());
	}
};

