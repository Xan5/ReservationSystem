#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QString>
#include "user.h"
#include "bowlingclub.h"
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void printTable(int day);
    void checkIfDisplayedC();
    void checkIfDisplayedD();
    void setPlot(QCustomPlot * customPlot, int day);
    bool saveUserInput();
    void saveUser();
    void setTable();
    QStandardItemModel * getModel1();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_10_clicked();

    void on_radioButton_62_clicked();

    void on_radioButton_63_clicked();

    void on_radioButton_64_clicked();

    void on_radioButton_65_clicked();

    void on_radioButton_66_clicked();

    void on_radioButton_67_clicked();

    void on_radioButton_68_clicked();

    void on_radioButton_69_clicked();

    void on_radioButton_70_clicked();

    void on_radioButton_71_clicked();

    void on_radioButton_72_clicked();

    void on_radioButton_73_clicked();

    void on_radioButton_74_clicked();

    void on_radioButton_75_clicked();

    void on_radioButton_76_clicked();

    void on_radioButton_77_clicked();

    void on_radioButton_78_clicked();

    void on_radioButton_79_clicked();

    void on_radioButton_80_clicked();

    void on_radioButton_81_clicked();

    void on_radioButton_82_clicked();

    void on_radioButton_83_clicked();

    void on_radioButton_84_clicked();

    void on_radioButton_85_clicked();

    void on_radioButton_86_clicked();

    void on_radioButton_87_clicked();

    void on_radioButton_88_clicked();

    void on_pushButton_11_clicked();

    void on_radioButton_35_clicked();

    void on_pushButton_9_clicked();

    void on_radioButton_36_clicked();

    void on_radioButton_37_clicked();

    void on_radioButton_38_clicked();

    void on_radioButton_39_clicked();

    void on_radioButton_40_clicked();

    void on_radioButton_41_clicked();

    void on_radioButton_42_clicked();

    void on_radioButton_43_clicked();

    void on_radioButton_44_clicked();

    void on_radioButton_45_clicked();

    void on_radioButton_46_clicked();

    void on_radioButton_47_clicked();

    void on_radioButton_48_clicked();

    void on_radioButton_49_clicked();

    void on_radioButton_50_clicked();

    void on_radioButton_51_clicked();

    void on_radioButton_52_clicked();

    void on_radioButton_53_clicked();

    void on_radioButton_54_clicked();

    void on_radioButton_55_clicked();

    void on_radioButton_56_clicked();

    void on_radioButton_57_clicked();

    void on_radioButton_58_clicked();

    void on_radioButton_59_clicked();

    void on_radioButton_60_clicked();

    void on_radioButton_61_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_17_clicked();

    void on_radioButton_22_clicked();

    void on_radioButton_23_clicked();

    void on_radioButton_24_clicked();

    void on_radioButton_25_clicked();

    void on_radioButton_26_clicked();

    void on_radioButton_27_clicked();

    void on_radioButton_28_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_8_clicked();
    
    void on_checkBox_toggled(bool checked);

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_18_clicked();

private:
    int day=0, hour=0, alley=0;
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QStandardItemModel *model1;
    User *user;
    BowlingClub *club;
};

#endif // MAINWINDOW_H
