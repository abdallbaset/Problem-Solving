#pragma once
#include "clsBankClient.h"
#include <iomanip>
#include  "clsScreen.h"
using namespace std;
class clsClientListScreen:protected clsScreen
{
private:
	static void _PrintClientRecordLine(clsBankClient client)
	{
		cout << left;
		cout << "|" << setw(16)
			<< client.AccountNumber;

		cout << "|" << setw(10)
			<< client.PinCode;

		cout << "|" << setw(36)
			<< client.FullName;

		cout << "|" << setw(20)
			<< client.Email;

		cout << "|" << setw(10)
			<< client.Phone;

		cout << "|" << setw(10)
			<< client.AccountBalance
			<< "|\n";
	}
	static void _HeaderClientList()
	{
		cout << left
			<< "-------------------------------------------------------------------------------------------------------------\n";
		cout << "|" << setw(16)
			<< " Account Number ";

		cout << "|" << setw(10)
			<< " Pin Code ";

		cout << "|" << setw(36)
			<< " Client Name ";

		cout << "|" << setw(20)
			<< " Email ";

		cout << "|" << setw(10)
			<< "Phone ";

		cout << "|" << setw(10)
			<< "Balance "
			<< "|\n";

		cout << "-------------------------------------------------------------------------------------------------------------\n";
	}
public:
	static void ShowClientsList()
	{
		if (!CheckAccsessRights(clsUser::enPermissions::pListClients))
		{
			return;
		}

		vector<clsBankClient>vClients = clsBankClient::GetClientsList();
		if (vClients.size() > 0)
		{
			string Title = "\tClients List Screen";
			string SubTitle = "\tClient list " + to_string(vClients.size()) + " clients(s)";
			_DrawScreenHeader(Title, SubTitle);
			_HeaderClientList();
			for (clsBankClient& client : vClients)
			{
				_PrintClientRecordLine(client);
				cout << "-------------------------------------------------------------------------------------------------------------\n";
			}

		}
		else
		{
			cout << "\t\t\t\t\tNo Clients Available in the System :-(\n";
		}
	}
};

