#ifndef QMWPARAMETERWIDGETBOOL_H
#define QMWPARAMETERWIDGETBOOL_H

#include <QCheckBox>

#include "QMwParameterWidget.h"

class QMwParameterWidgetBool :
        public QCheckBox,
        public QMwParameterWidget
{
    Q_OBJECT
public:
    explicit QMwParameterWidgetBool(MwParameter *parameter, IMwEditor *editor);

signals:

protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);

public slots:
    void OnStateChanged(int);

};

#endif // QMWPARAMETERWIDGETBOOL_H
