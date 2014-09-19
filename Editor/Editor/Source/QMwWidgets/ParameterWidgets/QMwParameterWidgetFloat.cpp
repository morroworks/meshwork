//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwParameterWidgetFloat.h"

QMwParameterWidgetFloat::QMwParameterWidgetFloat(MwParameter *parameter, IMwEditor *editor) :
    QMwParameterWidget(parameter, editor),
    QDoubleSpinBox()
{
    this->parameter = parameter;

    this->setRange(-2000000, 2000000);
    this->setValue((double)(*((float*)this->parameter->value)));
    this->setSingleStep(MwMath::Max((float)(MwMath::Abs((float)this->value()) / 10.0f), 0.01f));
    this->setDecimals(5);

    this->setAcceptDrops(true);

    QObject::connect(this, SIGNAL(valueChanged(double)), this, SLOT(OnValueChanged(double)));
}

void QMwParameterWidgetFloat::OnValueChanged(double)
{
    *((float*)this->parameter->value) = this->value();
    this->setSingleStep(MwMath::Max((float)(MwMath::Abs((float)this->value()) / 10.0f), 0.01f));
}

void QMwParameterWidgetFloat::dragEnterEvent(QDragEnterEvent *event)
{
    QMwParameterWidget::HandleDragEnterEvent(event);
}

void QMwParameterWidgetFloat::dropEvent(QDropEvent *event)
{
    QMwParameterWidget::HandleDragDropEvent(event);
}
