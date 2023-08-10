#pragma once 
#include <wx/window.h>
#include <stack>
#include <list>

class wxButton;
class wxTextCtrl;
class FileMungusPathLogic;

class TopPanel : public wxWindow
{
public: 
    TopPanel(wxWindow *parent, FileMungusPathLogic *pathLogic);

private: 
    wxButton *m_backBtn;
    wxButton *m_fowardBtn;
    wxTextCtrl *m_pathTextBox;
    FileMungusPathLogic *m_pathLogic;
};
