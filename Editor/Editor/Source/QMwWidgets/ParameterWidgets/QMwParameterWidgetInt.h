#ifndef QMWPARAMETERWIDGETINT_H
#define QMWPARAMETERWIDGETINT_H

#include <QSpinBox>

#include "QMwParameterWidget.h"

class QMwParameterWidgetInt :
        public QSpinBox,
        public QMwParameterWidget
{
    Q_OBJECT
public:
    explicit QMwParameterWidgetInt(MwParameter *parameter, IMwEditor *editor);

protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);

signals:

public slots:
    void OnValueChanged(int);
};

#endif // QMWPARAMETERWIDGETINT_H
