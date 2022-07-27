#pragma once
#include <stdio.h>
#include <windows.h>
#include "cv.h"
#include "Cube.h"
#include "VolumeBasedGHT.h"
#include "FrameSequenceToCubes.h"
#include "Ctreeview.h"
#include "VBGHTSimular.h"
#include "HumanRegionDetection.h"
#include "time.h"
#include "CountRank.h"

namespace VideoCube10 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Threading;

	//using namespace System::Windows::Forms;
	/// <summary>
	/// Form1 的摘要
	///
	/// 警告: 如果您變更這個類別的名稱，就必須變更與這個類別所依據之所有 .resx 檔案關聯的
	///          Managed 資源編譯器工具的 'Resource File Name' 屬性。
	///          否則，這些設計工具
	///          將無法與這個表單關聯的當地語系化資源
	///          正確互動。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		//char* OutPath;
		Form1(void)
		{
			InitializeComponent();

			//
			//TODO: 在此加入建構函式程式碼
			//

			Ctreeview CtreeviewObj;
			array<String^,1>^ p_logicalDrives =  gcnew cli::array <String^,1>(10);
			comboBox1->Items->Clear();
			p_logicalDrives = Directory::GetLogicalDrives();
			int numDrives = p_logicalDrives->Length;
			for (int i=0; i< numDrives; i++)
			{
				comboBox1->Items->Add(p_logicalDrives[i]);
			}

			CtreeviewObj.PopulateTreeView(treeView1,comboBox1->Text); 
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 




	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openFileToolStripMenuItem;
	private: System::Windows::Forms::ListView^  listView1;

	private: System::Windows::Forms::ProgressBar^  progressBar1;


	private: System::Windows::Forms::ToolStripMenuItem^  saveFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dataBaseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  建databaseToolStripMenuItem;




	private: System::Windows::Forms::TreeView^  treeView1;

	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;






	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::CheckBox^  checkBox6;
	private: System::Windows::Forms::CheckBox^  checkBox7;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::CheckBox^  checkBox5;


	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::CheckBox^  checkBox8;
	private: System::Windows::Forms::ListView^  listView3;
	private: System::Windows::Forms::ListView^  listView2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ToolStripMenuItem^  backgroundDifferenceToolStripMenuItem;




	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ListBox^  listBox2;


	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  T;
	private: System::Windows::Forms::ToolStripMenuItem^  catchImageToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::CheckBox^  checkBox9;

private: System::Windows::Forms::TextBox^  textBox6;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::TextBox^  textBox7;
private: System::Windows::Forms::GroupBox^  groupBox4;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::TextBox^  textBox8;
private: System::Windows::Forms::TextBox^  textBox9;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::TextBox^  textBox10;
private: System::Windows::Forms::CheckBox^  checkBox10;
private: System::Windows::Forms::ToolStripMenuItem^  videoRotationToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  noiseToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  resizeToolStripMenuItem;
private: System::Windows::Forms::CheckBox^  checkBox11;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::CheckBox^  checkBox3;
private: System::Windows::Forms::CheckBox^  checkBox12;
private: System::Windows::Forms::CheckBox^  checkBox1;







	private: System::ComponentModel::IContainer^  components;


	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改這個方法的內容。
		///
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dataBaseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->建databaseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->backgroundDifferenceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->catchImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->videoRotationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->noiseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->listView3 = (gcnew System::Windows::Forms::ListView());
			this->listView2 = (gcnew System::Windows::Forms::ListView());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox11 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox10 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox9 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox8 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->T = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox12 = (gcnew System::Windows::Forms::CheckBox());
			this->menuStrip1->SuspendLayout();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->dataBaseToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(990, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->openFileToolStripMenuItem, 
				this->saveFileToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openFileToolStripMenuItem
			// 
			this->openFileToolStripMenuItem->Name = L"openFileToolStripMenuItem";
			this->openFileToolStripMenuItem->Size = System::Drawing::Size(127, 22);
			this->openFileToolStripMenuItem->Text = L"OpenFile";
			this->openFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openFileToolStripMenuItem_Click);
			// 
			// saveFileToolStripMenuItem
			// 
			this->saveFileToolStripMenuItem->Name = L"saveFileToolStripMenuItem";
			this->saveFileToolStripMenuItem->Size = System::Drawing::Size(127, 22);
			this->saveFileToolStripMenuItem->Text = L"SaveFile";
			// 
			// dataBaseToolStripMenuItem
			// 
			this->dataBaseToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->建databaseToolStripMenuItem, 
				this->backgroundDifferenceToolStripMenuItem, this->catchImageToolStripMenuItem, this->videoRotationToolStripMenuItem, this->noiseToolStripMenuItem, 
				this->resizeToolStripMenuItem});
			this->dataBaseToolStripMenuItem->Name = L"dataBaseToolStripMenuItem";
			this->dataBaseToolStripMenuItem->Size = System::Drawing::Size(73, 20);
			this->dataBaseToolStripMenuItem->Text = L"DataBase";
			// 
			// 建databaseToolStripMenuItem
			// 
			this->建databaseToolStripMenuItem->Name = L"建databaseToolStripMenuItem";
			this->建databaseToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->建databaseToolStripMenuItem->Text = L"建database";
			this->建databaseToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::建databaseToolStripMenuItem_Click);
			// 
			// backgroundDifferenceToolStripMenuItem
			// 
			this->backgroundDifferenceToolStripMenuItem->Name = L"backgroundDifferenceToolStripMenuItem";
			this->backgroundDifferenceToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->backgroundDifferenceToolStripMenuItem->Text = L"BackgroundDifference";
			this->backgroundDifferenceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::backgroundDifferenceToolStripMenuItem_Click);
			// 
			// catchImageToolStripMenuItem
			// 
			this->catchImageToolStripMenuItem->Name = L"catchImageToolStripMenuItem";
			this->catchImageToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->catchImageToolStripMenuItem->Text = L"CatchImage";
			this->catchImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::catchImageToolStripMenuItem_Click);
			// 
			// videoRotationToolStripMenuItem
			// 
			this->videoRotationToolStripMenuItem->Name = L"videoRotationToolStripMenuItem";
			this->videoRotationToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->videoRotationToolStripMenuItem->Text = L"VideoRotation";
			this->videoRotationToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::videoRotationToolStripMenuItem_Click);
			// 
			// noiseToolStripMenuItem
			// 
			this->noiseToolStripMenuItem->Name = L"noiseToolStripMenuItem";
			this->noiseToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->noiseToolStripMenuItem->Text = L"Noise";
			this->noiseToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::noiseToolStripMenuItem_Click);
			// 
			// resizeToolStripMenuItem
			// 
			this->resizeToolStripMenuItem->Name = L"resizeToolStripMenuItem";
			this->resizeToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->resizeToolStripMenuItem->Text = L"Resize";
			this->resizeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::resizeToolStripMenuItem_Click);
			// 
			// listView1
			// 
			this->listView1->Location = System::Drawing::Point(0, 29);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(265, 170);
			this->listView1->TabIndex = 1;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::List;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(12, 628);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(950, 23);
			this->progressBar1->TabIndex = 3;
			// 
			// treeView1
			// 
			this->treeView1->Location = System::Drawing::Point(3, 28);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(197, 315);
			this->treeView1->TabIndex = 7;
			this->treeView1->NodeMouseDoubleClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &Form1::treeView1_NodeMouseDoubleClick);
			this->treeView1->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &Form1::treeView1_NodeMouseClick);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(3, 3);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(197, 20);
			this->comboBox1->TabIndex = 9;
			this->comboBox1->Text = L"D:\\";
			this->comboBox1->SelectedValueChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedValueChanged);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Location = System::Drawing::Point(12, 27);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->label5);
			this->splitContainer1->Panel1->Controls->Add(this->listBox2);
			this->splitContainer1->Panel1->Controls->Add(this->label4);
			this->splitContainer1->Panel1->Controls->Add(this->listBox1);
			this->splitContainer1->Panel1->Controls->Add(this->treeView1);
			this->splitContainer1->Panel1->Controls->Add(this->comboBox1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->label3);
			this->splitContainer1->Panel2->Controls->Add(this->label2);
			this->splitContainer1->Panel2->Controls->Add(this->label1);
			this->splitContainer1->Panel2->Controls->Add(this->listView3);
			this->splitContainer1->Panel2->Controls->Add(this->listView2);
			this->splitContainer1->Panel2->Controls->Add(this->listView1);
			this->splitContainer1->Size = System::Drawing::Size(475, 588);
			this->splitContainer1->SplitterDistance = 203;
			this->splitContainer1->TabIndex = 10;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 470);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(93, 12);
			this->label5->TabIndex = 16;
			this->label5->Text = L"DatabaseFileName:";
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->ItemHeight = 12;
			this->listBox2->Location = System::Drawing::Point(3, 485);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(200, 100);
			this->listBox2->TabIndex = 15;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 350);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(95, 12);
			this->label4->TabIndex = 15;
			this->label4->Text = L"TempleteFileName:";
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 12;
			this->listBox1->Location = System::Drawing::Point(0, 365);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(200, 100);
			this->listBox1->TabIndex = 14;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(3, 401);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(51, 12);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Templete:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(4, 207);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(33, 12);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Cube:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(4, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(36, 12);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Video:";
			// 
			// listView3
			// 
			this->listView3->Location = System::Drawing::Point(0, 416);
			this->listView3->Name = L"listView3";
			this->listView3->Size = System::Drawing::Size(265, 170);
			this->listView3->TabIndex = 3;
			this->listView3->UseCompatibleStateImageBehavior = false;
			this->listView3->View = System::Windows::Forms::View::List;
			// 
			// listView2
			// 
			this->listView2->Location = System::Drawing::Point(0, 222);
			this->listView2->Name = L"listView2";
			this->listView2->Size = System::Drawing::Size(265, 170);
			this->listView2->TabIndex = 2;
			this->listView2->UseCompatibleStateImageBehavior = false;
			this->listView2->View = System::Windows::Forms::View::List;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->checkBox11);
			this->groupBox2->Controls->Add(this->checkBox10);
			this->groupBox2->Controls->Add(this->checkBox6);
			this->groupBox2->Controls->Add(this->checkBox7);
			this->groupBox2->Location = System::Drawing::Point(501, 190);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(126, 120);
			this->groupBox2->TabIndex = 12;
			this->groupBox2->TabStop = false;
			// 
			// checkBox11
			// 
			this->checkBox11->AutoSize = true;
			this->checkBox11->Location = System::Drawing::Point(20, 90);
			this->checkBox11->Name = L"checkBox11";
			this->checkBox11->Size = System::Drawing::Size(100, 16);
			this->checkBox11->TabIndex = 22;
			this->checkBox11->Text = L"Detection Count";
			this->checkBox11->UseVisualStyleBackColor = true;
			// 
			// checkBox10
			// 
			this->checkBox10->AutoSize = true;
			this->checkBox10->Location = System::Drawing::Point(20, 68);
			this->checkBox10->Name = L"checkBox10";
			this->checkBox10->Size = System::Drawing::Size(102, 16);
			this->checkBox10->TabIndex = 20;
			this->checkBox10->Text = L"無用~同跑程式";
			this->checkBox10->UseVisualStyleBackColor = true;
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Location = System::Drawing::Point(20, 43);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(48, 16);
			this->checkBox6->TabIndex = 1;
			this->checkBox6->Text = L"測試";
			this->checkBox6->UseVisualStyleBackColor = true;
			// 
			// checkBox7
			// 
			this->checkBox7->AutoSize = true;
			this->checkBox7->Location = System::Drawing::Point(20, 21);
			this->checkBox7->Name = L"checkBox7";
			this->checkBox7->Size = System::Drawing::Size(60, 16);
			this->checkBox7->TabIndex = 0;
			this->checkBox7->Text = L"跑程式";
			this->checkBox7->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(903, 372);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 13;
			this->button1->Text = L"確定";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->textBox5);
			this->groupBox3->Controls->Add(this->textBox3);
			this->groupBox3->Controls->Add(this->checkBox9);
			this->groupBox3->Controls->Add(this->checkBox8);
			this->groupBox3->Controls->Add(this->textBox2);
			this->groupBox3->Controls->Add(this->textBox1);
			this->groupBox3->Controls->Add(this->checkBox4);
			this->groupBox3->Controls->Add(this->checkBox5);
			this->groupBox3->Location = System::Drawing::Point(493, 27);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(488, 114);
			this->groupBox3->TabIndex = 13;
			this->groupBox3->TabStop = false;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(146, 90);
			this->textBox5->Name = L"textBox5";
			this->textBox5->ReadOnly = true;
			this->textBox5->Size = System::Drawing::Size(332, 22);
			this->textBox5->TabIndex = 18;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(146, 64);
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(332, 22);
			this->textBox3->TabIndex = 6;
			// 
			// checkBox9
			// 
			this->checkBox9->AutoSize = true;
			this->checkBox9->Location = System::Drawing::Point(20, 92);
			this->checkBox9->Name = L"checkBox9";
			this->checkBox9->Size = System::Drawing::Size(47, 16);
			this->checkBox9->TabIndex = 17;
			this->checkBox9->Text = L"Path:";
			this->checkBox9->UseVisualStyleBackColor = true;
			// 
			// checkBox8
			// 
			this->checkBox8->AutoSize = true;
			this->checkBox8->Location = System::Drawing::Point(20, 66);
			this->checkBox8->Name = L"checkBox8";
			this->checkBox8->Size = System::Drawing::Size(93, 16);
			this->checkBox8->TabIndex = 5;
			this->checkBox8->Text = L"Template Path:";
			this->checkBox8->UseVisualStyleBackColor = true;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(146, 18);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(332, 22);
			this->textBox2->TabIndex = 4;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(146, 43);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(332, 22);
			this->textBox1->TabIndex = 3;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(20, 20);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(122, 16);
			this->checkBox4->TabIndex = 1;
			this->checkBox4->Text = L"Video Database Path:";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(19, 45);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(121, 16);
			this->checkBox5->TabIndex = 0;
			this->checkBox5->Text = L"Cube DataBase Path:";
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(575, 157);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(32, 22);
			this->textBox4->TabIndex = 16;
			this->textBox4->Text = L"10";
			// 
			// T
			// 
			this->T->AutoSize = true;
			this->T->Location = System::Drawing::Point(499, 163);
			this->T->Name = L"T";
			this->T->Size = System::Drawing::Size(71, 12);
			this->T->TabIndex = 7;
			this->T->Text = L"SimularTopN:";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(157, 15);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(32, 22);
			this->textBox6->TabIndex = 18;
			this->textBox6->Text = L"10";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 18);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(54, 12);
			this->label7->TabIndex = 19;
			this->label7->Text = L"TrainData:";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(87, 15);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(32, 22);
			this->textBox7->TabIndex = 20;
			this->textBox7->Text = L"10";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->label8);
			this->groupBox4->Controls->Add(this->label9);
			this->groupBox4->Controls->Add(this->textBox8);
			this->groupBox4->Controls->Add(this->textBox9);
			this->groupBox4->Controls->Add(this->label7);
			this->groupBox4->Controls->Add(this->label6);
			this->groupBox4->Controls->Add(this->textBox6);
			this->groupBox4->Controls->Add(this->textBox7);
			this->groupBox4->Location = System::Drawing::Point(662, 201);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(213, 73);
			this->groupBox4->TabIndex = 13;
			this->groupBox4->TabStop = false;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 46);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(48, 12);
			this->label8->TabIndex = 23;
			this->label8->Text = L"TestData:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(133, 46);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(9, 12);
			this->label9->TabIndex = 21;
			this->label9->Text = L"-";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(157, 43);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(32, 22);
			this->textBox8->TabIndex = 22;
			this->textBox8->Text = L"10";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(87, 43);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(32, 22);
			this->textBox9->TabIndex = 24;
			this->textBox9->Text = L"10";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(133, 18);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(9, 12);
			this->label6->TabIndex = 17;
			this->label6->Text = L"-";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(622, 163);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(57, 12);
			this->label10->TabIndex = 17;
			this->label10->Text = L"PeakTopN:";
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(685, 159);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(32, 22);
			this->textBox10->TabIndex = 18;
			this->textBox10->Text = L"10";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Controls->Add(this->checkBox3);
			this->groupBox1->Controls->Add(this->checkBox12);
			this->groupBox1->Location = System::Drawing::Point(501, 316);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(126, 93);
			this->groupBox1->TabIndex = 23;
			this->groupBox1->TabStop = false;
			this->groupBox1->Enter += gcnew System::EventHandler(this, &Form1::groupBox1_Enter);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(20, 63);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(68, 16);
			this->checkBox1->TabIndex = 2;
			this->checkBox1->Text = L"MutiVote";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(20, 43);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(58, 16);
			this->checkBox3->TabIndex = 1;
			this->checkBox3->Text = L"Scaling";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// checkBox12
			// 
			this->checkBox12->AutoSize = true;
			this->checkBox12->Location = System::Drawing::Point(20, 21);
			this->checkBox12->Name = L"checkBox12";
			this->checkBox12->Size = System::Drawing::Size(64, 16);
			this->checkBox12->TabIndex = 0;
			this->checkBox12->Text = L"Rotation";
			this->checkBox12->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(990, 663);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->textBox10);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->T);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->Panel2->PerformLayout();
			this->splitContainer1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: void Thread1()
{
	 char FileName[100],Path[200];
	 int NumberOfFiles = listView1->Items->Count;
	 char CubeFileName[300],VideoFileName[300];
	 int hasFile;
	 VolumeBasedGHT VolumeBasedGHTObj;

	 for(int FileIndex = 0; FileIndex < NumberOfFiles; FileIndex++)
	 {
		sprintf(FileName,"%s",listView1->Items[FileIndex]->Text->ToCharArray());
		listBox1->Items->Add(listView1->Items[FileIndex]->Text);
		sprintf(Path,"%s",textBox2->Text->ToCharArray());
		sprintf(VideoFileName, "%s\\%s",Path, FileName);
		sprintf(Path,"%s",textBox1->Text->ToCharArray());
		sprintf(CubeFileName, "%s\\%s", Path,FileName);
		hasFile = VolumeBasedGHTObj.ComputeCubeDataBase(VideoFileName,CubeFileName);
				
		if(hasFile == -1)
		{
			FILE *FilePtr2 = fopen("errorVideo.txt","a");
			fprintf(FilePtr2,"Input:%s\n",VideoFileName);
			fprintf(FilePtr2,"Database:%s\n",CubeFileName);
			fclose(FilePtr2);
		}			
	 }
}
private: void Thread2()
{
	char FileName[100],Path[200],ActionName[50];
	int TempleteNumberOfFiles = listView3->Items->Count;
	int CubeNumberOfFiles =  listView2->Items->Count;
	char VideoFileName[300],CubeFileName[300],TempleteFileName[300];
	VolumeBasedGHT VolumeBasedGHTObj;
	int hasFile,SimularTopN,PeakTopN;
	double TopSimilar;

	array<String^,1>^ ActionFileName;
	char TempleteAction[50],DatabaseAction[50];

	 char STestNumber[3], ETestNumber[3], STrainNumber[3], ETrainNumber[3];
	  int StrainNumber,EtrainNumber,StestNumber,EtestNumber;
	  sprintf(STrainNumber,"%s",textBox7->Text->ToCharArray());
	  StrainNumber = atoi(STrainNumber);
	  sprintf(ETrainNumber,"%s",textBox6->Text->ToCharArray());
	  EtrainNumber = atoi(ETrainNumber);
	  sprintf(STestNumber,"%s",textBox9->Text->ToCharArray());
	  StestNumber = atoi(STestNumber);
	  sprintf(ETestNumber,"%s",textBox8->Text->ToCharArray());
	  EtestNumber = atoi(ETestNumber);
	  sprintf(ETestNumber,"%s",textBox4->Text->ToCharArray());//simulartopN
	  SimularTopN = atoi(ETestNumber);
	  sprintf(ETestNumber,"%s",textBox10->Text->ToCharArray());//PeaktopN
	  PeakTopN = atoi(ETestNumber);
	  bool Scaling = false;
	  bool Rotation = false;
	  bool MutiVote = false;


	  if(checkBox1->Checked == true)
	  {
		MutiVote = true;
	  }
	  if(checkBox12->Checked == true)
	  {
		  Rotation = true;
	  }
	  if(checkBox3->Checked == true)
	  {
		  Scaling = true;
	  }

	progressBar1->Minimum = StestNumber;
	progressBar1->Maximum = StestNumber + (EtestNumber - StestNumber) - 1;
	for(int FileIndex = StestNumber ; FileIndex < StestNumber + (EtestNumber - StestNumber); FileIndex++)
	{
		progressBar1->Value = FileIndex;
		time_t start;
		VBGHTSimular VBGHTSimularObj(SimularTopN);
		sprintf(FileName,"%s",listView3->Items[FileIndex]->Text->ToCharArray()); //templete
		sprintf(Path,"%s",textBox3->Text->ToCharArray());
		sprintf(TempleteFileName, "%s\\%s", Path,FileName);
		for(int DataIndex = StrainNumber; DataIndex < EtrainNumber; DataIndex++)
		{
			ImagePoint *VoteCoordinate;
			sprintf(FileName,"%s",listView2->Items[DataIndex]->Text->ToCharArray()); //Cube
			sprintf(Path,"%s",textBox1->Text->ToCharArray());
			sprintf(CubeFileName, "%s\\%s",Path, FileName);
			sprintf(FileName,"%s",listView1->Items[DataIndex]->Text->ToCharArray()); //Video						
			sprintf(Path,"%s",textBox2->Text->ToCharArray());
			sprintf(VideoFileName, "%s\\%s", Path,FileName);
			start = clock();
			hasFile = VolumeBasedGHTObj.ComputeRTable(TempleteFileName);
			listBox1->Items->Add(listView3->Items[FileIndex]->Text);
			if(hasFile == -1)
			{
				FILE *FilePtr2 = fopen("errorVideo.txt","a");
				fprintf(FilePtr2,"Input:%s\n",TempleteFileName);
				fprintf(FilePtr2,"Database:%s\n",CubeFileName);
				fclose(FilePtr2);
			}
			else
			{
				hasFile = VolumeBasedGHTObj.LoadCubeDataBase(CubeFileName);//hasFile
				if(hasFile == -1)
				{
					FILE *FilePtr2 = fopen("errorVideo.txt","a");
					fprintf(FilePtr2,"Input:%s\n",TempleteFileName);
					fprintf(FilePtr2,"Database:%s\n",CubeFileName);
					fclose(FilePtr2);
				}
				else
				{
					TopSimilar = VolumeBasedGHTObj.Voting(VideoFileName,CubeFileName,PeakTopN,FileName,Scaling,Rotation,MutiVote);
					VoteCoordinate = VolumeBasedGHTObj.GetVoteCoordinate();
					ActionFileName = listView2->Items[DataIndex]->Text->Split('_','.');
					sprintf(FileName,"%s",listView2->Items[DataIndex]->Text->ToCharArray());
					sprintf(DatabaseAction,"%s",ActionFileName[1]); //DatabaseAction
					//VBGHTSimularObj.Simularity(TopSimilar,DatabaseAction,FileName);
					VBGHTSimularObj.VoteCoordinateSimularity(VoteCoordinate,PeakTopN);
					VolumeBasedGHTObj.ReleaseVoteTable();
					VolumeBasedGHTObj.Release();
				}

				VolumeBasedGHTObj.ReleaseRTable();
			}
			listBox2->Items->Add(listView2->Items[DataIndex]->Text);
			//delete VoteCoordinate;
			//VoteCoordinate = NULL;
		}
		ActionFileName = listView3->Items[FileIndex]->Text->Split('_','.');
		sprintf(TempleteAction,"%s",ActionFileName[1]); //DataBaseAction
		sprintf(FileName,"%s",listView3->Items[FileIndex]->Text->ToCharArray());
		time_t end = clock() - start;
		//VBGHTSimularObj.ResultSimular(TempleteAction,FileName,end);
		VBGHTSimularObj.SaveResultSimular(FileName,TempleteAction,end);
		VBGHTSimularObj.Release();		 
	}
}




private: System::Void openFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

				/*Stream^ myStream;
				  int NumberOfFiles,FileLen;
				  char cFileName[10];
				  array<String^,1>^ sFileName;
				  OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
				  openFileDialog1->InitialDirectory = "d:\\";
				  openFileDialog1->Filter = "";
				  openFileDialog1->FilterIndex = 2;
				  openFileDialog1->RestoreDirectory = true;
				  openFileDialog1->Multiselect = true;

				  if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				  {
					 if ( (myStream = openFileDialog1->OpenFile()) != nullptr )
					 {
						// Insert code to read the stream here.
						 NumberOfFiles = openFileDialog1->FileNames->Length;
						 for(int FileIndex = 0; FileIndex < NumberOfFiles; FileIndex++)
						 {
							sFileName = openFileDialog1->FileNames[FileIndex]->Split('\\');
						 }

						 myStream->Close();
					 }
				  }*/

		 }
private: System::Void 建databaseToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		Form::CheckForIllegalCrossThreadCalls = false;

		ThreadStart^ myThreadDelegate = gcnew ThreadStart(this, &VideoCube10::Form1::Thread1);
		Thread^ trd = gcnew Thread(myThreadDelegate);
		trd->IsBackground = true;
	    trd->Start();

   

	}


private: System::Void treeView1_NodeMouseClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e) {
			TreeNode^ newSelected = e->Node;
			DirectoryInfo^ nodeDirInfo = (DirectoryInfo^)newSelected->Tag;
			ListViewItem^ item;
			array<DirectoryInfo^>^ dir = nodeDirInfo->GetDirectories();
			if(checkBox4->Checked == true)
			{
				listView1->Items->Clear();
				for(int i = 0 ; i < dir->Length; i++)
				{
					item = gcnew ListViewItem(dir[i]->Name, 0);
					item->SubItems->Add("Directory");
					item->SubItems->Add( dir[i]->LastAccessTime.ToShortDateString());
					listView1->Items->Add(item);
				}
				array<FileInfo^>^ file = nodeDirInfo->GetFiles();
				for(int i = 0 ; i < file->Length; i++)
				{
					item = gcnew ListViewItem(file[i]->Name, 1);
					item->SubItems->Add("File");
					item->SubItems->Add(file[i]->LastAccessTime.ToShortDateString());
					listView1->Items->Add(item);
				}

				listView1->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
			}

			if(checkBox5->Checked == true)
			{
				listView2->Items->Clear();
				for(int i = 0 ; i < dir->Length; i++)
				{
					item = gcnew ListViewItem(dir[i]->Name, 0);
					item->SubItems->Add("Directory");
					item->SubItems->Add( dir[i]->LastAccessTime.ToShortDateString());
					listView2->Items->Add(item);
				}
				array<FileInfo^>^ file = nodeDirInfo->GetFiles();
				for(int i = 0 ; i < file->Length; i++)
				{
					item = gcnew ListViewItem(file[i]->Name, 1);
					item->SubItems->Add("File");
					item->SubItems->Add(file[i]->LastAccessTime.ToShortDateString());
					listView2->Items->Add(item);
				}

				listView2->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
			}

			if(checkBox8->Checked == true)
			{
				listView3->Items->Clear();
				for(int i = 0 ; i < dir->Length; i++)
				{
					item = gcnew ListViewItem(dir[i]->Name, 0);
					item->SubItems->Add("Directory");
					item->SubItems->Add( dir[i]->LastAccessTime.ToShortDateString());
					listView3->Items->Add(item);
				}
				array<FileInfo^>^ file = nodeDirInfo->GetFiles();
				for(int i = 0 ; i < file->Length; i++)
				{
					item = gcnew ListViewItem(file[i]->Name, 1);
					item->SubItems->Add("File");
					item->SubItems->Add(file[i]->LastAccessTime.ToShortDateString());
					listView3->Items->Add(item);
				}

				listView3->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
			}
		 }

private: System::Void comboBox1_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
			Ctreeview CtreeviewObj;
			treeView1->Nodes->Clear();
			listView1->Items->Clear();
			CtreeviewObj.PopulateTreeView(treeView1,comboBox1->Text); 
		 }
private: System::Void treeView1_NodeMouseDoubleClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e) {
			String^ Path = e->Node->FullPath;

				if(checkBox5->Checked == true)
				{
					textBox1->Text = Path;
				}
				if(checkBox4->Checked == true)
				{
					textBox2->Text = Path;
				}
				if(checkBox8->Checked == true)
				{
					textBox3->Text = Path;
				}

				if(checkBox9->Checked == true)
				{
					textBox5->Text = Path;
				}
		 }

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			Form::CheckForIllegalCrossThreadCalls = false;

				char FileName[100],Path[200],ActionName[50];
				int TempleteNumberOfFiles = listView3->Items->Count;
				int CubeNumberOfFiles =  listView2->Items->Count;
				char VideoFileName[300],CubeFileName[300],TempleteFileName[300];
				VolumeBasedGHT VolumeBasedGHTObj;
				int hasFile,SimularTopN,PeakTopN;
				double TopSimilar;
				ImagePoint *VoteCoordinate;
				array<String^,1>^ ActionFileName;
				char TempleteAction[50],DatabaseAction[50];
				bool Rotation = false;
				bool Scaling = false;
				bool MutiVote = false;

				 char STestNumber[3], ETestNumber[3], STrainNumber[3], ETrainNumber[3];
				  int StrainNumber,EtrainNumber,StestNumber,EtestNumber;
				  sprintf(STrainNumber,"%s",textBox7->Text->ToCharArray());
				  StrainNumber = atoi(STrainNumber);
				  sprintf(ETrainNumber,"%s",textBox6->Text->ToCharArray());
				  EtrainNumber = atoi(ETrainNumber);
				  sprintf(STestNumber,"%s",textBox9->Text->ToCharArray());
				  StestNumber = atoi(STestNumber);
				 sprintf(ETestNumber,"%s",textBox8->Text->ToCharArray());
				  EtestNumber = atoi(ETestNumber);
				  sprintf(ETestNumber,"%s",textBox4->Text->ToCharArray());//simulartopN
				  SimularTopN = atoi(ETestNumber);
				  sprintf(ETestNumber,"%s",textBox10->Text->ToCharArray());//PeaktopN
				  PeakTopN = atoi(ETestNumber);

				if(checkBox1->Checked == true)
				{
					MutiVote = true;
				}
				if(checkBox12->Checked == true)
				{
					Rotation = true;
				}
				if(checkBox3->Checked == true)
				{
					Scaling = true;
				}

				if(checkBox6->Checked == true)
				{
					//ThreadStart^ myThreadDelegate = gcnew ThreadStart(this, &VideoCube10::Form1::Thread5);
					//Thread^ trd = gcnew Thread(myThreadDelegate);
					//trd->IsBackground = true;
					//trd->Start();

					if(textBox1->Text->Length == 0 )
					{
						MessageBox::Show("Cube DataBase Path Error!");
					}
					else if( textBox2->Text->Length == 0 )
					{
						MessageBox::Show("Video DataBase Path Error!");
					}
					else if(textBox3->Text->Length == 0)
					{
						MessageBox::Show("Template Path Error!");
					}
					else
					{
						
						progressBar1->Minimum = 0;
						progressBar1->Maximum = TempleteNumberOfFiles-1;
						for(int FileIndex = 0; FileIndex < TempleteNumberOfFiles; FileIndex++)
						{
							progressBar1->Value = FileIndex;
							time_t start;
							VBGHTSimular VBGHTSimularObj(SimularTopN);
							sprintf(FileName,"%s",listView3->Items[FileIndex]->Text->ToCharArray()); //templete
							sprintf(Path,"%s",textBox3->Text->ToCharArray());
							sprintf(TempleteFileName, "%s\\%s", Path,FileName);
							for(int DataIndex = 0; DataIndex < CubeNumberOfFiles; DataIndex++)
							{
								sprintf(FileName,"%s",listView2->Items[DataIndex]->Text->ToCharArray()); //Cube
								sprintf(Path,"%s",textBox1->Text->ToCharArray());
								sprintf(CubeFileName, "%s\\%s",Path, FileName);
								sprintf(FileName,"%s",listView1->Items[DataIndex]->Text->ToCharArray()); //Video						
								sprintf(Path,"%s",textBox2->Text->ToCharArray());
								sprintf(VideoFileName, "%s\\%s", Path,FileName);
								//if(!strcmp(VideoFileName,TempleteFileName))
									//continue;
								//start = clock();
								hasFile = VolumeBasedGHTObj.ComputeRTable(TempleteFileName);
								listBox1->Items->Add(listView3->Items[FileIndex]->Text);
								if(hasFile == -1)
								{
									FILE *FilePtr2 = fopen("errorVideo.txt","a");
									fprintf(FilePtr2,"Input:%s\n",TempleteFileName);
									fprintf(FilePtr2,"Database:%s\n",CubeFileName);
									fclose(FilePtr2);
								}
								else
								{
									hasFile = VolumeBasedGHTObj.LoadCubeDataBase(CubeFileName);//hasFile
									if(hasFile == -1)
									{
										FILE *FilePtr2 = fopen("errorVideo.txt","a");
										fprintf(FilePtr2,"Input:%s\n",TempleteFileName);
										fprintf(FilePtr2,"Database:%s\n",CubeFileName);
										fclose(FilePtr2);
									}
									else
									{
										TopSimilar = VolumeBasedGHTObj.Voting(VideoFileName,CubeFileName,PeakTopN,FileName,Scaling,Rotation,MutiVote);
										VoteCoordinate = VolumeBasedGHTObj.GetVoteCoordinate();
										ActionFileName = listView2->Items[DataIndex]->Text->Split('_','.');
										sprintf(FileName,"%s",listView2->Items[DataIndex]->Text->ToCharArray());
										sprintf(DatabaseAction,"%s",ActionFileName[1]); //DatabaseAction
										//VBGHTSimularObj.Simularity(TopSimilar,DatabaseAction,FileName);
										VBGHTSimularObj.VoteCoordinateSimularity(VoteCoordinate,10);
										VolumeBasedGHTObj.ReleaseVoteTable();
										VolumeBasedGHTObj.Release();
									}

									VolumeBasedGHTObj.ReleaseRTable();
								}
								listBox2->Items->Add(listView2->Items[DataIndex]->Text);

							}
							ActionFileName = listView3->Items[FileIndex]->Text->Split('_','.');
							sprintf(TempleteAction,"%s",ActionFileName[1]); //DataBaseAction
							sprintf(FileName,"%s",listView3->Items[FileIndex]->Text->ToCharArray());
							time_t end = clock() - start;
							//VBGHTSimularObj.ResultSimular(TempleteAction,FileName,end);
							VBGHTSimularObj.SaveResultSimular(FileName,TempleteAction,end);
							VBGHTSimularObj.Release();	 
						}
					}
				}

				if(checkBox7->Checked == true)
				{
					if(textBox1->Text->Length == 0 )
					{
						MessageBox::Show("Cube DataBase Path Error!");
					}
					else if( textBox2->Text->Length == 0 )
					{
						MessageBox::Show("Video DataBase Path Error!");
					}
					else if(textBox3->Text->Length == 0)
					{
						MessageBox::Show("Template Path Error!");
					}
					else
					{

						ThreadStart^ myThreadDelegate = gcnew ThreadStart(this, &VideoCube10::Form1::Thread2);
						Thread^ trd = gcnew Thread(myThreadDelegate);
						trd->IsBackground = true;
						trd->Start();
					}

				}

				if(checkBox10->Checked == true)
				{
					if(textBox1->Text->Length == 0 )
					{
						MessageBox::Show("Cube DataBase Path Error!");
					}
					else if( textBox2->Text->Length == 0 )
					{
						MessageBox::Show("Video DataBase Path Error!");
					}
					else if(textBox3->Text->Length == 0)
					{
						MessageBox::Show("Template Path Error!");
					}
					else
					{
						progressBar1->Minimum = StestNumber;
						progressBar1->Maximum = EtestNumber  - 1; 
						for(int FileIndex = StestNumber ; FileIndex < EtestNumber; FileIndex++)
						{
							progressBar1->Value = FileIndex;
							time_t start;
							sprintf(FileName,"%s",listView3->Items[FileIndex]->Text->ToCharArray()); //templete
							sprintf(Path,"%s",textBox3->Text->ToCharArray());
							sprintf(TempleteFileName, "%s\\%s", Path,FileName);
							int DataIndex = FileIndex;
							ImagePoint *VoteCoordinate;

							sprintf(FileName,"%s",listView2->Items[DataIndex]->Text->ToCharArray()); //Cube
							sprintf(Path,"%s",textBox1->Text->ToCharArray());
							sprintf(CubeFileName, "%s\\%s",Path, FileName);
							sprintf(FileName,"%s",listView1->Items[DataIndex]->Text->ToCharArray()); //Video						
							sprintf(Path,"%s",textBox2->Text->ToCharArray());
							sprintf(VideoFileName, "%s\\%s", Path,FileName);
							start = clock();
							hasFile = VolumeBasedGHTObj.ComputeRTable(TempleteFileName);
							listBox1->Items->Add(listView3->Items[FileIndex]->Text);
							if(hasFile == -1)
							{
								FILE *FilePtr2 = fopen("errorVideo.txt","a");
								fprintf(FilePtr2,"Input:%s\n",TempleteFileName);
								fprintf(FilePtr2,"Database:%s\n",CubeFileName);
								fclose(FilePtr2);
							}
							else
							{
								hasFile = VolumeBasedGHTObj.LoadCubeDataBase(CubeFileName);//hasFile
								if(hasFile == -1)
								{
									FILE *FilePtr2 = fopen("errorVideo.txt","a");
									fprintf(FilePtr2,"Input:%s\n",TempleteFileName);
									fprintf(FilePtr2,"Database:%s\n",CubeFileName);
									fclose(FilePtr2);
								}
								else
								{
									TopSimilar = VolumeBasedGHTObj.Voting(VideoFileName,CubeFileName,PeakTopN,FileName,Scaling,Rotation,MutiVote);
									VoteCoordinate = VolumeBasedGHTObj.GetVoteCoordinate();
									VolumeBasedGHTObj.ReleaseVoteTable();
									VolumeBasedGHTObj.Release();
								}

								VolumeBasedGHTObj.ReleaseRTable();
							}
							time_t end = clock() - start;		
						}
					}
				}

			if(checkBox11->Checked == true)
			{
				if(textBox5->Text->Length == 0)
				{
					MessageBox::Show("Path Error!");
				}
				else
				{
					CountRank CountRankObj;
					for(int FileIndex = StestNumber ; FileIndex < EtestNumber; FileIndex++)
					{
						sprintf(FileName,"%s",listView3->Items[FileIndex]->Text->ToCharArray()); //templete
						sprintf(Path,"%s",textBox5->Text->ToCharArray());
						sprintf(TempleteFileName, "%s\\%s", Path,FileName);
						CountRankObj.ComputeRank(TempleteFileName,30,FileIndex);
					}	
					CountRankObj.SaveDetection("Test\\Detection.txt");
				}
			}

		 }

private: System::Void backgroundDifferenceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				  Stream^ myStream;
				  int hasFile;
				  array<wchar_t>^ wFileName;
				  int NumberOfFiles,FileLen,NumberOfList;
				  char cFileName[100];
				  array<String^,1>^ sFileName;
				  OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
				  openFileDialog1->InitialDirectory = "d:\\";
				  openFileDialog1->Filter = "";
				  openFileDialog1->FilterIndex = 2;
				  openFileDialog1->RestoreDirectory = true;
				  openFileDialog1->Multiselect = true;
				  VolumeBasedGHT VolumeBasedGHTObj;
				  char OutputFileName[300],InputFileName[300];
				  char* OutPath;
				  HumanRegionDetection HumanRegionDetectionObj;

					 if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
					 {
						if((myStream = openFileDialog1->OpenFile()) != nullptr )
						 {
							NumberOfFiles = openFileDialog1->FileNames->Length;
							for(int FileIndex = 0; FileIndex < NumberOfFiles; FileIndex++)
							{
								wFileName = openFileDialog1->FileNames[FileIndex]->ToCharArray();
								sFileName = openFileDialog1->FileNames[FileIndex]->Split('\\');
								sprintf(InputFileName, "%s", wFileName);
								//FileLen = sFileName->Length;
								//wFileName = sFileName[FileLen-1]->ToCharArray();
								//sprintf(cFileName, "%s", wFileName);
								//OutPath = new char[textBox1->Text->Length];
								//wFileName = textBox1->Text->ToCharArray();
								//sprintf(OutPath,"%s",wFileName);
								//sprintf(OutputFileName, "%s\\%s", OutPath,cFileName);
								HumanRegionDetectionObj.ComputeHumanRegion(InputFileName);
							}
						 }
					 }

		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void catchImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	 }
private: System::Void videoRotationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Stream^ myStream;
			  int Length;
			  array<wchar_t>^ wFileName;
			  int NumberOfFiles,FileLen,NumberOfList;
			  char cFileName[100];
			  array<String^,1>^ sFileName;
			  OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			  openFileDialog1->InitialDirectory = "d:\\";
			  openFileDialog1->Filter = "";
			  openFileDialog1->FilterIndex = 2;
			  openFileDialog1->RestoreDirectory = true;
			  openFileDialog1->Multiselect = true;
			  VolumeBasedGHT VolumeBasedGHTObj;
			  char InputFileName[300],FileName[100];
			  char OutPath[200];
			  HumanRegionDetection HumanRegionDetectionObj;
			  char framenumber[3];
			  sprintf(framenumber,"%s",textBox6->Text->ToCharArray());
			  int NumberFrame = atoi(framenumber);
				 if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				 {
					if((myStream = openFileDialog1->OpenFile()) != nullptr )
					 {
						NumberOfFiles = openFileDialog1->FileNames->Length;
						for(int FileIndex = 0; FileIndex < NumberOfFiles; FileIndex++)
						{
							wFileName = openFileDialog1->FileNames[FileIndex]->ToCharArray();
							sFileName = openFileDialog1->FileNames[FileIndex]->Split('\\');
							sprintf(OutPath,"%s",textBox5->Text->ToCharArray());
							sprintf(InputFileName, "%s",wFileName);
							Length = sFileName->Length;
							wFileName = sFileName[Length-1]->ToCharArray();
							sprintf(FileName,"%s",wFileName);
							HumanRegionDetectionObj.RotationVideo(30,InputFileName);
							HumanRegionDetectionObj.SaveVideo(OutPath,FileName);
						}
					 }
				 }

		 }
private: System::Void noiseToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			  Stream^ myStream;
			  int Length;
			  array<wchar_t>^ wFileName;
			  int NumberOfFiles,FileLen,NumberOfList;
			  char cFileName[100];
			  array<String^,1>^ sFileName;
			  OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			  openFileDialog1->InitialDirectory = "d:\\";
			  openFileDialog1->Filter = "";
			  openFileDialog1->FilterIndex = 2;
			  openFileDialog1->RestoreDirectory = true;
			  openFileDialog1->Multiselect = true;
			  VolumeBasedGHT VolumeBasedGHTObj;
			  char InputFileName[300],FileName[100];
			  char OutPath[200];
			  HumanRegionDetection HumanRegionDetectionObj;
			  char framenumber[3];
			  sprintf(framenumber,"%s",textBox6->Text->ToCharArray());
			  int NumberFrame = atoi(framenumber);
				 if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				 {
					if((myStream = openFileDialog1->OpenFile()) != nullptr )
					 {
						NumberOfFiles = openFileDialog1->FileNames->Length;
						for(int FileIndex = 0; FileIndex < NumberOfFiles; FileIndex++)
						{
							wFileName = openFileDialog1->FileNames[FileIndex]->ToCharArray();
							sFileName = openFileDialog1->FileNames[FileIndex]->Split('\\');
							sprintf(OutPath,"%s",textBox5->Text->ToCharArray());
							sprintf(InputFileName, "%s",wFileName);
							Length = sFileName->Length;
							wFileName = sFileName[Length-1]->ToCharArray();
							sprintf(FileName,"%s",wFileName);
							HumanRegionDetectionObj.AddNoise(InputFileName);
							HumanRegionDetectionObj.SaveVideo(OutPath,FileName);
						}
					 }
				 }

		 }
private: System::Void resizeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Stream^ myStream;
			  int Length;
			  array<wchar_t>^ wFileName;
			  int NumberOfFiles,FileLen,NumberOfList;
			  char cFileName[100];
			  array<String^,1>^ sFileName;
			  OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			  openFileDialog1->InitialDirectory = "d:\\";
			  openFileDialog1->Filter = "";
			  openFileDialog1->FilterIndex = 2;
			  openFileDialog1->RestoreDirectory = true;
			  openFileDialog1->Multiselect = true;
			  VolumeBasedGHT VolumeBasedGHTObj;
			  char InputFileName[300],FileName[100];
			  char OutPath[200];
			  HumanRegionDetection HumanRegionDetectionObj;
			  char framenumber[3];
			  sprintf(framenumber,"%s",textBox6->Text->ToCharArray());
			  int NumberFrame = atoi(framenumber);
				 if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				 {
					if((myStream = openFileDialog1->OpenFile()) != nullptr )
					 {
						NumberOfFiles = openFileDialog1->FileNames->Length;
						for(int FileIndex = 0; FileIndex < NumberOfFiles; FileIndex++)
						{
							wFileName = openFileDialog1->FileNames[FileIndex]->ToCharArray();
							sFileName = openFileDialog1->FileNames[FileIndex]->Split('\\');
							sprintf(OutPath,"%s",textBox5->Text->ToCharArray());
							sprintf(InputFileName, "%s",wFileName);
							Length = sFileName->Length;
							wFileName = sFileName[Length-1]->ToCharArray();
							sprintf(FileName,"%s",wFileName);
							HumanRegionDetectionObj.ReSize(2.0,InputFileName);
							HumanRegionDetectionObj.SaveVideo(OutPath,FileName);
						}
					 }
				 }

		 }
private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

