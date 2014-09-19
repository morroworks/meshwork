//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwParameterWidgetInt.h"

QMwParameterWidgetInt::QMwParameterWidgetInt(MwParameter *parameter, IMwEditor *editor) :
    QMwParameterWidget(parameter, editor),
    QSpinBox()
{
    this->parameter = parameter;

    this->setRange(-2000000, 2000000);
    this->setValue(*((int*)this->parameter->value));
    this->setSingleStep(MwMath::Max(MwMath::Abs(this->value()) / 10, 1));

    this->setAcceptDrops(true);

    QObject::connect(this, SIGNAL(valueChanged(int)), this, SLOT(OnValueChanged(int)));
}

void QMwParameterWidgetInt::OnValueChanged(int)
{
    *((int*)this->parameter->value) = this->value();
    this->setSingleStep(MwMath::Max(MwMath::Abs(this->value()) / 10, 1));
}

void QMwParameterWidgetInt::dragEnterEvent(QDragEnterEvent *event)
{
    QMwParameterWidget::HandleDragEnterEvent(event);
}

void QMwParameterWidgetInt::dropEvent(QDropEvent *event)
{
    QMwParameterWidget::HandleDragDropEvent(event);
}
