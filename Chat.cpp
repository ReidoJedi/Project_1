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
	for (auto& user : users_)
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
		std::cout << "Логин: ";
		std::cin >> login;
		std::cout << "Пароль: ";
		std::cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;

			std::cout << "Ошибка входа..." << std::endl;
			std::cout << "Нажмите (0) чтобы выйти или другую кнопку чтобы повторить вход: ";
			std::cin >> operation;

			if (operation == '0')
				break;

		}

	} while (!currentUser);
}

void Chat::signUp()
{
	std::string login, password, name;

	std::cout << "Логин: ";
	std::cin >> login;
	std::cout << "Пароль: ";
	std::cin >> password;
	std::cout << "Имя пользователя: ";
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
	currentUser_ = std::make_shared<User>(user);
}

void Chat::showChat() const
{
	std::string from;
	std::string to;

	std::cout << "- - - Чат - - -" << std::endl;

	for (auto& mess : messages_)
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
		std::cout << "\033[33m" << "(1)Вход" << std::endl;
		std::cout << "(2)Регистрация" << std::endl;
		std::cout << "(0)Выход" << std::endl;
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
			std::cout << "1 или 2 ..." << std::endl;
			break;
					
		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu()
{
	char operation;

	std::cout << "Привет, " << currentUser_->getUserName() << std::endl;

	while (currentUser_)
	{
		std::cout << "(1)Показать чат | (2)Отправить сообщение | (3)Показать кто в чате | (4)Выйти ";

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
			std::cout << "сделайте выбор.." << std::endl;
			break;
		}


	}
}

void Chat::showAllUsersName() const
{
	std::cout << "- - - В чате - - -" << std::endl;
	for (auto& user : users_)
	{
		std::cout << user.getUserName();

		if (currentUser_->getUserLogin() == user.getUserLogin())
			std::cout << "(me)";
		std::cout << std::endl;
	}
	std::cout << "- - - - - - - - -" << std::endl;
}

void Chat::addMessage()
{
	std::string to, text;

	std::cout << "Кому (пользователю или всем): ";
	std::sin >> to;
	std::cout << "Сообщение: ";
	std::sin.ignore();
	getline(std::cin, text);

	if (!(to == "all" || getUserByName(to)))
	{
		std::cout << "Такой пользователь не найден" << to << std::endl;
		return;
	}

	if (to == "all")
		messages_.push_back(Message{ currentUser_->getUserLogin(), "all", text });
	else
		messages_.push_back(Message{ currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text});

}