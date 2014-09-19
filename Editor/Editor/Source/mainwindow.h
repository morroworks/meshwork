#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QTreeWidgetItem>

#include "MeshworkEngine.h"

#include "EditorTools/ResourceSelectionHistory.h"
#include "QMwWidgets/IMwEditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow :
        public QMainWindow,
        public IMwEditor
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    MwList<int> keysPressed;

    bool paused;
    float lastTickout;
    bool tickOutMode;
    WId renderWindowHandle;

    QString importSceneDialogFilter, exportSceneDialogFilter, importImageDialogFilter, importSoundDialogFilter;
    QString openSceneDir, saveSceneDir, importSceneDir, importImageDir, importSoundDir;
    QString selectedGraphicsDevice, selectedAudioDevice;

    QString CreateDialogFilesFilter(MwList<MwDispatcher *> *dispatchers, unsigned int infoId, bool addAllSupportedAndAny);
    template <typename Func> void CreateDevicesMenu(MwList<MwDispatcher *> *dispatchers, QMenu *menu, Func slot, int selectedIndex);

    // Events
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

public:
    Meshwork *meshwork;

    MwBaseResource *selectedResource;

    ResourceSelectionHistory selectionHistory;

    QTimer *renderTimer;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    // IMwEditor interface methods

    void UpdateEnvironment();
    void ResetEnvironment();

    void SelectResource(MwBaseResource *resource);
    MwBaseResource *GetSelectedResource();

    void UpdateResourceName(MwBaseResource *resource);
    void UpdateResourceProperties(MwBaseResource *resource);

    void MouseDrag(int x, int y);

    Meshwork *GetMeshwork();

private slots:
    void Render();

    void GraphicsDeviceMenuItemClicked();
    void AudioDeviceMenuItemClicked();

    void ResourceFilterButtonClicked();

    void OnWindowVisibilityClicked();

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();

    void on_actionImport_triggered();

    void on_bBack_clicked();
    void on_bForward_clicked();

    void on_eFilterResource_textChanged(const QString &arg1);
    void on_bPlayPause_clicked();
    void on_sbPlaySpeed_valueChanged(double);
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_sliderPressed();
    void on_horizontalSlider_sliderReleased();

    void on_actionEmpty_Texture_triggered();
    void on_actionFrom_File_Texture_triggered();

    void on_actionEmpty_Sound_triggered();
    void on_actionFrom_File_Sound_triggered();

    void on_actionCreate_Material_triggered();
    void on_actionCreate_Sound_Emitter_triggered();
    void on_actionCreate_Sound_Receptor_triggered();
    void on_actionCreate_Light_triggered();
    void on_actionCreate_Camera_triggered();
    void on_actionCreate_Transform_triggered();
    void on_actionScreen_Plane_triggered();

    void on_actionLinear_triggered();
    void on_actionFloat_triggered();
    void on_actionNegate_float_triggered();
    void on_actionLinear_interpolation_triggered();
    void on_actionSine_triggered();
    void on_actionPivotal_triggered();
    void on_actionOrientation_triggered();
    void on_actionOrientation_lag_triggered();
    void on_actionTime_rate_triggered();
    void on_actionFrom_Height_Map_triggered();
    void on_actionCreate_Script_triggered();
    void on_actionPlane_triggered();
    void on_actionOnlineDocumentation_triggered();
    void on_actionHome_Page_triggered();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
