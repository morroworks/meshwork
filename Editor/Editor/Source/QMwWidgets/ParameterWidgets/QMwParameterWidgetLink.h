#ifndef QMWPARAMETERWIDGETLINK_H
#define QMWPARAMETERWIDGETLINK_H

#include <QWidget>

#include "QMwParameterWidgetLinkButton.h"
#include "QMwParameterWidgetLinkRecall.h"

class QMwParameterWidgetLink :
        public QWidget,
        public QMwParameterWidget
{
public:
    QMwParameterWidgetLinkButton *button;
    QMwParameterWidgetLinkRecall *recallButton;

    QMwParameterWidgetLink(MwParameter *parameter, IMwEditor *editor);
};

#endif // QMWPARAMETERWIDGETLINK_H
