//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwMaterialLayersWidget.h"

#include "../EditorTools/EditorUtils.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QSpacerItem>

QMwMaterialLayersWidget::QMwMaterialLayersWidget(QWidget *parent) :
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



    // Shader layers panel
    this->layersWidget = new QWidget(this);
    new QGridLayout(this->layersWidget);
    mainLayout->addWidget(layersWidget);



    // Message panel
    this->messageWidget = new QWidget(this);
    QVBoxLayout *messageLayout = new QVBoxLayout(this->messageWidget);
    mainLayout->addWidget(messageWidget);

    messageLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QLabel *messageIcon = new QLabel(this->messageWidget);
    messageIcon->setPixmap(QPixmap(EditorUtils::iconDelete));
    messageLayout->addWidget(messageIcon);

    this->messageText = new QLabel(this->messageWidget);
    this->messageText->setStyleSheet("color:brown;");
    messageLayout->addWidget(this->messageText);

    this->messageWidget->setVisible(false);

    this->selectedLayerIndex = -1;

    this->material = 0;
}

void QMwMaterialLayersWidget::SetResource(MwBaseResource *resource)
{
    if (resource != this->material)
        this->selectedLayerIndex = -1;

    this->material = 0;

    if (resource != 0)
        if (resource->resourceType == MwResourceType_Material)
            this->material = (MwMaterial*)resource;

    this->UpdateLayersPanel();
    this->SetMessage();
}

void QMwMaterialLayersWidget::UpdateLayersPanel()
{
    QGridLayout *layersLayout = (QGridLayout*)this->layersWidget->layout();

    QLayoutItem *child;
    while ((child = layersLayout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }

    if (this->material == 0)
        return;

    for (int layerIndex = 0; layerIndex < this->material->shaderSlots.count; layerIndex++)
    {
        QRadioButton *layerSelectRadioButton = new QRadioButton(this->layersWidget);
        layerSelectRadioButton->setChecked(layerIndex == this->selectedLayerIndex);
        layerSelectRadioButton->setProperty("layerIndex", QVariant(layerIndex));
        layerSelectRadioButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        QObject::connect(layerSelectRadioButton, SIGNAL(clicked()), this, SLOT(LayerSelected()));
        layersLayout->addWidget(layerSelectRadioButton, layerIndex, 0);

        QComboBox *shaderOpComboBox = new QComboBox(this->layersWidget);
        this->SetShaderOpComboBox(shaderOpComboBox, layerIndex);
        QObject::connect(shaderOpComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(LayerShaderOperationChanged(int)));
        layersLayout->addWidget(shaderOpComboBox, layerIndex, 1);

        QComboBox *colorOpComboBox = new QComboBox(this->layersWidget);
        this->SetColorOpComboBox(colorOpComboBox, layerIndex);
        QObject::connect(colorOpComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(LayerColorOperationChanged(int)));
        layersLayout->addWidget(colorOpComboBox, layerIndex, 2);
    }
}

void QMwMaterialLayersWidget::SetMessage()
{
    if (this->material == 0)
    {
        this->messageWidget->setVisible(false);
        return;
    }

    this->messageText->setText(EditorUtils::MwToQString(this->material->compilationMessage));
    this->messageWidget->setVisible(!this->material->successfullyCompiled);
}

void QMwMaterialLayersWidget::SetShaderOpComboBox(QComboBox *comboBox, int layerIndex)
{
    comboBox->setProperty("layerIndex", QVariant(layerIndex));

    void *dictionaryNode = 0;
    while ((dictionaryNode = EditorUtils::shaderOperationNames.GetNodeNext(dictionaryNode)) != 0)
    {
        comboBox->addItem(EditorUtils::shaderOperationNames.GetNodeValue(dictionaryNode).value, QVariant((int)EditorUtils::shaderOperationNames.GetNodeValue(dictionaryNode).key));
        comboBox->setMaxVisibleItems(1000);
        if (EditorUtils::shaderOperationNames.GetNodeValue(dictionaryNode).key == this->material->shaderSlots[layerIndex].shaderOp)
            comboBox->setCurrentIndex(comboBox->count() - 1);
    }
}

void QMwMaterialLayersWidget::SetColorOpComboBox(QComboBox *comboBox, int layerIndex)
{
    comboBox->setProperty("layerIndex", QVariant(layerIndex));

    void *dictionaryNode = 0;
    while ((dictionaryNode = EditorUtils::colorOperationNames.GetNodeNext(dictionaryNode)) != 0)
    {
        comboBox->addItem(EditorUtils::colorOperationNames.GetNodeValue(dictionaryNode).value, QVariant((int)EditorUtils::colorOperationNames.GetNodeValue(dictionaryNode).key));
        comboBox->setMaxVisibleItems(1000);
        if (EditorUtils::colorOperationNames.GetNodeValue(dictionaryNode).key == this->material->shaderSlots[layerIndex].colorOp)
            comboBox->setCurrentIndex(comboBox->count() - 1);
    }
}

void QMwMaterialLayersWidget::DeleteLayerClicked()
{
    if (this->selectedLayerIndex == -1)
        return;

    if (this->material == 0)
        return;

    this->material->RemoveShaderSlot(this->selectedLayerIndex);
    this->material->UpdateShader();

    this->selectedLayerIndex--;

    this->UpdateLayersPanel();
    this->SetMessage();

    this->editor->UpdateResourceProperties(this->material);
}

void QMwMaterialLayersWidget::MoveLayerDownClicked()
{
    if (this->selectedLayerIndex == -1)
        return;

    if (this->material == 0)
        return;

    if (this->selectedLayerIndex >= this->material->shaderSlots.count - 1)
        return;

    this->material->MoveShaderSlot(this->selectedLayerIndex, this->selectedLayerIndex + 1);
    this->material->UpdateShader();

    this->selectedLayerIndex++;

    this->UpdateLayersPanel();
    this->SetMessage();

    this->editor->UpdateResourceProperties(this->material);
}

void QMwMaterialLayersWidget::MoveLayerUpClicked()
{
    if (this->selectedLayerIndex == -1)
        return;

    if (this->material == 0)
        return;

    if (this->selectedLayerIndex < 1)
        return;

    this->material->MoveShaderSlot(this->selectedLayerIndex, this->selectedLayerIndex - 1);
    this->material->UpdateShader();

    this->selectedLayerIndex--;

    this->UpdateLayersPanel();
    this->SetMessage();

    this->editor->UpdateResourceProperties(this->material);
}

void QMwMaterialLayersWidget::InsertLayerClicked()
{
    if (this->material == 0)
        return;

    this->selectedLayerIndex = MwMath::Trim(this->selectedLayerIndex + 1, 0, this->material->shaderSlots.count - 1);

    this->material->InsertShaderSlot(MwShaderOperation_BasicShading, MwColorOperation_Set, this->selectedLayerIndex);
    this->material->UpdateShader();

    this->UpdateLayersPanel();
    this->SetMessage();

    this->editor->UpdateResourceProperties(this->material);
}

void QMwMaterialLayersWidget::AppendLayerClicked()
{
    if (this->material == 0)
        return;

    this->material->AddShaderSlot(MwShaderOperation_BasicShading, MwColorOperation_Set);
    this->material->UpdateShader();

    this->selectedLayerIndex = this->material->shaderSlots.count - 1;

    this->UpdateLayersPanel();
    this->SetMessage();

    this->editor->UpdateResourceProperties(this->material);
}

void QMwMaterialLayersWidget::LayerSelected()
{
    QRadioButton *sender = (QRadioButton*)QObject::sender();
    int layerIndex = sender->property("layerIndex").toInt();

    this->selectedLayerIndex = layerIndex;
}

void QMwMaterialLayersWidget::LayerShaderOperationChanged(int index)
{
    QComboBox *sender = (QComboBox*)QObject::sender();
    int layerIndex = sender->property("layerIndex").toInt();
    MwShaderOperation shaderOp = (MwShaderOperation)sender->itemData(index).toInt();
    MwColorOperation colorOp = this->material->shaderSlots[layerIndex].colorOp;

    this->material->RemoveShaderSlot(layerIndex);
    this->material->InsertShaderSlot(shaderOp, colorOp, layerIndex);
    this->material->UpdateShader();

    this->SetMessage();

    this->editor->UpdateResourceProperties(this->material);
}

void QMwMaterialLayersWidget::LayerColorOperationChanged(int index)
{
    QComboBox *sender = (QComboBox*)QObject::sender();
    int layerIndex = sender->property("layerIndex").toInt();
    MwColorOperation colorOp = (MwColorOperation)sender->itemData(index).toInt();

    this->material->shaderSlots[layerIndex].colorOp = colorOp;
    this->material->UpdateShader();

    this->SetMessage();
}

