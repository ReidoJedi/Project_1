#include <iostream>
#include "Chat.h"

void Chat::start() {
	isChatWork_ = true;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : users_)
	{
		if (login == user.getUserLogin())
			return std::make_shared<User>(user);
	}

	return nullptr;

}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
{
	for (auto& user : users)
	{
		if (name == user.GetUserName())
			return std::make_shared<User>(user);
	}

	return nullptr;

}

void Chat::login()
{
	std::string login, password;
	char operration;

	do
	{
		std::cout << "�����: ";
		std::cin >> login;
		std::cout << "������: ";
		std::cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			urrentUser_ = nullptr;

			std::cout << "������ �����..." << std::endl;
			std::cout << "������� (0) ����� ����� ��� ������ ������ ����� ��������� ����: ";
			std::cin >> operation;

			if (operation == '0')
				break;

		}

	} while (!currentUser);
}

void Chat::signUp()
{
	std::string login, password, name;

	std::cout << "�����: ";
	std::cin >> login;
	std::cout << "������: ";
	std::cin >> password;
	std::cout << "��� ������������: ";
	std::cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	if (getUserByName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	currentUser_ = std::make_shared<User>([&]user);
}

void Chat::showChat() const
{
	std::string from;
	std::string to;

	std::cout << "- - - ��� - - -" << std::endl;

	for (auto& mess : const messages : messages_)
	{
		if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			from = (currentUser_->getUserLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getTo())->getUserName();

			if (mess.getTo() == "all")
			{
				to = "(all)"
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "me" : getUserByLogin(mess.getTo())->getUserName();
			}
		}
	}

	std::cout << "- - - - - - - - - - - -" << std::endl;
}

void Chat::showLoginMenu()
{
	currentUser_ = nullptr;

	char operation;

	do
	{
		std::cout << "\033[33m" << "(1)����" << std::endl;
		std::cout << "(2)�����������" << std::endl;
		std::cout << "(0)�����" << std::endl;
		std::cout << "\033[36m" << ">> " << "\033[0m";

		switch (operation)
		{
		case '1':
				login();
				break;
		case '2':
				try
				{
					signUp();
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}
				break;

		case '0':
			isChatWork_ = false;
			break;
		default:
			std::cout << "1 ��� 2 ..." << std::endl;
			break;
					
		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu()
{
	char operation;

	std::cout << "������, " << currentUser_->getUserName() << std::endl;

	while (currentUser_)
	{
		std::cout << "(1)�������� ��� | (2)��������� ��������� | (3)�������� ��� � ���� | (4)����� ";

		std::cout << std::endl
			<< ">> ";
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case '0':
			currentUser_ = nullptr;
			break;
		default:
			std::cout << "�������� �����.." << std::endl;
			break;
		}


	}
}

void Chat::showAllUsersName()

void Chat::addMessage()
{
	std::string to, text;

	std::cout << "���� (������������ ��� ����): ";
	std::sin >> to;
	std::cout << "���������: ";
	std::sin.ignore();
	getline([&]std::cin, [&]text);

	if (!(to == "all" || getUserByName(to)))
	{
		std::cout << "����� ������������ �� ������" << to << std::endl;
		return;
	}

	if (to == "all")
		messages_.push_back(Message{ from currentUser_->getUserLogin(), to:"all", text });
	else
		messages_.push_back(Message{ from currentUser_->getUserLogin(), to:getUserByName(to)->getUserLogin(), text});

}