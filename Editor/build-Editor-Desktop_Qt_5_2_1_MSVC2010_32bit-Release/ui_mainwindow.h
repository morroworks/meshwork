/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QMwWidgets/QMwMaterialLayersWidget.h"
#include "QMwWidgets/QMwPropertiesResourceWidget.h"
#include "QMwWidgets/QMwRenderWidget.h"
#include "QMwWidgets/QMwResourcesWidget.h"
#include "QMwWidgets/QMwScriptCodeWidget.h"
#include "QMwWidgets/QMwScriptPropertiesWidget.h"
#include "QMwWidgets/QMwStructuresWidget.h"
#include "QMwWidgets/QMwTransformLayersWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionImport;
    QAction *actionNew;
    QAction *actionMeshwork_Soras;
    QAction *actionOpen_GL;
    QAction *actionComponent_priorities;
    QAction *actionResources;
    QAction *actionProperties;
    QAction *actionStructure;
    QAction *actionCreate_Material;
    QAction *actionLinear;
    QAction *actionFloat;
    QAction *actionNegate_float;
    QAction *actionLinear_interpolation;
    QAction *actionSine;
    QAction *actionPivotal;
    QAction *actionOrientation;
    QAction *actionOrientation_lag;
    QAction *actionCreate_Sound_Emitter;
    QAction *actionCreate_Sound_Receptor;
    QAction *actionCreate_Light;
    QAction *actionCreate_Camera;
    QAction *actionCreate_Transform;
    QAction *actionTime_rate;
    QAction *actionScreen_Plane;
    QAction *actionFrom_File_Texture;
    QAction *actionEmpty_Texture;
    QAction *actionFrom_File_Sound;
    QAction *actionEmpty_Sound;
    QAction *actionFrom_Height_Map;
    QAction *actionCreate_Script;
    QAction *actionPlane;
    QAction *actionOnlineDocumentation;
    QAction *actionAbout;
    QAction *actionHome_Page;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QGridLayout *gridLayout_5;
    QPushButton *bSelect;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *bTranslate;
    QPushButton *bRotate;
    QPushButton *bScale;
    QPushButton *bFly;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *bX;
    QPushButton *bY;
    QPushButton *bZ;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *bPlayPause;
    QDoubleSpinBox *sbPlaySpeed;
    QSlider *horizontalSlider;
    QLabel *lTickOutTime;
    QMwRenderWidget *wRender;
    QMenuBar *menuBar;
    QMenu *menuMeshwork;
    QMenu *menuSettings;
    QMenu *menuGraphics_Device;
    QMenu *menuAudio_Device;
    QMenu *menuWindows;
    QMenu *menuEntities;
    QMenu *menuCreate_Mechanism;
    QMenu *menuCreate_Mesh;
    QMenu *menuImport_Texture;
    QMenu *menuImpot_Sound;
    QMenu *menuHelp;
    QDockWidget *dwResources;
    QWidget *dockWidgetContents_6;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_4;
    QMwResourcesWidget *wResources;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *bBack;
    QPushButton *bForward;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *bCamera;
    QPushButton *bTransform;
    QPushButton *bMaterial;
    QPushButton *bMesh;
    QPushButton *bTexture;
    QPushButton *bMechanism;
    QPushButton *bLight;
    QPushButton *bPath;
    QPushButton *bScript;
    QPushButton *bSound;
    QPushButton *bSoundEmitter;
    QPushButton *bSoundReceptor;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *eFilterResource;
    QHBoxLayout *horizontalLayout;
    QPushButton *bNewResource;
    QPushButton *bDeleteResource;
    QDockWidget *dwProperties;
    QWidget *dockWidgetContents_7;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *tabProperties;
    QGridLayout *gridLayout_8;
    QScrollArea *scrollAreaProperties;
    QWidget *scrollAreaLayoutProperties;
    QGridLayout *gridLayout_7;
    QSpacerItem *verticalSpacer;
    QMwPropertiesResourceWidget *wProperties;
    QWidget *tabMaterial;
    QGridLayout *gridLayout_9;
    QScrollArea *scrollAreaMaterial;
    QWidget *scrollAreaLayoutMaterial;
    QGridLayout *gridLayout_10;
    QSpacerItem *verticalSpacer_2;
    QMwMaterialLayersWidget *wMaterialProperties;
    QWidget *tabTransform;
    QGridLayout *gridLayout_11;
    QScrollArea *scrollAreaTransform;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_12;
    QSpacerItem *verticalSpacer_3;
    QMwTransformLayersWidget *wTransformProperties;
    QWidget *tabScriptProperties;
    QGridLayout *gridLayout_15;
    QScrollArea *scrollAreaScriptProperties;
    QWidget *scrollAreaWidgetContents_4;
    QGridLayout *gridLayout_16;
    QMwScriptPropertiesWidget *wScriptProperties;
    QSpacerItem *verticalSpacer_4;
    QWidget *tabScriptCode;
    QGridLayout *gridLayout_13;
    QScrollArea *scrollAreaScriptCode;
    QWidget *scrollAreaWidgetContents_3;
    QGridLayout *gridLayout_14;
    QMwScriptCodeWidget *wScriptCode;
    QDockWidget *dwStructure;
    QWidget *dockWidgetContents_8;
    QGridLayout *gridLayout_6;
    QMwStructuresWidget *twStructure;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 640);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/Icons/Other/Main Icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionImport = new QAction(MainWindow);
        actionImport->setObjectName(QStringLiteral("actionImport"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionMeshwork_Soras = new QAction(MainWindow);
        actionMeshwork_Soras->setObjectName(QStringLiteral("actionMeshwork_Soras"));
        actionOpen_GL = new QAction(MainWindow);
        actionOpen_GL->setObjectName(QStringLiteral("actionOpen_GL"));
        actionOpen_GL->setChecked(false);
        actionComponent_priorities = new QAction(MainWindow);
        actionComponent_priorities->setObjectName(QStringLiteral("actionComponent_priorities"));
        actionResources = new QAction(MainWindow);
        actionResources->setObjectName(QStringLiteral("actionResources"));
        actionResources->setCheckable(true);
        actionProperties = new QAction(MainWindow);
        actionProperties->setObjectName(QStringLiteral("actionProperties"));
        actionProperties->setCheckable(true);
        actionStructure = new QAction(MainWindow);
        actionStructure->setObjectName(QStringLiteral("actionStructure"));
        actionStructure->setCheckable(true);
        actionCreate_Material = new QAction(MainWindow);
        actionCreate_Material->setObjectName(QStringLiteral("actionCreate_Material"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/Icons/Resources/Material.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Material->setIcon(icon1);
        actionLinear = new QAction(MainWindow);
        actionLinear->setObjectName(QStringLiteral("actionLinear"));
        actionFloat = new QAction(MainWindow);
        actionFloat->setObjectName(QStringLiteral("actionFloat"));
        actionNegate_float = new QAction(MainWindow);
        actionNegate_float->setObjectName(QStringLiteral("actionNegate_float"));
        actionLinear_interpolation = new QAction(MainWindow);
        actionLinear_interpolation->setObjectName(QStringLiteral("actionLinear_interpolation"));
        actionSine = new QAction(MainWindow);
        actionSine->setObjectName(QStringLiteral("actionSine"));
        actionPivotal = new QAction(MainWindow);
        actionPivotal->setObjectName(QStringLiteral("actionPivotal"));
        actionOrientation = new QAction(MainWindow);
        actionOrientation->setObjectName(QStringLiteral("actionOrientation"));
        actionOrientation_lag = new QAction(MainWindow);
        actionOrientation_lag->setObjectName(QStringLiteral("actionOrientation_lag"));
        actionCreate_Sound_Emitter = new QAction(MainWindow);
        actionCreate_Sound_Emitter->setObjectName(QStringLiteral("actionCreate_Sound_Emitter"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Icons/Icons/Resources/SoundEmitter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Sound_Emitter->setIcon(icon2);
        actionCreate_Sound_Receptor = new QAction(MainWindow);
        actionCreate_Sound_Receptor->setObjectName(QStringLiteral("actionCreate_Sound_Receptor"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Icons/Icons/Resources/SoundReceptor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Sound_Receptor->setIcon(icon3);
        actionCreate_Light = new QAction(MainWindow);
        actionCreate_Light->setObjectName(QStringLiteral("actionCreate_Light"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Icons/Icons/Resources/Light.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Light->setIcon(icon4);
        actionCreate_Camera = new QAction(MainWindow);
        actionCreate_Camera->setObjectName(QStringLiteral("actionCreate_Camera"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Icons/Icons/Resources/Camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Camera->setIcon(icon5);
        actionCreate_Transform = new QAction(MainWindow);
        actionCreate_Transform->setObjectName(QStringLiteral("actionCreate_Transform"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Icons/Icons/Resources/Transform.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Transform->setIcon(icon6);
        actionTime_rate = new QAction(MainWindow);
        actionTime_rate->setObjectName(QStringLiteral("actionTime_rate"));
        actionScreen_Plane = new QAction(MainWindow);
        actionScreen_Plane->setObjectName(QStringLiteral("actionScreen_Plane"));
        actionFrom_File_Texture = new QAction(MainWindow);
        actionFrom_File_Texture->setObjectName(QStringLiteral("actionFrom_File_Texture"));
        actionEmpty_Texture = new QAction(MainWindow);
        actionEmpty_Texture->setObjectName(QStringLiteral("actionEmpty_Texture"));
        actionFrom_File_Sound = new QAction(MainWindow);
        actionFrom_File_Sound->setObjectName(QStringLiteral("actionFrom_File_Sound"));
        actionEmpty_Sound = new QAction(MainWindow);
        actionEmpty_Sound->setObjectName(QStringLiteral("actionEmpty_Sound"));
        actionFrom_Height_Map = new QAction(MainWindow);
        actionFrom_Height_Map->setObjectName(QStringLiteral("actionFrom_Height_Map"));
        actionCreate_Script = new QAction(MainWindow);
        actionCreate_Script->setObjectName(QStringLiteral("actionCreate_Script"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Icons/Icons/Resources/Script.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Script->setIcon(icon7);
        actionPlane = new QAction(MainWindow);
        actionPlane->setObjectName(QStringLiteral("actionPlane"));
        actionOnlineDocumentation = new QAction(MainWindow);
        actionOnlineDocumentation->setObjectName(QStringLiteral("actionOnlineDocumentation"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionHome_Page = new QAction(MainWindow);
        actionHome_Page->setObjectName(QStringLiteral("actionHome_Page"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setMinimumSize(QSize(0, 30));
        widget_2->setBaseSize(QSize(0, 0));
        gridLayout_5 = new QGridLayout(widget_2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setHorizontalSpacing(12);
        gridLayout_5->setContentsMargins(10, 0, 10, 0);
        bSelect = new QPushButton(widget_2);
        bSelect->setObjectName(QStringLiteral("bSelect"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Icons/Icons/Manipulate/Select.png"), QSize(), QIcon::Normal, QIcon::Off);
        bSelect->setIcon(icon8);
        bSelect->setIconSize(QSize(20, 20));
        bSelect->setCheckable(true);
        bSelect->setAutoExclusive(true);
        bSelect->setDefault(false);
        bSelect->setFlat(false);

        gridLayout_5->addWidget(bSelect, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 1, 10, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        bTranslate = new QPushButton(widget_2);
        bTranslate->setObjectName(QStringLiteral("bTranslate"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/Icons/Icons/Manipulate/Translate.png"), QSize(), QIcon::Normal, QIcon::Off);
        bTranslate->setIcon(icon9);
        bTranslate->setIconSize(QSize(20, 20));
        bTranslate->setCheckable(true);
        bTranslate->setAutoExclusive(true);

        horizontalLayout_6->addWidget(bTranslate);

        bRotate = new QPushButton(widget_2);
        bRotate->setObjectName(QStringLiteral("bRotate"));
        bRotate->setMouseTracking(false);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/Icons/Icons/Manipulate/Rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        bRotate->setIcon(icon10);
        bRotate->setIconSize(QSize(20, 20));
        bRotate->setCheckable(true);
        bRotate->setAutoExclusive(true);
        bRotate->setFlat(false);

        horizontalLayout_6->addWidget(bRotate);

        bScale = new QPushButton(widget_2);
        bScale->setObjectName(QStringLiteral("bScale"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/Icons/Icons/Manipulate/Scale.png"), QSize(), QIcon::Normal, QIcon::Off);
        bScale->setIcon(icon11);
        bScale->setIconSize(QSize(20, 20));
        bScale->setCheckable(true);
        bScale->setAutoExclusive(true);

        horizontalLayout_6->addWidget(bScale);

        bFly = new QPushButton(widget_2);
        bFly->setObjectName(QStringLiteral("bFly"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/Icons/Icons/Manipulate/Fly.png"), QSize(), QIcon::Normal, QIcon::Off);
        bFly->setIcon(icon12);
        bFly->setIconSize(QSize(20, 20));
        bFly->setCheckable(true);
        bFly->setAutoExclusive(true);

        horizontalLayout_6->addWidget(bFly);


        gridLayout_5->addLayout(horizontalLayout_6, 1, 5, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(2);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        bX = new QPushButton(widget_2);
        bX->setObjectName(QStringLiteral("bX"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/Icons/Icons/Manipulate/X.png"), QSize(), QIcon::Normal, QIcon::Off);
        bX->setIcon(icon13);
        bX->setIconSize(QSize(20, 20));
        bX->setCheckable(true);

        horizontalLayout_7->addWidget(bX);

        bY = new QPushButton(widget_2);
        bY->setObjectName(QStringLiteral("bY"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/Icons/Icons/Manipulate/Y.png"), QSize(), QIcon::Normal, QIcon::Off);
        bY->setIcon(icon14);
        bY->setIconSize(QSize(20, 20));
        bY->setCheckable(true);

        horizontalLayout_7->addWidget(bY);

        bZ = new QPushButton(widget_2);
        bZ->setObjectName(QStringLiteral("bZ"));
        sizePolicy.setHeightForWidth(bZ->sizePolicy().hasHeightForWidth());
        bZ->setSizePolicy(sizePolicy);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/Icons/Icons/Manipulate/Z.png"), QSize(), QIcon::Normal, QIcon::Off);
        bZ->setIcon(icon15);
        bZ->setIconSize(QSize(20, 20));
        bZ->setCheckable(true);

        horizontalLayout_7->addWidget(bZ);


        gridLayout_5->addLayout(horizontalLayout_7, 1, 6, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(2);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        bPlayPause = new QPushButton(widget_2);
        bPlayPause->setObjectName(QStringLiteral("bPlayPause"));
        bPlayPause->setMouseTracking(false);
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/Icons/Icons/Manipulate/Pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        bPlayPause->setIcon(icon16);
        bPlayPause->setIconSize(QSize(20, 20));
        bPlayPause->setFlat(false);

        horizontalLayout_8->addWidget(bPlayPause);

        sbPlaySpeed = new QDoubleSpinBox(widget_2);
        sbPlaySpeed->setObjectName(QStringLiteral("sbPlaySpeed"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sbPlaySpeed->sizePolicy().hasHeightForWidth());
        sbPlaySpeed->setSizePolicy(sizePolicy1);
        sbPlaySpeed->setDecimals(3);
        sbPlaySpeed->setValue(1);

        horizontalLayout_8->addWidget(sbPlaySpeed);

        horizontalSlider = new QSlider(widget_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy2);
        horizontalSlider->setMinimumSize(QSize(150, 0));
        horizontalSlider->setMinimum(-100);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(horizontalSlider);

        lTickOutTime = new QLabel(widget_2);
        lTickOutTime->setObjectName(QStringLiteral("lTickOutTime"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lTickOutTime->sizePolicy().hasHeightForWidth());
        lTickOutTime->setSizePolicy(sizePolicy3);
        lTickOutTime->setMinimumSize(QSize(40, 0));

        horizontalLayout_8->addWidget(lTickOutTime);


        gridLayout_5->addLayout(horizontalLayout_8, 1, 11, 1, 1);


        verticalLayout->addWidget(widget_2);

        wRender = new QMwRenderWidget(centralWidget);
        wRender->setObjectName(QStringLiteral("wRender"));
        wRender->setAcceptDrops(true);

        verticalLayout->addWidget(wRender);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        menuMeshwork = new QMenu(menuBar);
        menuMeshwork->setObjectName(QStringLiteral("menuMeshwork"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuGraphics_Device = new QMenu(menuSettings);
        menuGraphics_Device->setObjectName(QStringLiteral("menuGraphics_Device"));
        menuGraphics_Device->setToolTipsVisible(true);
        menuAudio_Device = new QMenu(menuSettings);
        menuAudio_Device->setObjectName(QStringLiteral("menuAudio_Device"));
        menuAudio_Device->setToolTipsVisible(true);
        menuWindows = new QMenu(menuBar);
        menuWindows->setObjectName(QStringLiteral("menuWindows"));
        menuEntities = new QMenu(menuBar);
        menuEntities->setObjectName(QStringLiteral("menuEntities"));
        menuCreate_Mechanism = new QMenu(menuEntities);
        menuCreate_Mechanism->setObjectName(QStringLiteral("menuCreate_Mechanism"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/Icons/Icons/Resources/Mechanism.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuCreate_Mechanism->setIcon(icon17);
        menuCreate_Mesh = new QMenu(menuEntities);
        menuCreate_Mesh->setObjectName(QStringLiteral("menuCreate_Mesh"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/Icons/Icons/Resources/Mesh.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuCreate_Mesh->setIcon(icon18);
        menuImport_Texture = new QMenu(menuEntities);
        menuImport_Texture->setObjectName(QStringLiteral("menuImport_Texture"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/Icons/Icons/Resources/Texture.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuImport_Texture->setIcon(icon19);
        menuImpot_Sound = new QMenu(menuEntities);
        menuImpot_Sound->setObjectName(QStringLiteral("menuImpot_Sound"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/Icons/Icons/Resources/Sound.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuImpot_Sound->setIcon(icon20);
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        dwResources = new QDockWidget(MainWindow);
        dwResources->setObjectName(QStringLiteral("dwResources"));
        dwResources->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetVerticalTitleBar);
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QStringLiteral("dockWidgetContents_6"));
        gridLayout = new QGridLayout(dockWidgetContents_6);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        scrollArea_2 = new QScrollArea(dockWidgetContents_6);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 998, 69));
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        wResources = new QMwResourcesWidget(scrollAreaWidgetContents_2);
        wResources->setObjectName(QStringLiteral("wResources"));

        gridLayout_4->addWidget(wResources, 0, 0, 1, 1);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_2->addWidget(scrollArea_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(12);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, -1, 10, -1);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        bBack = new QPushButton(dockWidgetContents_6);
        bBack->setObjectName(QStringLiteral("bBack"));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/Icons/Icons/Manipulate/BackArrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        bBack->setIcon(icon21);
        bBack->setIconSize(QSize(20, 20));
        bBack->setCheckable(false);
        bBack->setAutoExclusive(false);

        horizontalLayout_5->addWidget(bBack);

        bForward = new QPushButton(dockWidgetContents_6);
        bForward->setObjectName(QStringLiteral("bForward"));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/Icons/Icons/Manipulate/ForwardArrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        bForward->setIcon(icon22);
        bForward->setIconSize(QSize(20, 20));
        bForward->setCheckable(false);
        bForward->setAutoExclusive(false);

        horizontalLayout_5->addWidget(bForward);


        horizontalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        bCamera = new QPushButton(dockWidgetContents_6);
        bCamera->setObjectName(QStringLiteral("bCamera"));
        bCamera->setIcon(icon5);
        bCamera->setIconSize(QSize(20, 20));
        bCamera->setCheckable(true);
        bCamera->setAutoExclusive(true);
        bCamera->setProperty("MwResourceType", QVariant(1));

        horizontalLayout_3->addWidget(bCamera);

        bTransform = new QPushButton(dockWidgetContents_6);
        bTransform->setObjectName(QStringLiteral("bTransform"));
        bTransform->setIcon(icon6);
        bTransform->setIconSize(QSize(20, 20));
        bTransform->setCheckable(true);
        bTransform->setAutoExclusive(true);
        bTransform->setProperty("MwResourceType", QVariant(2));

        horizontalLayout_3->addWidget(bTransform);

        bMaterial = new QPushButton(dockWidgetContents_6);
        bMaterial->setObjectName(QStringLiteral("bMaterial"));
        bMaterial->setIcon(icon1);
        bMaterial->setIconSize(QSize(20, 20));
        bMaterial->setCheckable(true);
        bMaterial->setAutoExclusive(true);
        bMaterial->setProperty("MwResourceType", QVariant(3));

        horizontalLayout_3->addWidget(bMaterial);

        bMesh = new QPushButton(dockWidgetContents_6);
        bMesh->setObjectName(QStringLiteral("bMesh"));
        bMesh->setIcon(icon18);
        bMesh->setIconSize(QSize(20, 20));
        bMesh->setCheckable(true);
        bMesh->setAutoExclusive(true);
        bMesh->setProperty("MwResourceType", QVariant(4));

        horizontalLayout_3->addWidget(bMesh);

        bTexture = new QPushButton(dockWidgetContents_6);
        bTexture->setObjectName(QStringLiteral("bTexture"));
        bTexture->setIcon(icon19);
        bTexture->setIconSize(QSize(20, 20));
        bTexture->setCheckable(true);
        bTexture->setAutoExclusive(true);
        bTexture->setProperty("MwResourceType", QVariant(6));

        horizontalLayout_3->addWidget(bTexture);

        bMechanism = new QPushButton(dockWidgetContents_6);
        bMechanism->setObjectName(QStringLiteral("bMechanism"));
        bMechanism->setIcon(icon17);
        bMechanism->setIconSize(QSize(20, 20));
        bMechanism->setCheckable(true);
        bMechanism->setAutoExclusive(true);
        bMechanism->setProperty("MwResourceType", QVariant(8));

        horizontalLayout_3->addWidget(bMechanism);

        bLight = new QPushButton(dockWidgetContents_6);
        bLight->setObjectName(QStringLiteral("bLight"));
        bLight->setIcon(icon4);
        bLight->setIconSize(QSize(20, 20));
        bLight->setCheckable(true);
        bLight->setAutoExclusive(true);
        bLight->setProperty("MwResourceType", QVariant(9));

        horizontalLayout_3->addWidget(bLight);

        bPath = new QPushButton(dockWidgetContents_6);
        bPath->setObjectName(QStringLiteral("bPath"));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/Icons/Icons/Resources/Path.png"), QSize(), QIcon::Normal, QIcon::Off);
        bPath->setIcon(icon23);
        bPath->setIconSize(QSize(20, 20));
        bPath->setCheckable(true);
        bPath->setAutoExclusive(true);

        horizontalLayout_3->addWidget(bPath);

        bScript = new QPushButton(dockWidgetContents_6);
        bScript->setObjectName(QStringLiteral("bScript"));
        bScript->setIcon(icon7);
        bScript->setIconSize(QSize(20, 20));
        bScript->setCheckable(true);
        bScript->setAutoExclusive(true);
        bScript->setProperty("MwResourceType", QVariant(13));

        horizontalLayout_3->addWidget(bScript);

        bSound = new QPushButton(dockWidgetContents_6);
        bSound->setObjectName(QStringLiteral("bSound"));
        bSound->setIcon(icon20);
        bSound->setIconSize(QSize(20, 20));
        bSound->setCheckable(true);
        bSound->setAutoExclusive(true);
        bSound->setProperty("MwResourceType", QVariant(10));

        horizontalLayout_3->addWidget(bSound);

        bSoundEmitter = new QPushButton(dockWidgetContents_6);
        bSoundEmitter->setObjectName(QStringLiteral("bSoundEmitter"));
        bSoundEmitter->setIcon(icon2);
        bSoundEmitter->setIconSize(QSize(20, 20));
        bSoundEmitter->setCheckable(true);
        bSoundEmitter->setAutoExclusive(true);
        bSoundEmitter->setProperty("MwResourceType", QVariant(11));

        horizontalLayout_3->addWidget(bSoundEmitter);

        bSoundReceptor = new QPushButton(dockWidgetContents_6);
        bSoundReceptor->setObjectName(QStringLiteral("bSoundReceptor"));
        bSoundReceptor->setIcon(icon3);
        bSoundReceptor->setIconSize(QSize(20, 20));
        bSoundReceptor->setCheckable(true);
        bSoundReceptor->setAutoExclusive(true);
        bSoundReceptor->setProperty("MwResourceType", QVariant(12));

        horizontalLayout_3->addWidget(bSoundReceptor);


        horizontalLayout_2->addLayout(horizontalLayout_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(dockWidgetContents_6);
        label->setObjectName(QStringLiteral("label"));
        label->setMargin(0);

        horizontalLayout_4->addWidget(label);

        eFilterResource = new QLineEdit(dockWidgetContents_6);
        eFilterResource->setObjectName(QStringLiteral("eFilterResource"));

        horizontalLayout_4->addWidget(eFilterResource);


        horizontalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        bNewResource = new QPushButton(dockWidgetContents_6);
        bNewResource->setObjectName(QStringLiteral("bNewResource"));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/Icons/Icons/Manipulate/New.png"), QSize(), QIcon::Normal, QIcon::Off);
        bNewResource->setIcon(icon24);
        bNewResource->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(bNewResource);

        bDeleteResource = new QPushButton(dockWidgetContents_6);
        bDeleteResource->setObjectName(QStringLiteral("bDeleteResource"));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/Icons/Icons/Manipulate/Delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        bDeleteResource->setIcon(icon25);
        bDeleteResource->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(bDeleteResource);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        dwResources->setWidget(dockWidgetContents_6);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(4), dwResources);
        dwProperties = new QDockWidget(MainWindow);
        dwProperties->setObjectName(QStringLiteral("dwProperties"));
        dwProperties->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_7 = new QWidget();
        dockWidgetContents_7->setObjectName(QStringLiteral("dockWidgetContents_7"));
        gridLayout_3 = new QGridLayout(dockWidgetContents_7);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(dockWidgetContents_7);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabProperties = new QWidget();
        tabProperties->setObjectName(QStringLiteral("tabProperties"));
        gridLayout_8 = new QGridLayout(tabProperties);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        scrollAreaProperties = new QScrollArea(tabProperties);
        scrollAreaProperties->setObjectName(QStringLiteral("scrollAreaProperties"));
        scrollAreaProperties->setWidgetResizable(true);
        scrollAreaLayoutProperties = new QWidget();
        scrollAreaLayoutProperties->setObjectName(QStringLiteral("scrollAreaLayoutProperties"));
        scrollAreaLayoutProperties->setGeometry(QRect(0, 0, 188, 460));
        gridLayout_7 = new QGridLayout(scrollAreaLayoutProperties);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer, 1, 0, 1, 1);

        wProperties = new QMwPropertiesResourceWidget(scrollAreaLayoutProperties);
        wProperties->setObjectName(QStringLiteral("wProperties"));

        gridLayout_7->addWidget(wProperties, 0, 0, 1, 1);

        scrollAreaProperties->setWidget(scrollAreaLayoutProperties);

        gridLayout_8->addWidget(scrollAreaProperties, 0, 0, 1, 1);

        QIcon icon26;
        icon26.addFile(QStringLiteral(":/Icons/Icons/Other/Properties.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabProperties, icon26, QString());
        tabMaterial = new QWidget();
        tabMaterial->setObjectName(QStringLiteral("tabMaterial"));
        gridLayout_9 = new QGridLayout(tabMaterial);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        scrollAreaMaterial = new QScrollArea(tabMaterial);
        scrollAreaMaterial->setObjectName(QStringLiteral("scrollAreaMaterial"));
        scrollAreaMaterial->setWidgetResizable(true);
        scrollAreaLayoutMaterial = new QWidget();
        scrollAreaLayoutMaterial->setObjectName(QStringLiteral("scrollAreaLayoutMaterial"));
        scrollAreaLayoutMaterial->setGeometry(QRect(0, 0, 188, 460));
        gridLayout_10 = new QGridLayout(scrollAreaLayoutMaterial);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 352, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_2, 1, 0, 1, 1);

        wMaterialProperties = new QMwMaterialLayersWidget(scrollAreaLayoutMaterial);
        wMaterialProperties->setObjectName(QStringLiteral("wMaterialProperties"));

        gridLayout_10->addWidget(wMaterialProperties, 0, 0, 1, 1);

        scrollAreaMaterial->setWidget(scrollAreaLayoutMaterial);

        gridLayout_9->addWidget(scrollAreaMaterial, 0, 0, 1, 1);

        tabWidget->addTab(tabMaterial, icon1, QString());
        tabTransform = new QWidget();
        tabTransform->setObjectName(QStringLiteral("tabTransform"));
        gridLayout_11 = new QGridLayout(tabTransform);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        scrollAreaTransform = new QScrollArea(tabTransform);
        scrollAreaTransform->setObjectName(QStringLiteral("scrollAreaTransform"));
        scrollAreaTransform->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 188, 460));
        gridLayout_12 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 352, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_12->addItem(verticalSpacer_3, 1, 0, 1, 1);

        wTransformProperties = new QMwTransformLayersWidget(scrollAreaWidgetContents);
        wTransformProperties->setObjectName(QStringLiteral("wTransformProperties"));

        gridLayout_12->addWidget(wTransformProperties, 0, 0, 1, 1);

        scrollAreaTransform->setWidget(scrollAreaWidgetContents);

        gridLayout_11->addWidget(scrollAreaTransform, 0, 0, 1, 1);

        tabWidget->addTab(tabTransform, icon6, QString());
        tabScriptProperties = new QWidget();
        tabScriptProperties->setObjectName(QStringLiteral("tabScriptProperties"));
        gridLayout_15 = new QGridLayout(tabScriptProperties);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_15->setContentsMargins(0, 0, 0, 0);
        scrollAreaScriptProperties = new QScrollArea(tabScriptProperties);
        scrollAreaScriptProperties->setObjectName(QStringLiteral("scrollAreaScriptProperties"));
        scrollAreaScriptProperties->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 188, 460));
        gridLayout_16 = new QGridLayout(scrollAreaWidgetContents_4);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        gridLayout_16->setContentsMargins(0, 0, 0, 0);
        wScriptProperties = new QMwScriptPropertiesWidget(scrollAreaWidgetContents_4);
        wScriptProperties->setObjectName(QStringLiteral("wScriptProperties"));

        gridLayout_16->addWidget(wScriptProperties, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 352, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_16->addItem(verticalSpacer_4, 1, 0, 1, 1);

        scrollAreaScriptProperties->setWidget(scrollAreaWidgetContents_4);

        gridLayout_15->addWidget(scrollAreaScriptProperties, 0, 0, 1, 1);

        QIcon icon27;
        icon27.addFile(QStringLiteral(":/Icons/Icons/Other/ScriptProperties.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabScriptProperties, icon27, QString());
        tabScriptCode = new QWidget();
        tabScriptCode->setObjectName(QStringLiteral("tabScriptCode"));
        gridLayout_13 = new QGridLayout(tabScriptCode);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        gridLayout_13->setContentsMargins(0, 0, 0, 0);
        scrollAreaScriptCode = new QScrollArea(tabScriptCode);
        scrollAreaScriptCode->setObjectName(QStringLiteral("scrollAreaScriptCode"));
        scrollAreaScriptCode->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 188, 460));
        gridLayout_14 = new QGridLayout(scrollAreaWidgetContents_3);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        gridLayout_14->setContentsMargins(0, 0, 0, 0);
        wScriptCode = new QMwScriptCodeWidget(scrollAreaWidgetContents_3);
        wScriptCode->setObjectName(QStringLiteral("wScriptCode"));

        gridLayout_14->addWidget(wScriptCode, 0, 0, 1, 1);

        scrollAreaScriptCode->setWidget(scrollAreaWidgetContents_3);

        gridLayout_13->addWidget(scrollAreaScriptCode, 0, 0, 1, 1);

        tabWidget->addTab(tabScriptCode, icon7, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 1, 1);

        dwProperties->setWidget(dockWidgetContents_7);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dwProperties);
        dwStructure = new QDockWidget(MainWindow);
        dwStructure->setObjectName(QStringLiteral("dwStructure"));
        dwStructure->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_8 = new QWidget();
        dockWidgetContents_8->setObjectName(QStringLiteral("dockWidgetContents_8"));
        gridLayout_6 = new QGridLayout(dockWidgetContents_8);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        twStructure = new QMwStructuresWidget(dockWidgetContents_8);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        twStructure->setHeaderItem(__qtreewidgetitem);
        twStructure->setObjectName(QStringLiteral("twStructure"));
        twStructure->setAcceptDrops(true);
        twStructure->header()->setVisible(false);

        gridLayout_6->addWidget(twStructure, 0, 0, 1, 1);

        dwStructure->setWidget(dockWidgetContents_8);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dwStructure);

        menuBar->addAction(menuMeshwork->menuAction());
        menuBar->addAction(menuEntities->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuWindows->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuMeshwork->addAction(actionNew);
        menuMeshwork->addAction(actionOpen);
        menuMeshwork->addAction(actionSave);
        menuMeshwork->addSeparator();
        menuMeshwork->addAction(actionImport);
        menuSettings->addAction(menuGraphics_Device->menuAction());
        menuSettings->addAction(menuAudio_Device->menuAction());
        menuSettings->addAction(actionComponent_priorities);
        menuWindows->addAction(actionResources);
        menuWindows->addAction(actionProperties);
        menuWindows->addAction(actionStructure);
        menuEntities->addAction(actionCreate_Camera);
        menuEntities->addAction(actionCreate_Transform);
        menuEntities->addAction(actionCreate_Material);
        menuEntities->addAction(menuCreate_Mesh->menuAction());
        menuEntities->addAction(menuImport_Texture->menuAction());
        menuEntities->addAction(menuCreate_Mechanism->menuAction());
        menuEntities->addAction(actionCreate_Light);
        menuEntities->addAction(actionCreate_Script);
        menuEntities->addAction(menuImpot_Sound->menuAction());
        menuEntities->addAction(actionCreate_Sound_Emitter);
        menuEntities->addAction(actionCreate_Sound_Receptor);
        menuCreate_Mechanism->addAction(actionFloat);
        menuCreate_Mechanism->addAction(actionNegate_float);
        menuCreate_Mechanism->addAction(actionLinear);
        menuCreate_Mechanism->addAction(actionLinear_interpolation);
        menuCreate_Mechanism->addAction(actionSine);
        menuCreate_Mechanism->addAction(actionPivotal);
        menuCreate_Mechanism->addAction(actionOrientation);
        menuCreate_Mechanism->addAction(actionOrientation_lag);
        menuCreate_Mechanism->addAction(actionTime_rate);
        menuCreate_Mesh->addAction(actionScreen_Plane);
        menuCreate_Mesh->addAction(actionPlane);
        menuCreate_Mesh->addAction(actionFrom_Height_Map);
        menuImport_Texture->addAction(actionFrom_File_Texture);
        menuImport_Texture->addAction(actionEmpty_Texture);
        menuImpot_Sound->addAction(actionFrom_File_Sound);
        menuImpot_Sound->addAction(actionEmpty_Sound);
        menuHelp->addAction(actionOnlineDocumentation);
        menuHelp->addAction(actionHome_Page);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Meshwork", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save as", 0));
        actionImport->setText(QApplication::translate("MainWindow", "Import", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionMeshwork_Soras->setText(QApplication::translate("MainWindow", "Meshwork Soras", 0));
        actionOpen_GL->setText(QApplication::translate("MainWindow", "Open GL", 0));
        actionComponent_priorities->setText(QApplication::translate("MainWindow", "Component priorities", 0));
        actionResources->setText(QApplication::translate("MainWindow", "Resources", 0));
        actionResources->setProperty("windowName", QVariant(QApplication::translate("MainWindow", "dwResources", 0)));
        actionProperties->setText(QApplication::translate("MainWindow", "Properties", 0));
        actionProperties->setProperty("windowName", QVariant(QApplication::translate("MainWindow", "dwProperties", 0)));
        actionStructure->setText(QApplication::translate("MainWindow", "Structure", 0));
        actionStructure->setProperty("windowName", QVariant(QApplication::translate("MainWindow", "dwStructure", 0)));
        actionCreate_Material->setText(QApplication::translate("MainWindow", "Create Material", 0));
#ifndef QT_NO_TOOLTIP
        actionCreate_Material->setToolTip(QApplication::translate("MainWindow", "Creates a new empty Material. To customize it, manage its layers and set the properties they will create.", 0));
#endif // QT_NO_TOOLTIP
        actionLinear->setText(QApplication::translate("MainWindow", "Linear", 0));
        actionFloat->setText(QApplication::translate("MainWindow", "Float", 0));
        actionNegate_float->setText(QApplication::translate("MainWindow", "Negate float", 0));
        actionLinear_interpolation->setText(QApplication::translate("MainWindow", "Linear interpolation", 0));
        actionSine->setText(QApplication::translate("MainWindow", "Sine", 0));
        actionPivotal->setText(QApplication::translate("MainWindow", "Pivotal", 0));
        actionOrientation->setText(QApplication::translate("MainWindow", "Orientation", 0));
        actionOrientation_lag->setText(QApplication::translate("MainWindow", "Orientation lag", 0));
        actionCreate_Sound_Emitter->setText(QApplication::translate("MainWindow", "Create Sound Emitter", 0));
        actionCreate_Sound_Receptor->setText(QApplication::translate("MainWindow", "Create Sound Receptor", 0));
#ifndef QT_NO_TOOLTIP
        actionCreate_Sound_Receptor->setToolTip(QApplication::translate("MainWindow", "Creates a new Sound Receptor", 0));
#endif // QT_NO_TOOLTIP
        actionCreate_Light->setText(QApplication::translate("MainWindow", "Create Light", 0));
#ifndef QT_NO_TOOLTIP
        actionCreate_Light->setToolTip(QApplication::translate("MainWindow", "Creates a new Light with default settings", 0));
#endif // QT_NO_TOOLTIP
        actionCreate_Camera->setText(QApplication::translate("MainWindow", "Create Camera", 0));
#ifndef QT_NO_TOOLTIP
        actionCreate_Camera->setToolTip(QApplication::translate("MainWindow", "Creates a new Camera with default settings", 0));
#endif // QT_NO_TOOLTIP
        actionCreate_Transform->setText(QApplication::translate("MainWindow", "Create Transform", 0));
#ifndef QT_NO_TOOLTIP
        actionCreate_Transform->setToolTip(QApplication::translate("MainWindow", "Creates a new Transform. To add automated motion, manage its layers and set the properties they will create", 0));
#endif // QT_NO_TOOLTIP
        actionTime_rate->setText(QApplication::translate("MainWindow", "Time rate", 0));
        actionScreen_Plane->setText(QApplication::translate("MainWindow", "Screen Plane", 0));
        actionFrom_File_Texture->setText(QApplication::translate("MainWindow", "From File", 0));
        actionEmpty_Texture->setText(QApplication::translate("MainWindow", "Empty Texture", 0));
        actionFrom_File_Sound->setText(QApplication::translate("MainWindow", "From File", 0));
        actionEmpty_Sound->setText(QApplication::translate("MainWindow", "Empty Sound", 0));
        actionFrom_Height_Map->setText(QApplication::translate("MainWindow", "From Height Map", 0));
        actionCreate_Script->setText(QApplication::translate("MainWindow", "Create Script", 0));
        actionPlane->setText(QApplication::translate("MainWindow", "Plane", 0));
        actionOnlineDocumentation->setText(QApplication::translate("MainWindow", "Online Documentation", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionHome_Page->setText(QApplication::translate("MainWindow", "Home Page", 0));
#ifndef QT_NO_TOOLTIP
        bSelect->setToolTip(QApplication::translate("MainWindow", "Select", 0));
#endif // QT_NO_TOOLTIP
        bSelect->setText(QString());
#ifndef QT_NO_TOOLTIP
        bTranslate->setToolTip(QApplication::translate("MainWindow", "Move", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        bRotate->setToolTip(QApplication::translate("MainWindow", "Rotate", 0));
#endif // QT_NO_TOOLTIP
        bRotate->setText(QString());
#ifndef QT_NO_TOOLTIP
        bScale->setToolTip(QApplication::translate("MainWindow", "Scale", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        bFly->setToolTip(QApplication::translate("MainWindow", "Fly", 0));
#endif // QT_NO_TOOLTIP
        bX->setText(QString());
        bZ->setText(QString());
#ifndef QT_NO_TOOLTIP
        bPlayPause->setToolTip(QApplication::translate("MainWindow", "Rotate", 0));
#endif // QT_NO_TOOLTIP
        bPlayPause->setText(QString());
        lTickOutTime->setText(QApplication::translate("MainWindow", "0.0", 0));
        menuMeshwork->setTitle(QApplication::translate("MainWindow", "Scene", 0));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0));
        menuGraphics_Device->setTitle(QApplication::translate("MainWindow", "Graphics Device", 0));
        menuAudio_Device->setTitle(QApplication::translate("MainWindow", "Audio Device", 0));
        menuWindows->setTitle(QApplication::translate("MainWindow", "Windows", 0));
        menuEntities->setTitle(QApplication::translate("MainWindow", "Entities", 0));
        menuCreate_Mechanism->setTitle(QApplication::translate("MainWindow", "Create Mechanism", 0));
        menuCreate_Mesh->setTitle(QApplication::translate("MainWindow", "Create Mesh", 0));
        menuImport_Texture->setTitle(QApplication::translate("MainWindow", "Create Texture", 0));
        menuImpot_Sound->setTitle(QApplication::translate("MainWindow", "Create Sound", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        dwResources->setWindowTitle(QApplication::translate("MainWindow", "Resources", 0));
        bBack->setText(QString());
        bForward->setText(QString());
        bCamera->setText(QString());
        bTransform->setText(QString());
        bMaterial->setText(QString());
        bMesh->setText(QString());
        bTexture->setText(QString());
        bMechanism->setText(QString());
        bLight->setText(QString());
        bPath->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Filter", 0));
        bNewResource->setText(QString());
        bDeleteResource->setText(QString());
#ifndef QT_NO_TOOLTIP
        dwProperties->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        dwProperties->setWindowTitle(QApplication::translate("MainWindow", "Properties", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabProperties), QString());
        tabWidget->setTabText(tabWidget->indexOf(tabMaterial), QString());
        tabWidget->setTabText(tabWidget->indexOf(tabTransform), QString());
        tabWidget->setTabText(tabWidget->indexOf(tabScriptProperties), QString());
        tabWidget->setTabText(tabWidget->indexOf(tabScriptCode), QString());
        dwStructure->setWindowTitle(QApplication::translate("MainWindow", "Structure", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
