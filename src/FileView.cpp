#include "FileView.h"
#include "FileMungusPathLogic.h"
#include <cassert>
#include <cstddef>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <wx/event.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/dir.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <wx/regex.h>

const wxString &GetFileMarker()
{
    static wxString marker(wxString::FromUTF8("🏷️ "));
    return marker;
}

const wxString &GetFolderMarker()
{
    static wxString marker(wxString::FromUTF8("🗀 "));
    return marker;
}

FileView::FileView(wxWindow *parent, FileMungusPathLogic *pathLogic) : wxWindow(parent, wxID_ANY)
        ,  m_pathLogic(pathLogic)
{
    m_content = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    auto *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_content, 1, wxEXPAND);
    m_pathLogic->SubscribeToPathEvent([this](PathEvent evt){
        if(evt == PathEvent::UpdatePath)
            ScanPath(m_pathLogic->GetPath());
    });

    m_content->Bind(wxEVT_LISTBOX_DCLICK, &FileView::DoOperation, this, wxID_ANY); 

    SetSizer(sizer);
}

wxString DifferentiateFF(const wxString &path, const wxString &fileName) //FF = Files and folders
{
    wxString out;
    wxString tmp;
    if(wxDirExists(path + '/' + fileName) == true)
    
        out = GetFolderMarker() + fileName;
    else
        out = GetFileMarker() + fileName;
    
    return out;
}

void FileView::ScanPath(const wxString &path)
{
    m_content->Clear();
    m_content->Insert("<--", 0);

    wxDir dir(path);
    wxArrayString files;
    wxString file;
    if(!dir.GetFirst(&file))
        return;
    files.Add(DifferentiateFF(path, file));
    while(dir.GetNext(&file))
        files.Add(DifferentiateFF(path, file));

    files.Sort(true); //Sorted after adding file and folder icon 
    m_content->InsertItems(files,1); //ListBox only accepts wxArrayString
}

void FileView::GoToPreviousFolder()
{
    const wxString &path = m_pathLogic->GetPath();

    if(path == "/")
        return;
    
    decltype(path.rbegin()) last = std::find(path.rbegin() + 1, path.rend(), '/'); //well its not AUTO
    assert(last != path.rend());
    ptrdiff_t distance = path.rend() - last;
    m_pathLogic->SetPath(path.substr(0, static_cast<size_t>(distance))); //substring 
}

void FileView::DoOperation(wxCommandEvent &event)
{
    int index = m_content->GetSelection();
    if(index == wxNOT_FOUND)
        return;
    
    if(index == 0)
    {
        GoToPreviousFolder();
        return;    
    }

    wxString selected = m_content->GetString(static_cast<unsigned int>(index)); //GetSelection only returns int
                                                                                //GetString only accepts unsigned int 
                                                                                //this is why static cast is needed
    //idealni zjistit zda je to slozka TO DO
    if(selected.StartsWith(GetFileMarker()))
    {
        wxRegEx reFile(wxString::FromUTF8(".+\\..+")); //using wxWidgets buildin Regex, it first goes through string until it finds "." after that It reads file extension and than opens it accordingly 
        wxString fileName = selected.substr(GetFileMarker().size());
        if(reFile.Matches(fileName))
            system(("xdg-open " + m_pathLogic->GetPath() + fileName).c_str()); 
        else 
            system((m_pathLogic->GetPath() + fileName).c_str());
    }
    else if(selected.StartsWith(GetFolderMarker()))
        m_pathLogic->SetPath(m_pathLogic->GetPath() + selected.substr(GetFolderMarker().size()));
    else 
        throw std::runtime_error("WTF");   
}
