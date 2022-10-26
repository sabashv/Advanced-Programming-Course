#include "EXception.hpp"
using namespace std;



Invalid_User_Error::Invalid_User_Error(string error_message){error =error_message;}
const char* Invalid_User_Error::what() const throw()
    {
        return error.c_str();
    }



Player_Cant_Perform_Role_Error::Player_Cant_Perform_Role_Error(string error_message){error =error_message;}

const char* Player_Cant_Perform_Role_Error::what() const throw()
    {
        return error.c_str();
    }



Invalid_Command_Error::Invalid_Command_Error(string error_message){error =error_message;}
const char* Invalid_Command_Error::what() const throw(){
    return error.c_str();
}

Swap_Error::Swap_Error(string error_message)
{error =error_message;}

const char* Swap_Error::what() const throw()
{
    return error.c_str();
}



const char* No_Game_Created_Error::what() const throw()
{
    return "No Game created\n";
}


const char* Player_Has_No_Role_Error::what() const throw()
{
	return "One or more players do not have a role\n";
}


