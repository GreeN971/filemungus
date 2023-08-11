#include "FileMungusApp.h"
#include "FileMungusMainWindow.h"
#include <wx/frame.h>
#include <wx/image.h>
#include <wx/xrc/xmlres.h>
extern void InitXmlResource(); //doesnt anticipate included header, searches for function InitXmlResource through all files, can backfire If I have functions with same name

bool FileMungusApp::OnInit()
{
    wxXmlResource::Get()->InitAllHandlers();
    wxInitAllImageHandlers();
    InitXmlResource();
    FileMungusMainWindow *win = new FileMungusMainWindow();
    win->Show();
    return true;
}

