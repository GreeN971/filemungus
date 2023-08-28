#pragma once
#include <wx/dialog.h>
/*
enum class FileType 
{
    IsFolder,     
    IsFile
};
*/
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
