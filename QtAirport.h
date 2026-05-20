#ifndef QTAIRPORT_H
#define QTAIRPORT_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <string>
#include "structs.h"
#include "data_base.h"
#include "functions.h"


class QtAirport : public QMainWindow {
    Q_OBJECT

public:
    explicit QtAirport(int airportID, QWidget* parent = nullptr);
    void refresh();   // call this after any backend mutation to re sync
    ~QtAirport() {
        SAVE_DATA();
        this->close();
    }

private:
    int airport_ID;


    QWidget* centralWidget;
    QHBoxLayout* mainLayout;
    QFrame* sidebar;
    QVBoxLayout* sidebarLayout;
    QStackedWidget* contentStack;


    //  Buttons
    QPushButton* btnDashboard;
    QPushButton* btnAirplanes;
    QPushButton* btnSchedule;
    QPushButton* btnRequests;
    QPushButton* btnLogout;

    //  dashboard cards
    QLabel* lblTotalLanes;
    QLabel* lblAvailablePlanes;
    QLabel* lblScheduledFlights;
    QLabel* lblPendingRequests;

    // Pages
    QWidget* DashboardPage();
    QWidget* AirplanesPage();
    QWidget* SchedulePage();
    QWidget* FlightRequestsPage();
    
    //tables

    QTableWidget* airplanesTable;
    QTableWidget* scheduleTable;
    QTableWidget* requestsTable;
    QTableWidget* sentRequestsTable;

    //  functions
    QWidget* createStatCard(const QString& title, const QString& value,
                const QString& color, QLabel*& outLabel);
    
    void applyStyles();
    void populateAirplanesTable();
    void populateScheduleTable();
    void populateRequestsTable();
    


 private slots:
        void openBuyAirplane();
        void openScheduleDialog();
        void handleAcceptRequest();
        void handleDenyRequest();
        
};

#endif
