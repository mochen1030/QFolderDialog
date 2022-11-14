# Introduction
This is an implement of multi-selection folder dialog using windows api, which can be used in Qt program.

It is surprise that there is no function to select folders and return the paths of folders by class QFileDialog in Qt, My Qt version in use is Qt 5.12.11.

I do not know that if this feature is available in the later version. I hope it.

Btw, there is a solution by native Qt. The code is as follows:

```
QFileDialog *pFileDlg = new QFileDialog(this, QString::fromLocal8Bit("Open file"));
pFileDlg->setFileMode(QFileDialog::Directory);
pFileDlg->setOption(QFileDialog::DontUseNativeDialog, true);
pFileDlg->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);
pFileDlg->setAttribute(Qt::WA_DeleteOnClose);
pFileDlg->resize(960, 540);
QListView *listView = pFileDlg->findChild<QListView *>();
QTreeView *treeView = pFileDlg->findChild<QTreeView *>();
if (listView)
{
	listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	listView->setContextMenuPolicy(Qt::NoContextMenu);
}
if (treeView)
{
	treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	treeView->setContextMenuPolicy(Qt::NoContextMenu);
}
pFileDlg->exec();
```

But, this file dialog is not beautiful enough, and it even may cause my program crash in other Windows PC. I prefer the native Windows file dialog.

After searching a lot, I get a solution. It is not hard to open a multi-selection folder dialog by windows api. And the windows api can be used in Qt program directly. 

All details are given in the repository, the folder named **FolderDialog**.

Refer: Common Item Dialog: https://learn.microsoft.com/en-us/windows/win32/shell/common-file-dialog?redirectedfrom=MSDN

# Contact me

I have just learned Qt programming for about one year, I'm glad you gave me some advice for the code or other.

If you want, you can contact me by email: 503343831@qq.com or wangjunweiwang1030@gmail.com.

It's my pleasure.
