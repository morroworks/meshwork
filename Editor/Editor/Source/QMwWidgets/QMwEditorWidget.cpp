//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "QMwEditorWidget.h"

QMwEditorWidget::QMwEditorWidget()
{
    this->editor = 0;
}

void QMwEditorWidget::SetEditorInterface(IMwEditor *editor)
{
    this->editor = editor;
}
