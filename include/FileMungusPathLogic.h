#pragma once
#include "ObservableStack.h"
#include <wx/string.h>

enum class PathEvent
{
    UpdatePath
};

class FileMungusPathLogic
{
public: 
    void SubscribeToUndo(const std::function<void(StackEvent)> &sub); 
    void SubscribeToRedo(const std::function<void(StackEvent)> &sub);
    void SubscribeToPathEvent(const std::function<void(PathEvent)> &sub);
    void SetPath(const wxString &path);
    const wxString &GetPath() const noexcept;
    static char GetPathSeparator();
    void Undo();
    void Redo();

private: 
    void ChangePath(const wxString &path);
    
    std::vector<std::function<void(PathEvent)>> m_subscribers;
    ObservableStack<wxString> m_undo;
    ObservableStack<wxString> m_redo;
    wxString m_currentPath;
};
