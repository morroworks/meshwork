#ifndef QMWEDITORWIDGET_H
#define QMWEDITORWIDGET_H

#include "IMwEditor.h"

class QMwEditorWidget
{
public:
    IMwEditor *editor;

    QMwEditorWidget();

    virtual void SetEditorInterface(IMwEditor *editor);
};

#endif // QMWEDITORWIDGET_H
