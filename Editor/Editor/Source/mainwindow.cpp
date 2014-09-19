//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "EditorTools/EditorUtils.h"

#include <QSettings>
#include <QFileDialog>
#include <QDrag>
#include <QMimeData>
#include <QPixmap>
#include <QDesktopServices>
#include <QMessageBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->paused = false;
    this->ui->sbPlaySpeed->setRange(-100.0, 100.0);
    this->lastTickout = 0.0f;
    this->tickOutMode = false;

    // Restore window, docking and toolbars states
    QSettings settings;
    this->restoreState(settings.value("mainWindowState").toByteArray());
    this->restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
    this->openSceneDir = settings.value("openSceneDir").toString();
    this->saveSceneDir = settings.value("saveSceneDir").toString();
    this->importSceneDir = settings.value("importSceneDir").toString();
    this->importImageDir = settings.value("importImageDir").toString();
    this->importSoundDir = settings.value("importSoundDir").toString();
    this->selectedGraphicsDevice = settings.value("selectedGraphicsDevice").toString();
    this->selectedAudioDevice = settings.value("selectedAudioDevice").toString();

    this->ui->actionProperties->setChecked(!this->ui->dwProperties->isHidden());
    this->ui->actionResources->setChecked(!this->ui->dwResources->isHidden());
    this->ui->actionStructure->setChecked(!this->ui->dwStructure->isHidden());

    // Initialize Meshwork Engine
    this->renderWindowHandle = this->ui->wRender->winId();
    this->meshwork = new Meshwork((void*)&this->renderWindowHandle);
#ifdef QT_DEBUG
    this->meshwork->LoadModules(MwFileSystem::MergePaths(MwOSUtils::GetApplicationPath(), MwString("..\\..\\..\\Engine\\Debug")));
#else
    this->meshwork->LoadModules(MwFileSystem::MergePaths(MwOSUtils::GetApplicationPath(), MwString("..\\..\\..\\Engine\\Release")));
#endif

    int selectedGraphicsDeviceIndex = this->meshwork->SetGraphicsDevice(EditorUtils::QToMwString(this->selectedGraphicsDevice));
    int selectedAudioDeviceIndex = this->meshwork->SetAudioDevice(EditorUtils::QToMwString(this->selectedAudioDevice));

    // Create a timer for the continuous rendering
    this->renderTimer = new QTimer(this);
    QObject::connect(this->renderTimer, SIGNAL(timeout()), this, SLOT(Render()));
    this->renderTimer->start(20);

    this->ui->wProperties->SetEditorInterface(this);
    this->ui->wResources->SetEditorInterface(this);
    this->ui->wRender->SetEditorInterface(this);
    this->ui->twStructure->SetEditorInterface(this);
    this->ui->wMaterialProperties->SetEditorInterface(this);
    this->ui->wTransformProperties->SetEditorInterface(this);
    this->ui->wScriptProperties->SetEditorInterface(this);
    this->ui->wScriptCode->SetEditorInterface(this);

    this->ui->wResources->SetItemSource(this->meshwork->resources);

    this->importSceneDialogFilter = this->CreateDialogFilesFilter(&this->meshwork->sceneMediaDispatchers, MwDispatcher::infoId_MediaDeserializationFormatExtension, true);
    this->exportSceneDialogFilter = this->CreateDialogFilesFilter(&this->meshwork->sceneMediaDispatchers, MwDispatcher::infoId_MediaSerializationFormatExtension, false);
    this->importImageDialogFilter = this->CreateDialogFilesFilter(&this->meshwork->imageMediaDispatchers, MwDispatcher::infoId_MediaDeserializationFormatExtension, true);
    this->importSoundDialogFilter = this->CreateDialogFilesFilter(&this->meshwork->soundMediaDispatchers, MwDispatcher::infoId_MediaDeserializationFormatExtension, true);

    this->CreateDevicesMenu(&this->meshwork->graphicsDeviceDispatchers, this->ui->menuGraphics_Device, SLOT(GraphicsDeviceMenuItemClicked()), selectedGraphicsDeviceIndex);
    this->CreateDevicesMenu(&this->meshwork->audioDeviceDispatchers, this->ui->menuAudio_Device, SLOT(AudioDeviceMenuItemClicked()), selectedAudioDeviceIndex);

    QObject::connect(this->ui->actionResources, SIGNAL(triggered()), this, SLOT(OnWindowVisibilityClicked()));
    QObject::connect(this->ui->actionProperties, SIGNAL(triggered()), this, SLOT(OnWindowVisibilityClicked()));
    QObject::connect(this->ui->actionStructure, SIGNAL(triggered()), this, SLOT(OnWindowVisibilityClicked()));

    QObject::connect(this->ui->bCamera, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));
    QObject::connect(this->ui->bTransform, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));
    QObject::connect(this->ui->bMesh, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));
    QObject::connect(this->ui->bMaterial, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));
    QObject::connect(this->ui->bTexture, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));
    QObject::connect(this->ui->bMechanism, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));
    QObject::connect(this->ui->bLight, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));
    QObject::connect(this->ui->bScript, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));
    QObject::connect(this->ui->bSound, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));
    QObject::connect(this->ui->bSoundEmitter, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));
    QObject::connect(this->ui->bSoundReceptor, SIGNAL(clicked()), this, SLOT(ResourceFilterButtonClicked()));

    this->selectedResource = 0;

    while (this->ui->tabWidget->count() > 1)
        this->ui->tabWidget->removeTab(1);
}

MainWindow::~MainWindow()
{
    this->renderTimer->stop();

    delete this->meshwork;

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    // Save window, docking and toolbars states
    QSettings settings;
    settings.setValue("mainWindowGeometry", this->saveGeometry());
    settings.setValue("mainWindowState", this->saveState());
    // Save working dirs
    settings.setValue("openSceneDir", this->openSceneDir);
    settings.setValue("saveSceneDir", this->saveSceneDir);
    settings.setValue("importSceneDir", this->importSceneDir);
    settings.setValue("importImageDir", this->importImageDir);
    settings.setValue("importSoundDir", this->importSoundDir);
    settings.setValue("selectedGraphicsDevice", this->selectedGraphicsDevice);
    settings.setValue("selectedAudioDevice", this->selectedAudioDevice);
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    if (e->isAutoRepeat())
        return;

    this->keysPressed.Add(e->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent* e)
{
    if (e->isAutoRepeat())
        return;

    this->keysPressed.RemoveAll(e->key());
}

QString MainWindow::CreateDialogFilesFilter(MwList<MwDispatcher*> *dispatchers, unsigned int infoId, bool addAllSupportedAndAny)
{
    // The filter has the format "Filter name1 (*.ext1 *.extN);;Filter nameN (*.ext1 *.extN)"
    MwStrings allUniqueExtensions;
    MwString result;
    int numDispatchers = dispatchers->count;
    for (int dispatcherIndex = 0; dispatcherIndex < numDispatchers; dispatcherIndex++)
    {
        MwString formatExtension;
        MwStrings formatExtensions;
        for (int formatIndex = 0; dispatchers->Get(dispatcherIndex)->GetInfo(infoId, formatIndex, formatExtension); formatIndex++)
        {
            formatExtension = formatExtension.ToLower();

            formatExtensions.Add(formatExtension);

            if (allUniqueExtensions.IndexOf(formatExtension) == -1)
                allUniqueExtensions.Add(formatExtension);
        }

        if (formatExtensions.count > 0)
        {
            if (result.length != 0)
                result += ";;";

            MwString dispatcherName;
            dispatchers->Get(dispatcherIndex)->GetInfo(MwDispatcher::infoId_Name, 0, dispatcherName);
            result += dispatcherName + " (*." + formatExtensions.ToString(" *.") + ")";
        }
    }

    if (addAllSupportedAndAny)
        if (result.length != 0)
            result = MwString("Supported Files (*.") + allUniqueExtensions.ToString(" *.") + ");;" + result + ";;All Files (*.*)";

    return EditorUtils::MwToQString(result);
}

template <typename Func> void MainWindow::CreateDevicesMenu(MwList<MwDispatcher*> *dispatchers, QMenu *menu, Func slot, int selectedIndex)
{
    QActionGroup *deviceSelectActionGroup = new QActionGroup(this);
    deviceSelectActionGroup->setExclusive(true);
    for (int i = 0; i < dispatchers->count; i++)
    {
        MwString deviceName, deviceDescription;
        dispatchers->Get(i)->GetInfo(MwDispatcher::infoId_Name, 0, deviceName);
        dispatchers->Get(i)->GetInfo(MwDispatcher::infoId_Description, 0, deviceDescription);

        QAction *action = new QAction(this);
        action->setText(EditorUtils::MwToQString(deviceName));
        action->setToolTip(EditorUtils::MwToQString(deviceDescription));
        action->setCheckable(true);
        action->setChecked(i == selectedIndex);
        action->setProperty("dispatcherIndex", QVariant::fromValue(i));

        deviceSelectActionGroup->addAction(action);

        QObject::connect(action, SIGNAL(triggered()), this, slot);

        menu->addAction(action);
    }
}

void MainWindow::UpdateEnvironment()
{
    this->ui->twStructure->BuildAnew(this->meshwork->root);
    this->ui->wResources->SetItemSource(this->meshwork->resources);
}

void MainWindow::ResetEnvironment()
{
    this->SelectResource(0);
    this->selectionHistory.Clear();

    this->UpdateEnvironment();
}

void MainWindow::SelectResource(MwBaseResource *resource)
{
    if (resource == this->selectedResource)
        return;

    bool differentResourceTypes = ((resource == 0) != (this->selectedResource == 0)) || ((resource != 0) && (this->selectedResource != 0) && (resource->typeId != this->selectedResource->typeId));

    this->selectedResource = resource;

    this->selectionHistory.PushHistory(this->selectedResource);

    this->ui->wProperties->SetResource(this->selectedResource);

    this->ui->wMaterialProperties->SetResource(this->selectedResource);
    this->ui->wTransformProperties->SetResource(this->selectedResource);
    this->ui->wScriptProperties->SetResource(this->selectedResource);
    this->ui->wScriptCode->SetResource(this->selectedResource);

    if (differentResourceTypes)
    {
        while (this->ui->tabWidget->count() > 1)
            this->ui->tabWidget->removeTab(1);

        if (this->selectedResource != 0)
        {
            QString iconName;
            EditorUtils::resourceTypeIcons.GetValue(this->selectedResource->resourceType, iconName);

            if (this->selectedResource->resourceType == MwResourceType_Material)
                this->ui->tabWidget->addTab(this->ui->tabMaterial, QIcon(iconName), "");
            else if (this->selectedResource->resourceType == MwResourceType_Transform)
                this->ui->tabWidget->addTab(this->ui->tabTransform, QIcon(iconName), "");
            else if (this->selectedResource->resourceType == MwResourceType_Script)
            {
                this->ui->tabWidget->addTab(this->ui->tabScriptProperties, QIcon(EditorUtils::iconScriptProperties), "");
                this->ui->tabWidget->addTab(this->ui->tabScriptCode, QIcon(iconName), "");
            }
        }
    }
}

void MainWindow::UpdateResourceName(MwBaseResource *resource)
{
    MwList<QTreeWidgetItem*> result;
    this->ui->twStructure->FindResourceItems(result, resource);
    for (int i = 0; i < result.count; i++)
    {
        QMwStructuresWidget::SetMwResourceToItem(result[i], resource);
    }
}

void MainWindow::UpdateResourceProperties(MwBaseResource *resource)
{
    if (resource == this->selectedResource)
    {
        this->ui->wProperties->SetResource(this->selectedResource);
    }
}

MwBaseResource *MainWindow::GetSelectedResource()
{
    return this->selectedResource;
}

void MainWindow::MouseDrag(int x, int y)
{
    if (this->selectedResource == 0)
        return;

    if (this->selectedResource->resourceType == MwResourceType_Transform)
    {
        MwTransform *transform = (MwTransform*)this->selectedResource;

        if (this->ui->bTranslate->isChecked())
        {
            MwMatrix m;
            MwVector3 translationVector;
            if (this->ui->bX->isChecked())
            {
                translationVector.x = x;
            }
            if (this->ui->bY->isChecked())
            {
                translationVector.y = y;
            }
            if (this->ui->bZ->isChecked())
            {
                translationVector.z = y;
            }
            MwMatrix::CreateTranslation(m, translationVector);
            MwMatrix::Multiply(((MwTransform*)this->selectedResource)->manual, ((MwTransform*)this->selectedResource)->manual, m);
        }

        else if (this->ui->bRotate->isChecked())
        {
            MwMatrix m;
            if (this->ui->bX->isChecked())
            {
                MwMatrix::CreateRotationX(m, y / 500.0f);
                MwMatrix::Multiply(((MwTransform*)this->selectedResource)->manual, ((MwTransform*)this->selectedResource)->manual, m);
            }
            if (this->ui->bY->isChecked())
            {
                MwMatrix::CreateRotationY(m, x / 500.0f);
                MwMatrix::Multiply(((MwTransform*)this->selectedResource)->manual, ((MwTransform*)this->selectedResource)->manual, m);
            }
            if (this->ui->bZ->isChecked())
            {
                MwMatrix::CreateRotationZ(m, y / 500.0f);
                MwMatrix::Multiply(((MwTransform*)this->selectedResource)->manual, ((MwTransform*)this->selectedResource)->manual, m);
            }
        }

        if (this->ui->bScale->isChecked())
        {
            MwMatrix m;
            MwVector3 scalingVector(1.0f);
            if (this->ui->bX->isChecked())
            {
                scalingVector.x += x / 200.0f;
            }
            if (this->ui->bY->isChecked())
            {
                scalingVector.y += y / 200.0f;
            }
            if (this->ui->bZ->isChecked())
            {
                scalingVector.z += y / 200.0f;
            }
            MwMatrix::CreateScale(m, scalingVector);
            MwMatrix::Multiply(((MwTransform*)this->selectedResource)->manual, ((MwTransform*)this->selectedResource)->manual, m);
        }

        else if (this->ui->bFly->isChecked())
        {
            MwMatrix m;
            MwMatrix::CreateRotationY(m, x / 200.0f);
            MwMatrix::Multiply(transform->manual, m, transform->manual);
            MwMatrix::CreateRotationX(m, -y / 200.0f);
            MwMatrix::Multiply(transform->manual, m, transform->manual);
        }
    }
}

Meshwork *MainWindow::GetMeshwork()
{
    return this->meshwork;
}


void MainWindow::Render()
{
    if (this->selectedResource != 0)
    {
        if (this->selectedResource->resourceType == MwResourceType_Transform)
        {
            MwTransform *transform = (MwTransform*)this->selectedResource;

            if (this->ui->bFly->isChecked())
            {
                MwVector3 moveVector(
                            (this->keysPressed.IndexOf(Qt::Key_A) != -1)    - (this->keysPressed.IndexOf(Qt::Key_D) != -1),
                            (this->keysPressed.IndexOf(Qt::Key_Alt) != -1)  - (this->keysPressed.IndexOf(Qt::Key_Shift) != -1),
                            (this->keysPressed.IndexOf(Qt::Key_W) != -1)    - (this->keysPressed.IndexOf(Qt::Key_S) != -1));

                MwVector3::SetLength(moveVector, moveVector, 20.0f * this->meshwork->timer->time);

                MwMatrix m;
                MwMatrix::CreateTranslation(m, moveVector);
                MwMatrix::Multiply(transform->manual, m, transform->manual);
            }
        }
    }

    this->meshwork->RenderWorld();
}

void MainWindow::on_actionNew_triggered()
{
    this->meshwork->Reset();

    this->ResetEnvironment();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open scene file"), this->openSceneDir, this->importSceneDialogFilter);
    if (fileName != 0)
    {
        this->meshwork->Reset();

        //TODO: remove this
        this->ResetEnvironment();

        this->meshwork->ImportScene(MwString(fileName.toStdWString().c_str()).Replace("/", "\\"));

        this->openSceneDir = QFileInfo(fileName).absoluteFilePath();

        this->UpdateEnvironment();
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save scene file"), this->saveSceneDir, this->exportSceneDialogFilter);
    if (fileName != 0)
    {
        this->meshwork->ExportScene(MwFileSystem::CreateFileNameWithExtension(EditorUtils::QToMwString(fileName).Replace("/", "\\"), MwString("mw")));

        // Make a backup copy of the file
        //MwFileStream(MwFileSystem::CreateFileNameWithExtension(EditorUtils::QToMwString(fileName).Replace("/", "\\"), MwString("mwback")), FileStreamAccessMode_Write).WriteStreamData(MwFileStream(MwFileSystem::CreateFileNameWithExtension(EditorUtils::QToMwString(fileName).Replace("/", "\\"), MwString("mw")), FileStreamAccessMode_Read));

        this->saveSceneDir = QFileInfo(fileName).absoluteFilePath();
    }
}

void MainWindow::on_actionImport_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Import scene file"), this->importSceneDir, this->importSceneDialogFilter);
    if (fileName != 0)
    {
        this->meshwork->ImportScene(MwString(fileName.toStdWString().c_str()).Replace("/", "\\"));

        this->importSceneDir = QFileInfo(fileName).absoluteFilePath();

        this->UpdateEnvironment();
    }
}


void MainWindow::on_actionFrom_File_Texture_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Import image file"), this->importImageDir, this->importImageDialogFilter);
    if (fileName != 0)
    {
        this->meshwork->AcquireTexture(MwString(fileName.toStdWString().c_str()).Replace("/", "\\"));

        this->importImageDir = QFileInfo(fileName).absoluteFilePath();

        this->UpdateEnvironment();
    }
}

void MainWindow::on_actionEmpty_Texture_triggered()
{
    this->meshwork->AddResource(*new MwTexture2D(*this->meshwork));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionFrom_File_Sound_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Import sound file"), this->importSoundDir, this->importSoundDialogFilter);
    if (fileName != 0)
    {
        this->meshwork->AcquireSound(MwString(fileName.toStdWString().c_str()).Replace("/", "\\"));

        this->importSoundDir = QFileInfo(fileName).absoluteFilePath();

        this->UpdateEnvironment();
    }
}

void MainWindow::on_actionEmpty_Sound_triggered()
{
    this->meshwork->AddResource(*new MwSound(this->meshwork));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionCreate_Material_triggered()
{
    this->meshwork->AddResource(*new MwMaterial(*this->meshwork));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionCreate_Sound_Emitter_triggered()
{
    this->meshwork->AddResource(*new MwSoundEmitter(this->meshwork));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionCreate_Sound_Receptor_triggered()
{
    this->meshwork->AddResource(*new MwSoundReceptor(this->meshwork));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionCreate_Light_triggered()
{
    this->meshwork->AddResource(*new MwLight());
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionCreate_Camera_triggered()
{
    this->meshwork->AddResource(*new MwCamera(this->meshwork));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionCreate_Transform_triggered()
{
    this->meshwork->AddResource(*new MwTransform());
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionCreate_Script_triggered()
{
    this->meshwork->AddResource(*new MwScript(this->meshwork));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionScreen_Plane_triggered()
{
    MwMesh *mesh = (MwMesh*)this->meshwork->AddResource(*new MwMesh(*this->meshwork));
    this->ui->wResources->RefreshItems();

    MwPlaneGeometry(*mesh->deviceMesh, 1, 1, MwVector3(2, 0, 0), MwVector3(0, 2, 0));

    mesh->deviceMesh->UpdateVertices(0, mesh->deviceMesh->GetVertexCount());
    mesh->deviceMesh->UpdateIndices(0, mesh->deviceMesh->GetIndexCount());
}

void MainWindow::on_actionFrom_Height_Map_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Import image file"), this->importImageDir, this->importImageDialogFilter);
    if (fileName == 0)
        return;

    this->importImageDir = QFileInfo(fileName).absoluteFilePath();

    MwImage *heightMap = this->meshwork->CreateImage(EditorUtils::QToMwString(fileName).Replace("/", "\\"));
    if (heightMap == 0)
        return;

    MwMesh *mesh = (MwMesh*)this->meshwork->AddResource(*new MwMesh(*this->meshwork));
    this->ui->wResources->RefreshItems();

    // Create a flat plane
    MwPlaneGeometry(*mesh->deviceMesh, heightMap->width, heightMap->height, MwVector3(heightMap->width, 0, 0), MwVector3(0, 0, heightMap->height));
    MwPlanarTexCoords(*mesh->deviceMesh, MwVector3(heightMap->width, 0, 0), MwVector3(0, 0, heightMap->height));
    MwGenerateNormals(*mesh->deviceMesh);

    // Heighten the flat plane along its normals
    MwHeightMapGeometry(*mesh->deviceMesh, *heightMap, heightMap->width * heightMap->height * 0.002f);
    delete heightMap;

    mesh->ComputeBounds();
    mesh->ComputeNormals();

    mesh->deviceMesh->UpdateVertices(0, mesh->deviceMesh->GetVertexCount());
    mesh->deviceMesh->UpdateIndices(0, mesh->deviceMesh->GetIndexCount());
}


void MainWindow::on_actionPlane_triggered()
{
    MwMesh *mesh = (MwMesh*)this->meshwork->AddResource(*new MwMesh(*this->meshwork));
    this->ui->wResources->RefreshItems();

    // Create a flat plane
    int width = 160, height = 160;
    MwPlaneGeometry(*mesh->deviceMesh, width, height, MwVector3(width, 0, 0), MwVector3(0, 0, height));
    MwPlanarTexCoords(*mesh->deviceMesh, MwVector3(width, 0, 0), MwVector3(0, 0, height));

    mesh->ComputeBounds();
    mesh->ComputeNormals();

    mesh->deviceMesh->UpdateVertices(0, mesh->deviceMesh->GetVertexCount());
    mesh->deviceMesh->UpdateIndices(0, mesh->deviceMesh->GetIndexCount());
}

// Creation of new Mechanisms >>
void MainWindow::on_actionLinear_triggered()
{
    this->meshwork->AddResource(*new MwLinearMechanism(0.0f, MwMath::Pi2, MwMath::Pi2 / 10.f, false));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionFloat_triggered()
{
    this->meshwork->AddResource(*new MwFloatMechanism(0.0f));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionNegate_float_triggered()
{
    this->meshwork->AddResource(*new MwFloatMechanism(0.0f));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionLinear_interpolation_triggered()
{
    this->meshwork->AddResource(*new MwLinearInterpolationMechanism(0.0f, 10.0f, 0.0f));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionSine_triggered()
{
    this->meshwork->AddResource(*new MwSineMechanism(0.0f, MwMath::Pi2, 10.0f, false));
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionPivotal_triggered()
{
    this->meshwork->AddResource(*new MwPivotalMechanism());
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionOrientation_triggered()
{
    this->meshwork->AddResource(*new MwDirectionMechanism());
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionOrientation_lag_triggered()
{
    this->meshwork->AddResource(*new MwDirectionLagMechanism());
    this->ui->wResources->RefreshItems();
}

void MainWindow::on_actionTime_rate_triggered()
{
    this->meshwork->AddResource(*new MwTimeRateMechanism(this->meshwork));
    this->ui->wResources->RefreshItems();
}
// Creation of new Mechanisms <<

void MainWindow::on_bBack_clicked()
{
    MwBaseResource *previous = this->selectionHistory.Back();
    if (previous != 0)
        this->SelectResource(previous);
}

void MainWindow::on_bForward_clicked()
{
    MwBaseResource *next = this->selectionHistory.Forward();
    if (next != 0)
        this->SelectResource(next);
}

void MainWindow::on_eFilterResource_textChanged(const QString &arg1)
{
    this->ui->wResources->SetFilterString(EditorUtils::QToMwString(arg1));
}

void MainWindow::GraphicsDeviceMenuItemClicked()
{
    QAction *sender = (QAction*)QObject::sender();

    //if (!sender->isChecked()) // sender is already checked when this method is called
    {
        int dispatcherIndex = sender->property("dispatcherIndex").toInt();

        this->meshwork->SetGraphicsDevice((MwGraphicsDevice*)this->meshwork->graphicsDeviceDispatchers[dispatcherIndex]->CreateObject());
        this->ResetEnvironment();

        MwString deviceName;
        this->meshwork->graphicsDeviceDispatchers[dispatcherIndex]->GetInfo(MwDispatcher::infoId_Name, 0, deviceName);
        this->selectedGraphicsDevice = EditorUtils::MwToQString(deviceName);
    }
}

void MainWindow::AudioDeviceMenuItemClicked()
{
    QAction *sender = (QAction*)QObject::sender();

    //if (!sender->isChecked()) // sender is already checked when this method is called
    {
        int dispatcherIndex = sender->property("dispatcherIndex").toInt();

        this->meshwork->SetAudioDevice((MwAudioDevice*)this->meshwork->graphicsDeviceDispatchers[dispatcherIndex]->CreateObject());
        this->ResetEnvironment();

        MwString deviceName;
        this->meshwork->audioDeviceDispatchers[dispatcherIndex]->GetInfo(MwDispatcher::infoId_Name, 0, deviceName);
        this->selectedAudioDevice = EditorUtils::MwToQString(deviceName);
    }
}

void MainWindow::ResourceFilterButtonClicked()
{
    QPushButton *sender = (QPushButton*)QObject::sender();
    MwResourceType filterType = (MwResourceType)sender->property("MwResourceType").toInt();

    if (this->ui->wResources->filterType == filterType)
    {
        sender->setCheckable(false);
        sender->setChecked(false);
        sender->setCheckable(true);
        sender->update();

        this->ui->wResources->SetFilterType((MwResourceType)-1);
    }
    else
        this->ui->wResources->SetFilterType(filterType);
}

void MainWindow::OnWindowVisibilityClicked()
{
    QAction *sender = (QAction*)QObject::sender();
    QString windowName = sender->property("windowName").toString();

    QWidget *window = this->findChild<QWidget*>(windowName);
    window->setVisible(sender->isChecked());
}

void MainWindow::on_bPlayPause_clicked()
{
    this->paused = !this->paused;
    if (this->paused)
    {
        this->meshwork->timer->speed = 0.0f;
        this->ui->bPlayPause->setIcon(QIcon(EditorUtils::iconPlay));
    }
    else
    {
        this->meshwork->timer->speed = (float)this->ui->sbPlaySpeed->value();
        this->ui->bPlayPause->setIcon(QIcon(EditorUtils::iconPause));
    }
}

void MainWindow::on_sbPlaySpeed_valueChanged(double)
{
    this->ui->sbPlaySpeed->setSingleStep(MwMath::Max((float)(MwMath::Abs((float)this->ui->sbPlaySpeed->value()) / 10.0f), 0.01f));
    if (!this->paused)
        this->meshwork->timer->speed = this->ui->sbPlaySpeed->value();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if (!this->tickOutMode)
        return;

    float x = value / 100.0f;
    //x = x * x * x * 60.0f;
    x *= 10.0f;
    this->meshwork->timer->TickOut(-this->lastTickout + x);
    this->ui->lTickOutTime->setText(QString::number(x));
    this->lastTickout = x;
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    this->tickOutMode = true;
    this->meshwork->timer->speed = 0.0f;
    //this->ui->lTickOutTime->setVisible(true);
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    this->tickOutMode = false;
    //this->ui->lTickOutTime->setVisible(false);
    this->ui->lTickOutTime->setText("");
    this->ui->horizontalSlider->setValue(0);

    if (!this->paused)
        this->meshwork->timer->speed = this->ui->sbPlaySpeed->value();
}

void MainWindow::on_actionOnlineDocumentation_triggered()
{
    QDesktopServices::openUrl(QUrl("http://morroworks.com/meshwork/docs/"));
}

void MainWindow::on_actionHome_Page_triggered()
{
    QDesktopServices::openUrl(QUrl("http://morroworks.com/meshwork/"));
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "Meshwork", "Meshwork Editor pre-alpha<br/>Unofiicial release for evaluation purposes<br/><a href=\"http://morroworks.com\">morroworks.com</a>");
}
