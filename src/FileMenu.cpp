#include "FileMenu.h"
#include "FileView.h"
#include <iostream>
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/listbox.h>
#include <wx/debug.h>
#include <wx/artprov.h>

enum
{
    RENAME_ID = 0x6969,
    REMOVE_ID = 0x1337,
    COPY_ID = 6969,
    PASTE_ID = 0x420,
    CREATEFILE_ID = 1337,
    CREATEFOLDER = 4205
};

FileMenu::FileMenu(FileView *parent) 
    : wxMenu()
    , m_fileView(parent)
{
    wxASSERT_MSG(parent != nullptr, "FileView is null");
    wxMenuItem *renameItem = new wxMenuItem(this, RENAME_ID, "Rename");
    wxMenuItem *createFileItem = new wxMenuItem(this, CREATEFILE_ID, "Create File");
    wxMenuItem *createFolderItem = new wxMenuItem(this, CREATEFOLDER, "Create Folder"); 
    renameItem->SetBitmap(wxArtProvider::GetBitmap(wxART_WARNING));
    Bind(wxEVT_MENU, [this](wxCommandEvent &e){
        
        std::cout<< e.GetId() << std::endl;
        if(e.GetId() == RENAME_ID)
            m_fileView->RenameSelected();

        if(e.GetId() == CREATEFILE_ID)
            m_fileView->CreateFile();

        if(e.GetId() == CREATEFOLDER)
           m_fileView->CreateFolder(); 

    });
    /*
    Bind(wxEVT_MENU, [this](wxCommandEvent &e){
     std::cout<< e.GetId() << std::endl;
        if(e.GetId() == CREATEFILE_ID)
            m_fileView->CreateFile();

    });
    */
    
    Append(renameItem);
    Append(createFileItem);
    Append(createFolderItem);
    Append(wxID_ANY, "Remove");
    Append(wxID_ANY, "Copy");
    //m_content->Append("Paste"); 
}  
