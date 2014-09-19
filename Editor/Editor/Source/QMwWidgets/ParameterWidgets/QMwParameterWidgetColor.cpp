//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwParameterWidgetColor.h"

#include <QHBoxLayout>

QMwParameterWidgetColor::QMwParameterWidgetColor(MwParameter *parameter, IMwEditor *editor) :
    QMwParameterWidget(parameter, editor),
    QWidget()
{
    this->parameter = parameter;

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    this->setAcceptDrops(true);

    this->rgbWidget = new QMwParameterWidgetColorRgb(this->parameter, editor);
    layout->addWidget(this->rgbWidget);

    this->alphaWidget = new QMwParameterWidgetColorAlpha(this->parameter, editor);
    layout->addWidget(this->alphaWidget);
}

void QMwParameterWidgetColor::dragEnterEvent(QDragEnterEvent *event)
{
    QMwParameterWidget::HandleDragEnterEvent(event);
}

void QMwParameterWidgetColor::dropEvent(QDropEvent *event)
{
    QMwParameterWidget::HandleDragDropEvent(event);
}
