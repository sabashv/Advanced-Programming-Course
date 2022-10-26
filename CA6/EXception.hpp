#ifndef Exception_H
#define Exception_H "Exception_H"

#include <string>
#include <exception>



class Invalid_User_Error : public std::exception {
public:
	Invalid_User_Error(std::string error_message);
	const char* what() const throw();
private:
	std::string error;
};

class Player_Cant_Perform_Role_Error : public std::exception
{
public:
	Player_Cant_Perform_Role_Error(std::string error_message);
	const char* what() const throw();
private:
	std::string error;
};

class Invalid_Command_Error: public std::exception
{
public:
	Invalid_Command_Error(std::string error_message);
	const char* what() const throw();
private:
	std::string error;
};

class Swap_Error : public std::exception
{
public:
	Swap_Error(std::string error_message);
	const char* what() const throw();
private:
	std::string error;
};

class No_Game_Created_Error : public std::exception
{
public:
	const char* what() const throw();
};

class Player_Has_No_Role_Error : public std::exception
{
public:
	const char* what() const throw();
};

#endif
