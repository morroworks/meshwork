#ifndef QMWPARAMETERWIDGETCOLORRGB_H
#define QMWPARAMETERWIDGETCOLORRGB_H

#include <QPushButton>
#include <QColorDialog>
#include "QMwParameterWidget.h"


class QMwParameterWidgetColorRgb :
        public QPushButton,
        public QMwParameterWidget
{
    Q_OBJECT

private:
    QColorDialog colorDialog;
    MwVector4 revertColor;

public:
    explicit QMwParameterWidgetColorRgb(MwParameter *parameter, IMwEditor *editor);

public slots:
    void OnClicked();

    void OnColorDialogColorChanged(const QColor & color);
    void OnColorDialogColorAccepted();
    void OnColorDialogColorRejected();
};

#endif // QMWPARAMETERWIDGETCOLORRGB_H
