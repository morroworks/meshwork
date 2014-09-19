//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "EditorUtils.h"

#include <QMimeData>
#include <QPixmap>

QString EditorUtils::iconRecallParameter = QString(":/Icons/Icons/Manipulate/RecallParameter.png");
QString EditorUtils::iconPlay = QString(":/Icons/Icons/Manipulate/Play.png");
QString EditorUtils::iconPause = QString(":/Icons/Icons/Manipulate/Pause.png");
QString EditorUtils::iconNew = QString(":/Icons/Icons/Manipulate/New.png");
QString EditorUtils::iconDelete = QString(":/Icons/Icons/Manipulate/Delete.png");
QString EditorUtils::iconInsert = QString(":/Icons/Icons/Manipulate/Insert.png");
QString EditorUtils::iconMoveUp = QString(":/Icons/Icons/Manipulate/MoveUp.png");
QString EditorUtils::iconMoveDown = QString(":/Icons/Icons/Manipulate/MoveDown.png");
QString EditorUtils::iconScriptProperties = QString(":/Icons/Icons/Other/ScriptProperties.png");

MwDictionary<MwResourceType, QString> EditorUtils::resourceTypeIcons;
MwDictionary<MwShaderOperation, QString> EditorUtils::shaderOperationNames;
MwDictionary<MwColorOperation, QString> EditorUtils::colorOperationNames;
MwDictionary<MwTransformOperation, QString> EditorUtils::transformOperationNames;
MwDictionary<MwParameterType, QString> EditorUtils::parameterTypeNames;

EditorUtils::Initialization EditorUtils::initialization;

EditorUtils::Initialization::Initialization(void)
{
    // Map resource types to their respective icon names
    EditorUtils::resourceTypeIcons.Add(MwResourceType_EntitySet, ":/Icons/Icons/Resources/EntitySet.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_Mesh, ":/Icons/Icons/Resources/Mesh.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_Transform, ":/Icons/Icons/Resources/Transform.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_Material, ":/Icons/Icons/Resources/Material.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_Mechanism, ":/Icons/Icons/Resources/Mechanism.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_Camera, ":/Icons/Icons/Resources/Camera.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_Texture, ":/Icons/Icons/Resources/Texture.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_Light, ":/Icons/Icons/Resources/Light.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_Sound, ":/Icons/Icons/Resources/Sound.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_SoundEmitter, ":/Icons/Icons/Resources/SoundEmitter.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_SoundReceptor, ":/Icons/Icons/Resources/SoundReceptor.png");
    EditorUtils::resourceTypeIcons.Add(MwResourceType_Script, ":/Icons/Icons/Resources/Script.png");

    EditorUtils::shaderOperationNames.Add(MwShaderOperation_None, "None");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_BasicShading, "Basic Shading");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_Material, "Material");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_LightSource, "Light Source");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_VertexLighting, "Vertex Lighting");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_PixelLighting, "Pixel Lighting");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_ColorMap, "Color Map");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_EnvMap, "Env Map");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_NormalMap, "Normal Map");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_RefractionMap, "Refraction Map");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_AlignScreenQuad, "Align Screen Quad");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_BlurMap, "Blur Map");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_Tint, "Tint");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_HBlur, "Horizontal Blur");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_VBlur, "Vertical Blur");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_ProjectTexture, "Project Texture");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_ProjectPicture, "Project Picture");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_ShadowMapWriter, "Shadow Map Writer");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_ShadowMap, "Shadow Map");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_BlendTexture, "Blend Texture");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_TextureTransform, "Texture Transform");
    EditorUtils::shaderOperationNames.Add(MwShaderOperation_Skinning, "Skinning");

    EditorUtils::colorOperationNames.Add(MwColorOperation_None, "None");
    EditorUtils::colorOperationNames.Add(MwColorOperation_Set, "Set");
    EditorUtils::colorOperationNames.Add(MwColorOperation_Add, "Add");
    EditorUtils::colorOperationNames.Add(MwColorOperation_Subtract, "Subtract");
    EditorUtils::colorOperationNames.Add(MwColorOperation_Modulate, "Modulate");
    EditorUtils::colorOperationNames.Add(MwColorOperation_Lighter, "Lighter");
    EditorUtils::colorOperationNames.Add(MwColorOperation_Darker, "Darker");

    EditorUtils::transformOperationNames.Add(MwTransformOperation_Translate, "Translate");
    EditorUtils::transformOperationNames.Add(MwTransformOperation_RotateX, "RotateX");
    EditorUtils::transformOperationNames.Add(MwTransformOperation_RotateY, "RotateY");
    EditorUtils::transformOperationNames.Add(MwTransformOperation_RotateZ, "RotateZ");
    EditorUtils::transformOperationNames.Add(MwTransformOperation_Scale, "Scale");
    EditorUtils::transformOperationNames.Add(MwTransformOperation_TranslateAbsolute, "TranslateAbsolute");
    EditorUtils::transformOperationNames.Add(MwTransformOperation_RotateAbsoluteX, "RotateAbsoluteX");
    EditorUtils::transformOperationNames.Add(MwTransformOperation_RotateAbsoluteY, "RotateAbsoluteY");
    EditorUtils::transformOperationNames.Add(MwTransformOperation_RotateAbsoluteZ, "RotateAbsoluteZ");
    EditorUtils::transformOperationNames.Add(MwTransformOperation_ScaleAbsolute, "ScaleAbsolute");

    EditorUtils::parameterTypeNames.Add(MwParameterType_None, "None");
    EditorUtils::parameterTypeNames.Add(MwParameterType_Int, "Int");
    EditorUtils::parameterTypeNames.Add(MwParameterType_Float, "Float");
    EditorUtils::parameterTypeNames.Add(MwParameterType_Bool, "Bool");
    EditorUtils::parameterTypeNames.Add(MwParameterType_Color, "Color");
    EditorUtils::parameterTypeNames.Add(MwParameterType_ReferenceVector3, "Vector3");
    EditorUtils::parameterTypeNames.Add(MwParameterType_ReferenceTexture, "Texture");
    EditorUtils::parameterTypeNames.Add(MwParameterType_ReferenceCamera, "Camera");
    EditorUtils::parameterTypeNames.Add(MwParameterType_ReferenceMechanism, "Mecanism");
    EditorUtils::parameterTypeNames.Add(MwParameterType_ReferenceTransform, "Transform");
    EditorUtils::parameterTypeNames.Add(MwParameterType_ReferenceSound, "Sound");
}

EditorUtils::EditorUtils()
{
}

QString EditorUtils::Vector4ToHtmlColor(MwVector4 &vector, bool withAlpha)
{
    unsigned int value = MwMath::Trim((int)(0xff * vector.x / 1.0f), 0x00, 0xff);
    value <<= 8;
    value |= MwMath::Trim((int)(0xff * vector.y / 1.0f), 0x00, 0xff);
    value <<= 8;
    value |= MwMath::Trim((int)(0xff * vector.z / 1.0f), 0x00, 0xff);

    if (withAlpha)
    {
        value <<= 8;
        value |= MwMath::Trim((int)(0xff * vector.w / 1.0f), 0x00, 0xff);

        return QString(MwString(value, 16).PadLeft(8, '0').GetCharContents());
    }
    else
        return QString(MwString(value, 16).PadLeft(6, '0').GetCharContents());
}

QColor EditorUtils::Vector4ToQColor(MwVector4 &vector)
{
    return QColor(MwMath::Trim((int)(0xff * vector.x / 1.0f), 0x00, 0xff),
                  MwMath::Trim((int)(0xff * vector.y / 1.0f), 0x00, 0xff),
                  MwMath::Trim((int)(0xff * vector.z / 1.0f), 0x00, 0xff),
                  MwMath::Trim((int)(0xff * vector.w / 1.0f), 0x00, 0xff));
}

void EditorUtils::QColorToVector4(const QColor &color, MwVector4 &vector, bool withAlpha)
{
    vector.x = (float)color.redF();
    vector.y = (float)color.greenF();
    vector.z = (float)color.blueF();
    if (withAlpha)
        vector.w = (float)color.alphaF();
}

QDrag *EditorUtils::CreateResourceDrag(QObject *dragSource, MwBaseResource *resource)
{
    QDrag *drag = new QDrag(dragSource);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/mwresource", QByteArray(MwString((unsigned int)resource).GetCharContents()));
    drag->setMimeData(mimeData);

    QString iconName;
    if (EditorUtils::resourceTypeIcons.GetValue(resource->resourceType, iconName))
        drag->setPixmap(QPixmap(iconName));

    return drag;
}

MwString EditorUtils::QToMwString(const QString &string)
{
    return MwString(string.toStdWString().c_str());
}


QString EditorUtils::MwToQString(const MwString &string)
{
    return QString::fromWCharArray(string.contents);
}
