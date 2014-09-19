#ifndef QMWSTRUCTURESWIDGET_H
#define QMWSTRUCTURESWIDGET_H

#include "../../Engine/Meshwork/Source/MeshworkEngine.h"

#include "QMwEditorWidget.h"

#include <QTreeWidget>
#include <QMouseEvent>
#include <QMenu>

class QMwStructuresWidget :
        public QTreeWidget,
        public QMwEditorWidget
{
    Q_OBJECT
private:
    QMenu *contextMenu;
    QTreeWidgetItem *contextMenuItem;

    int dragMode;

    QTreeWidgetItem *GetItemParent(QTreeWidgetItem *item);
    void InsertItem(QTreeWidgetItem *destItemParent, QTreeWidgetItem *item, int destIndex);

public:
    static const int DragMode_None = 0;
    static const int DragMode_Resource = 1;

    explicit QMwStructuresWidget(QWidget *parent = 0);

    virtual void SetEditorInterface(IMwEditor *editor);

    void BuildAnew(MwEntitySet *entitySet);
    int FindResourceItems(MwList<QTreeWidgetItem*> &result, MwBaseResource *resource);

    MwBaseResource *GetSelectedItem();

    static MwBaseResource *GetMwResourceFromItem(QTreeWidgetItem *item);
    static void SetMwResourceToItem(QTreeWidgetItem *item, MwBaseResource *resource);

    // Returns the number of items found and added to result
    static int FindStructureChildItems(MwList<QTreeWidgetItem*> &result, QTreeWidgetItem *item, MwBaseResource *resource, bool subItems = true);
    static void BuildStructureTreeNode(MwEntitySet *resourceNode, QTreeWidgetItem *viewNode, bool recursive);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

signals:

public slots:
    void CurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void ContextMenuRequested(QPoint pos);
    void ContextMenuDeleteTriggered();
    void ContextMenuWrapInEntitySetTriggered();

private:
    QPoint dragStartPos;

};

#endif // QMWSTRUCTURESWIDGET_H
