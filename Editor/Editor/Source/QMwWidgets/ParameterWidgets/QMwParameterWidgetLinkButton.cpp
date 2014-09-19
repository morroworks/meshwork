//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwParameterWidgetLinkButton.h"

#include "../../EditorTools/EditorUtils.h"

QMwParameterWidgetLinkButton::QMwParameterWidgetLinkButton(MwParameter *parameter, IMwEditor *editor) :
    QMwParameterWidget(parameter, editor),
    QPushButton()
{
    this->parameter = parameter;

    MwBaseResource *linkReference = (MwBaseResource*)this->parameter->value;

    if (linkReference != 0)
    {
        this->setText(linkReference->name.GetCharContents());

        QString iconName;
        if (EditorUtils::resourceTypeIcons.GetValue(linkReference->resourceType, iconName))
            this->setIcon(QIcon(iconName));

        QObject::connect(this, SIGNAL(clicked()), this, SLOT(OnClicked()));
    }

    this->setAcceptDrops(true);
}

void QMwParameterWidgetLinkButton::dragEnterEvent(QDragEnterEvent *event)
{
    QMwParameterWidget::HandleDragEnterEvent(event);
}

void QMwParameterWidgetLinkButton::dropEvent(QDropEvent *event)
{
    QMwParameterWidget::HandleDragDropEvent(event);
}


void QMwParameterWidgetLinkButton::OnClicked()
{
    this->editor->SelectResource((MwBaseResource*)this->parameter->value);
}
