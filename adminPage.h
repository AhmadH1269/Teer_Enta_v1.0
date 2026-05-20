#ifndef ADMINPAGE_H
#define ADMINPAGE_H
#include<QLabel>
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <string>
#include <QMessageBox>
#include <QHeaderView>
#include<QDialog>
#include<QFrame>
#include<QLineEdit>
#include <QList>
#include "structs.h"
#include<QScrollArea>
#include <QComboBox>
#include "functions.h"
#include "data_base.h"



class AdminPage : public QWidget {
    Q_OBJECT 

public:
    
    explicit AdminPage(int adminID, QWidget* parent = nullptr);

    ~AdminPage() {
        SAVE_DATA();
        this->close();
    }

    void setAdminInfo(QString name);
    void loadUsersTable();
    void loadAdminsTable();
    void loadPlanesTable();
    void loadAirportsCards();
signals:
    void logoutRequested(); 
private slots:
   
    void showAddUserDialog();
    void addPlaneToSystem();
    void showAddAdminDialog();
    void addAirportToSystem();
    void updateAirportCombo();


private:
    int admin_ID; 

    // Declaraation
    QLabel* logoLabel;
    QTableWidget* usersTable;
    QTableWidget* adminsTable;
    QWidget* addPlaneWidget;
    QStackedWidget* stackedWidget;
    QWidget* adminsWidget;
    QPushButton* viewAdminsBtn;
    QWidget* addAirportWidget;
    QPushButton* addAirportBtn;
    QWidget* airportsContainer;
    QVBoxLayout* airportsCardsLayout;
    QScrollArea* airportsScrollArea;
    QComboBox* airportCombo;
    QLineEdit* airportEmailEdit;
    QLineEdit* airportPassEdit;
    QLineEdit* airportConfirmPassEdit;
    QLineEdit* airportCapacityEdit;


    QPushButton* addPlaneBtn;
    QPushButton* userManagmentBtn;
    QPushButton* addUserBtn; 
    QPushButton* addAdminBtn;
    QPushButton* logoutBtn;


    QLabel* tableTitleLabel;
    QLabel* profilePicLabel;
    QLabel* adminNameLabel;

    // QWidget* addPlaneWidget;
    QLineEdit* manufacturerEdit;
    QLineEdit* modelEdit;
    QLineEdit* planeSeatsEdit;
    QLineEdit* planeSpeedEdit;
    QLineEdit* planeFuelEdit;
    QTableWidget* planesTable;

    // Methods
    void setupTables();
    void setupLayout();
    void setupAddPlaneForm();
    void setupConnections();
    void setupEnterNavigation(QList<QLineEdit*> fields); 
    void setupAddAirportForm();
};

#endif
