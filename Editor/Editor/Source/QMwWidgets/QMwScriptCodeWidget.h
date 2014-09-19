#ifndef QMWSCRIPTCODEWIDGET_H
#define QMWSCRIPTCODEWIDGET_H

#include <QWidget>

#include <QPlainTextEdit>

#include "QMwEditorWidget.h"

class QMwScriptCodeWidget :
        public QWidget,
        public QMwEditorWidget
{
    Q_OBJECT
private:
    QPlainTextEdit *sourceCodeEdit, *compilationMessagesEdit;

public:
    MwScript *script;

    explicit QMwScriptCodeWidget(QWidget *parent = 0);

    void SetResource(MwBaseResource *resource);

signals:

public slots:
    void BuildClicked();
    void RunClicked();

    void SourceCodeChanged();
};

#endif // QMWSCRIPTCODEWIDGET_H
