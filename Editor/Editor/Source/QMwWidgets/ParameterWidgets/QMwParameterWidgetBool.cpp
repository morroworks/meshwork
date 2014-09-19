//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwParameterWidgetBool.h"

QMwParameterWidgetBool::QMwParameterWidgetBool(MwParameter *parameter, IMwEditor *editor) :
    QMwParameterWidget(parameter, editor),
    QCheckBox()
{
    this->parameter = parameter;

    QObject::connect(this, SIGNAL(stateChanged(int)), this, SLOT(OnStateChanged(int)));

    this->setChecked(*((bool*)this->parameter->value));

    this->setAcceptDrops(true);
}

void QMwParameterWidgetBool::OnStateChanged(int)
{
    *((bool*)this->parameter->value) = this->isChecked();
}

void QMwParameterWidgetBool::dragEnterEvent(QDragEnterEvent *event)
{
    QMwParameterWidget::HandleDragEnterEvent(event);
}

void QMwParameterWidgetBool::dropEvent(QDropEvent *event)
{
    QMwParameterWidget::HandleDragDropEvent(event);
}
