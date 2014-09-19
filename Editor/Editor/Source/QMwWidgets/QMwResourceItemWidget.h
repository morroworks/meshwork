#ifndef QMWRESOURCEITEMWIDGET_H
#define QMWRESOURCEITEMWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include "QMwResourceItemButtonWidget.h"

class QMwResourceItemWidget :
        public QWidget,
        public QMwEditorWidget
{
    Q_OBJECT
public:
    MwBaseResource *resource;

    QVBoxLayout *layout;
    QMwResourceItemButtonWidget *button;
    QLabel *nameLabel;

    explicit QMwResourceItemWidget(QWidget *parent = 0);

    void SetEditorInterface(IMwEditor *editor);

    void SetResource(MwBaseResource *resource);

signals:

public slots:

};

#endif // QMWRESOURCEITEMWIDGET_H
