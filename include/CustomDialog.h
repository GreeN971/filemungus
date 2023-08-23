#pragma once
#include <wx/dialog.h>

class CustomDialog : public wxDialog
{
public:
    CustomDialog(const wxString &title);
    bool IsSuccesfull() const noexcept;
protected:
    void SetSucces(bool succ) noexcept;
private: 
    bool m_succ;
};
