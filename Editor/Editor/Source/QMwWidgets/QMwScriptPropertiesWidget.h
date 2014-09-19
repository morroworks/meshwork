#ifndef QMWSCRIPTPROPERTIESWIDGET_H
#define QMWSCRIPTPROPERTIESWIDGET_H

#include <QWidget>
#include <QComboBox>

#include "QMwEditorWidget.h"

class QMwScriptPropertiesWidget :
        public QWidget,
        public QMwEditorWidget
{
    Q_OBJECT
private:
    void SetPropertyTypeComboBox(QComboBox *comboBox, int layerIndex);
    void UpdateLayersPanel();

public:
    QWidget *layersWidget;

    MwScript *script;

    int selectedLayerIndex;

    explicit QMwScriptPropertiesWidget(QWidget *parent = 0);

    void SetResource(MwBaseResource *resource);

signals:

public slots:
    void DeleteLayerClicked();
    void AppendLayerClicked();

    void LayerSelected();
    void LayerNameChanged();
    void LayerTypeChanged(int index);

};

#endif // QMWSCRIPTPROPERTIESWIDGET_H
