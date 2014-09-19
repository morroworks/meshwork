#ifndef QMWMATERIALLAYERSWIDGET_H
#define QMWMATERIALLAYERSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>

#include "QMwEditorWidget.h"

class QMwMaterialLayersWidget :
        public QWidget,
        public QMwEditorWidget
{
    Q_OBJECT
private:
    QWidget *layersWidget, *messageWidget;
    QLabel *messageText;

    MwMaterial *material;

    int selectedLayerIndex;

    void UpdateLayersPanel();
    void SetMessage();

    void SetShaderOpComboBox(QComboBox *comboBox, int layerIndex);
    void SetColorOpComboBox(QComboBox *comboBox, int layerIndex);

public:
    explicit QMwMaterialLayersWidget(QWidget *parent = 0);

    void SetResource(MwBaseResource *resource);

signals:

public slots:
    void DeleteLayerClicked();
    void MoveLayerDownClicked();
    void MoveLayerUpClicked();
    void InsertLayerClicked();
    void AppendLayerClicked();

    void LayerSelected();
    void LayerShaderOperationChanged(int index);
    void LayerColorOperationChanged(int index);

};

#endif // QMWMATERIALLAYERSWIDGET_H
