//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwScriptCodeWidget.h"

#include "../EditorTools/EditorUtils.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QPlainTextEdit>

QMwScriptCodeWidget::QMwScriptCodeWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Control panel with buttons
    QWidget *controlPanelWidget = new QWidget(this);
    QHBoxLayout *controlPanelLayout = new QHBoxLayout(controlPanelWidget);
    mainLayout->addWidget(controlPanelWidget);

    controlPanelLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton *buildButton = new QPushButton(controlPanelWidget);
    buildButton->setText("Build");
    QObject::connect(buildButton, SIGNAL(clicked()), this, SLOT(BuildClicked()));
    controlPanelLayout->addWidget(buildButton);

    QPushButton *runButton = new QPushButton(controlPanelWidget);
    runButton->setText("Run");
    QObject::connect(runButton, SIGNAL(clicked()), this, SLOT(RunClicked()));
    controlPanelLayout->addWidget(runButton);

    this->sourceCodeEdit = new QPlainTextEdit(this);
    this->sourceCodeEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    QSizePolicy sourceCodeSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sourceCodeSizePolicy.setVerticalStretch(5);
    this->sourceCodeEdit->setSizePolicy(sourceCodeSizePolicy);
    QObject::connect(this->sourceCodeEdit, SIGNAL(textChanged()), this, SLOT(SourceCodeChanged()));
    mainLayout->addWidget(this->sourceCodeEdit);

    this->compilationMessagesEdit = new QPlainTextEdit(this);
    this->compilationMessagesEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    QSizePolicy messagesSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    messagesSizePolicy.setVerticalStretch(1);
    this->compilationMessagesEdit->setSizePolicy(messagesSizePolicy);
    mainLayout->addWidget(this->compilationMessagesEdit);

    this->script = 0;
}

void QMwScriptCodeWidget::SetResource(MwBaseResource *resource)
{
    this->script = 0;

    if (resource != 0)
        if (resource->resourceType == MwResourceType_Script)
            this->script = (MwScript*)resource;

    if (this->script != 0)
        this->sourceCodeEdit->setPlainText(EditorUtils::MwToQString(this->script->sourceCode));
}

void QMwScriptCodeWidget::BuildClicked()
{
}

void QMwScriptCodeWidget::RunClicked()
{
    if (this->script == 0)
        return;

    this->script->RunCode();

    while (this->editor->GetMeshwork()->scriptProcessor.stackPos > 0)
    {
        int i = this->editor->GetMeshwork()->scriptProcessor.PopInt();
        this->compilationMessagesEdit->appendPlainText(QString("Stack:\t%0,\t%1").arg(QString::number(i), QString::number((double)(*(float*)&i))));
    }
}

void QMwScriptCodeWidget::SourceCodeChanged()
{
    if (this->script == 0)
        return;

    this->script->sourceCode = EditorUtils::QToMwString(this->sourceCodeEdit->toPlainText());
    this->script->CompileCode();

    if (this->script->successfullyCompiled)
        this->compilationMessagesEdit->setPlainText("Compilation Successful");
    else
        this->compilationMessagesEdit->setPlainText(QString("Error at \"%0\"").arg(EditorUtils::MwToQString(this->script->errorCode)));
}
