//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwTransformLayersWidget.h"

#include "../EditorTools/EditorUtils.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QSpacerItem>

QMwTransformLayersWidget::QMwTransformLayersWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Control panel with buttons
    QWidget *controlPanelWidget = new QWidget(this);
    QHBoxLayout *controlPanelLayout = new QHBoxLayout(controlPanelWidget);
    mainLayout->addWidget(controlPanelWidget);

    QPushButton *deleteButton = new QPushButton(controlPanelWidget);
    deleteButton->setIcon(QIcon(EditorUtils::iconDelete));
    QObject::connect(deleteButton, SIGNAL(clicked()), this, SLOT(DeleteLayerClicked()));
    controlPanelLayout->addWidget(deleteButton);

    controlPanelLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton *downButton = new QPushButton(controlPanelWidget);
    downButton->setIcon(QIcon(EditorUtils::iconMoveDown));
    QObject::connect(downButton, SIGNAL(clicked()), this, SLOT(MoveLayerDownClicked()));
    controlPanelLayout->addWidget(downButton);

    QPushButton *upButton = new QPushButton(controlPanelWidget);
    upButton->setIcon(QIcon(EditorUtils::iconMoveUp));
    QObject::connect(upButton, SIGNAL(clicked()), this, SLOT(MoveLayerUpClicked()));
    controlPanelLayout->addWidget(upButton);

    controlPanelLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton *insertButton = new QPushButton(controlPanelWidget);
    insertButton->setIcon(QIcon(EditorUtils::iconInsert));
    QObject::connect(insertButton, SIGNAL(clicked()), this, SLOT(InsertLayerClicked()));
    controlPanelLayout->addWidget(insertButton);

    QPushButton *appendButton = new QPushButton(controlPanelWidget);
    appendButton->setIcon(QIcon(EditorUtils::iconNew));
    QObject::connect(appendButton, SIGNAL(clicked()), this, SLOT(AppendLayerClicked()));
    controlPanelLayout->addWidget(appendButton);



    // Layers panel
    this->layersWidget = new QWidget(this);
    new QGridLayout(this->layersWidget);
    mainLayout->addWidget(layersWidget);



    this->selectedLayerIndex = -1;

    this->transform = 0;
}

void QMwTransformLayersWidget::SetResource(MwBaseResource *resource)
{
    if (resource != this->transform)
        this->selectedLayerIndex = -1;

    this->transform = 0;

    if (resource != 0)
        if (resource->resourceType == MwResourceType_Transform)
            this->transform = (MwTransform*)resource;

    this->UpdateLayersPanel();
}


void QMwTransformLayersWidget::UpdateLayersPanel()
{
    QGridLayout *layersLayout = (QGridLayout*)this->layersWidget->layout();

    QLayoutItem *child;
    while ((child = layersLayout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }

    if (this->transform == 0)
        return;

    for (int layerIndex = 0; layerIndex < this->transform->transformSlots.count; layerIndex++)
    {
        QRadioButton *layerSelectRadioButton = new QRadioButton(this->layersWidget);
        layerSelectRadioButton->setChecked(layerIndex == this->selectedLayerIndex);
        layerSelectRadioButton->setProperty("layerIndex", QVariant(layerIndex));
        layerSelectRadioButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        QObject::connect(layerSelectRadioButton, SIGNAL(clicked()), this, SLOT(LayerSelected()));
        layersLayout->addWidget(layerSelectRadioButton, layerIndex, 0);

        QComboBox *transformOpComboBox = new QComboBox(this->layersWidget);
        this->SetLayerComboBox(transformOpComboBox, layerIndex);
        QObject::connect(transformOpComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(LayerOperationChanged(int)));
        layersLayout->addWidget(transformOpComboBox, layerIndex, 1);
    }
}


void QMwTransformLayersWidget::SetLayerComboBox(QComboBox *comboBox, int layerIndex)
{
    comboBox->setProperty("layerIndex", QVariant(layerIndex));

    void *dictionaryNode = 0;
    while ((dictionaryNode = EditorUtils::transformOperationNames.GetNodeNext(dictionaryNode)) != 0)
    {
        comboBox->addItem(EditorUtils::transformOperationNames.GetNodeValue(dictionaryNode).value, QVariant((int)EditorUtils::transformOperationNames.GetNodeValue(dictionaryNode).key));
        comboBox->setMaxVisibleItems(1000);
        if (EditorUtils::transformOperationNames.GetNodeValue(dictionaryNode).key == this->transform->transformSlots[layerIndex].operation)
            comboBox->setCurrentIndex(comboBox->count() - 1);
    }
}


// SLOTS

void QMwTransformLayersWidget::DeleteLayerClicked()
{
    if (this->selectedLayerIndex == -1)
        return;

    if (this->transform == 0)
        return;

    this->transform->RemoveTransformSlot(this->selectedLayerIndex);

    this->selectedLayerIndex--;

    this->UpdateLayersPanel();

    this->editor->UpdateResourceProperties(this->transform);
}

void QMwTransformLayersWidget::MoveLayerDownClicked()
{
}

void QMwTransformLayersWidget::MoveLayerUpClicked()
{
}

void QMwTransformLayersWidget::InsertLayerClicked()
{
    if (this->transform == 0)
        return;

    this->selectedLayerIndex = MwMath::Trim(this->selectedLayerIndex + 1, 0, this->transform->transformSlots.count - 1);

    this->transform->InsertTransformSlot(MwTransformOperation_Translate, this->selectedLayerIndex);

    this->selectedLayerIndex = this->transform->transformSlots.count - 1;

    this->UpdateLayersPanel();

    this->editor->UpdateResourceProperties(this->transform);
}

void QMwTransformLayersWidget::AppendLayerClicked()
{
    if (this->transform == 0)
        return;

    this->transform->AddTransformSlot(MwTransformOperation_Translate);

    this->selectedLayerIndex = this->transform->transformSlots.count - 1;

    this->UpdateLayersPanel();

    this->editor->UpdateResourceProperties(this->transform);
}


void QMwTransformLayersWidget::LayerSelected()
{
    QRadioButton *sender = (QRadioButton*)QObject::sender();
    int layerIndex = sender->property("layerIndex").toInt();

    this->selectedLayerIndex = layerIndex;
}

void QMwTransformLayersWidget::LayerOperationChanged(int index)
{
    QComboBox *sender = (QComboBox*)QObject::sender();
    int layerIndex = sender->property("layerIndex").toInt();
    MwTransformOperation transformOp = (MwTransformOperation)sender->itemData(index).toInt();

    this->transform->RemoveTransformSlot(layerIndex);
    this->transform->InsertTransformSlot(transformOp, layerIndex);

    this->editor->UpdateResourceProperties(this->transform);
}

