//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwParameterWidgetColorAlpha.h"

#include "../../EditorTools/EditorUtils.h"

QMwParameterWidgetColorAlpha::QMwParameterWidgetColorAlpha(MwParameter *parameter, IMwEditor *editor) :
    QMwParameterWidget(parameter, editor),
    QDoubleSpinBox()
{
    this->parameter = parameter;

    this->setRange(0.0, 1.0);
    this->setSingleStep(0.05);
    this->setValue((double)(((MwVector4*)this->parameter->value)->w));

    QObject::connect(this, SIGNAL(valueChanged(double)), this, SLOT(OnValueChanged(double)));
}

void QMwParameterWidgetColorAlpha::OnValueChanged(double)
{
    ((MwVector4*)this->parameter->value)->w = this->value();
}
