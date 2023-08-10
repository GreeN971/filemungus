#include "FileMungusPathLogic.h"
#include <wx/dir.h>
#include <wx/filefn.h>

void FileMungusPathLogic::SubscribeToUndo(const std::function<void(StackEvent)> &sub)
{
    m_undo.Subscribe(sub); //IsNotEmpty
}

void FileMungusPathLogic::SubscribeToRedo(const std::function<void(StackEvent)> &sub)
{
    m_redo.Subscribe(sub); //IsNotEmpty
}

void FileMungusPathLogic::SubscribeToPathEvent(const std::function<void (PathEvent)> &sub)
{
    m_subscribers.push_back(sub); 
}

void FileMungusPathLogic::SetPath(const wxString &path)
{
    if(path.IsEmpty())
        return;
    wxString validPath = path;
    if(*validPath.rbegin() != '/') //overloaded operator *, its not a pointer 
        validPath.Append('/');
     
    if(m_currentPath == validPath)
        return;
    else if(!wxDirExists(validPath)) 
        return;
    
    if(!m_currentPath.IsEmpty())
        m_undo.Push(m_currentPath);
    m_redo.Clear();
    
    ChangePath(validPath); 
}

const wxString &FileMungusPathLogic::GetPath() const noexcept
{
    return m_currentPath;
}

void FileMungusPathLogic::Undo()
{
    if(m_undo.IsEmpty())
        return;
   
    m_redo.Push(m_currentPath);
    ChangePath(m_undo.Pop());
}

void FileMungusPathLogic::Redo()
{
    if(m_redo.IsEmpty())
        return;

    m_undo.Push(m_currentPath);
    ChangePath(m_redo.Pop());
}

void FileMungusPathLogic::ChangePath(const wxString &path)
{
    m_currentPath = path;
    for(const auto &sub : m_subscribers)
        sub(PathEvent::UpdatePath);
}
