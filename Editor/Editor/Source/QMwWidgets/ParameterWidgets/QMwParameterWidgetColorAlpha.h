#ifndef QMWPARAMETERWIDGETCOLORALPHA_H
#define QMWPARAMETERWIDGETCOLORALPHA_H

#include <QDoubleSpinBox>
#include "QMwParameterWidget.h"

class QMwParameterWidgetColorAlpha :
        public QDoubleSpinBox,
        public QMwParameterWidget
{
    Q_OBJECT

public:
    explicit QMwParameterWidgetColorAlpha(MwParameter *parameter, IMwEditor *editor);

public slots:
    void OnValueChanged(double);
};

#endif // QMWPROPERTYWIDGETCOLORALPHA_H
