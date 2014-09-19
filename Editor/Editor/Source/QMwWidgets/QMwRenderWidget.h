#ifndef QMWRENDERWIDGET_H
#define QMWRENDERWIDGET_H

#include <QWidget>

#include "QMwEditorWidget.h"

#include <QMouseEvent>
#include <QResizeEvent>

class QMwRenderWidget :
        public QWidget,
        public QMwEditorWidget
{
    Q_OBJECT
private:
    static const int DragMode_None = 0;
    static const int DragMode_Editor = 1;
    static const int DragMode_Resource = 2;

    QPoint dragStartPos, mouseMovePos;
    int dragMode;

    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void resizeEvent(QResizeEvent * event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

public:
    explicit QMwRenderWidget(QWidget *parent = 0);


signals:

public slots:

};

#endif // QMWRENDERWIDGET_H
