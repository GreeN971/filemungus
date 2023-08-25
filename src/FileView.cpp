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
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <wx/regex.h>
#include "FileMenu.h"
#include "RenameDialog.h"
#include "CreateDialog.h"
#include <wx/menu.h>
#include <wx/msgdlg.h>

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

FileView::FileView(wxWindow *parent, FileMungusPathLogic *pathLogic) 
        : wxWindow(parent, wxID_ANY)
        , m_pathLogic(pathLogic)
        , m_menu(this)
{
    m_content = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    auto *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_content, 1, wxEXPAND);
    m_pathLogic->SubscribeToPathEvent([this](PathEvent evt){
        if(evt == PathEvent::UpdatePath)
            ScanPath(m_pathLogic->GetPath());
    });

    m_content->Bind(wxEVT_LISTBOX_DCLICK, &FileView::LeftDoubleClickHandler, this, wxID_ANY); 
    
    m_content->Bind(wxEVT_RIGHT_DOWN, [this](wxMouseEvent&){
        m_content->PopupMenu(&m_menu);
    });

    SetSizer(sizer);
}

wxString DifferentiateFF(const wxString &path, const wxString &fileName) //FF = Files and folders
{
    wxString out;
    wxString tmp;
    if(wxDirExists(path + FileMungusPathLogic::GetPathSeparator() + fileName) == true)
    
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

#ifdef WIN32
    if (path.length() == 3) /* C:\ */
        return;
#else
    if(path == "/")
        return;
#endif    
    decltype(path.rbegin()) last = std::find(path.rbegin() + 1, path.rend(), FileMungusPathLogic::GetPathSeparator()); //well its not AUTO
    assert(last != path.rend());
    ptrdiff_t distance = path.rend() - last;
    m_pathLogic->SetPath(path.substr(0, static_cast<size_t>(distance))); //substring 
}

void FileView::LeftDoubleClickHandler(wxCommandEvent&)
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
    if (selected.StartsWith(GetFileMarker()))
    {
#ifdef WIN32
        wxRegEx reFile(wxString::FromUTF8(".+\\..+^(exe)$"));
#else
        wxRegEx reFile(wxString::FromUTF8(".+\\..+")); //using wxWidgets buildin Regex, it first goes through string until it finds "." after that It reads file extension and than opens it accordingly 
#endif
        wxString fileName = selected.substr(GetFileMarker().size());
        if (reFile.Matches(fileName))
        {
#ifdef WIN32
            system(("start \"" + m_pathLogic->GetPath() + fileName + "\"").c_str());
#else
            system(("xdg-open \"" + m_pathLogic->GetPath() + fileName + "\"").c_str()); //system accepts only C type string
#endif
        }
        else
            system(("\"" + m_pathLogic->GetPath() + fileName + "\"").c_str());
    }
    else if(selected.StartsWith(GetFolderMarker()))
        m_pathLogic->SetPath(m_pathLogic->GetPath() + selected.substr(GetFolderMarker().size()));
    else 
        throw std::runtime_error("WTF");  
}

void FileView::RenameSelected()
{
    long index = m_content->GetSelection();
    if(index == wxNOT_FOUND || index == 0)
        return;
   
    wxString selected = m_content->GetString(static_cast<unsigned int>(index));
    
    wxString marker;
    wxString fileName; 
    if(selected.StartsWith(GetFileMarker()))
    {
        marker = GetFileMarker();
        fileName = selected.substr(marker.size());
    }
    else if(selected.StartsWith(GetFolderMarker()))
    {   
        marker = GetFolderMarker();
        fileName = selected.substr(marker.size());
    }
    else 
        throw std::runtime_error("WTF2");
    
    RenameDialog dlg(m_pathLogic->GetPath(), fileName);
    dlg.ShowModal();

    if(!dlg.IsSuccesfull())
        return;
    
    if(fileName == dlg.GetNewFileName())
        return;
    else if(wxFileExists(m_pathLogic->GetPath() + dlg.GetNewFileName()))
    {
        wxMessageBox("File with same name already exists", "warning", wxOK | wxCENTRE | wxICON_INFORMATION);
        return;
    }
    rename((m_pathLogic->GetPath() + fileName).c_str(), (m_pathLogic->GetPath() + dlg.GetNewFileName()).c_str()); 

    m_content->SetString(static_cast<unsigned int>(index), marker + dlg.GetNewFileName());
}

void FileView::CreateFile()
{
    long index = m_content->GetCount();
    if(index == wxNOT_FOUND || index == 0)
        return;

    wxString fileMarker = GetFileMarker();
    wxString newFileName;
    
    CreateDialog dlg;
    dlg.ShowModal();

    if(!dlg.IsSuccesfull())
        return;
    
    if(wxFileExists(m_pathLogic->GetPath() + dlg.GetNewFileName()))
    {
        wxMessageBox("File with same name already exists", "warning", wxOK | wxCENTRE | wxICON_INFORMATION);
        return;
    }
    
    std::ofstream myFile((m_pathLogic->GetPath() + dlg.GetNewFileName()).c_str());
    myFile.close();
    
    ScanPath(m_pathLogic->GetPath());
}

void FileView::CreateFolder()
{
    long index = m_content->GetCount();
    if(index == wxNOT_FOUND || index == 0)
        return;

    wxString folderMarker = GetFolderMarker();
    wxString newFileName;
    
    CreateDialog dlg;
    dlg.ShowModal();

    if(!dlg.IsSuccesfull())
        return;
    
    if(wxFileExists(m_pathLogic->GetPath() + dlg.GetNewFileName()))
    {
        wxMessageBox("File with same name already exists", "warning", wxOK | wxCENTRE | wxICON_INFORMATION);
        return;
    }

#ifdef WIN32
    _mkdir((m_pathLogic->GetPath() + dlg.GetNewFileName()).c_str()); 
#else    
    mkdir((m_pathLogic->GetPath() + dlg.GetNewFileName()).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); //0777 superman 
#endif
    
    ScanPath(m_pathLogic->GetPath());
}

