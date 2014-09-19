#ifndef EDITORUTILS_H
#define EDITORUTILS_H

#include <QString>
#include <QColor>
#include <QDrag>

#include "../MeshworkEngine.h"


#include "../QMwWidgets/IMwEditor.h"

class EditorUtils
{
private:
    class Initialization
    {
    public:
        Initialization(void);
    };

    static Initialization initialization;

public:
    static QString iconRecallParameter;
    static QString iconPlay;
    static QString iconPause;
    static QString iconNew;
    static QString iconDelete;
    static QString iconInsert;
    static QString iconMoveUp;
    static QString iconMoveDown;
    static QString iconScriptProperties;

    static MwDictionary<MwResourceType, QString> resourceTypeIcons;
    static MwDictionary<MwShaderOperation, QString> shaderOperationNames;
    static MwDictionary<MwColorOperation, QString> colorOperationNames;
    static MwDictionary<MwTransformOperation, QString> transformOperationNames;
    static MwDictionary<MwParameterType, QString> parameterTypeNames;

    EditorUtils();

    static QString Vector4ToHtmlColor(MwVector4 &vector, bool withAlpha = false);
    static QColor Vector4ToQColor(MwVector4 &vector);
    static void QColorToVector4(const QColor &color, MwVector4 &vector, bool withAlpha);

    static QDrag *CreateResourceDrag(QObject *dragSource, MwBaseResource *resource);

    static MwString QToMwString(const QString &string);
    static QString MwToQString(const MwString &string);

};

#endif // EDITORUTILS_H
