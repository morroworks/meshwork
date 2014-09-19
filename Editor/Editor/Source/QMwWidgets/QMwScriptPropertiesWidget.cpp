//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwScriptPropertiesWidget.h"

#include "../EditorTools/EditorUtils.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QSpacerItem>

QMwScriptPropertiesWidget::QMwScriptPropertiesWidget(QWidget *parent) :
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

    QPushButton *appendButton = new QPushButton(controlPanelWidget);
    appendButton->setIcon(QIcon(EditorUtils::iconNew));
    QObject::connect(appendButton, SIGNAL(clicked()), this, SLOT(AppendLayerClicked()));
    controlPanelLayout->addWidget(appendButton);



    // Properties control panel
    this->layersWidget = new QWidget(this);
    new QGridLayout(this->layersWidget);
    mainLayout->addWidget(layersWidget);


    this->script = 0;

    this->selectedLayerIndex = -1;
}

void QMwScriptPropertiesWidget::SetResource(MwBaseResource *resource)
{
    this->script = 0;

    if (resource != 0)
        if (resource->resourceType == MwResourceType_Script)
            this->script = (MwScript*)resource;

    this->UpdateLayersPanel();
}

void QMwScriptPropertiesWidget::SetPropertyTypeComboBox(QComboBox *comboBox, int layerIndex)
{
    comboBox->setProperty("layerIndex", QVariant(layerIndex));

    void *dictionaryNode = 0;
    while ((dictionaryNode = EditorUtils::parameterTypeNames.GetNodeNext(dictionaryNode)) != 0)
    {
        comboBox->addItem(EditorUtils::parameterTypeNames.GetNodeValue(dictionaryNode).value, QVariant((int)EditorUtils::parameterTypeNames.GetNodeValue(dictionaryNode).key));
        comboBox->setMaxVisibleItems(1000);
        if (EditorUtils::parameterTypeNames.GetNodeValue(dictionaryNode).key == this->script->properties[layerIndex]->type)
            comboBox->setCurrentIndex(comboBox->count() - 1);
    }
}

void QMwScriptPropertiesWidget::UpdateLayersPanel()
{
    QGridLayout *layersLayout = (QGridLayout*)this->layersWidget->layout();

    QLayoutItem *child;
    while ((child = layersLayout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }

    if (this->script == 0)
        return;

    for (int layerIndex = 0; layerIndex < this->script->properties.count; layerIndex++)
    {
        QRadioButton *layerSelectRadioButton = new QRadioButton(this->layersWidget);
        layerSelectRadioButton->setChecked(layerIndex == this->selectedLayerIndex);
        layerSelectRadioButton->setProperty("layerIndex", QVariant(layerIndex));
        layerSelectRadioButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        QObject::connect(layerSelectRadioButton, SIGNAL(clicked()), this, SLOT(LayerSelected()));
        layersLayout->addWidget(layerSelectRadioButton, layerIndex, 0);

        QLineEdit *layerNameEdit = new QLineEdit(this->layersWidget);
        layerNameEdit->setText(EditorUtils::MwToQString(this->script->properties[layerIndex]->name));
        QObject::connect(layerNameEdit, SIGNAL(editingFinished()), this, SLOT(LayerNameChanged()));
        layersLayout->addWidget(layerNameEdit, layerIndex, 1);

        QComboBox *shaderOpComboBox = new QComboBox(this->layersWidget);
        this->SetPropertyTypeComboBox(shaderOpComboBox, layerIndex);
        QObject::connect(shaderOpComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(LayerTypeChanged(int)));
        layersLayout->addWidget(shaderOpComboBox, layerIndex, 2);
    }
}

void QMwScriptPropertiesWidget::DeleteLayerClicked()
{
    if (this->selectedLayerIndex == -1)
        return;

    if (this->script == 0)
        return;

    delete this->script->properties[this->selectedLayerIndex];
    this->script->properties.RemoveAt(this->selectedLayerIndex);

    this->selectedLayerIndex--;

    this->UpdateLayersPanel();

    this->editor->UpdateResourceProperties(this->script);
}

void QMwScriptPropertiesWidget::AppendLayerClicked()
{
    if (this->script == 0)
        return;

    this->script->properties.Add(new MwProperty("New Property", MwParameterType_None, 0));

    this->selectedLayerIndex = this->script->properties.count - 1;

    this->UpdateLayersPanel();

    this->editor->UpdateResourceProperties(this->script);
}


void QMwScriptPropertiesWidget::LayerSelected()
{
    QRadioButton *sender = (QRadioButton*)QObject::sender();
    int layerIndex = sender->property("layerIndex").toInt();

    this->selectedLayerIndex = layerIndex;
}

void QMwScriptPropertiesWidget::LayerNameChanged()
{
    QLineEdit *sender = (QLineEdit*)QObject::sender();
    int layerIndex = sender->property("layerIndex").toInt();
    MwString name = EditorUtils::QToMwString(sender->text());

    this->script->properties[layerIndex]->name = name;

    this->editor->UpdateResourceProperties(this->script);
}

void QMwScriptPropertiesWidget::LayerTypeChanged(int index)
{
    QComboBox *sender = (QComboBox*)QObject::sender();
    int layerIndex = sender->property("layerIndex").toInt();
    MwParameterType type = (MwParameterType)sender->itemData(index).toInt();


    this->script->properties[layerIndex]->SetType(type);

    this->editor->UpdateResourceProperties(this->script);
}
