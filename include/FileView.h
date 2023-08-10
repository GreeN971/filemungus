#pragma once 
#include <wx/string.h>
#include <wx/window.h>

class wxListBox;
class FileMungusPathLogic;

class FileView : public wxWindow
{
public:
    FileView(wxWindow *parent, FileMungusPathLogic *pathLogic);
    void ScanPath(const wxString &path);
    void DoOperation(wxCommandEvent &event);
    void GoToPreviousFolder();

private:
   wxListBox *m_content; 
   FileMungusPathLogic *m_pathLogic;
};
