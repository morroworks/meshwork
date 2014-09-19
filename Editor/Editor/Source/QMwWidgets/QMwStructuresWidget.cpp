//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwStructuresWidget.h"

#include "../EditorTools/EditorUtils.h"

#include <QApplication>
#include <QDrag>
#include <QMimeData>

QMwStructuresWidget::QMwStructuresWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    this->contextMenu = new QMenu(this);
    QAction *deleteAction = new QAction("Delete", this);
    QObject::connect(deleteAction, SIGNAL(triggered()), this, SLOT(ContextMenuDeleteTriggered()));
    this->contextMenu->addAction(deleteAction);

    QAction *wrapInEntitySetAction = new QAction("Wrap in Entity set", this);
    QObject::connect(wrapInEntitySetAction, SIGNAL(triggered()), this, SLOT(ContextMenuWrapInEntitySetTriggered()));
    this->contextMenu->addAction(wrapInEntitySetAction);

    QObject::connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(CurrentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(ContextMenuRequested(QPoint)));

    this->dragMode = QMwStructuresWidget::DragMode_None;
}

void QMwStructuresWidget::SetEditorInterface(IMwEditor *editor)
{
    QMwEditorWidget::SetEditorInterface(editor);

    QMwStructuresWidget::SetMwResourceToItem(this->invisibleRootItem(), this->editor->GetMeshwork()->root);
}

void QMwStructuresWidget::BuildAnew(MwEntitySet *entitySet)
{
    this->clear();

    this->BuildStructureTreeNode(entitySet, this->invisibleRootItem(), true);
}

int QMwStructuresWidget::FindResourceItems(MwList<QTreeWidgetItem*> &result, MwBaseResource *resource)
{
    return QMwStructuresWidget::FindStructureChildItems(result, this->invisibleRootItem(), resource, true);
}

MwBaseResource *QMwStructuresWidget::GetSelectedItem()
{
    if (this->selectedItems().count() == 0)
        return 0;

    return QMwStructuresWidget::GetMwResourceFromItem(this->selectedItems()[0]);
}

MwBaseResource *QMwStructuresWidget::GetMwResourceFromItem(QTreeWidgetItem *item)
{
    if (item == 0)
        return 0;

    return (MwBaseResource*)item->data(0, Qt::UserRole).value<unsigned int>();
}

void QMwStructuresWidget::SetMwResourceToItem(QTreeWidgetItem *item, MwBaseResource *resource)
{
    QString iconName;
    if (EditorUtils::resourceTypeIcons.GetValue(resource->resourceType, iconName))
        item->setIcon(0, QIcon(iconName));
    item->setText(0, resource->name.GetCharContents());

    item->setData(0, Qt::UserRole, QVariant::fromValue((unsigned int)resource));
}

int QMwStructuresWidget::FindStructureChildItems(MwList<QTreeWidgetItem*> &result, QTreeWidgetItem *item, MwBaseResource *resource, bool subItems)
{
    if (resource == 0)
        return 0;

    int numResultItems = result.count;

    int numChildren = item->childCount();
    for (int i = 0; i < numChildren; i++)
    {
        QTreeWidgetItem *childItem = item->child(i);
        if (resource == ((MwBaseResource*)childItem->data(0, Qt::UserRole).value<unsigned int>()))
        {
            result.Add(childItem);
        }
        else
        {
            if (subItems)
            {
                QMwStructuresWidget::FindStructureChildItems(result, childItem, resource, subItems);
            }
        }
    }

    return result.count - numResultItems;
}

void QMwStructuresWidget::BuildStructureTreeNode(MwEntitySet *resourceNode, QTreeWidgetItem *viewNode, bool recursive)
{
    while (viewNode->childCount() > 0)
        viewNode->removeChild(viewNode->child(0));

    QMwStructuresWidget::SetMwResourceToItem(viewNode, resourceNode);

    for (int i = 0; i < resourceNode->references.count; i++)
    {
        MwBaseResource *reference = resourceNode->references[i];

        QTreeWidgetItem *item = new QTreeWidgetItem(viewNode);

        QMwStructuresWidget::SetMwResourceToItem(item, reference);

        viewNode->addChild(item);

        if (reference->resourceType == MwResourceType_EntitySet)
            if (recursive)
                QMwStructuresWidget::BuildStructureTreeNode((MwEntitySet*)reference, item, recursive);
    }
}

void QMwStructuresWidget::mousePressEvent(QMouseEvent *event)
{
    QTreeWidget::mousePressEvent(event);
    //return;

    if (event->button() == Qt::LeftButton)
        this->dragStartPos = event->pos();

    this->dragMode = QMwStructuresWidget::DragMode_None;
}

void QMwStructuresWidget::mouseMoveEvent(QMouseEvent *event)
{
    QTreeWidget::mouseMoveEvent(event);
    //return;

    if (!(event->buttons() & Qt::LeftButton))
        return;

//    if ((event->pos() - this->dragStartPos).manhattanLength() < QApplication::startDragDistance())
//        return;


    QTreeWidgetItem *draggedItem = this->itemAt(this->dragStartPos);
    MwBaseResource *selectedResource = QMwStructuresWidget::GetMwResourceFromItem(draggedItem);
    if (selectedResource == 0)
        return;

    switch (this->dragMode)
    {
        case QMwStructuresWidget::DragMode_None:
        {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/mwresource", MwString((unsigned int)selectedResource).GetCharContents());
            mimeData->setData("application/twitem", MwString((unsigned int)draggedItem).GetCharContents());
            drag->setMimeData(mimeData);
            QString iconName;
            if (EditorUtils::resourceTypeIcons.GetValue(selectedResource->resourceType, iconName))
                drag->setPixmap(QPixmap(iconName));

            this->dragMode = QMwStructuresWidget::DragMode_Resource;

            drag->exec(Qt::CopyAction | Qt::MoveAction);

            break;
        }
    }
}

void QMwStructuresWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void QMwStructuresWidget::dragMoveEvent(QDragMoveEvent *event)
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

    event->accept();
}

void QMwStructuresWidget::dropEvent(QDropEvent *event)
{
    unsigned int resource;
    if (!MwString(event->mimeData()->data("application/mwresource").data()).ToUInt(resource))
    {
        event->ignore();
        return;
    }

    MwBaseResource *droppedResource = (MwBaseResource*)resource;

    QTreeWidgetItem *destItemParent;
    MwEntitySet *destParentSet;
    int destIndex;
    QTreeWidgetItem *destItem = this->itemAt(event->pos());
    if (destItem != 0)
    {
        destItemParent = this->GetItemParent(destItem);
        destParentSet = (MwEntitySet*)this->GetMwResourceFromItem(destItemParent);
        destIndex = destItemParent->indexOfChild(destItem);
    }
    else
    {
        destItemParent = this->invisibleRootItem();
        destParentSet = this->editor->GetMeshwork()->root;
        destIndex = this->editor->GetMeshwork()->root->references.count;
    }

    switch (this->dragMode)
    {
        case QMwStructuresWidget::DragMode_None:
        {
            destParentSet->references.Insert(destIndex, droppedResource);

            QTreeWidgetItem *item = new QTreeWidgetItem(destItemParent);
            QMwStructuresWidget::SetMwResourceToItem(item, droppedResource);
            this->InsertItem(destItemParent, destItem, destIndex);

            event->acceptProposedAction();

            break;
        }

        // Dragging has started from this widget, so the dropped resource has to be moved. In order to do that, first we need to remove it from its old location
        case QMwStructuresWidget::DragMode_Resource:
        {
            unsigned int sourceItemAddress;
            if (!MwString(event->mimeData()->data("application/twitem").data()).ToUInt(sourceItemAddress))
                break;

            QTreeWidgetItem *sourceItem = (QTreeWidgetItem*)sourceItemAddress;
            if (sourceItem == destItem)
                break;

            QTreeWidgetItem *sourceItemParent = this->GetItemParent(sourceItem);
            MwEntitySet *sourceParentSet = (MwEntitySet*)this->GetMwResourceFromItem(sourceItemParent);
            int sourceIndex = sourceItemParent->indexOfChild(sourceItem);

            if ((sourceItemParent == destItemParent) && (sourceIndex < destIndex))
                destIndex--;

            sourceParentSet->references.RemoveAt(sourceIndex);
            sourceItemParent->removeChild(sourceItem);

            destParentSet->references.Insert(destIndex, droppedResource);
            this->InsertItem(destItemParent, sourceItem, destIndex);

            event->acceptProposedAction();

            break;
        }
    }
}

void QMwStructuresWidget::CurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);

    this->editor->SelectResource(QMwStructuresWidget::GetMwResourceFromItem(current));
}

void QMwStructuresWidget::ContextMenuRequested(QPoint pos)
{
    this->contextMenuItem = this->itemAt(pos);

    if (this->contextMenuItem != 0)
        this->contextMenu->popup(this->viewport()->mapToGlobal(pos));
}

void QMwStructuresWidget::ContextMenuDeleteTriggered()
{
    QTreeWidgetItem *contextItemParent = this->GetItemParent(this->contextMenuItem);
    MwEntitySet *contextParentSet = (MwEntitySet*)this->GetMwResourceFromItem(contextItemParent);
    int contextItemIndex = contextItemParent->indexOfChild(this->contextMenuItem);

    contextParentSet->references.RemoveAt(contextItemIndex);

    contextItemParent->removeChild(this->contextMenuItem);
}

void QMwStructuresWidget::ContextMenuWrapInEntitySetTriggered()
{
    MwBaseResource *contextMenuResource = this->GetMwResourceFromItem(this->contextMenuItem);
    QTreeWidgetItem *contextItemParent = this->GetItemParent(this->contextMenuItem);
    MwEntitySet *contextParentSet = (MwEntitySet*)this->GetMwResourceFromItem(contextItemParent);
    int contextItemIndex = contextItemParent->indexOfChild(this->contextMenuItem);

    // Create new entity set and put the resoruce inside
    MwEntitySet *newSet = (MwEntitySet*)this->editor->GetMeshwork()->AddResource(*new MwEntitySet());
    newSet->name = this->editor->GetMeshwork()->AcquireResourceName(contextMenuResource->name, MwResourceType_EntitySet);
    newSet->references.Add(contextMenuResource);

    // Remove the resource and put the new entity set in its place
    contextParentSet->references.RemoveAt(contextItemIndex);
    contextParentSet->references.Insert(contextItemIndex, newSet);

    // Create the new tree widget item
    QTreeWidgetItem *item = new QTreeWidgetItem(contextItemParent);
    this->BuildStructureTreeNode(newSet, item, true);

    // Remove the old tree widget item and put the new one in its place
    contextItemParent->removeChild(this->contextMenuItem);
    this->InsertItem(contextItemParent, item, contextItemIndex);
}

QTreeWidgetItem *QMwStructuresWidget::GetItemParent(QTreeWidgetItem *item)
{
    QTreeWidgetItem *result = item->parent();

    if (result != 0)
        return result;

    return this->invisibleRootItem();
}

// Method to be used instead of QMwStructuresWidget.insertChild(), which does not work as expected
void QMwStructuresWidget::InsertItem(QTreeWidgetItem *destItemParent, QTreeWidgetItem *item, int destIndex)
{
    //destItemParent->insertChild(destIndex, item); // Does not work. Always "inserts" the item at the end (Qt 5.2.1)

    destItemParent->addChild(item);

    int swapCount = destItemParent->childCount() - destIndex - 1;
    for (int i = 0; i < swapCount; i++)
    {
        QTreeWidgetItem *child = destItemParent->child(destIndex);
        destItemParent->removeChild(child);
        destItemParent->addChild(child);
    }
}
