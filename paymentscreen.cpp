#include "paymentscreen.h"
#include "ui_userpage.h"
#include "ui_paymentscreen.h"
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QButtonGroup>
#include <QPropertyAnimation>


PaymentScreen::PaymentScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PaymentScreen)
{
    ui->setupUi(this);

    //sets the images on each label
    QPixmap MasterCard(":/resources/img/MasterCardLogo.png");
    int w = ui->MasterCardLogo->width();
    int h = ui->MasterCardLogo->height();
    ui->MasterCardLogo->setPixmap(MasterCard.scaled(w,h,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));

    QPixmap Visa(":/resources/img/VisaLogo.png");
    ui->VisaLogo->setPixmap(Visa.scaled(w,h,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));


    QButtonGroup *PaymentMethod = new QButtonGroup(this);
    PaymentMethod->setExclusive(true);

    PaymentMethod->addButton(ui->VisaButton);
    PaymentMethod->addButton(ui->MasterCardButton);
    PaymentMethod->addButton(ui->PayAirportButton);

    ui->VisaButton->setCheckable(true);
    ui->MasterCardButton->setCheckable(true);
    ui->PayAirportButton->setCheckable(true);

    connect(ui->CheckOutButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->CancelButton, &QPushButton::clicked, this, &QDialog::reject);

    setAttribute(Qt::WA_StyledBackground, true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);



    this->setStyleSheet(
        "#PaymentScreen { background-color: #0f172a; border: 1px solid #1e293b; border-radius: 15px;}"

        "QLabel{"
        "   background-color: transparent;"
        "   color: white"
        ""
        "}"



        "QStackedWidget {"
        "   background-color: #020617;"
        "   border: 1px solid transparent;"
        "   border-radius: 15px;"
        "}"


        "QPushButton{ background-color: transparent; "
        "   color: #94a3b8; "
        "   border: 1px solid #334155; "
        "   padding: 12px; "
        "   border-radius: 8px; "
        "   font-weight: bold; "
        "   margin-top: 10px; }"

        "QPushButton:hover { "
        "   background-color:#1e293b;  "
        "   color: white; }"

        "QPushButton:checked {"
        "   background-color: #0078D4;"
        "   color: white;"
        "   border: 1px solid #005A9E;"
        "   font-weight: bold;"
        "}"



        "#CancelButton { "
        "   background-color: transparent; "
        "   color: #94a3b8; "
        "   border: 1px solid #334155; "
        "   padding: 12px; "
        "   border-radius: 8px; "
        "   font-weight: bold; "
        "   margin-top: 10px; "
        "} "
        "#CancelButton:hover { "
        "   background-color: #EF4444; "
        "   color: white; "
        "   border: 2px solid #960D0D; "
        "} "


        "#CheckOutButton { "
        "   background-color: transparent; "
        "   color: #94a3b8; "
        "   border: 1px solid #334155; "
        "   padding: 12px; "
        "   border-radius: 8px; "
        "   font-weight: bold; "
        "   margin-top: 10px; "
        "} "
        "#CheckOutButton:hover { "
        "   background-color: #44EF9A; "
        "   color: white; "
        "   border: 2px solid #11C069; "
        "} "



        "QLineEdit {"
        "    background-color: #0A101E;"
        "    border: 1px solid #1A2234;"
        "    border-radius: 8px;"
        "    padding: 8px 12px;"
        "    color: #FFFFFF;"
        "    selection-background-color: #0078D4;"
        "}"
        "QLineEdit:hover {"
        "    border: 1px solid #303B52;"
        "}"

        "QLineEdit:focus {"
        "    border: 1px solid #0078D4;"
        "    background-color: #0D1425;"
        "}"


        "QComboBox {"
        "   border: 1px solid #333333;"
        "   border-radius: 4px;"
        "   padding: 5px 5px;"
        "   background-color: #0f172a;"
        "   color: #E0E0E0;"
        "   font-size: 12px;"
        "   min-width: 6em;"
        "}"

        "QComboBox:focus {"
        "    border: 1px solid #0078D4;"
        "    background-color: #0D1425;"
        "}"

        "QComboBox:hover {border: 1px solid #1e293b;background-color: #1e293b;}"

        "QComboBox:on { border-bottom-left-radius: 0px;border-bottom-right-radius: 0px;}"

        "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 15px;border-left: 1px solid #333333;}"

        "QComboBox QAbstractItemView {background-color: #0f172a;border: 1px solid #333333;selection-background-color: #0078D4;selection-color: white;outline: none;}"

        "QComboBox QAbstractItemView::item { padding: 8px;color: #E0E0E0;})"



    );

}



PaymentScreen::~PaymentScreen()
{
    delete ui;
}



//Animates the page on start
void PaymentScreen::showAnimated() {
    this->setWindowOpacity(0.0);
    this->show();

    //Creates animation based on the window opacity
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(180);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void PaymentScreen::on_PayAirportButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}


void PaymentScreen::on_MasterCardButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void PaymentScreen::on_VisaButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

//Checkout Message box (also saves data in the booking history)
void PaymentScreen::on_CheckOutButton_clicked()
{
    UserPageMain *mainWin = qobject_cast<UserPageMain*>(this->parent());
    if (mainWin) {
        mainWin->savechanges();
        mainWin->BacktoHome();
    }

    QMessageBox *msg = new QMessageBox();
    msg->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    msg->setText("Check out complete!!!");
    msg->setStyleSheet("QMessageBox {"
                       "    background-color: #050914;"
                       "    border: 1px solid #1A2234;"
                       "}"
                       "QMessageBox QLabel {"
                       "    color: #FFFFFF;"
                       "    font-size: 13px;"
                       "    min-width: 200px;"
                       "    qproperty-alignment: 'AlignCenter';"
                       "    width: 100%;"
                       "}"

                       "QDialogButtonBox {"
                       "    qproperty-centerButtons: true;"
                       "}"

                       "QPushButton{ background-color: transparent; "
                       "   color: #94a3b8; "
                       "   border: 1px solid #334155; "
                       "   padding: 7px; "
                       "   border-radius: 8px; "
                       "   font-weight: bold; "
                       "   margin-top: 7px; "
                       "   width: 100%;"
                       "}"

                       "QPushButton:hover { "
                       "   background-color:#1e293b;  "
                       "   color: white; }"
                       );
    msg->show();
    QTimer::singleShot(2000, msg, &QMessageBox::close);



}


void UserPageMain::savechanges() {
    int row = ui->BookedTableWidget->rowCount();


    if(TicketID == ui->BookedTableWidget->currentRow()){
        users[m_uID].tickets[TicketID].adults = ui->AdultComboBox->currentIndex() + 1;
        users[m_uID].tickets[TicketID].children = ui->ChildrenComboBox->currentIndex();
        users[m_uID].tickets[TicketID].flight_ID = IDFlight;
        for (int r = 0; r < ui->SeatSelection->rowCount(); ++r) {
            for (int c = 0; c < ui->SeatSelection->columnCount(); ++c) {

                QPushButton *btn = qobject_cast<QPushButton*>(ui->SeatSelection->cellWidget(r, c));

                // 3. Check if the seat is valid and selected
                if (btn && btn->isChecked()) {
                    Seat selectedSeat;

                    // USE THE LOOP ITERATORS 'r' AND 'c' HERE
                    selectedSeat.row = r;
                    selectedSeat.column = c;
                    selectedSeat.booked = true;

                    // Determine tier based on the actual row index 'r'
                    if (r < 2) {
                        selectedSeat.tier = 1;
                    }
                    else if (r < 6) {
                        selectedSeat.tier = 2;
                    }
                    else {
                        selectedSeat.tier = 3;
                    }

                    // Add the unique seat to your vector
                    users[m_uID].tickets[TicketID].seats.push_back(selectedSeat);
                }
            }
        }
        QString DepartureAir = ui->DepartureAirport->currentText();
        QString ArrivalAir = ui->ArrivalAirport->currentText();
        ui->BookedTableWidget->setItem(TicketID, 1, new QTableWidgetItem(DepartureAir));
        ui->BookedTableWidget->setItem(TicketID, 2, new QTableWidgetItem(ArrivalAir));

        QString departureText[3];
        for (int i = 0; i < 3; ++i) {
            auto formattedTime = std::format("{:%F %R}", flights[i].departure_date);
            departureText[i] = QString::fromStdString(formattedTime);
        }


        if(ui->FirstAvFlight->isChecked()) {
            ui->BookedTableWidget->setItem(TicketID, 3, new QTableWidgetItem(departureText[0]));
        };
        if(ui->SecondAvFlight->isChecked()) {
            ui->BookedTableWidget->setItem(TicketID, 3, new QTableWidgetItem(departureText[1]));
        };
        if(ui->ThirdAvFlight->isChecked()) {
            ui->BookedTableWidget->setItem(TicketID, 3, new QTableWidgetItem(departureText[2]));
        };

        int maxSelection = 1;

        maxSelection += ui->AdultComboBox->currentIndex();
        maxSelection += ui->ChildrenComboBox->currentIndex();
        ui->BookedTableWidget->setItem(TicketID, 4, new QTableWidgetItem(QString::number(maxSelection)));




    }

    else{

        ui->BookedTableWidget->insertRow(row);


        Ticket newTicket;
        newTicket.adults = ui->AdultComboBox->currentIndex() + 1;
        newTicket.children = ui->ChildrenComboBox->currentIndex();
        newTicket.flight_ID = IDFlight;

        // 2. Loop through the grid exactly once
        for (int r = 0; r < ui->SeatSelection->rowCount(); ++r) {
            for (int c = 0; c < ui->SeatSelection->columnCount(); ++c) {

                QPushButton *btn = qobject_cast<QPushButton*>(ui->SeatSelection->cellWidget(r, c));

                // 3. Check if the seat is valid and selected
                if (btn && btn->isChecked()) {
                    Seat selectedSeat;

                    // USE THE LOOP ITERATORS 'r' AND 'c' HERE
                    selectedSeat.row = r;
                    selectedSeat.column = c;
                    selectedSeat.booked = true;

                    // Determine tier based on the actual row index 'r'
                    if (r < 2) {
                        selectedSeat.tier = 1;
                    }
                    else if (r < 6) {
                        selectedSeat.tier = 2;
                    }
                    else {
                        selectedSeat.tier = 3;
                    }

                    // Add the unique seat to your vector
                    newTicket.seats.push_back(selectedSeat);
                }
            }
        }
        users[m_uID].tickets.push_back(newTicket);

        ui->BookedTableWidget->setItem(row,0,new QTableWidgetItem(QString::number(row + 1)));

        QString DepartureAir = ui->DepartureAirport->currentText();
        QString ArrivalAir = ui->ArrivalAirport->currentText();
        ui->BookedTableWidget->setItem(row, 1, new QTableWidgetItem(DepartureAir));
        ui->BookedTableWidget->setItem(row, 2, new QTableWidgetItem(ArrivalAir));

        QString departureText[3];
        for (int i = 0; i < 3; ++i) {
            auto formattedTime = std::format("{:%F %R}", flights[i].departure_date);
            departureText[i] = QString::fromStdString(formattedTime);
        }


        if(ui->FirstAvFlight->isChecked()) {
            ui->BookedTableWidget->setItem(row, 3, new QTableWidgetItem(departureText[0]));
        };
        if(ui->SecondAvFlight->isChecked()) {
            ui->BookedTableWidget->setItem(row, 3, new QTableWidgetItem(departureText[1]));
        };
        if(ui->ThirdAvFlight->isChecked()) {
            ui->BookedTableWidget->setItem(row, 3, new QTableWidgetItem(departureText[2]));
        };

        int maxSelection = 1;

        maxSelection += ui->AdultComboBox->currentIndex();
        maxSelection += ui->ChildrenComboBox->currentIndex();
        ui->BookedTableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(maxSelection)));

        QComboBox *comboBox = new QComboBox(ui->BookedTableWidget);

        // 2. Add normal dropdown text options
        QStringList options = {"Edit Booking", "Delete Booking"};
        comboBox->addItems(options);

        comboBox->setPlaceholderText("Options");

        comboBox->setCurrentIndex(-1);

        QObject::connect(comboBox, &QComboBox::activated, [this, comboBox](int index) {

            int currentRealRow = ui->BookedTableWidget->indexAt(comboBox->pos()).row();

            switch (index) {
            case 0:
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(ui->BookedTableWidget, "Edit Booking...", "Are you sure you want to edit this booking?",
                                              QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    EditBooking();
                    comboBox->setCurrentIndex(-1);
                }
                else {
                    comboBox->setCurrentIndex(-1);

                }
                break;
            case 1:
                QMessageBox::StandardButton reply2;
                reply = QMessageBox::question(ui->BookedTableWidget, "Delete Booking...", "Are you sure you want to delete this booking?",
                                              QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    DeleteBooking();
                    comboBox->setCurrentIndex(-1);
                }
                else {
                    comboBox->setCurrentIndex(-1);

                }
                break;
            default:
                break;
            }
        });

        // 4. Inject the combo box directly into the specified grid coordinates
        ui->BookedTableWidget->setCellWidget(row, 5, comboBox);


    }






}oid UserPageMain::BacktoHome() {
    ui->stackedWidget->setCurrentIndex(0);
}
