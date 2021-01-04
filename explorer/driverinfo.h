#ifndef DRIVERINFO_H
#define DRIVERINFO_H

#include <QString>
#include <QPushButton>

class DriverInfo
{
public:
    DriverInfo(QString name, QString path, qint64 vol, qint64 volFree);
    ~DriverInfo();

    QString getName(void);
    QString getPath(void);
    qint64  getVolSum(void);
    qint64  getVolFree(void);
private:
    QString name;   //驱动器名称
    QString path;   //驱动器盘符
    qint64  volSum; //驱动器容量
    qint64  volFree;//剩余容量
};

#endif // DRIVERINFO_H
