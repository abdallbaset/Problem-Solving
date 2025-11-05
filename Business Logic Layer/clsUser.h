#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
using namespace std;
class clsUser: public clsPerson
{
private:
	enum enMainMenuOptions { ShowClientList = 1, Add_NewClient = 2, DeleteClient = 3, Update_ClientInfo = 4, FindClient = 5, Transactions = 6, ManageUser = 7, Logout = 8 };

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _PassWord;
	int _Permission;
	bool _MarkForDelete = false;


	string _PrepareLogInRecord(string Separator="#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
		LoginRecord += _UserName + Separator;
		LoginRecord += clsUtil::EncryptText(_PassWord) + Separator;
		LoginRecord += to_string(_Permission);
		return LoginRecord;
	}
public:
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64 ,pLoginRegister = 128
	};


	struct stLoginRegisterRecord
	{
		string UserName="";
		string PassWord="";
		string DateTime="";
		int  Permission=0;
	};

	clsUser(enMode Mode ,string FirstName, string LastName, string Email, string Phone, string UserName, string PassWord, short Permission) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		 _Mode=Mode;
		_UserName = UserName;
		_PassWord = PassWord;
		_Permission = Permission;
	}
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	void SetMarkForDelete(bool Mark)
	{
		_MarkForDelete = Mark;
	}
	bool GetMarkForDelete()
	{
		return _MarkForDelete;
	}
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassWord(string PassWord)
	{
		_PassWord = PassWord;
	}
	string GetPassWord()
	{
		return _PassWord;
	}
	__declspec(property(get = GetPassWord, put = SetPassWord)) string PassWord;

	void SetPermission(short Permission)
	{
		_Permission = Permission;
	}
	short GetPermission()
	{
		return _Permission;
	}
	__declspec(property(get = GetPermission, put = SetPermission)) short Permission;


	static clsUser ConvertLinetoUserObject(string LineData, string Sepertor = "#//#")
	{
		vector<string> vWord = clsString::Split(LineData, Sepertor);
		return clsUser(enMode::UpdateMode, vWord[0], vWord[1], vWord[2], vWord[3], vWord[4],clsUtil::DecryptText( vWord[5]), stod(vWord[6]));

	}
	static stLoginRegisterRecord ConvertLinetoLoginRegisterRcord(string LineData, string Sepertor = "#//#")
	{
		vector<string> vLoginRegisterDataLine = clsString::Split(LineData, Sepertor);
		stLoginRegisterRecord LoginRegisterRecord;
		LoginRegisterRecord.DateTime = vLoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = vLoginRegisterDataLine[1];
		LoginRegisterRecord.PassWord = clsUtil::DecryptText(vLoginRegisterDataLine[2]);
		LoginRegisterRecord.Permission = stoi(vLoginRegisterDataLine[3]);
		return LoginRegisterRecord;
	}


	static clsUser _GetEmptyUserObject()
	{
		return  clsUser(enMode::EmptyMode, " ", " ", " ", " ", " ", " ", 0);
	}

	static vector<clsUser> _LoadUserDataFromFaile()
	{
		vector<clsUser>vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		string line = "";
		if (MyFile.is_open())
		{
			while (getline(MyFile, line))
			{
				clsUser UserInfo = ConvertLinetoUserObject(line);
				vUsers.push_back(UserInfo);
			}
			MyFile.close();
		}
		return vUsers;
	}

	static vector<stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector<stLoginRegisterRecord>vLoginRegister;
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);
		string line = "";
		if (MyFile.is_open())
		{
			while (getline(MyFile, line))
			{
				stLoginRegisterRecord LoginRegisterRecord = ConvertLinetoLoginRegisterRcord(line);
				vLoginRegister.push_back(LoginRegisterRecord);
			}
			MyFile.close();
		}
		return vLoginRegister;
	}



	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsUser User = ConvertLinetoUserObject(line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();

		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName,string PassWord)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsUser User = ConvertLinetoUserObject(line);
				if (User.UserName == UserName && User.PassWord == PassWord)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();

		}
		return _GetEmptyUserObject();
	}


	void RegisterLogIn()
	{
		string LineData = _PrepareLogInRecord();
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::app | ios::out);
		if (MyFile.is_open())
		{
			MyFile << LineData << endl;
		}
		MyFile.close();
    }


	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}


	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}
	static vector<clsUser> GetUsersList()
	{
		return _LoadUserDataFromFaile();
	}
	static vector<stLoginRegisterRecord> GetLoginRegister()
	{
		return GetLoginRegisterList();
	}

	static string _ConvertUserObjectToline(clsUser UserInfo, string Separator = "#//#")
	{
		string Line = "";
		Line += UserInfo.FirstName + Separator;
		Line += UserInfo.LastName + Separator;
		Line += UserInfo.Email + Separator;
		Line += UserInfo.Phone + Separator;
		Line += UserInfo.UserName + Separator;
		Line += clsUtil::EncryptText(UserInfo.PassWord) + Separator;
		Line += to_string(UserInfo.Permission) + Separator;

		return Line;
	} 

	static void SaveUsersDataToFile(vector<clsUser> vUsers)
	{
		string LineData = "";
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsUser& User : vUsers)
			{
				if (User._MarkForDelete == false)
				{
					LineData = _ConvertUserObjectToline(User);
					MyFile << LineData << endl;
				}
			}
			MyFile.close();
		}
	}
	bool Delete()
	{
		vector<clsUser> vUsers;
		vUsers = _LoadUserDataFromFaile();
		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName)
			{
				User._MarkForDelete = true;
				break;
			}
		}

		SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}
	void _Update()
	{
		vector<clsUser> vUsers;
		vUsers = _LoadUserDataFromFaile();
		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName)
			{
				User = *this;
				break;
			}
		}

		SaveUsersDataToFile(vUsers);
	}
	void AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::app | ios::out);
		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}
	void AddNew()
	{
		AddDataLineToFile(_ConvertUserObjectToline(*this));
	}

	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:	return enSaveResult::svFaildEmptyObject;

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResult::svSucceeded;
		}
		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExist(UserName))
				return enSaveResult::svFaildAccountNumberExists;

			AddNew();
			_Mode = enMode::UpdateMode;
			return enSaveResult::svSucceeded;
		}


		}
	}

	 bool CheckAccessPermission(enPermissions Permission)
	{
		 if (this->Permission == enPermissions::eAll)
			 return true;

		 if ((Permission & this->Permission) == Permission)
			    return true;
			 else
				 return false;
	}
};

