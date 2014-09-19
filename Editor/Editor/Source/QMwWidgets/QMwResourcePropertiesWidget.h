#ifndef QMWRESOURCEPROPERTIESWIDGET_H
#define QMWRESOURCEPROPERTIESWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "../MeshworkEngine.h"

#include "ParameterWidgets/QMwParameterWidget.h"

class QMwResourcePropertiesWidget :
        public QWidget,
        public QMwEditorWidget
{
    Q_OBJECT

public:
    static QWidget *CreateMwParameterWidget(MwParameter *parameter, IMwEditor *editor = 0);

    QGridLayout *layout;

    MwBaseResource *resource;

    QMwResourcePropertiesWidget(QWidget *parent = 0);

    void SetResource(MwBaseResource *resource);
};

#endif // QMWRESOURCEPROPERTIESWIDGET_H
