#ifndef QMWPARAMETERWIDGETLINKRECALL_H
#define QMWPARAMETERWIDGETLINKRECALL_H

#include <QPushButton>

#include "QMwParameterWidget.h"

class QMwParameterWidgetLinkRecall :
        public QPushButton,
        public QMwParameterWidget
{
    Q_OBJECT
public:
    QMwParameterWidgetLinkRecall(MwParameter *parameter, IMwEditor *editor);

public slots:
    void OnClicked();
};

#endif // QMWPARAMETERWIDGETLINKRECALL_H
