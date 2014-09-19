#ifndef QMWPARAMETERWIDGETLINKBUTTON_H
#define QMWPARAMETERWIDGETLINKBUTTON_H

#include <QPushButton>

#include "QMwParameterWidget.h"

class QMwParameterWidgetLinkButton :
        public QPushButton,
        public QMwParameterWidget
{
    Q_OBJECT
public:
    explicit QMwParameterWidgetLinkButton(MwParameter *parameter, IMwEditor *editor);

protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);

signals:

public slots:
    void OnClicked();
};

#endif // QMWPARAMETERWIDGETLINKBUTTON_H
