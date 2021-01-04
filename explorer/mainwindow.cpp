#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nofocusdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateDisksList(); //获取磁盘信息列表
    initNewPage(ui->tabWidget);
    initSideBar(ui->drivers_box);

    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->setMovable(true);

    addTabBtn = new QPushButton("+");
    addTabBtn->setObjectName("addTabBtn");
    ui->tabWidget->setCornerWidget(addTabBtn); //添加"+"按钮
    connect(addTabBtn, SIGNAL(clicked()), this, SLOT(addTabBtn_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDisksList(void)
{
    storageList = QStorageInfo::mountedVolumes();

    driverList.clear();
    for (int i = 0; i < storageList.count(); i++) {
        DriverInfo driver(storageList[i].name(), storageList[i].rootPath(), storageList[i].bytesTotal(), storageList[i].bytesFree());
        driverList.append(driver);

        sideBtn.append(new QPushButton(driverList[i].getName()));
    }
}

void MainWindow::initSideBar(QGroupBox *box)
{
    QVBoxLayout *sideLay = new QVBoxLayout();

    sideBtn.prepend(new QPushButton("主页"));

    for (int i = 0; i < sideBtn.count(); i++) {
        sideBtn[i]->setFixedSize(150, 40);
        sideLay->addWidget(sideBtn[i]);

        sideBtn[i]->setObjectName(QString::number(i));
        connect(sideBtn[i], SIGNAL(clicked()), this, SLOT(sideBtn_clicked()));
    }
    sideLay->addStretch();
    sideLay->setSpacing(10);
    box->setLayout(sideLay);
}

void MainWindow::initNewPage(QTabWidget *tab)
{
    QVBoxLayout *homeLay = new QVBoxLayout();
    QTableWidget *view = new QTableWidget();
    QStringList header;

    header << "名称" << "修改日期" << "类型" << "大小";
    view->setObjectName("filesView");
    view->setColumnCount(4);
    view->setHorizontalHeaderLabels(header);
    view->setShowGrid(false); //隐藏网格
    view->verticalHeader()->setVisible(false); //隐藏列表头
    view->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    view->setSelectionBehavior(QAbstractItemView::SelectRows); //设置按行选中
    view->setEditTriggers(QAbstractItemView::SelectedClicked); //单击已选时，触发编辑
    view->horizontalHeader()->setHighlightSections(false);  //表头塌陷
    view->setItemDelegate(new NoFocusDelegate()); //去除选择时的虚线外框

    homeLay->addWidget(view);

    tab->currentWidget()->setLayout(homeLay); //设置布局（添加按钮）
    tab->setTabText(tab->currentIndex(), "新标签页"); //更新标签显示
}

void MainWindow::addTabBtn_clicked()
{
    QWidget *newTab = new QWidget();

    ui->tabWidget->addTab(newTab, "新标签页");
    ui->tabWidget->setCurrentWidget(newTab);
    initNewPage(ui->tabWidget);
}

void MainWindow::sideBtn_clicked()
{
    QString fileType;
    QString rootPath;
    QString fileSize;
    QFileIconProvider fileIconSys;
    QDir rootDir;
    QFileInfoList fileList;
    QFileInfo fileInfo;
    QString btn = QObject::sender()->objectName();
    QTableWidget *view = ui->tabWidget->currentWidget()->findChild<QTableWidget *>("filesView");

    switch (btn.toInt()) {
    case 0:
        qDebug() << sideBtn[0]->text();
        break;
    default:
        rootPath = driverList[btn.toInt() - 1].getPath();
        break;
    }

    rootDir.cd(rootPath);
    if(rootDir.exists())
    {
        fileList = rootDir.entryInfoList();
        for (int i  =0; i < fileList.count(); i++) {
            fileInfo = fileList.at(i);

            QTableWidgetItem *timeItem = new QTableWidgetItem(fileInfo.metadataChangeTime().toString("yyyy/MM/dd hh:mm:ss"), QTableWidgetItem::Type);
            if (fileInfo.isDir()) {
                fileType = "文件夹";
                fileSize = "";
            }
            else if(fileInfo.isFile())
            {
                fileType = fileInfo.suffix() + "文件";
                fileSize = QString::number(fileInfo.size() / 1024) + " KB";
            }

            QTableWidgetItem *nameItem = new QTableWidgetItem(fileIconSys.icon(fileInfo), fileInfo.fileName(), QTableWidgetItem::Type);
            QTableWidgetItem *typeItem = new QTableWidgetItem(fileType, QTableWidgetItem::Type);
            QTableWidgetItem *sizeItem = new QTableWidgetItem(fileSize, QTableWidgetItem::Type);

            /* 设置该条目不可编辑 */
            timeItem->setFlags(timeItem->flags() & (~Qt::ItemIsEditable));
            typeItem->setFlags(typeItem->flags() & (~Qt::ItemIsEditable));
            sizeItem->setFlags(sizeItem->flags() & (~Qt::ItemIsEditable));

            view->setRowCount(i + 1);
            view->setItem(i, 0, nameItem);
            view->setItem(i, 1, timeItem);
            view->setItem(i, 2, typeItem);
            view->setItem(i, 3, sizeItem);
        }
    }
}
