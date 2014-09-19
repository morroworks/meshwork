#ifndef IMWEDITOR_H
#define IMWEDITOR_H

#include "../MeshworkEngine.h"

class IMwEditor
{
public:
    virtual void SelectResource(MwBaseResource *resource) = 0;
    virtual MwBaseResource *GetSelectedResource() = 0;

    virtual void UpdateResourceName(MwBaseResource *resource) = 0;
    virtual void UpdateResourceProperties(MwBaseResource *resource) = 0;

    virtual void MouseDrag(int x, int y) = 0;

    virtual Meshwork *GetMeshwork() = 0;
};

#endif // IMWEDITOR_H
