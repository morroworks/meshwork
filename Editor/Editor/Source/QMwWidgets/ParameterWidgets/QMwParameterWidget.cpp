//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwParameterWidget.h"

#include <QMimeData>

QMwParameterWidget::QMwParameterWidget(MwParameter *parameter, IMwEditor *editor)
{
    this->parameter = parameter;

    this->SetEditorInterface(editor);
}

void QMwParameterWidget::HandleDragEnterEvent(QDragEnterEvent *event)
{
    if (!event->mimeData()->hasFormat("application/mwresource"))
        return;

    unsigned int resource;
    if (!MwString(event->mimeData()->data("application/mwresource").data()).ToUInt(resource))
        return;

    MwBaseResource *droppedResource = (MwBaseResource*)resource;

    bool accept = false;

    switch (droppedResource->resourceType)
    {
        case MwResourceType_Mechanism:
        {
            accept = this->parameter->GetEffectiveParameter()->type == ((MwBaseMechanism*)droppedResource)->parameter.GetEffectiveParameter()->type;
            break;
        }

        case MwResourceType_Texture:
        {
            accept = this->parameter->GetEffectiveParameter()->type == MwParameterType_ReferenceTexture;
            break;
        }
        case MwResourceType_Camera:
        {
            accept = this->parameter->GetEffectiveParameter()->type == MwParameterType_ReferenceCamera;
            break;
        }
        case MwResourceType_Transform:
        {
            accept = (this->parameter->GetEffectiveParameter()->type == MwParameterType_ReferenceTransform) ||
                     (this->parameter->GetEffectiveParameter()->type == MwParameterType_ReferenceVector3);
            break;
        }

        case MwResourceType_Sound:
        {
            accept = this->parameter->GetEffectiveParameter()->type == MwParameterType_ReferenceSound;
        }
    }

    if (accept)
        event->acceptProposedAction();
}

void QMwParameterWidget::HandleDragDropEvent(QDropEvent *event)
{
    unsigned int resource;
    if (!MwString(event->mimeData()->data("application/mwresource").data()).ToUInt(resource))
        return;

    MwBaseResource *droppedResource = (MwBaseResource*)resource;

    switch (droppedResource->resourceType)
    {
        case MwResourceType_Mechanism:
        {
            this->parameter->SetReference(MwParameterType_ReferenceMechanism, droppedResource);

            break;
        }

        default:
        {
            this->parameter->SetReference(this->parameter->GetEffectiveParameter()->type, droppedResource);
        }
    }

    event->acceptProposedAction();

    // TODO: Generally, UpdateResourceProperties() should not be called directly from here, as it recreates all the parameter widgets and therefore destroys this object while its calling method has not yet returned
    this->editor->UpdateResourceProperties(this->editor->GetSelectedResource());
}
