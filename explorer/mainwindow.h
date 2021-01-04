#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStorageInfo>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QDebug>
#include <QDir>
#include <QTableWidget>
#include <QDateTime>
#include <QHeaderView>
#include <QFileIconProvider>
#include "driverinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateDisksList(void);
    void initNewPage(QTabWidget *tab);
    void initSideBar(QGroupBox *box);
private slots:
    void addTabBtn_clicked();
    void sideBtn_clicked();

private:
    Ui::MainWindow *ui;

    QList<QStorageInfo> storageList;
    QList<DriverInfo> driverList;
    QList<QTabWidget> tabs;

    QList<QPushButton*>sideBtn;

    QPushButton *addTabBtn;
};
#endif // MAINWINDOW_H
