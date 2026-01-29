#include "MainWindow.h"
#include <QHeaderView>

// ================= CONSTRUCTOR / DESTRUCTOR =================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initializeData();
    setupUI();
    applyStyles();
    updateDashboard();
}

MainWindow::~MainWindow()
{
    delete engine;
    delete city;
}

// ================= DATA INITIALIZATION =================

void MainWindow::initializeData()
{
    city = new City();

    for (int i = 0; i <= 5; i++)
        city->addLocation(i);

    city->addRoad(0, 1, 5);
    city->addRoad(0, 2, 10);
    city->addRoad(1, 3, 3);
    city->addRoad(2, 3, 7);
    city->addRoad(3, 4, 4);
    city->addRoad(4, 5, 6);

    city->setZone(0, 1);
    city->setZone(1, 1);
    city->setZone(2, 2);
    city->setZone(3, 2);
    city->setZone(4, 3);
    city->setZone(5, 3);

    engine = new DispatchEngine(city);

    engine->registerDriver(new Driver(101, 0, 1));
    engine->registerDriver(new Driver(102, 2, 2));
    engine->registerDriver(new Driver(103, 4, 3));
}

// ================= UI SETUP =================

void MainWindow::setupUI()
{
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // ---------- TOP BAR ----------
    auto *topBar = new QHBoxLayout();

    QLabel *logo = new QLabel("RIDE<font color='#10b981'>SHARE</font> PRO");
    logo->setStyleSheet("font-size: 24px; font-weight: bold;");

    statDrivers = new QLabel("Drivers Online: 0");
    statTrips = new QLabel("Active Trips: 0");

    topBar->addWidget(logo);
    topBar->addStretch();
    topBar->addWidget(statDrivers);
    topBar->addWidget(statTrips);

    mainLayout->addLayout(topBar);

    // ---------- CONTENT ----------
    auto *contentLayout = new QHBoxLayout();

    // ---- LEFT CARD (INPUT) ----
    auto *sideLayout = new QVBoxLayout();

    pickupInput = new QLineEdit();
    pickupInput->setPlaceholderText("Pickup Node (0–5)");

    dropoffInput = new QLineEdit();
    dropoffInput->setPlaceholderText("Dropoff Node (0–5)");

    auto *btnRequest = new QPushButton("REQUEST RIDE");
    connect(btnRequest, &QPushButton::clicked,
            this, &MainWindow::handleRequestRide);

    sideLayout->addWidget(new QLabel("PICKUP"));
    sideLayout->addWidget(pickupInput);
    sideLayout->addWidget(new QLabel("DROPOFF"));
    sideLayout->addWidget(dropoffInput);
    sideLayout->addSpacing(10);
    sideLayout->addWidget(btnRequest);
    sideLayout->addStretch();

    contentLayout->addWidget(createCard("NEW TRIP", sideLayout), 1);

    // ---- CENTER (TABLES) ----
    auto *tablesLayout = new QVBoxLayout();

    driverTable = new QTableWidget(0, 4);
    driverTable->setHorizontalHeaderLabels({"ID", "LOCATION", "ZONE", "STATUS"});
    driverTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    driverTable->verticalHeader()->setVisible(false);
    driverTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tripTable = new QTableWidget(0, 4);
    tripTable->setHorizontalHeaderLabels({"TRIP ID", "RIDER", "FARE", "STATE"});
    tripTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tripTable->verticalHeader()->setVisible(false);
    tripTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tablesLayout->addWidget(new QLabel("LIVE DRIVERS"));
    tablesLayout->addWidget(driverTable);
    tablesLayout->addWidget(new QLabel("ACTIVE TRIPS"));
    tablesLayout->addWidget(tripTable);

    contentLayout->addLayout(tablesLayout, 2);

    // ---- RIGHT CARD (LOG) ----
    auto *logLayout = new QVBoxLayout();
    systemLog = new QPlainTextEdit();
    systemLog->setReadOnly(true);
    logLayout->addWidget(systemLog);

    contentLayout->addWidget(createCard("SYSTEM EVENTS", logLayout), 1);

    mainLayout->addLayout(contentLayout);
    setCentralWidget(centralWidget);
    resize(1200, 800);
}

// ================= STYLES =================

void MainWindow::applyStyles()
{
    setStyleSheet(R"(
        QMainWindow { background-color: #0f172a; }
        QLabel { color: #f8fafc; font-family: Segoe UI; }
        QFrame#card {
            background-color: #1e293b;
            border-radius: 12px;
            padding: 10px;
        }
        QLineEdit {
            background-color: #334155;
            border-radius: 6px;
            padding: 8px;
            color: white;
        }
        QPushButton {
            background-color: #10b981;
            border-radius: 6px;
            padding: 12px;
            font-weight: bold;
        }
        QPushButton:hover { background-color: #059669; }
        QTableWidget {
            background-color: #1e293b;
            color: #e2e8f0;
            gridline-color: #334155;
        }
        QHeaderView::section {
            background-color: #0f172a;
            color: #94a3b8;
            font-weight: bold;
        }
        QPlainTextEdit {
            background-color: #020617;
            color: #10b981;
            font-family: Consolas;
        }
    )");
}

// ================= BUTTON HANDLER =================

void MainWindow::handleRequestRide()
{
    bool ok1, ok2;
    int pickup = pickupInput->text().toInt(&ok1);
    int dropoff = dropoffInput->text().toInt(&ok2);

    if (!ok1 || !ok2 || pickup < 0 || pickup > 5 || dropoff < 0 || dropoff > 5) {
        QMessageBox::warning(this, "Invalid Input",
                             "Pickup and Dropoff must be between 0 and 5");
        return;
    }

    Rider rider(riderIdCounter++, pickup, dropoff);
    Trip *trip = engine->requestTrip(rider);

    if (trip) {
        logMessage(QString("✔ TRIP %1 | DRIVER %2 | FARE %3")
                       .arg(trip->getId())
                       .arg(trip->getDriverId())
                       .arg(trip->getFare()));
    } else {
        logMessage("✖ DISPATCH FAILED");
    }

    pickupInput->clear();
    dropoffInput->clear();
    pickupInput->setFocus();

    updateDashboard();
}

// ================= DASHBOARD =================

void MainWindow::updateDashboard()
{
    statDrivers->setText(
        QString("Drivers Online: %1").arg(engine->getTotalDriverCount()));

    statTrips->setText(QString("Active Trips: %1")
        .arg(engine->getTripCount()));


    updateDriverTable();
    updateTripTable();
}

// ================= TABLE UPDATERS =================

void MainWindow::updateDriverTable()
{
    driverTable->setRowCount(0);

    for (int id = 101; id <= 103; id++) {
        Driver *d = engine->findDriverById(id);
        if (!d) continue;

        int row = driverTable->rowCount();
        driverTable->insertRow(row);

        driverTable->setItem(row, 0, new QTableWidgetItem(QString::number(d->getId())));
        driverTable->setItem(row, 1, new QTableWidgetItem(QString::number(d->getCurrentLocation())));
        driverTable->setItem(row, 2, new QTableWidgetItem(QString::number(d->getZoneId())));
        driverTable->setItem(row, 3, new QTableWidgetItem(
                                         Driver::statusToString(d->getStatus())));
    }
}

void MainWindow::updateTripTable()
{
    tripTable->setRowCount(0);

    Trip** trips = engine->getTrips();
    int count = engine->getTripCount();

    for (int i = 0; i < count; i++) {
        Trip* t = trips[i];
        if (!t) continue;

        int row = tripTable->rowCount();
        tripTable->insertRow(row);

        tripTable->setItem(row, 0,
                           new QTableWidgetItem(QString::number(t->getId())));

        tripTable->setItem(row, 1,
                           new QTableWidgetItem(QString::number(t->getRiderId())));

        tripTable->setItem(row, 2,
                           new QTableWidgetItem(QString::number(t->getFare())));

        auto* stateItem =
            new QTableWidgetItem(Trip::stateToString(t->getState()));
        stateItem->setForeground(QBrush(QColor("#10b981")));

        tripTable->setItem(row, 3, stateItem);
    }
}


// ================= HELPERS =================

void MainWindow::logMessage(const QString &msg)
{
    systemLog->appendPlainText(
        QString("[%1] %2")
            .arg(QTime::currentTime().toString("hh:mm:ss"))
            .arg(msg));
}

QFrame* MainWindow::createCard(const QString &title, QLayout *contentLayout)
{
    QFrame *card = new QFrame();
    card->setObjectName("card");

    auto *layout = new QVBoxLayout(card);

    QLabel *label = new QLabel(title);
    label->setStyleSheet("font-size: 11px; color: #94a3b8; font-weight: bold;");

    layout->addWidget(label);
    layout->addLayout(contentLayout);

    return card;
}
