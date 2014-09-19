//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwResourceItemWidget.h"

#include "../EditorTools/EditorUtils.h"

QMwResourceItemWidget::QMwResourceItemWidget(QWidget *parent) :
    QWidget(parent)
{
    this->layout = new QVBoxLayout(this);
    this->layout->setContentsMargins(0, 0, 0, 0);

    this->button = new QMwResourceItemButtonWidget();
    this->button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->layout->addWidget(this->button);

    this->nameLabel = new QLabel();
    this->nameLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    this->nameLabel->setAlignment(Qt::AlignCenter);
    this->nameLabel->setWordWrap(true);
    this->layout->addWidget(this->nameLabel);
}

void QMwResourceItemWidget::SetEditorInterface(IMwEditor *editor)
{
    QMwEditorWidget::SetEditorInterface(editor);

    this->button->SetEditorInterface(editor);
}

void QMwResourceItemWidget::SetResource(MwBaseResource *resource)
{
    this->resource = resource;

    this->button->SetResource(resource);

    this->nameLabel->setText(EditorUtils::MwToQString(this->resource->name));
}
