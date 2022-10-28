//own
#include "mainwindow.h"
#include "ui_mainwindow.h"

//Qt
#include <QDebug>

//windows api files
#include <atlbase.h>
#include <shobjidl.h>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //create a com instance for the fileFialog
    IFileOpenDialog* fileFialog = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&fileFialog));

    //get the window's flags and set it
    DWORD flags;
    hr = fileFialog->GetOptions(&flags);
    hr = fileFialog->SetOptions(flags | FOS_ALLOWMULTISELECT | FOS_PICKFOLDERS);//support multiselect folder;

    //set the title of the fileFialog
    LPCWSTR title = _T("Open Folders");
    hr = fileFialog->SetTitle(title);

    //get the handle of this window, and set it the parent hander of the fileFialog
    hr = fileFialog->Show((HWND)this->winId());

    if (SUCCEEDED(hr))
    {
        //get all the selected folders
        IShellItemArray* items = nullptr;
        fileFialog->GetResults(&items);

        //get the number of all the selected folders
        DWORD itemsNum = 0;
        items->GetCount(&itemsNum);

        for (int i = 0; i < itemsNum; ++i)
        {
            //get one folder
            IShellItem* item = nullptr;
            items->GetItemAt(i, &item);

            //get the folder name
            LPWSTR path = nullptr;
            item->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &path);

            //convert LPWSTR to char*
            int nInputStrLen = wcslen(path);
            int nOutputStrLen = WideCharToMultiByte(CP_ACP, 0, path, nInputStrLen, NULL, 0, 0, 0) + 2;
            char* data = new char[nOutputStrLen];
            if (data != nullptr)
            {
                memset(data, 0x00, nOutputStrLen);
                WideCharToMultiByte(CP_ACP, 0, path, nInputStrLen, data, nOutputStrLen, 0, 0);
            }

            //free memory
            CoTaskMemFree(path);

            QString folderName = QString::fromLocal8Bit(data);
            qDebug() << folderName;
         }
    }
    else
    {
        qDebug() << "error: failed to initialize the IFileOpenDialog";
    }
}

