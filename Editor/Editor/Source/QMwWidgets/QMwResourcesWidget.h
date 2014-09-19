#ifndef QMWRESOURCESWIDGET_H
#define QMWRESOURCESWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "QMwEditorWidget.h"

class QMwResourcesWidget :
        public QWidget,
        public QMwEditorWidget

{
    Q_OBJECT
private:

public:
    MwResourceType filterType;
    MwString filterString;
    MwList<MwBaseResource*> *items;

    QGridLayout *layout;

    explicit QMwResourcesWidget(QWidget *parent = 0);

    void RefreshItems();

    void SetItemSource(MwList<MwBaseResource *> &items);

    void SetFilterType(MwResourceType filterType);
    void SetFilterString(const MwString &filterString);

signals:

public slots:

};

#endif // QMWRESOURCESWIDGET_H
