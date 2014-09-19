#ifndef QMWPARAMETERWIDGET_H
#define QMWPARAMETERWIDGET_H

#include "../QMwEditorWidget.h"

#include <QDragEnterEvent>
#include <QDropEvent>

class QMwParameterWidget :
        public QMwEditorWidget
{
public:
    MwParameter *parameter;

    QMwParameterWidget(MwParameter *parameter, IMwEditor *editor);

protected:
    // Methods to handle events in inheriting classes. Can't simply override the events here, because this class shouldn't inherit QWidget, as its descendants themselves will inherit different classes descendants of QWidget, such as QCheckBox, QSpinEdit, QPushButton and etc.
    void HandleDragEnterEvent(QDragEnterEvent *event);
    void HandleDragDropEvent(QDropEvent *event);
};

#endif // QMWPARAMETERWIDGET_H
