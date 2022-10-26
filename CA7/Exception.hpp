
#ifndef EXception_H
#define  EXception_H "EXception_H"

#include <exception>
#include <string>


class Bad_Request_Error : public std::exception
{
public:
	const char* what() const throw();
};

class Permission_Denied_Error : public std::exception
{
public:
	const char* what() const throw();
};

class Empty_List_Error : public std::exception
{
public:
	const char* what() const throw();
};


class Not_Found_Error : public std::exception
{
public:
	const char* what() const throw();
};

#endif