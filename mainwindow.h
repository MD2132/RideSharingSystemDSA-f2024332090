#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QPlainTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include <QFrame>
#include <QMessageBox>

#include "DispatchEngine.h"
#include "Citydj.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleRequestRide();
    void updateDashboard();

private:
    // -------- CORE DATA --------
    City* city = nullptr;
    DispatchEngine* engine = nullptr;
    int riderIdCounter = 500;

    // -------- INPUTS --------
    QLineEdit *pickupInput = nullptr;
    QLineEdit *dropoffInput = nullptr;

    // -------- TABLES --------
    QTableWidget *driverTable = nullptr;
    QTableWidget *tripTable = nullptr;

    // -------- LOG --------
    QPlainTextEdit *systemLog = nullptr;

    // -------- STATS --------
    QLabel *statDrivers = nullptr;
    QLabel *statTrips = nullptr;

    // -------- UI SETUP --------
    void initializeData();
    void setupUI();
    void applyStyles();

    // -------- HELPERS --------
    void logMessage(const QString &msg);
    QFrame* createCard(const QString &title, QLayout *contentLayout);

    // -------- TABLE UPDATERS --------
    void updateDriverTable();
    void updateTripTable();
};

#endif // MAINWINDOW_H
