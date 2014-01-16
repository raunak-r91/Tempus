/*
Author : Hunar Khanna
Form1 does the following:
--Forms the main interface between the user and the MainLogic
--Consists of a number of event triggers and helper functions to ease the user interaction with the system
--The information entered by the user is passed to the MainLogic where it is processed and the returned output is displayed to the user.
*/
#pragma once
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "user32.lib")

//#include <tlhelp32.h>
#include "MainLogic.h"
#include "SplashScreen.h"
#include <windows.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>

#define AUTOCOMPLETE_LIST_SIZE 25
#define MAX_LINES_PER_PAGE 15
#using<system.dll>


namespace TempusGUI {
	using namespace std;
	using namespace System;
	using namespace System::Media;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Specialized;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	enum BackgroundWorkType 
	{
		DO_NOTHING = 0,
		REMINDER = 1 ,
		UPDATE_AGENDA = 2
	};
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		
		[DllImport("user32")]
		static bool AnimateWindow(IntPtr hwnd, int time, int flags);
		Form1(void)
		{
			splash = gcnew SplashScreen();
			test1 = new MainLogic();
			pages = gcnew StringCollection;
			COMMANDHELP_TEXT = L"Commands :    add       show       delete       edit       agenda" + Environment::NewLine   
				                              + "                            done       undo       history       pending       exit"; 
			COMMANDBOX_TEXT = L"                             Enter Command Here";
			stringCollection = gcnew cli::array<System::String ^>(AUTOCOMPLETE_LIST_SIZE){
			L"show",L"add",
				L"delete",
				L"edit",
				L"date",
				L"time",L"location",L"exit",L"priority",L"time",L"today",L"tomorrow",L"undo",L"history"
				,L"pending",L"monday",L"tuesday",L"wednesday",L"thursday",L"friday",L"saturday",L"sunday"
				,L"agenda",L"done", L"ftime"};
			InitializeComponent();
			this->SetStyle(ControlStyles::DoubleBuffer |
				ControlStyles::OptimizedDoubleBuffer |
				ControlStyles::UserPaint |
				ControlStyles::AllPaintingInWmPaint, true);
			this->UpdateStyles();
			tabPressed = false;
			backgroundTask = DO_NOTHING;
			mainLabel = "";
			wait = false;
			subLabel = "";
			indexLastSpace = 0;
			spaceCount = 0;
			label1->Text = convertToGUIString(test1->getLabel());
			isLastCharSpace = false;
			//forwardSlashCount = 2;
			currentPage = 0;
			checkValidity = true;
			splash->Show();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			notifyIcon1->Visible = false;
			delete test1;
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  outputBox;
	private: int forwardSlashCount;
			 int currentPage;
	public:  MainLogic * test1;
	private: BackgroundWorkType backgroundTask;
	private: int spaceCount, indexLastSpace;
	private: StringCollection ^ pages;
			 String ^ mainLabel, ^ subLabel;
			 //int linesToBeColored[16];
	private: bool isLastCharSpace, dragging, checkValidity, tabPressed,wait;
	private: Point pointClicked;
	private: cli::array<System::String ^> ^ stringCollection;
	private: String ^ COMMANDBOX_TEXT ;
	private: String ^ COMMANDHELP_TEXT;
	private: SplashScreen ^ splash;
	protected: 



	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::NotifyIcon^  notifyIcon1;
	private: System::Windows::Forms::ContextMenuStrip^  rightClickMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  restoreToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::Panel^  titleBar;
	private: System::Windows::Forms::Button^  closeButton;
	private: System::Windows::Forms::Button^  minimizeButton;
	private: System::Windows::Forms::Label^  TempusLabel;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::TextBox^  commandBox;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Label^  commandHelpLabel;
	private: System::Windows::Forms::Label^  pageCountLabel;
	private: System::Windows::Forms::Label^  resultLabel;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker2;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker3;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label1;


	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->outputBox = (gcnew System::Windows::Forms::RichTextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->notifyIcon1 = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->rightClickMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->restoreToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->titleBar = (gcnew System::Windows::Forms::Panel());
			this->TempusLabel = (gcnew System::Windows::Forms::Label());
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->minimizeButton = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->commandBox = (gcnew System::Windows::Forms::TextBox());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->commandHelpLabel = (gcnew System::Windows::Forms::Label());
			this->pageCountLabel = (gcnew System::Windows::Forms::Label());
			this->resultLabel = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker3 = (gcnew System::ComponentModel::BackgroundWorker());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->rightClickMenu->SuspendLayout();
			this->titleBar->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// outputBox
			// 
			this->outputBox->BackColor = System::Drawing::SystemColors::Info;
			this->outputBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->outputBox->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->outputBox->Location = System::Drawing::Point(15, 19);
			this->outputBox->Name = L"outputBox";
			this->outputBox->ReadOnly = true;
			this->outputBox->Size = System::Drawing::Size(463, 421);
			this->outputBox->TabIndex = 0;
			this->outputBox->TabStop = false;
			this->outputBox->Text = L"";
			this->outputBox->WordWrap = false;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker1_DoWork);
			// 
			// notifyIcon1
			// 
			this->notifyIcon1->BalloonTipText = L"Press CTRL + ALT + S to activate";
			this->notifyIcon1->BalloonTipTitle = L"Tempus";
			this->notifyIcon1->ContextMenuStrip = this->rightClickMenu;
			this->notifyIcon1->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"notifyIcon1.Icon")));
			this->notifyIcon1->Text = L"notifyIcon1";
			this->notifyIcon1->Visible = true;
			this->notifyIcon1->DoubleClick += gcnew System::EventHandler(this, &Form1::notifyIcon1_DoubleClick);
			// 
			// rightClickMenu
			// 
			this->rightClickMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->restoreToolStripMenuItem, 
				this->exitToolStripMenuItem});
			this->rightClickMenu->Name = L"rightClickMenu";
			this->rightClickMenu->Size = System::Drawing::Size(129, 52);
			// 
			// restoreToolStripMenuItem
			// 
			this->restoreToolStripMenuItem->Name = L"restoreToolStripMenuItem";
			this->restoreToolStripMenuItem->Size = System::Drawing::Size(128, 24);
			this->restoreToolStripMenuItem->Text = L"Restore";
			this->restoreToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::restoreToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(128, 24);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// titleBar
			// 
			this->titleBar->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"titleBar.BackgroundImage")));
			this->titleBar->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->titleBar->Controls->Add(this->TempusLabel);
			this->titleBar->Controls->Add(this->closeButton);
			this->titleBar->Controls->Add(this->minimizeButton);
			this->titleBar->Location = System::Drawing::Point(0, -1);
			this->titleBar->Name = L"titleBar";
			this->titleBar->Size = System::Drawing::Size(737, 48);
			this->titleBar->TabIndex = 5;
			this->titleBar->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::titleBar_MouseDown);
			this->titleBar->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::titleBar_MouseMove);
			this->titleBar->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::titleBar_MouseUp);
			// 
			// TempusLabel
			// 
			this->TempusLabel->AutoSize = true;
			this->TempusLabel->BackColor = System::Drawing::Color::Transparent;
			this->TempusLabel->Font = (gcnew System::Drawing::Font(L"Forte", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->TempusLabel->ForeColor = System::Drawing::Color::White;
			this->TempusLabel->Location = System::Drawing::Point(221, 6);
			this->TempusLabel->Name = L"TempusLabel";
			this->TempusLabel->Size = System::Drawing::Size(117, 32);
			this->TempusLabel->TabIndex = 2;
			this->TempusLabel->Text = L"Tempus";
			// 
			// closeButton
			// 
			this->closeButton->BackColor = System::Drawing::Color::Transparent;
			this->closeButton->FlatAppearance->BorderSize = 0;
			this->closeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closeButton->Font = (gcnew System::Drawing::Font(L"Mistral", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->closeButton->ForeColor = System::Drawing::Color::White;
			this->closeButton->Location = System::Drawing::Point(528, 2);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(43, 42);
			this->closeButton->TabIndex = 1;
			this->closeButton->TabStop = false;
			this->closeButton->Text = L"X";
			this->closeButton->UseVisualStyleBackColor = false;
			this->closeButton->Click += gcnew System::EventHandler(this, &Form1::closeButton_Click);
			// 
			// minimizeButton
			// 
			this->minimizeButton->BackColor = System::Drawing::Color::Transparent;
			this->minimizeButton->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
			this->minimizeButton->FlatAppearance->BorderSize = 0;
			this->minimizeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->minimizeButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->minimizeButton->ForeColor = System::Drawing::Color::White;
			this->minimizeButton->Location = System::Drawing::Point(479, 2);
			this->minimizeButton->Name = L"minimizeButton";
			this->minimizeButton->Size = System::Drawing::Size(43, 42);
			this->minimizeButton->TabIndex = 0;
			this->minimizeButton->TabStop = false;
			this->minimizeButton->Text = L"-";
			this->minimizeButton->UseVisualStyleBackColor = false;
			this->minimizeButton->Click += gcnew System::EventHandler(this, &Form1::minimizeButton_Click);
			// 
			// panel2
			// 
			this->panel2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"panel2.BackgroundImage")));
			this->panel2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel2->Controls->Add(this->outputBox);
			this->panel2->Location = System::Drawing::Point(42, 90);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(499, 453);
			this->panel2->TabIndex = 6;
			// 
			// panel3
			// 
			this->panel3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"panel3.BackgroundImage")));
			this->panel3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel3->Controls->Add(this->commandBox);
			this->panel3->Location = System::Drawing::Point(42, 596);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(499, 58);
			this->panel3->TabIndex = 7;
			// 
			// commandBox
			// 
			this->commandBox->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Append;
			this->commandBox->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->commandBox->BackColor = System::Drawing::SystemColors::Info;
			this->commandBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->commandBox->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->commandBox->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->commandBox->Location = System::Drawing::Point(15, 17);
			this->commandBox->Name = L"commandBox";
			this->commandBox->Size = System::Drawing::Size(463, 24);
			this->commandBox->TabIndex = 0;
			this->commandBox->Click += gcnew System::EventHandler(this, &Form1::commandBox_Click);
			this->commandBox->TextChanged += gcnew System::EventHandler(this, &Form1::commandBox_TextChanged);
			this->commandBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::commandBox_KeyDown);
			this->commandBox->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::commandBox_KeyUp);
			this->commandBox->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &Form1::commandBox_PreviewKeyDown);
			// 
			// panel4
			// 
			this->panel4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"panel4.BackgroundImage")));
			this->panel4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel4->Controls->Add(this->commandHelpLabel);
			this->panel4->Location = System::Drawing::Point(0, 674);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(592, 60);
			this->panel4->TabIndex = 8;
			// 
			// commandHelpLabel
			// 
			this->commandHelpLabel->AutoSize = true;
			this->commandHelpLabel->BackColor = System::Drawing::Color::Transparent;
			this->commandHelpLabel->Font = (gcnew System::Drawing::Font(L"Calibri", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->commandHelpLabel->ForeColor = System::Drawing::SystemColors::Window;
			this->commandHelpLabel->Location = System::Drawing::Point(38, 10);
			this->commandHelpLabel->Name = L"commandHelpLabel";
			this->commandHelpLabel->Size = System::Drawing::Size(0, 23);
			this->commandHelpLabel->TabIndex = 0;
			// 
			// pageCountLabel
			// 
			this->pageCountLabel->AutoSize = true;
			this->pageCountLabel->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->pageCountLabel->Location = System::Drawing::Point(475, 574);
			this->pageCountLabel->Name = L"pageCountLabel";
			this->pageCountLabel->Size = System::Drawing::Size(0, 19);
			this->pageCountLabel->TabIndex = 9;
			// 
			// resultLabel
			// 
			this->resultLabel->AutoSize = true;
			this->resultLabel->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->resultLabel->Location = System::Drawing::Point(38, 546);
			this->resultLabel->Name = L"resultLabel";
			this->resultLabel->Size = System::Drawing::Size(0, 20);
			this->resultLabel->TabIndex = 10;
			// 
			// backgroundWorker2
			// 
			this->backgroundWorker2->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker2_DoWork);
			this->backgroundWorker2->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker2_RunWorkerCompleted);
			// 
			// backgroundWorker3
			// 
			this->backgroundWorker3->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker3_DoWork);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(51, 50);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 35);
			this->label1->TabIndex = 11;
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Info;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(583, 734);
			this->Controls->Add(this->titleBar);
			this->Controls->Add(this->resultLabel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->pageCountLabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(593, 771);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form1";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->rightClickMenu->ResumeLayout(false);
			this->titleBar->ResumeLayout(false);
			this->titleBar->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private:	 System::Void pageCountLabelText( int pageNo )
			 {
				 pageCountLabel->Text = "Page : " + pageNo + "/" + pages->Count;
			 }
			 String ^ convertToGUIString( std::string cliString )
			 {
				 String ^ convertedString = gcnew String( cliString.c_str() );
				 return convertedString;
			 }
			 String ^ tab()
			 {
				 return convertToGUIString("\t");
			 }

			 System::Void colorOutputBox()
			 {
				 int i , arrayLines[16], numberOfLines;
				 String ^ tempStorage;
				 numberOfLines = outputBox->Lines->Length;
				 for(i=0;i<16;i++)
					 arrayLines[i]=1;
				 // The next block finds lines which require coloring and of what kind.
				 // This depends on the nature of the text displayed in that line( Date, Completed Task etc.)
				 for (i = 0; i < numberOfLines; i++)
				 {
					 String ^ currentLine = outputBox->Lines[i];
					 if(currentLine->Length>0)
					 {
						 if( !currentLine->Substring(0,1)->Equals("\t"))
						 {
							 if(Equals(currentLine->Substring(currentLine->Length-3,3), " nd"))
							 {
								 arrayLines[i] = 1; 
								 tempStorage += currentLine->Substring(0,currentLine->Length-3) + Environment::NewLine;
							 }
							 else if(Equals(currentLine->Substring(currentLine->Length-2,2), " d"))
							 {
								 arrayLines[i] = 2;
								 tempStorage += currentLine->Substring(0,currentLine->Length-2) + Environment::NewLine;
							 }
							 else 
							 {
								 arrayLines[i] = 1;
								 tempStorage += currentLine + Environment::NewLine;
							 }
						 }
						 else
						 {
							 arrayLines[i] = 3;
							 tempStorage += currentLine + Environment::NewLine;
						 }
					 }
				 }
				 outputBox->Text= tempStorage;
				 numberOfLines = outputBox->Lines->Length;
				 //This block colors each line as per the requirements 
				 for( i =0; i< numberOfLines; i++ )
				 {
					 String ^ currentLine = outputBox->Lines[i];
					 if( arrayLines[i] == 1)
					 {
						 System::Drawing::Font ^ uncompletedTaskFont = gcnew System::Drawing::Font(L"Comic Sans MS", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
						 colorOutputLine( i, Color::Black, uncompletedTaskFont);
					 }
					 else if(arrayLines[i] == 2)
					 { 
						 System::Drawing::Font ^ completedTaskFont = gcnew System::Drawing::Font(L"Comic Sans MS", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
						 colorOutputLine( i, Color::DarkGreen, completedTaskFont);
					 }
					 else if(arrayLines[i] == 3)
					 {
						  System::Drawing::Font ^ titleFont = gcnew System::Drawing::Font(L"Comic Sans MS", 11.2F, System::Drawing::FontStyle::Bold , System::Drawing::GraphicsUnit::Point);
						 colorOutputLine( i, Color::Navy, titleFont);
					 }
				 }
			 }
private:	 System::Void colorOutputLine( int lineNumber, Color newColor, System::Drawing::Font ^ newFont)
			 {
					int lineIndex;
					String ^ currentLine = outputBox->Lines[lineNumber];

					lineIndex = outputBox->GetFirstCharIndexFromLine(lineNumber);
					outputBox->SelectionStart = lineIndex;
					outputBox->SelectionLength = currentLine->Length;
					outputBox->SelectionFont = newFont;
					outputBox->SelectionColor = newColor;
					outputBox->SelectionLength = 0;
			 }
			 std::string convertToCliString( String ^ guiString)
			 {
				 std::string convertedString;
				 const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(guiString)).ToPointer();
				 convertedString = chars;
				 Marshal::FreeHGlobal(IntPtr((void*)chars));
				 return convertedString;
			 }
			 String ^ mergeNewLine( std::string text)
			 {
				 int i, textLength, startIndex;
				 ostringstream modified(text);
				 String ^ displayString;
				
				 startIndex = 0;
				 textLength = text.length();
				 for( i = 0; i < textLength; i++ )
				 {
					 String^ tempLine;
					 if( text[i] == '\n' || i == (textLength - 1))
					 {
						 tempLine= ( convertToGUIString(text.substr( startIndex, i - startIndex)) );
						 if(i != (textLength - 1))
						 {
							 tempLine += Environment::NewLine;
						 }
						 startIndex = i+1;
						  displayString +=tempLine;
					 }
					
				 }
				 return displayString;
			 }
private:	 System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 
				 splash->Close();
				 AnimateWindow(this->Handle, 1000, AW_BLEND );
				 backgroundWorker1->RunWorkerAsync();
				 backgroundWorker2->RunWorkerAsync();
				 backgroundWorker3->RunWorkerAsync();
				 resetCommandBox();
				 resetAutoComplete();
				 this->ControlBox = false;
				 this->Text = " ";
				 displayAgenda();
			 }


private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		
		if (RegisterHotKey(NULL,1,MOD_ALT | MOD_CONTROL,0x53))  //0x53 is 's'
		 { 
		 }
		 MSG msg = {0};
		 while (GetMessage(&msg, NULL, 0, 0) == 1)
		 {
			 if (msg.message == WM_HOTKEY)
			 {
				 if (this->WindowState == FormWindowState::Normal)
				 {
					 minimizeToTray();
				 }
				 else
				 {
					restoreFormToNormal();
				 }
			 }
		
		 }
	}
private: System::Void restoreFormToNormal()
		 {
			 this->Show();
			 this->WindowState = FormWindowState::Normal;
			 focusTextBox();	
			 displayAgenda();
		 }
private: System::Void focusTextBox()
		 {
				
				commandBox->Focus();
				commandHelpLabel->Text = COMMANDHELP_TEXT;

				commandBox->SelectionStart = 0;
				commandBox->SelectionLength = 0;
		 }

private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void restoreToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			restoreFormToNormal();
		 }

private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			
			 if (MessageBox::Show("Do you really want to exit Tempus?","Confirm Exit", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
			 {
				 e->Cancel = false;
			 } 
			 else
			 {
				 e->Cancel = true;
				 focusTextBox();
			 }
		 }

private: System::Void displayAgenda()
		 {
			 pages->Clear();
			 this->outputBox->Text = mergeNewLine(test1->displayOutput());
			if (!outputBox->Text->Equals(""))
			 {
				 displayText(pages);
				 pageCountLabelText(1);
			 }
		 }
private: System::Void notifyIcon1_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
			 restoreFormToNormal();
		 }
private: System::Void minimizeToTray()
		 {
			 this->WindowState = FormWindowState::Minimized;
			 notifyIcon1->Visible = true;
			 this->notifyIcon1->BalloonTipText = L"Press CTRL + ALT + S to activate";
			this->notifyIcon1->BalloonTipTitle = L"Tempus";
			 notifyIcon1->ShowBalloonTip(500);
			 this->Hide();
		 }
private: System::Void minimizeButton_Click(System::Object^  sender, System::EventArgs^  e) {
				minimizeToTray();
		 }
private: System::Void closeButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }

private: System::Void titleBar_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if (dragging){
				 Point pointMoveTo;
				 Point temp = Point(e->X,e->Y);
				 pointMoveTo = this->PointToScreen(temp);

				 pointMoveTo.Offset(-pointClicked.X, -pointClicked.Y);

				 this->Location = pointMoveTo;
			 } 
		 }
private: System::Void titleBar_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if (e->Button ==  System::Windows::Forms::MouseButtons::Left )
			 {
				 dragging = true;
				 pointClicked = Point(e->X, e->Y);
			 }
			 else
			 {
				 dragging = false;
			 }
		 }
private: System::Void titleBar_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 dragging = false;
		 }
private: System::Void restoreFontSettings()  {
			 this->commandBox->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				 static_cast<System::Byte>(0)));
			 this->commandBox->ForeColor = System::Drawing::SystemColors::WindowText;
			 this->commandBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		 }
private: System::Void newlineFontSettings()
		 {
			 this->commandBox->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				 static_cast<System::Byte>(0)));
			 this->commandBox->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			 this->commandBox->Text = COMMANDBOX_TEXT;
			 commandBox->SelectionStart = 0;
		 }

private: System::Void resetAutoComplete()
		 {
			     commandBox->AutoCompleteCustomSource->Clear();
 				 commandBox->AutoCompleteCustomSource->AddRange(stringCollection);
				 commandBox->AutoCompleteSource = AutoCompleteSource::CustomSource;
		 }
private: System::Void updateAutoComplete()
		 {
			 int i;
			 cli::array<System::String ^> ^ tempCollection = gcnew cli::array<System::String ^>(AUTOCOMPLETE_LIST_SIZE);
			 for ( i = 0; i < AUTOCOMPLETE_LIST_SIZE; i++)
			 {
				 tempCollection[i] = commandBox->Text +  stringCollection[i];
			 }
			 this->commandBox->AutoCompleteCustomSource->AddRange(tempCollection);
			 this->commandBox->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
		 }
private: System::Void goToPreviousPage()
		 {
			 if (currentPage > 0)
			 {
				 currentPage--;
				 outputBox->Text = pages[currentPage];
				 pageCountLabelText(currentPage+1);
				 formatOutputBox();
			 }
			 resultLabel->Text = "";
		 }
private: System::Void goToNextPage()
		 {
			 if (currentPage < pages->Count-1)
			 {
				 currentPage++;
				 outputBox->Text = pages[currentPage];
				 pageCountLabelText(currentPage+1);
				 formatOutputBox();
			 }
			 resultLabel->Text = "";
		 }

private: System::Void resetCommandBox()
		 {
			 newlineFontSettings();
			 resetAutoComplete();
			 resetParameters();
			 commandBox->SelectionStart = 0;
			 commandBox->SelectionLength = 0;
		 }

private: bool isMainCommandEntered()
		 {
			 return (spaceCount == 1);
		 }
private: System::Void spacePressed()
		 {
				updateAutoComplete();
				spaceCount++;
				if(isMainCommandEntered())
				{
					displayLabel();
					commandHelpLabel->Text = mainLabel;
				}
		 }

private: System::Void enterPressed()
		 {
			 bool pageTurned = false;
			
			 if (EqualsIgnoreCase(commandBox->Text,"p"))
			 {
				 pageTurned= true;
				 goToPreviousPage();
			 } 
			 else if (EqualsIgnoreCase(commandBox->Text,"n"))
			 {
				 pageTurned = true;
				 goToNextPage(); 
			 }
			 else if (EqualsIgnoreCase(commandBox->Text,"exit") || EqualsIgnoreCase(commandBox->Text,"exit "))
			 {
				 this->Close();
			 }
			 else if (commandBox->Text->Equals(""))
			 {
				 //do nothing
			 }
			 else {

				 pages->Clear();
				 test1->processCommand(convertToCliString(commandBox->Text));
				 outputBox->Text = mergeNewLine(test1->displayOutput());
				 resultLabel->Text = convertToGUIString(test1->getStatusMessage());
				 if (!outputBox->Text->Equals(""))
				 {
					 displayText(pages);
					 pageCountLabelText(1);
				 }
			 }

			 resetCommandBox();		 
			label1->Text = convertToGUIString(test1->getLabel());

			if(!pageTurned)
				 resultLabel->Text = convertToGUIString(test1->getStatusMessage());
		 }
private: System::Void commandBox_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (commandBox->SelectionLength > 0)
			 {
				 checkValidity = true;
			 }
			 else
				 checkValidity = false;
			 
			 if((e->KeyCode == Keys::Right || e->KeyCode == Keys::Left) && commandBox->Text->Equals(COMMANDBOX_TEXT))
			 { 
				  resetCommandBox();
				return;
			 }
			 if(e->KeyCode == Keys::Tab && commandBox->SelectionLength > 0)
			 {
				 commandBox->Focus();
				 commandBox->Text += " ";
				 commandBox->SelectionStart = commandBox->Text->Length;
				 commandBox->SelectionLength = 0;

				 spacePressed();
				 // tabPressed = false;
			 }
			 if (e->KeyCode == Keys::Down && commandBox->SelectionLength == 0)
			 {
				 if (commandBox->SelectionStart > 0)
				 {
					 commandBox->SelectionStart = commandBox->SelectionStart-1;
				 }
				 goToNextPage();
				 resetCommandBox();
				 return;
			 }
			 if (e->KeyCode == Keys::Up && commandBox->SelectionLength == 0)
			 {
				 goToPreviousPage();
				 resetCommandBox();
				 return;
			 }
			 if (e->KeyCode == Keys::Back )
			 {
				 if( commandBox->Text->Length == 0 || commandBox->Text->Equals(COMMANDBOX_TEXT))
				 {
					 resetCommandBox();
					 return;
				 }
				 if (isLastCharSpace)
				 {
					 spaceCount--;
					 if( commandBox->Text->Length > 0)
							isLastCharSpace = commandBox->Text->Substring( commandBox->Text->Length - 1 , 1)->Equals(" ");
					 else
							isLastCharSpace = false;
					 resetAutoComplete();
				 }
			 }
			 if (e->KeyCode ==  Keys::Enter)
			 {
				 enterPressed();
				 return;
			 }
			 if (e->KeyCode == Keys::Space)
			 {
				 commandBox->SelectionStart = commandBox->Text->Length;
				 commandBox->SelectionLength = 0;
				 spacePressed();
			 }
			 if ( commandBox->Text->Length > 0 && commandBox->Text->Substring(commandBox->Text->Length-1,1)->Equals(" "))
			 {
				 indexLastSpace = commandBox->Text->Length-1;
				 isLastCharSpace = true;
				 updateAutoComplete();
			 }
			 else
				 isLastCharSpace = false;
		 }
		 
private: System::Void formatOutputBox( )
		 {
			 colorOutputBox();
		 }
private: System::Void displayText(StringCollection ^ collection)
		 {
			 int i , numberOfLines = outputBox->Lines->Length;
			 int pageLineCount = 0, pageCount = 0;
			 String ^ temp = "";
			 for ( i = 0; i < numberOfLines; i++ )
			 {
				 String ^ currentLine = outputBox->Lines[i];
				 pageLineCount++;
				 if (pageLineCount  <= MAX_LINES_PER_PAGE )
				 {
					 temp += currentLine; 
					 if (pageLineCount == MAX_LINES_PER_PAGE)
					 {
						 collection->Add(temp);
						 temp = "";
						 pageLineCount = 0;
						 pageCount++;
						 continue;
					 }
					 
					 if (i==(numberOfLines -1))
					 {
						 collection->Add(temp);
						 pageCount++;
					 } 
					 temp +=  Environment::NewLine;
				 }
				 
			 }
			 currentPage = 0;
			 outputBox->Text = collection[currentPage];
			 formatOutputBox();
		 }
private: System::Void commandBox_Click(System::Object^  sender, System::EventArgs^  e) { 
			 if( commandBox->Text->Equals(COMMANDBOX_TEXT))
			 {
			 commandBox->SelectionStart = 0;
			 commandBox->SelectionLength = 0;
			 }
		 }
private: System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e) {
			 focusTextBox();
		 }
private: System::Void resetParameters()
		 {
			 indexLastSpace = 0;
			 spaceCount = 0;
			 subLabel = "";
			 mainLabel = "";
			 checkValidity = true;
		 }

private: System::Void commandBox_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
			
		 }
private: bool EqualsIgnoreCase ( String ^ str1, String ^ str2 ) 
		 {
			 bool isEqual;
			 isEqual =  str1->ToLower()->Equals(str2->ToLower());
			 return isEqual;
		 }
private: System::Void commandBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == Keys::Back && isLastCharSpace)
			 {
					spaceCount--;
					String ^ abc = commandBox->Text;
					abc = abc->Remove( commandBox->Text->Length - 1);
					commandBox->Text = abc;
					commandBox->SelectionStart = commandBox->Text->Length;
					resetAutoComplete();
					if( commandBox->Text->Length > 0)
							isLastCharSpace = commandBox->Text->Substring( commandBox->Text->Length - 1 , 1)->Equals(" ");
					 else
							isLastCharSpace = false;
			 }
			 if( commandBox->Text->Equals(COMMANDBOX_TEXT))
			 {	
					if(e->KeyCode == Keys::Right || e->KeyCode == Keys::Left)
					 { 
						 commandBox->SelectionStart = 0;
						 return;
					 }
					 commandBox->Text = "";
					 restoreFontSettings();
			 }
		 }

private: bool isDay( String ^ word)
		 {
			if( EqualsIgnoreCase(word,"monday ") || EqualsIgnoreCase(word,"tuesday ")
						 || EqualsIgnoreCase(word,"wednesday ")|| EqualsIgnoreCase(word,"thursday") ||
						 EqualsIgnoreCase(word,"friday ")|| EqualsIgnoreCase(word,"saturday") || EqualsIgnoreCase(word,"sunday "))
						 return true;
			else
				return false;
		 }
private: System::Void displayLabel()
		 {
			 //Display help for each command
				 String ^ firstWord  = commandBox->Text;
				 if(EqualsIgnoreCase(firstWord,"show "))
				 {
					 mainLabel = "e.g show 21/12 or show meeting"; 
				 } 
				 else if (EqualsIgnoreCase(firstWord,"edit "))
				 {
					 mainLabel = "e.g edit 1 date 21 nov location home ";
				 } 
				 else if (EqualsIgnoreCase(firstWord,"delete "))
				 {
					 mainLabel = "e.g delete 2";
				 }
				 else if (EqualsIgnoreCase(firstWord,"done "))
				 {
					 mainLabel = "e.g done 1";
				 }
				 else if (EqualsIgnoreCase(firstWord,"agenda "))
				 {
					 mainLabel = "Shows the agenda";
				 }
				 else if (EqualsIgnoreCase(firstWord,"exit "))
				 {
					 mainLabel = "Exit Tempus";
				 }
				 else if (EqualsIgnoreCase(firstWord,"undo "))
				 {
					 mainLabel = "Undo recent changes";
				 }
				  else if (EqualsIgnoreCase(firstWord,"history "))
				 {
					 mainLabel = "Displays the past tasks";
				 }
				 else if (EqualsIgnoreCase(firstWord,"pending "))
				 {
					 mainLabel = "See your pending tasks";
				 }
				  else if (EqualsIgnoreCase(firstWord,"ftime "))
				 {
					 mainLabel = "e.g ftime monday (free time on Monday)";
				 }
				 else if ( isDay( firstWord) )
				 {
					// do nothing
				 }
				 else 
				 {
					 mainLabel = "e.g meeting date 31 oct time 7 pm - 8 pm location home";
				 }
		 }
private: System::Void commandBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if ( commandBox->Text->Equals(COMMANDBOX_TEXT) )
			 {
				 commandHelpLabel->Text = COMMANDHELP_TEXT;
			 }
			 resultLabel->Text = "";
		 }
private: System::Void backgroundWorker2_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 
				backgroundTask = DO_NOTHING;
				//if time match found
				 if(test1->checkIfReminder())
				 {
					 backgroundTask = REMINDER; 
				 }
				 //if 12:00 am
				 if(test1->readIfNextday())
				 {
					 backgroundTask = UPDATE_AGENDA;
				 }
		 }

private: System::Void backgroundWorker2_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			 if(backgroundTask == REMINDER && !wait)
			 {
					 showReminder();
					 Beep( 600,400);
					 waitFor(60);
			 }
			 else if (backgroundTask == UPDATE_AGENDA && !wait)
			 {
					 displayAgenda();
					 waitFor(1);
			 }
			 backgroundWorker2->RunWorkerAsync();
		 }
private: System::Void showReminder()
		 {
			    notifyIcon1->BalloonTipTitle = L"Reminder";
				notifyIcon1->BalloonTipText = convertToGUIString(test1->getReminderText());
				notifyIcon1->ShowBalloonTip(500);
		 }
private: System::Void waitFor( int seconds)
		 {
			    int valueInMilliseconds = seconds*1000;

				wait = true;
				timer1->Interval = valueInMilliseconds;
				timer1->Enabled = true;
				timer1->Start();
		 }
private: System::Void backgroundWorker3_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			 if (RegisterHotKey(NULL,1,MOD_ALT | MOD_CONTROL,0x41))  //0x41 is 'A'
			 { 
			 }
			 MSG msg = {0};
			 while (GetMessage(&msg, NULL, 0, 0) == 1)
			 {
				 if (msg.message == WM_HOTKEY)
				 {
					 pages->Clear();
					 test1->processCommand("agenda");
					 outputBox->Text = mergeNewLine(test1->displayOutput());
					 resultLabel->Text = convertToGUIString(test1->getStatusMessage());
					 if (!outputBox->Text->Equals(""))
					 {
						 displayText(pages);
						 pageCountLabelText(1);
					 }
					 label1->Text = convertToGUIString(test1->getLabel());
				 }
			 }
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			  timer1->Stop();
			 wait = false;
		 }
};
}

