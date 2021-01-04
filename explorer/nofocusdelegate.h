#ifndef NOFOCUSDELEGATE_H
#define NOFOCUSDELEGATE_H

#include <QPainter>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>

class NoFocusDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit NoFocusDelegate(QObject *parent = nullptr);
    void paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const;
signals:

public slots:
};

#endif // NOFOCUSDELEGATE_H
