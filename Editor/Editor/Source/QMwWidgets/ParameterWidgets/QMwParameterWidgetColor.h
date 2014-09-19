#ifndef QMWPARAMETERWIDGETCOLOR_H
#define QMWPARAMETERWIDGETCOLOR_H

#include <QWidget>

#include "QMwParameterWidgetColorRgb.h"
#include "QMwParameterWidgetColorAlpha.h"

class QMwParameterWidgetColor :
        public QWidget,
        public QMwParameterWidget
{
public:
    QMwParameterWidgetColorRgb *rgbWidget;
    QMwParameterWidgetColorAlpha *alphaWidget;

    explicit QMwParameterWidgetColor(MwParameter *parameter, IMwEditor *editor);
protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);

};

#endif // QMWPARAMETERWIDGETCOLOR_H
