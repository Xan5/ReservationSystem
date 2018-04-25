// Autor: Michał Niczyporuk

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setFocusPolicy(Qt::ClickFocus);
    club= new BowlingClub();
    model=new QStandardItemModel(10,10,this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Alloy 1"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Alloy 2"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Alloy 3"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Alloy 4"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Alloy 5"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Alloy 6"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Alloy 7"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Alloy 8"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Alloy 9"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Alloy 10"));
    model->setHeaderData(0, Qt::Vertical, QObject::tr("12:00 - 12:59"));
    model->setHeaderData(1, Qt::Vertical, QObject::tr("13:00 - 13:59"));
    model->setHeaderData(2, Qt::Vertical, QObject::tr("14:00 - 14:59"));
    model->setHeaderData(3, Qt::Vertical, QObject::tr("15:00 - 15:59"));
    model->setHeaderData(4, Qt::Vertical, QObject::tr("16:00 - 16:59"));
    model->setHeaderData(5, Qt::Vertical, QObject::tr("17:00 - 17:59"));
    model->setHeaderData(6, Qt::Vertical, QObject::tr("18:00 - 18:59"));
    model->setHeaderData(7, Qt::Vertical, QObject::tr("19:00 - 19:59"));
    model->setHeaderData(8, Qt::Vertical, QObject::tr("20:00 - 20:59"));
    model->setHeaderData(9, Qt::Vertical, QObject::tr("21:00 - 21:59"));

    setPlot(ui->customPlot,0);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTable(){
	QStandardItemModel * model1 = getModel1();
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_2->setFocusPolicy(Qt::ClickFocus);
    model1=new QStandardItemModel(100,4,this);
    model1->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Reserved Hours"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone"));
    ifstream plik;
    plik.open("passwd.txt", ios::in);
    if (plik.good() == false)
    {
        QMessageBox::information(this,"Error","Error in loading file!");
        return;
    }
    string a1, a2,a6,a5;
    int a3,a4;
    for (int j = 0; !plik.eof() ; ++j) {
        plik >> a1 >> a2 >> a3>>a4>>a5>>a6;
        QModelIndex index= model1->index(j,0,QModelIndex());
        model1->setData(index, QString::fromStdString(a1));
        index= model1->index(j,1,QModelIndex());
        model1->setData(index, QString::number(a4));
        index= model1->index(j,2,QModelIndex());
        model1->setData(index, QString::fromStdString(a5));
        index= model1->index(j,3,QModelIndex());
        model1->setData(index, QString::fromStdString(a6));
    }
    ui->tableView_2->setModel(model1);
    plik.close();
}

QStandardItemModel * MainWindow::getModel1(){return model1;}

bool MainWindow::saveUserInput(){
    string  e,  p;
    ifstream plik;
    plik.open("passwd.txt", ios::in);
    if (plik.good() == false)
    {
        QMessageBox::information(this,"Error","Error in loading file!");
        return false;
    }
    e = ui->emailInput->text().toStdString();
    p = ui->phoneInput->text().toStdString();
    if(e == "" || p == ""){
        QMessageBox::information(this,"Error","Wrong data!");
        return false;
    }
    vector<string>data;
    string line,tmp;
    int r1,r2,r3,r4,r5;
    while (getline(plik, line)) {
        if (line.find(user->getName()+ " ") != std::string::npos) {
            tmp=line;
            r1=tmp.find(' ');
            r2=tmp.find(' ',r1+1);
            r3=tmp.find(' ',r2+1);
            r4=tmp.find(' ',r3+1);
            r5=tmp.find(' ',r4+1);
            tmp.replace(r5+1, line.length()-r5-1, p);
            tmp.replace(r4+1, r5-r4-1, e);
            data.push_back(tmp);
        } else {
            data.push_back(line);
        }
    }
    plik.close();
    ofstream plik1;
    plik1.open("passwd.txt", ios::out);
    int looper;
    for (looper = 0; looper < (int) data.size(); looper++) {
        plik1 << data[looper] << endl;
    }
    plik1.close();
    return true;
}

void MainWindow::saveUser(){
    ifstream plik;
    plik.open("passwd.txt", ios::in);
    if (plik.good() == false)
    {
        QMessageBox::information(this,"Error","Error in loading file!");
        return ;
    }
    vector<string>data;
    string line,tmp;
    int r1,r2,r3,r4,r5;
    while (getline(plik, line)) {
        if (line.find(user->getName()+ " ") != std::string::npos) {
            tmp=line;
            r1=tmp.find(' ');
            r2=tmp.find(' ',r1+1);
            r3=tmp.find(' ',r2+1);
            r4=tmp.find(' ',r3+1);
            r5=tmp.find(' ',r4+1);
            tmp.replace(r3+1, r4-r3-1, to_string(user->getReserved()));
            data.push_back(tmp);
        } else {
            data.push_back(line);
        }
    }
    plik.close();
    ofstream plik1;
    plik1.open("passwd.txt", ios::out);
    int looper;
    for (looper = 0; looper < (int) data.size(); looper++) {
        plik1 << data[looper] << endl;
    }
    plik1.close();
    return ;
}

void MainWindow::on_pushButton_clicked()
{
    string  name,  pass;
    ifstream plik;
    plik.open("passwd.txt", ios::in);
    if (plik.good() == false)
    {
        QMessageBox::information(this,"Error","Error in loading file!");
        return;
    }
    name = ui->loginInput->text().toStdString();
    pass = ui->passInput->text().toStdString();
    if(name == "" || pass == ""){
        QMessageBox::information(this,"Error","Wrong login or password!");
        return;
    }
    while (!plik.eof())
    {
        string a1, a2,a6,a5;
        int a3,a4;
        plik >> a1 >> a2 >> a3>>a4>>a5>>a6;
        if (a1.compare(name) == 0) {
            if (a2.compare(pass) == 0){
                user=new User(a1,a2,a3,a4,a5,a6);
                ui->label_2->setText("Welcome " + QString::fromStdString(user->getName()));
                if(user->getLevel() != 9999) ui->pushButton_18->hide();
                ui->stackedWidget->setCurrentIndex(1);
                plik.close();
                return;
            }
            else break;
        }
    }
    QMessageBox::information(this,"Error","Wrong login or password!");
    return;
}

void MainWindow::setPlot(QCustomPlot * customPlot, int day){
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    customPlot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    QCPBars *alley = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    alley->setAntialiased(false);
    alley->setStackingGap(1);
    // set names and colors:
    alley->setName("Reserved alleys");
    alley->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    alley->setBrush(QColor(111, 9, 176));

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7<<8<<9<<10;
    labels << "12:00 - 12:59"
              << "13:00 - 13:59"
              << "14:00 - 14:59"
              << "15:00 - 15:59"
              << "16:00 - 16:59"
              << "17:00 - 17:59"
              << "18:00 - 18:59"
              << "19:00 - 19:59"
              << "20:00 - 20:59"
              << "21:00 - 21:59";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 5);
    customPlot->xAxis->setRange(0, 11);
    customPlot->xAxis->setBasePen(QPen(Qt::white));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 10);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Alley reserved");
    customPlot->yAxis->setSubTicks(false);
    customPlot->yAxis->setBasePen(QPen(Qt::white));
    customPlot->yAxis->setTickPen(QPen(Qt::white));
    customPlot->yAxis->grid()->setSubGridVisible(false);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> alleyData;
    int q;
    for(int i=0;i<10;++i){
        q=0;
        for(int j=0;j<10;++j){
            if(club->getReservations()[day][i][j].compare("+")!=0){
                q++;
            }
        }
        alleyData  << q;
    }
    alley->setData(ticks, alleyData);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::printTable(int day){
    if (user->getLevel() == 9999) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; ++j) {
                QModelIndex index= model->index(i,j,QModelIndex());
                model->setData(index, QString::fromStdString(club->getReservations()[day][i][j]));
            }
        }
    }else
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; ++j) {
            QModelIndex index= model->index(i,j,QModelIndex());
            if(club->getReservations()[day][i][j].compare("+")==0){
                model->setData(index, QString::fromStdString("+"));
            }
            else if(user->getName().compare(club->getReservations()[day][i][j])==0)
                model->setData(index, QString::fromStdString("You"));
            else
                model->setData(index, QString::fromStdString("-"));
        }
    }
    ui->tableView->setModel(model);
}

void MainWindow::checkIfDisplayedC(){
    bool first = false;
    if(club->ifReservationAvailable(day,hour,0)==0) ui->radioButton_79->hide(); else { ui->radioButton_79->show(); if(first==false) { first=true; alley=0; ui->radioButton_79->setChecked(true);}}
    if(club->ifReservationAvailable(day,hour,1)==0) ui->radioButton_80->hide(); else { ui->radioButton_80->show(); if(first==false) { first=true; alley=1; ui->radioButton_80->setChecked(true);}}
    if(club->ifReservationAvailable(day,hour,2)==0) ui->radioButton_81->hide(); else { ui->radioButton_81->show(); if(first==false) { first=true; alley=2; ui->radioButton_81->setChecked(true);}}
    if(club->ifReservationAvailable(day,hour,3)==0) ui->radioButton_82->hide(); else { ui->radioButton_82->show(); if(first==false) { first=true; alley=3; ui->radioButton_82->setChecked(true);}}
    if(club->ifReservationAvailable(day,hour,4)==0) ui->radioButton_83->hide(); else { ui->radioButton_83->show(); if(first==false) { first=true; alley=4; ui->radioButton_83->setChecked(true);}}
    if(club->ifReservationAvailable(day,hour,5)==0) ui->radioButton_84->hide(); else { ui->radioButton_84->show(); if(first==false) { first=true; alley=5; ui->radioButton_84->setChecked(true);}}
    if(club->ifReservationAvailable(day,hour,6)==0) ui->radioButton_85->hide(); else { ui->radioButton_85->show(); if(first==false) { first=true; alley=6; ui->radioButton_85->setChecked(true);}}
    if(club->ifReservationAvailable(day,hour,7)==0) ui->radioButton_86->hide(); else { ui->radioButton_86->show(); if(first==false) { first=true; alley=7; ui->radioButton_86->setChecked(true);}}
    if(club->ifReservationAvailable(day,hour,8)==0) ui->radioButton_87->hide(); else { ui->radioButton_87->show(); if(first==false) { first=true; alley=8; ui->radioButton_87->setChecked(true);}}
    if(club->ifReservationAvailable(day,hour,9)==0) ui->radioButton_88->hide(); else { ui->radioButton_88->show(); if(first==false) { first=true; alley=9; ui->radioButton_88->setChecked(true);}}
    if(first == false){
        QMessageBox::information(this,"Notice","No alleys available on this time!");
    }
}

void MainWindow::checkIfDisplayedD(){
    bool first = false;

        if(club->getReservations()[day][hour][0].compare("+")!=0)
            if(user->getName().compare(club->getReservations()[day][hour][0])!=0 && user->getLevel()!=9999)
            {
                ui->radioButton_52->hide();
            } else {
                ui->radioButton_52->show();
                if(first==false)
                { first=true; alley=0;
                    ui->radioButton_52->setChecked(true);
                }
            }
        else ui->radioButton_52->hide();
        if(club->getReservations()[day][hour][1].compare("+")!=0)
            if(user->getName().compare(club->getReservations()[day][hour][1])!=0 && user->getLevel()!=9999){
                ui->radioButton_53->hide();
            } else {
                ui->radioButton_53->show();
                if(first==false){
                    first=true;
                    alley=1;
                    ui->radioButton_53->setChecked(true);
                }
            } else ui->radioButton_53->hide();
        if(club->getReservations()[day][hour][2].compare("+")!=0)
            if(user->getName().compare(club->getReservations()[day][hour][2])!=0 && user->getLevel()!=9999){
                ui->radioButton_54->hide();
            } else {
                ui->radioButton_54->show();
                if(first==false){
                    first=true;
                    alley=2;
                    ui->radioButton_54->setChecked(true);
                }
            } else ui->radioButton_54->hide();
        if(club->getReservations()[day][hour][3].compare("+")!=0)
            if(user->getName().compare(club->getReservations()[day][hour][3])!=0 && user->getLevel()!=9999){
                ui->radioButton_55->hide();
            } else {ui->radioButton_55->show();
                if(first==false){
                    first=true;
                    alley=3;
                    ui->radioButton_55->setChecked(true);
                }
            } else ui->radioButton_55->hide();
        if(club->getReservations()[day][hour][4].compare("+")!=0)
            if(user->getName().compare(club->getReservations()[day][hour][4])!=0 && user->getLevel()!=9999){
                ui->radioButton_56->hide();
            } else {ui->radioButton_56->show();
                if(first==false){
                    first=true;
                    alley=4;
                    ui->radioButton_56->setChecked(true);
                }
            } else ui->radioButton_56->hide();
        if(club->getReservations()[day][hour][5].compare("+")!=0)
            if(user->getName().compare(club->getReservations()[day][hour][5])!=0 && user->getLevel()!=9999){
                ui->radioButton_57->hide();
            } else {ui->radioButton_57->show();
                if(first==false){
                    first=true;
                    alley=5;
                    ui->radioButton_57->setChecked(true);
                }
            } else ui->radioButton_57->hide();
        if(club->getReservations()[day][hour][6].compare("+")!=0)
            if(user->getName().compare(club->getReservations()[day][hour][6])!=0 && user->getLevel()!=9999){
                ui->radioButton_58->hide();
            } else {ui->radioButton_58->show();
                if(first==false){
                    first=true;
                    alley=6;
                    ui->radioButton_58->setChecked(true);
                }
            } else ui->radioButton_58->hide();
        if(club->getReservations()[day][hour][7].compare("+")!=0)
            if(user->getName().compare(club->getReservations()[day][hour][7])!=0 && user->getLevel()!=9999){
                ui->radioButton_59->hide();
            } else {ui->radioButton_59->show();
                if(first==false){
                    first=true;
                    alley=7;
                    ui->radioButton_59->setChecked(true);
                }
            } else ui->radioButton_59->hide();
        if(club->getReservations()[day][hour][8].compare("+")!=0)
            if(user->getName().compare(club->getReservations()[day][hour][8])!=0 && user->getLevel()!=9999){
                ui->radioButton_60->hide();} else {
                ui->radioButton_60->show();
                if(first==false){
                    first=true;
                    alley=8;
                    ui->radioButton_60->setChecked(true);
                }
            } else ui->radioButton_60->hide();
        if(club->getReservations()[day][hour][9].compare("+")!=0)
            if(user->getName().compare(club->getReservations()[day][hour][9])!=0 && user->getLevel()!=9999){
                ui->radioButton_61->hide();
            } else {ui->radioButton_61->show();
                if(first==false){
                    first=true;
                    alley=9;
                    ui->radioButton_61->setChecked(true);
                }
            } else ui->radioButton_61->hide();
    if(first == false){
        QMessageBox::information(this,"Notice","No reservations available to delete on this time!");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    printTable(0);
}

void MainWindow::on_radioButton_clicked()
{
    printTable(0);
}

void MainWindow::on_radioButton_2_clicked()
{
    printTable(1);
}

void MainWindow::on_radioButton_3_clicked()
{
    printTable(2);
}

void MainWindow::on_radioButton_4_clicked()
{
    printTable(3);
}

void MainWindow::on_radioButton_5_clicked()
{
    printTable(4);
}

void MainWindow::on_radioButton_6_clicked()
{
    printTable(5);
}

void MainWindow::on_radioButton_7_clicked()
{
    printTable(6);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    checkIfDisplayedC();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    checkIfDisplayedD();
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_radioButton_62_clicked()
{
    day=0;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_63_clicked()
{
    day=1;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_64_clicked()
{
    day=2;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_65_clicked()
{
    day=3;
    checkIfDisplayedC();

}

void MainWindow::on_radioButton_66_clicked()
{
    day=4;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_67_clicked()
{
    day=5;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_68_clicked()
{
    day=6;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_69_clicked()
{
    hour=0;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_70_clicked()
{
    hour=1;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_71_clicked()
{
    hour=2;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_72_clicked()
{
    hour=3;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_73_clicked()
{
    hour=4;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_74_clicked()
{
    hour=5;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_75_clicked()
{
    hour=6;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_76_clicked()
{
    hour=7;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_77_clicked()
{
    hour=8;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_78_clicked()
{
    hour=9;
    checkIfDisplayedC();
}

void MainWindow::on_radioButton_79_clicked()
{
    alley=0;
}

void MainWindow::on_radioButton_80_clicked()
{
    alley=1;
}

void MainWindow::on_radioButton_81_clicked()
{
    alley=2;
}

void MainWindow::on_radioButton_82_clicked()
{
    alley=3;
}

void MainWindow::on_radioButton_83_clicked()
{
    alley=4;
}

void MainWindow::on_radioButton_84_clicked()
{
    alley=5;
}

void MainWindow::on_radioButton_85_clicked()
{
    alley=6;
}

void MainWindow::on_radioButton_86_clicked()
{
    alley=7;
}

void MainWindow::on_radioButton_87_clicked()
{
    alley=8;
}

void MainWindow::on_radioButton_88_clicked()
{
    alley=9;
}

void MainWindow::on_pushButton_11_clicked()
{
    if(club->ifReservationAvailable(day,hour,alley)){
        club->createReservations(day,hour,alley,*user);
        user->incReserved();
        club->saveReservations();
        saveUser();
    }else
        QMessageBox::information(this,"Error","Wrong data");
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_9_clicked()
{
    if(club->ifReservationAvailable(day,hour,alley)==0){
        club->deleteReservations(day,hour,alley,*user);
        user->decReserved();
        club->saveReservations();
        saveUser();
    }else
        QMessageBox::information(this,"Error","Wrong data");
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_radioButton_35_clicked()
{
    day=0;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_36_clicked()
{
    day=1;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_37_clicked()
{
    day=2;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_38_clicked()
{
    day=3;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_39_clicked()
{
    day=4;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_40_clicked()
{
    day=5;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_41_clicked()
{
    day=6;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_42_clicked()
{
    hour=0;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_43_clicked()
{
    hour=1;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_44_clicked()
{
    hour=2;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_45_clicked()
{
    hour=3;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_46_clicked()
{
    hour=4;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_47_clicked()
{
    hour=5;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_48_clicked()
{
    hour=6;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_49_clicked()
{
    hour=7;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_50_clicked()
{
    hour=8;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_51_clicked()
{
    hour=9;
    checkIfDisplayedD();
}

void MainWindow::on_radioButton_52_clicked()
{
    alley=0;
}

void MainWindow::on_radioButton_53_clicked()
{
    alley=1;
}

void MainWindow::on_radioButton_54_clicked()
{
    alley=2;
}

void MainWindow::on_radioButton_55_clicked()
{
    alley=3;
}

void MainWindow::on_radioButton_56_clicked()
{
    alley=4;
}

void MainWindow::on_radioButton_57_clicked()
{
    alley=5;
}

void MainWindow::on_radioButton_58_clicked()
{
    alley=6;
}

void MainWindow::on_radioButton_59_clicked()
{
    alley=7;
}

void MainWindow::on_radioButton_60_clicked()
{
    alley=8;
}

void MainWindow::on_radioButton_61_clicked()
{
    alley=9;
}

void MainWindow::on_pushButton_7_clicked()
{
        QMessageBox::information(this,"Help",
                                 "<h3>Bowling Club</h3>"
                                 "<br>Show all - show all reservations"
                                 "<br>Create - create new reservation"
                                 "<br>Delete - delete your reservation"
                                 "<br>My Profile - see and edit your profile"
                                 "<br>Stats - see statistics about reservations"
                                 "<br>"
                                 "<br>Author: Michał Niczyporuk");
}

void MainWindow::on_radioButton_22_clicked()
{
    for( int g=0; g< ui->customPlot->graphCount() ; g++ )
    {
        ui->customPlot->graph(g)->data().data()->clear();
    }
    ui->customPlot->clearPlottables();
    setPlot(ui->customPlot,0);
    ui->customPlot->replot();
}

void MainWindow::on_radioButton_23_clicked()
{
    for( int g=0; g<ui->customPlot->graphCount(); g++ )
    {
        ui->customPlot->graph(g)->data().data()->clear();
    }
    ui->customPlot->clearPlottables();
    setPlot(ui->customPlot,1);
    ui->customPlot->replot();
}

void MainWindow::on_radioButton_24_clicked()
{
    for( int g=0; g<ui->customPlot->graphCount(); g++ )
    {
        ui->customPlot->graph(g)->data().data()->clear();
    }
    ui->customPlot->clearPlottables();
    setPlot(ui->customPlot,2);
    ui->customPlot->replot();
}

void MainWindow::on_radioButton_25_clicked()
{
    for( int g=0; g<ui->customPlot->graphCount(); g++ )
    {
        ui->customPlot->graph(g)->data().data()->clear();
    }
    ui->customPlot->clearPlottables();

    setPlot(ui->customPlot,3);
    ui->customPlot->replot();
}

void MainWindow::on_radioButton_26_clicked()
{
    for( int g=0; g<ui->customPlot->graphCount(); g++ )
    {
        ui->customPlot->graph(g)->data().data()->clear();
    }
    ui->customPlot->clearPlottables();

    setPlot(ui->customPlot,4);
    ui->customPlot->replot();
}

void MainWindow::on_radioButton_27_clicked()
{
    for( int g=0; g<ui->customPlot->graphCount(); g++ )
    {
        ui->customPlot->graph(g)->data().data()->clear();
    }
    ui->customPlot->clearPlottables();

    setPlot(ui->customPlot,5);
    ui->customPlot->replot();
}

void MainWindow::on_radioButton_28_clicked()
{
    for( int g=0; g<ui->customPlot->graphCount(); g++ )
    {
        ui->customPlot->graph(g)->data().data()->clear();
    }
    ui->customPlot->clearPlottables();

    setPlot(ui->customPlot,6);
    ui->customPlot->replot();
}

void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->emailInput->hide();
    ui->phoneInput->hide();
    ui->pushButton_14->hide();
    ui->checkBox->setChecked(0);
    ui->lemail->setText(QString::fromStdString(user->getEmail()));
    ui->lphone->setText(QString::fromStdString(user->getPhone()));
    ui->lreserved->setText(QString::number(user->getReserved()));
}

void MainWindow::on_pushButton_14_clicked()
{
    if(saveUserInput())
        ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked){
        ui->emailInput->show();
        ui->phoneInput->show();
        ui->pushButton_14->show();
    }else{
        ui->emailInput->hide();
        ui->phoneInput->hide();
        ui->pushButton_14->hide();
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_18_clicked()
{
    setTable();
    ui->stackedWidget->setCurrentIndex(7);
}
