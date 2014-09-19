#ifndef QMWTRANSFORMLAYERSWIDGET_H
#define QMWTRANSFORMLAYERSWIDGET_H

#include <QWidget>
#include <QComboBox>

#include "QMwEditorWidget.h"

class QMwTransformLayersWidget :
        public QWidget,
        public QMwEditorWidget
{
    Q_OBJECT
private:
    QWidget *layersWidget;

    MwTransform *transform;

    int selectedLayerIndex;

    void UpdateLayersPanel();

    void SetLayerComboBox(QComboBox *comboBox, int layerIndex);

public:
    explicit QMwTransformLayersWidget(QWidget *parent = 0);

    void SetResource(MwBaseResource *resource);

signals:

public slots:
    void DeleteLayerClicked();
    void MoveLayerDownClicked();
    void MoveLayerUpClicked();
    void InsertLayerClicked();
    void AppendLayerClicked();

    void LayerSelected();
    void LayerOperationChanged(int index);

};

#endif // QMWTRANSFORMLAYERSWIDGET_H
