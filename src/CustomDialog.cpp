#include "CustomDialog.h"


CustomDialog::CustomDialog(const wxString &title) 
    : wxDialog(nullptr, wxID_ANY, title)                                                  
    , m_succ(false)
{
     
}

bool CustomDialog::IsSuccesfull() const noexcept
{
    return m_succ;
}

void CustomDialog::SetSucces(bool succ) noexcept
{
    m_succ = succ; 
}

