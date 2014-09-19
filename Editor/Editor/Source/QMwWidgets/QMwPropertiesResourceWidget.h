#ifndef QMWPROPERTIESRESOURCEWIDGET_H
#define QMWPROPERTIESRESOURCEWIDGET_H

#include <QLabel>
#include <QLineEdit>

#include "QMwResourcePropertiesWidget.h"
#include "IMwEditor.h"

class QMwPropertiesResourceWidget :
        public QWidget,
        public QMwEditorWidget
{
    Q_OBJECT
private:
    bool CheckNameValidity(const MwString &name);

public:
    QLabel *nameIcon;
    QLineEdit *nameEdit;

    QMwResourcePropertiesWidget *propertiesWidget;

    MwBaseResource *resource;

    explicit QMwPropertiesResourceWidget(QWidget *parent = 0);

    void SetEditorInterface(IMwEditor *editor);

    void SetResource(MwBaseResource *resource);

signals:

public slots:
    void on_nameEdit_textChanged(const QString &arg1);
    void on_nameEdit_editingFinished();

};

#endif // QMWPROPERTIESRESOURCEWIDGET_H
