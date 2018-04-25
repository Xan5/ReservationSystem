#ifndef USER_H
#define USER_H
#include <string>

using namespace std;

class User
{
protected:
    string login;
    string pass;
    int level;
    int reserved;
    string email;
    string phone;

public:
    User(string l, string p, int lev, int r, string e, string ph);
    ~User();
    string getName();
    int getLevel();
    int getReserved();
    string getEmail();
    string getPhone();
    void setEmail(string e);
    void setPhone(string p);
    void incReserved();
    void decReserved();
};

#endif // USER_H
