//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwResourcesWidget.h"

#include "QMwResourceItemWidget.h"

QMwResourcesWidget::QMwResourcesWidget(QWidget *parent) :
    QWidget(parent)
{
    this->layout = new QGridLayout(this);

    this->items = 0;
    this->filterType = (MwResourceType)-1;
    this->filterString = "";
}

void QMwResourcesWidget::SetItemSource(MwList<MwBaseResource*> &items)
{
    this->items = &items;
    this->RefreshItems();
}

void QMwResourcesWidget::SetFilterType(MwResourceType filterType)
{
    this->filterType = filterType;
    this->RefreshItems();
}

void QMwResourcesWidget::SetFilterString(const MwString &filterString)
{
    this->filterString = filterString;
    this->RefreshItems();
}

void QMwResourcesWidget::RefreshItems()
{
    const int itemWidth = 64;
    int ml, mr, mt, mb;
    this->layout->getContentsMargins(&ml, &mr, &mt, &mb);
    int clientWidth = this->width() - ml - mr;
    int hSpacing = this->layout->horizontalSpacing();
    int numHorizontalItems = (clientWidth + hSpacing) / (itemWidth + hSpacing);

    QLayoutItem *child;
    while ((child = this->layout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }

    if (this->items == 0)
        return;

    int column = 0;
    int row = 0;
    for (int i = 0; i < this->items->count; i++)
    {
        MwBaseResource *item = (*(this->items))[i];
        if ((((int)this->filterType == -1) || (this->filterType == item->resourceType)) && (item->resourceType != MwResourceType_EntitySet))
        {
            if ((this->filterString.length == 0) || (item->name.IndexOf(this->filterString) != -1))
            {
                QMwResourceItemWidget *widget = new QMwResourceItemWidget();
                widget->SetEditorInterface(this->editor);
                widget->SetResource(item);
                widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                widget->setMinimumSize(64, 64);
                widget->setMaximumSize(64, 64);

                this->layout->addWidget(widget, row, column);

                column++;
                if (column >= numHorizontalItems)
                {
                    column = 0;
                    row++;
                }
            }
        }
    }
}
