#-------------------------------------------------
#
# Project created by QtCreator 2014-04-02T20:00:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app


SOURCES += Source/main.cpp \
     Source/mainwindow.cpp \
    Source/EditorTools/EditorUtils.cpp \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetColorAlpha.cpp \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetColorRgb.cpp \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetColor.cpp \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetLinkButton.cpp \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetLinkRecall.cpp \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetLink.cpp \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetInt.cpp \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetBool.cpp \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetFloat.cpp \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidget.cpp \
    Source/EditorTools/ResourceSelectionHistory.cpp \
    Source/QMwWidgets/QMwStructuresWidget.cpp \
    Source/QMwWidgets/QMwResourcePropertiesWidget.cpp \
    Source/QMwWidgets/QMwPropertiesResourceWidget.cpp \
    Source/QMwWidgets/QMwResourcesWidget.cpp \
    Source/QMwWidgets/QMwResourceItemWidget.cpp \
    Source/QMwWidgets/QMwResourceItemButtonWidget.cpp \
    Source/QMwWidgets/QMwRenderWidget.cpp \
    Source/QMwWidgets/QMwEditorWidget.cpp \
    Source/QMwWidgets/QMwMaterialLayersWidget.cpp \
    Source/QMwWidgets/QMwTransformLayersWidget.cpp \
    Source/QMwWidgets/QMwScriptCodeWidget.cpp \
    Source/QMwWidgets/QMwScriptPropertiesWidget.cpp

HEADERS  += Source/mainwindow.h \
    Source/EditorTools/EditorUtils.h \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetColorAlpha.h \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetColorRgb.h \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetColor.h \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetLinkButton.h \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetLinkRecall.h \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetLink.h \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetInt.h \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetBool.h \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetFloat.h \
    Source/QMwWidgets/ParameterWidgets/QMwParameterWidget.h \
    Source/EditorTools/ResourceSelectionHistory.h \
    Source/QMwWidgets/QMwStructuresWidget.h \
    Source/QMwWidgets/QMwResourcePropertiesWidget.h \
    Source/MeshworkEngine.h \
    Source/QMwWidgets/QMwPropertiesResourceWidget.h \
    Source/QMwWidgets/QMwResourcesWidget.h \
    Source/QMwWidgets/QMwResourceItemWidget.h \
    Source/QMwWidgets/QMwResourceItemButtonWidget.h \
    Source/QMwWidgets/QMwRenderWidget.h \
    Source/QMwWidgets/IMwEditor.h \
    Source/QMwWidgets/QMwEditorWidget.h \
    Source/QMwWidgets/QMwMaterialLayersWidget.h \
    Source/QMwWidgets/QMwTransformLayersWidget.h \
    Source/QMwWidgets/QMwScriptCodeWidget.h \
    Source/QMwWidgets/QMwScriptPropertiesWidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Engine/release/ -lMeshwork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Engine/debug/ -lMeshwork
else:unix: LIBS += -L$$PWD/../../Engine/ -lMeshwork
