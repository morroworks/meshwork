#ifndef QMWPARAMETERWIDGETFLOAT_H
#define QMWPARAMETERWIDGETFLOAT_H

#include <QDoubleSpinBox>

#include "QMwParameterWidget.h"

class QMwParameterWidgetFloat :
        public QDoubleSpinBox,
        public QMwParameterWidget
{
    Q_OBJECT
public:
    QMwParameterWidgetFloat(MwParameter *parameter, IMwEditor *editor);

protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);

public slots:
    void OnValueChanged(double);

};

#endif // QMWPARAMETERWIDGETFLOAT_H
