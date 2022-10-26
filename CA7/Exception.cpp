#include "Exception.hpp"

using namespace std;


const char* Bad_Request_Error::what() const throw()
{
    return "Bad request\n";
}


const char* Permission_Denied_Error::what() const throw()
{
    return "Permission Denied\n";
}


const char* Empty_List_Error::what() const throw()
{
    return "Empty\n";
}



const char* Not_Found_Error::what() const throw()
{
    return "Not Found\n";
}