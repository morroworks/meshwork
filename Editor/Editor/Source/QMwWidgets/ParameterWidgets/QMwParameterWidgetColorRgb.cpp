//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwParameterWidgetColorRgb.h"

#include <QDoubleSpinBox>

#include "../../EditorTools/EditorUtils.h"

QMwParameterWidgetColorRgb::QMwParameterWidgetColorRgb(MwParameter *parameter, IMwEditor *editor) :
    QMwParameterWidget(parameter, editor),
    QPushButton()
{
    this->parameter = parameter;

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(OnClicked()));

    QObject::connect(&this->colorDialog, SIGNAL(currentColorChanged(const QColor &)), this, SLOT(OnColorDialogColorChanged(const QColor &)));
    QObject::connect(&this->colorDialog, SIGNAL(accepted()), this, SLOT(OnColorDialogColorAccepted()));
    QObject::connect(&this->colorDialog, SIGNAL(rejected()), this, SLOT(OnColorDialogColorRejected()));

    this->setStyleSheet(QString("background-color:#%1;").arg(EditorUtils::Vector4ToHtmlColor(*(MwVector4*)this->parameter->value)));
}

void QMwParameterWidgetColorRgb::OnClicked()
{
    this->revertColor = *((MwVector4*)this->parameter->value);

    this->colorDialog.setCurrentColor(EditorUtils::Vector4ToQColor(this->revertColor));
    this->colorDialog.show();
}

void QMwParameterWidgetColorRgb::OnColorDialogColorChanged(const QColor & color)
{
    EditorUtils::QColorToVector4(color, *((MwVector4*)this->parameter->value), false);
}

void QMwParameterWidgetColorRgb::OnColorDialogColorAccepted()
{
    this->setStyleSheet(QString("background-color:#%1;").arg(EditorUtils::Vector4ToHtmlColor(*(MwVector4*)this->parameter->value)));
}

void QMwParameterWidgetColorRgb::OnColorDialogColorRejected()
{
    *((MwVector4*)this->parameter->value) = this->revertColor;
}
