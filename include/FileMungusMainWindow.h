#pragma once
#include <wx/frame.h>
#include <memory>
#include <wx/bitmap.h>
#include <wx/gdicmn.h>


class FileMungusPathLogic;

class FileMungusMainWindow : public wxFrame
{
public:
    FileMungusMainWindow();
    ~FileMungusMainWindow();
    
private:
    std::unique_ptr<FileMungusPathLogic> m_pathLogic;
};
