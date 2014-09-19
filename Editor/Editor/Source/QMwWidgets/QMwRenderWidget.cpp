//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwRenderWidget.h"

#include <QApplication>

#include <QDrag>
#include <QMimeData>

#include <QMessageBox>

#include "../EditorTools/EditorUtils.h"

QMwRenderWidget::QMwRenderWidget(QWidget *parent) :
    QWidget(parent)
{
    this->dragMode = QMwRenderWidget::DragMode_None;
}

void QMwRenderWidget::mousePressEvent(QMouseEvent * event)
{
    QWidget::mousePressEvent(event);

    if (event->button() == Qt::LeftButton)
    {
        this->dragStartPos = event->pos();
        this->mouseMovePos = event->pos();
    }

    this->dragMode = QMwRenderWidget::DragMode_None;
}

void QMwRenderWidget::mouseReleaseEvent(QMouseEvent * event)
{
    QWidget::mouseReleaseEvent(event);

    if (event->button() != Qt::LeftButton)
        return;

    if (this->editor == 0)
        return;

    switch (this->dragMode)
    {
        case QMwRenderWidget::DragMode_None:
        {
            MwIntersectionInfo intersectionInfo;
            MwTraceParameters entityInfo;
            if (this->editor->GetMeshwork()->Pick(event->pos().x(), event->pos().y(), this->width(), this->height(), intersectionInfo, entityInfo))
            {
                this->editor->SelectResource(entityInfo.materialRef);
            }

            break;
        }
    }
}

void QMwRenderWidget::mouseMoveEvent(QMouseEvent * event)
{
    QWidget::mouseMoveEvent(event);

    if ((event->buttons() & Qt::LeftButton) == 0)
        return;

//    if ((event->pos() - dragStartPos).manhattanLength() < QApplication::startDragDistance())
//        return;

    switch (this->dragMode)
    {
        case QMwRenderWidget::DragMode_None:
        {
            MwIntersectionInfo intersectionInfo;
            MwTraceParameters entityInfo;
            if (this->editor->GetMeshwork()->Pick(this->dragStartPos.x(), this->dragStartPos.y(), this->width(), this->height(), intersectionInfo, entityInfo))
            {
                if (entityInfo.materialRef != 0)
                {
                    Qt::DropAction dropAction = EditorUtils::CreateResourceDrag(this, entityInfo.materialRef)->exec(Qt::CopyAction | Qt::MoveAction);

                    this->dragMode = QMwRenderWidget::DragMode_Resource;
                }
            }
            else
            {
                QPoint deltaMove = this->mouseMovePos - event->pos();
                this->editor->MouseDrag(deltaMove.x(), deltaMove.y());

                this->dragMode = QMwRenderWidget::DragMode_Editor;
            }
            break;
        }

        case QMwRenderWidget::DragMode_Editor:
        {
            QPoint deltaMove = this->mouseMovePos - event->pos();
            this->editor->MouseDrag(deltaMove.x(), deltaMove.y());

            break;
        }
    }

    this->mouseMovePos = event->pos();
}

void QMwRenderWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);

    if (this->editor != 0)
        this->editor->GetMeshwork()->SetViewport(event->size().width(), event->size().height());
}

void QMwRenderWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void QMwRenderWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (this->editor == 0)
    {
        event->ignore();
        return;
    }

    if (!event->mimeData()->hasFormat("application/mwresource"))
    {
        event->ignore();
        return;
    }

    unsigned int resource;
    if (!MwString(event->mimeData()->data("application/mwresource").data()).ToUInt(resource))
    {
        event->ignore();
        return;
    }

    MwBaseResource *droppedResource = (MwBaseResource*)resource;

    MwIntersectionInfo intersectionInfo;
    MwTraceParameters entityInfo;
    if (!this->editor->GetMeshwork()->Pick(event->pos().x(), event->pos().y(), this->width(), this->height(), intersectionInfo, entityInfo))
    {
        event->ignore();
        return;
    }


    bool accept = false;

    switch (droppedResource->resourceType)
    {
        case MwResourceType_Material:
        {
            accept = entityInfo.meshRef != 0;
            break;
        }
    }

    if (accept)
        event->accept();
    else
        event->ignore();
}

void QMwRenderWidget::dropEvent(QDropEvent *event)
{
    if (this->editor == 0)
        return;

    unsigned int resource;
    if (!MwString(event->mimeData()->data("application/mwresource").data()).ToUInt(resource))
        return;

    MwBaseResource *droppedResource = (MwBaseResource*)resource;

    MwIntersectionInfo intersectionInfo;
    MwTraceParameters entityInfo;
    if (!this->editor->GetMeshwork()->Pick(event->pos().x(), event->pos().y(), this->width(), this->height(), intersectionInfo, entityInfo))
        return;

    switch (droppedResource->resourceType)
    {
        case MwResourceType_Material:
        {
            if (entityInfo.materialRef != 0)
            {
                entityInfo.materialBranch->references[entityInfo.materialIndex] = droppedResource;
            }
            else
            {
                entityInfo.meshBranch->references.Insert(entityInfo.meshIndex, droppedResource);
            }
            break;
        }
    }


    event->acceptProposedAction();
}
