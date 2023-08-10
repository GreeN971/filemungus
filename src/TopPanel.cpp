#include "TopPanel.h"
#include "FileMungusPathLogic.h"
#include "ObservableStack.h"
#include <cassert>
#include <set>
#include <wx/button.h>
#include <wx/stringimpl.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>


TopPanel::TopPanel(wxWindow *parent, FileMungusPathLogic *pathLogic) 
    : wxWindow(parent, wxID_ANY)
    , m_pathLogic(pathLogic)
{
    assert(pathLogic != nullptr);

    const auto leftBtnMargin = FromDIP(5);
    const auto rightBtnMargin = FromDIP(3);
    
    auto *sizer = new wxBoxSizer(wxVERTICAL); 
    auto *content = new wxBoxSizer(wxHORIZONTAL);
    
    sizer->Add(content, 1, wxEXPAND | wxTOP | wxBOTTOM, 3);


    m_backBtn = new wxButton(this, wxID_ANY, wxString::FromUTF8("undo"));//"🢀"
    m_backBtn->Enable(false);
    m_pathLogic->SubscribeToUndo([this](StackEvent evt){
        if(evt == StackEvent::Empty)
            m_backBtn->Disable();
        else if(evt == StackEvent::IsNotEmpty)
            m_backBtn->Enable(); 
    });

    m_backBtn->Bind(wxEVT_BUTTON,[this] (wxCommandEvent&){ 
        m_pathLogic->Undo();    
    });
    
    wxFont font = m_backBtn->GetFont();
    font.SetPointSize(10);
    
    m_backBtn->SetFont(font);
    m_fowardBtn = new wxButton(this, wxID_ANY, wxString::FromUTF8("redo")); //"🢂"
    m_fowardBtn->Disable();
    m_pathLogic->SubscribeToRedo([this](StackEvent evt){
        if(evt == StackEvent::Empty)
            m_fowardBtn->Disable();
        else if(evt == StackEvent::IsNotEmpty)
            m_fowardBtn->Enable(); 
    });

    m_fowardBtn->Bind(wxEVT_BUTTON,[this] (wxCommandEvent&){
        m_pathLogic->Redo();
    });

    m_fowardBtn->SetFont(font);

    content->Add(m_backBtn, 0, wxLEFT, leftBtnMargin);
    content->Add(m_fowardBtn, 0, wxLEFT, rightBtnMargin);

    auto *textBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_pathTextBox = new wxTextCtrl(this, wxID_ANY);
    m_pathLogic->SubscribeToPathEvent([this](PathEvent evt){
        if(evt == PathEvent::UpdatePath)
            m_pathTextBox->SetValue(m_pathLogic->GetPath());
    });

    m_pathTextBox->SetWindowStyle(wxTE_PROCESS_ENTER | m_pathTextBox->GetWindowStyle());
    m_pathTextBox->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent&){
        m_pathLogic->SetPath(m_pathTextBox->GetValue());        
    });

    content->Add(textBoxSizer,1, wxEXPAND);
    textBoxSizer->Add(m_pathTextBox, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    
    SetSizer(sizer);
}






















