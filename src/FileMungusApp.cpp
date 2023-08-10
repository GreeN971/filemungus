#include "FileMungusApp.h"
#include "FileMungusMainWindow.h"
#include <wx/frame.h>
bool FileMungusApp::OnInit()
{
    FileMungusMainWindow *win = new FileMungusMainWindow();
    win->Show();
    return true;
}

