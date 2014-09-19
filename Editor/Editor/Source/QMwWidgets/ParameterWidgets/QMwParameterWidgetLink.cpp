//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwParameterWidgetLink.h"

#include <QHBoxLayout>

QMwParameterWidgetLink::QMwParameterWidgetLink(MwParameter *parameter, IMwEditor *editor) :
    QMwParameterWidget(parameter, editor),
    QWidget()
{
    this->parameter = parameter;

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    this->button = new QMwParameterWidgetLinkButton(this->parameter, editor);
    layout->addWidget(this->button);

    MwBaseResource *linkReference = (MwBaseResource*)this->parameter->value;

    if ((linkReference != 0) && (linkReference->resourceType == MwResourceType_Mechanism))
    {
        this->recallButton = new QMwParameterWidgetLinkRecall(this->parameter, editor);
        this->recallButton->setMaximumWidth(30);

        layout->addWidget(this->recallButton);
    }
    else
        this->recallButton = 0;
}
