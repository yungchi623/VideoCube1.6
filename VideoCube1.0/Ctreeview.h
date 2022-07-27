#pragma once
using namespace System::IO;
using namespace System;
using namespace System::Windows::Forms;


ref class Ctreeview
{
public:
	Ctreeview(void);
	void PopulateTreeView(TreeView^ treeView1, String ^ Path);
	void GetDirectories(array<DirectoryInfo^>^ subDirs,  TreeNode^ nodeToAddTo);
};
