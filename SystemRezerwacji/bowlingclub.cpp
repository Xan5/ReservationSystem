#include "bowlingclub.h"

BowlingClub::BowlingClub()
{
    reservations = new string**[7];
            for (int i = 0; i < 7; i++) {
                reservations[i] = new string*[10];
                for (int j = 0; j < 10; ++j) {
                    reservations[i][j] = new string[10];
                    for (int k = 0; k < 10; ++k) {
                        reservations[i][j][k] = "+";
                    }
                }
            }
            loadReservations();
}
void BowlingClub::loadReservations(){
    ifstream file;
            file.open("reservations.txt", ios::in);
            if (file.good() == false)
            {
                system("PAUSE");
                return;
            }
            while (!file.eof())
            {
                for (int i = 0; i < 7; i++) {
                    for (int j = 0; j < 10; ++j) {
                        for (int k = 0; k < 10; ++k) {
                            file >> reservations[i][j][k];
                        }
                    }
                }
            }
            file.close();
}
void BowlingClub::saveReservations(){
    ofstream file;
    file.open("reservations.txt", ios::out);

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                file << reservations[i][j][k] << " ";
            }
        }
        file << endl;
    }
    file.close();
}
bool BowlingClub::createReservations(int day, int hour, int alley, User user){
    if (day >= 0 && day < 7 && hour >= 0 && hour < 10 && alley >= 0 && alley < 10) {
                reservations[day][hour][alley] = user.getName();
                return 1;
            }
            return 0;
}
bool BowlingClub::deleteReservations(int day, int hour, int alley, User user){
    if (day >= 0 && day < 7 && hour >= 0 && hour < 10 && alley >= 0 && alley < 10) {
                if (user.getLevel() == 9999 || user.getName() == reservations[day][hour][alley]) {
                    reservations[day][hour][alley] = "+";
                    return 1;
                }
            }
            return 0;
}
string ***BowlingClub::getReservations(){
    return reservations;
}
bool BowlingClub::ifReservationAvailable(int day, int hour, int alley){
    if (day >= 0 && day < 7 && hour >= 0 && hour < 10 && alley >= 0 && alley < 10) {
                if (reservations[day][hour][alley] == "+")
                    return 1;
            }
            return 0;
}
BowlingClub::~BowlingClub(){
    for (int i = 0; i < 7; ++i) {
                delete reservations[i];
            }
            delete reservations;
}
