//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwResourceItemButtonWidget.h"

#include <QVariant>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

#include "../EditorTools/EditorUtils.h"

QMwResourceItemButtonWidget::QMwResourceItemButtonWidget(QWidget *parent) :
    QPushButton(parent)
{
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(OnClicked()));
}

void QMwResourceItemButtonWidget::SetResource(MwBaseResource *resource)
{
    this->resource = resource;

    QString iconName;
    if (EditorUtils::resourceTypeIcons.GetValue(this->resource->resourceType, iconName))
    {
        this->setIcon(QIcon(iconName));
    }
    else
    {
        this->setIcon(QIcon());
    }
}

void QMwResourceItemButtonWidget::mousePressEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);

    if (event->button() == Qt::LeftButton)
        dragStartPos = event->pos();
}

void QMwResourceItemButtonWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPushButton::mouseMoveEvent(event);

    if (!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - dragStartPos).manhattanLength() < QApplication::startDragDistance())
        return;

    if (this->resource == 0)
        return;

    Qt::DropAction dropAction = EditorUtils::CreateResourceDrag(this, this->resource)->exec(Qt::CopyAction | Qt::MoveAction);
}

void QMwResourceItemButtonWidget::OnClicked()
{
    if (this->editor != 0)
        this->editor->SelectResource(this->resource);
}
