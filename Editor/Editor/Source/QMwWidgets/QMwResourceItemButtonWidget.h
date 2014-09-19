#ifndef QMWRESOURCEITEMBUTTONWIDGET_H
#define QMWRESOURCEITEMBUTTONWIDGET_H

#include <QPushButton>

#include "QMwEditorWidget.h"

class QMwResourceItemButtonWidget :
        public QPushButton,
        public QMwEditorWidget
{
    Q_OBJECT
private:
    QPoint dragStartPos;
    MwBaseResource *GetMwResource();

public:
    MwBaseResource *resource;

    explicit QMwResourceItemButtonWidget(QWidget *parent = 0);

    void SetResource(MwBaseResource *resource);

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:
    void OnClicked();

};

#endif // QMWRESOURCEITEMBUTTONWIDGET_H
