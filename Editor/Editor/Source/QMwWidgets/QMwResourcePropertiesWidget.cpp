//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwResourcePropertiesWidget.h"

#include "../QMwWidgets/ParameterWidgets/QMwParameterWidgetColor.h"
#include "../QMwWidgets/ParameterWidgets/QMwParameterWidgetLink.h"
#include "../QMwWidgets/ParameterWidgets/QMwParameterWidgetBool.h"
#include "../QMwWidgets/ParameterWidgets/QMwParameterWidgetInt.h"
#include "../QMwWidgets/ParameterWidgets/QMwParameterWidgetFloat.h"

#include "../EditorTools/EditorUtils.h"

#include <QLabel>

QWidget *QMwResourcePropertiesWidget::CreateMwParameterWidget(MwParameter *parameter, IMwEditor *editor)
{
    switch (parameter->type)
    {
        case MwParameterType_Bool:
        {
            return new QMwParameterWidgetBool(parameter, editor);
        }

        case MwParameterType_Int:
        {
            return new QMwParameterWidgetInt(parameter, editor);
        }

        case MwParameterType_Float:
        {
            return new QMwParameterWidgetFloat(parameter, editor);
        }

        case MwParameterType_Color:
        {
            return new QMwParameterWidgetColor(parameter, editor);

            break;
        }

        case MwParameterType_ReferenceTexture:
        case MwParameterType_ReferenceTransform:
        case MwParameterType_ReferenceVector3:
        case MwParameterType_ReferenceMechanism:
        case MwParameterType_ReferenceCamera:
        case MwParameterType_ReferenceSound:
        {
            return new QMwParameterWidgetLink(parameter, editor);

            break;
        }

        default:
        {
            return 0;
        }
    }
}

QMwResourcePropertiesWidget::QMwResourcePropertiesWidget(QWidget *parent)
    : QWidget(parent)
{
    this->layout = new QGridLayout(this);
    this->resource = 0;
}

void QMwResourcePropertiesWidget::SetResource(MwBaseResource *resource)
{
    this->resource = resource;

    QLayoutItem *child;
    while ((child = this->layout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }

    if (resource == 0)
        return;

    for (int i = 0; i < resource->properties.count; i++)
    {
        MwProperty *resourceProperty = resource->properties[i];

        this->layout->addWidget(new QLabel(resourceProperty->name.GetCharContents(), this), i, 0);

        QWidget *mwParameterWidget = QMwResourcePropertiesWidget::CreateMwParameterWidget(resourceProperty, this->editor);
        if (mwParameterWidget != 0)
            this->layout->addWidget(mwParameterWidget, i, 1);
    }
}
