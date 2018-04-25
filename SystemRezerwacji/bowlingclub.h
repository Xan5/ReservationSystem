#ifndef BOWLINGCLUB_H
#define BOWLINGCLUB_H
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "user.h"

using namespace std;

class BowlingClub
{
protected:
    string ***reservations;	//rezerwacje na nastepujacy  tydzien, przy czym keregielnia jest czynna od 12 do 22 i ma 10 torow;
public:
    BowlingClub();
    void loadReservations();
    void saveReservations();
    bool createReservations(int day, int hour, int alley, User user);
    bool deleteReservations(int day, int hour, int alley, User user);
    string *** getReservations();
    bool ifReservationAvailable(int day, int hour, int alley);
    ~BowlingClub();
};

#endif // BOWLINGCLUB_H
