#include "StdAfx.h"
#include "Ctreeview.h"
#include <stdio.h>
Ctreeview::Ctreeview(void)
{
}

void Ctreeview::PopulateTreeView(TreeView^ treeView1, String^ Path)
{
	DirectoryInfo^ info = gcnew DirectoryInfo(Path);
	TreeNode^ rootNode = gcnew TreeNode;
    if (info->Exists)
    {
		rootNode = gcnew TreeNode(info->Name);
		rootNode->Tag = info;
		GetDirectories(info->GetDirectories(), rootNode);
		treeView1->Nodes->Add(rootNode);
    }
}

void Ctreeview::GetDirectories(array<DirectoryInfo^>^ subDirs, TreeNode^ nodeToAddTo)
{
    array<DirectoryInfo^>^ subSubDirs;
	TreeNode^ aNode;

	for(int i = 0 ; i < subDirs->Length; i++)
	{
		//aNode->Name = subDirs[i]->Name;
		aNode = gcnew TreeNode(subDirs[i]->Name,0,0);
		aNode->Tag = subDirs[i];
	    aNode->ImageKey = "folder";

		try
		{
			subSubDirs = subDirs[i]->GetDirectories();
			if (subSubDirs->Length != 0)
			{
				GetDirectories(subSubDirs, aNode);
			}
			nodeToAddTo->Nodes->Add(aNode);
		}
		catch(UnauthorizedAccessException^ e)
		{
			continue;
		}

	}
}


