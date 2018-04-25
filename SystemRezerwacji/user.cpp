#include "user.h"

User::User(string l, string p, int lev, int r, string e, string ph) : login(l), pass(p), level(lev), reserved(r), email(e), phone(ph) {}
User::~User() {}
int User::getLevel(){ return level; }
int User::getReserved(){ return reserved; }
string User::getName() { return login; }
string User::getEmail() { return email; }
string User::getPhone() { return phone; }
void User::incReserved(){reserved++;}
void User::decReserved(){reserved--;}
void User::setEmail(string e) { email=e; }
void User::setPhone(string p) { phone=p; }
