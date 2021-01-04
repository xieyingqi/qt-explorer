#include "driverinfo.h"

DriverInfo::DriverInfo(QString name, QString path, qint64 vol, qint64 volFree)
{
    this->name = name;
    this->path = path;
    this->volSum = vol;
    this->volFree = volFree;

    if(name == nullptr)
    {
        this->name = "本地磁盘";
    }
    this->name = this->name + '(' + this->path.split('/')[0] + ')';
}

DriverInfo::~DriverInfo()
{

}

QString DriverInfo::getName(void)
{
    return this->name;
}

QString DriverInfo::getPath(void)
{
    return this->path;
}

qint64 DriverInfo::getVolSum(void)
{
    return this->volSum;
}

qint64 DriverInfo::getVolFree(void)
{
    return this->volFree;
}

