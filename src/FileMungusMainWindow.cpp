#include "FileMungusMainWindow.h"
#include "SidePanel.h"
#include "TopPanel.h"
#include "FileView.h"
#include "FileMungusPathLogic.h"
#include <memory>
#include <iostream>
#include <wx/colour.h>
#include <wx/gdicmn.h>
#include <wx/listbox.h>
#include <wx/dir.h>
#include <wx/control.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/xrc/xmlres.h>

FileMungusMainWindow::FileMungusMainWindow()
    : wxFrame(nullptr, wxID_ANY, "FileMungus")
    , m_pathLogic(std::make_unique<FileMungusPathLogic>())
{
    wxIcon icon = wxXmlResource::Get()->LoadIcon("sussy_icon");;
    SetIcon(icon); 

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *content = new wxBoxSizer(wxVERTICAL);

    FileView *fileView = new FileView(this, m_pathLogic.get());

    wxBoxSizer *topPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    
    content->Add(topPanelSizer, 0, wxEXPAND);

    TopPanel *topPanel = new TopPanel(this, m_pathLogic.get());
    topPanelSizer->Add(topPanel, 1, wxEXPAND);
    
    topPanel->SetBackgroundColour(wxColour("FE9E21"));

    wxBoxSizer *bottomPanelSizer = new wxBoxSizer(wxHORIZONTAL);

    //BottomPanel *bottomPanel = new BottomPanel(this);
    //bottomPanel->SetMinSize(wxSize(50,50));
    //bottomPanel->SetBackgroundColour(wxColour("FE9E21"));
    //bottomPanelSizer->Add(bottomPanel, 1, wxEXPAND, 5);
    
    sizer->Add(bottomPanelSizer);    
#ifdef WIN32
    m_pathLogic->SetPath(getenv("USERPROFILE"));
#else 
    m_pathLogic->SetPath(getenv("HOME")); //getenviroment
#endif
    content->Add(fileView, 1, wxEXPAND);
    sizer->Add(content, 1, wxEXPAND);
    this->SetSizer(sizer);    
};

FileMungusMainWindow::~FileMungusMainWindow() = default;

