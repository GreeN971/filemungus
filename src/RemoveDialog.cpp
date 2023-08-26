#include "RemoveDialog.h"
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/log.h>

RemoveDialog::RemoveDialog() 
    : CustomDialog("Remove Dialog")
{
    SetMinSize(wxSize(300,-1));  
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *content = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *textSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticText *statText = new wxStaticText(this, wxID_ANY, "Do you want to remove");
    statText->SetFont(statText->GetFont().Scale(1.0f));

    textSizer->Add(statText, 0, wxALIGN_CENTER, 4);

    wxButton *ok = new wxButton(this, wxID_ANY, "OK");
    ok->Bind(wxEVT_BUTTON, [this](wxCommandEvent&){
        SetSucces(true);
        Close();
    });

    wxButton *cancel = new wxButton(this, wxID_ANY, "Cancel");
    cancel->Bind(wxEVT_BUTTON, [this](wxCommandEvent&){ Close(); });
    
    buttonSizer->AddSpacer(10);
    buttonSizer->Add(ok, 0, wxALL | wxBOTTOM, 4);
    buttonSizer->AddStretchSpacer();
    buttonSizer->Add(cancel, 0, wxALL | wxBOTTOM, 4);
    buttonSizer->AddSpacer(10);

    content->Add(textSizer, 0, wxLEFT, 4);
    content->AddSpacer(20);
    content->Add(buttonSizer, 1, wxLEFT | wxEXPAND, 4);
    sizer->Add(content, 1, wxEXPAND);

    SetSizerAndFit(sizer);
}

const wxString &RemoveDialog::GetNewFileName() const noexcept
{
   return m_fileName; 
}

