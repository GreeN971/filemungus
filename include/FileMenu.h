#pragma once 
#include <wx/popupwin.h>
#include <chrono>
#include <wx/timer.h>
#include <wx/menu.h>

class wxListBox;
class FileView;

class FileMenu : public wxMenu
{
public:
    FileMenu(FileView *parent);
    //bool Show(bool show = true) override; COMING SOON TM? 
private:
    //wxTimer m_timer;
    wxListBox *m_content;
    FileView *m_fileView;
};
