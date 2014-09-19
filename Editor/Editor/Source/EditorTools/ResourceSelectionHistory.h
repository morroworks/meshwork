#ifndef RESOURCESELECTIONHISTORY_H
#define RESOURCESELECTIONHISTORY_H

#include "EditorUtils.h"

class ResourceSelectionHistory
{
public:
    MwList<MwBaseResource*> history;
    int selectedIndex, capacity;

    ResourceSelectionHistory(int capacity = 20);
    ~ResourceSelectionHistory();

    void Clear();

    void PushHistory(MwBaseResource *selection);

    MwBaseResource *Back();
    MwBaseResource *Forward();
};

#endif // RESOURCESELECTIONHISTORY_H
