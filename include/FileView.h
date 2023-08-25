#pragma once 
#include <wx/string.h>
#include <wx/window.h>
#include "FileMenu.h"

class wxListBox;
class FileMungusPathLogic;

class FileView : public wxWindow
{
public:
    FileView(wxWindow *parent, FileMungusPathLogic *pathLogic);
    void ScanPath(const wxString &path);
    void LeftDoubleClickHandler(wxCommandEvent &event);
    void LeftClickHandler(wxCommandEvent &event);
    void GoToPreviousFolder();
    void RenameSelected();
    void CreateFile();
    void CreateFolder();

private:
   wxListBox *m_content; 
   FileMungusPathLogic *m_pathLogic;
   FileMenu m_menu;
};
