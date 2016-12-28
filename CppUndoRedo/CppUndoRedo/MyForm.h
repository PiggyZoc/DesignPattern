#pragma once


#include<iostream>
#include<vector>
#include<math.h>
#include "DrawingGraphicEdit.h"
#include "UndoableEditSupport.h"
#include "UndoManager.h"




namespace Project {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::PictureBox^  drawMap;
	private: vector<MySquare*>* squares;
	private: vector<MyGraphic*>* graphics;
	private: UndoableEditSupport* editSupport;
	private: UndoManager* manager;
	private:Bitmap^ bitmap;
	private:Pen^ pen = gcnew Pen(Color::Red, 1);
	private:Pen^ EraserPen;
	private:Graphics^ g;
	private:Point^ sourcePoint;
	private:Point^ currentPoint;
	private:Point^ previousPoint;

	private:bool DrawASquare = false;
	private:bool DrawATriangle = false;



	private: System::Windows::Forms::Button^  button2;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox2;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->drawMap = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->drawMap))->BeginInit();
			this->SuspendLayout();
			// 
			// drawMap
			// 
			this->drawMap->Cursor = System::Windows::Forms::Cursors::Default;
			this->drawMap->Location = System::Drawing::Point(1, 29);
			this->drawMap->Name = L"drawMap";
			this->drawMap->Size = System::Drawing::Size(499, 262);
			this->drawMap->TabIndex = 1;
			this->drawMap->TabStop = false;
			this->drawMap->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::drawMap_MouseUp);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 306);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 47);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Clear";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(198, 306);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(90, 47);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Undo";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(361, 306);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(96, 47);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Redo";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoEllipsis = true;
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(83, 7);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(60, 16);
			this->checkBox1->TabIndex = 6;
			this->checkBox1->Text = L"Square";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(296, 7);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(72, 16);
			this->checkBox2->TabIndex = 7;
			this->checkBox2->Text = L"Triangle";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 365);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->drawMap);
			this->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->drawMap))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		bitmap = gcnew Bitmap(drawMap->Width, drawMap->Height);
		drawMap->Image = bitmap;
		
		EraserPen = gcnew Pen(drawMap->BackColor, 2);
	//	squares = new vector < MySquare* >;
		graphics = new vector < MyGraphic* > ;
	    editSupport = new UndoableEditSupport();
		manager = new UndoManager();
		editSupport->addUndoManger(manager);
		setCanUndo();
		setCanRedo();
	/*	UndoableEditSupport* support = NULL;
		UndoManager* manager = NULL;
		support->addUndoManger(manager);*/

		
	}



	private: System::Void drawMap_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		if ((!DrawASquare) && (!DrawATriangle))
			return;
		
		currentPoint = e->Location;
		bitmap = gcnew Bitmap(bitmap);
		drawMap->Image = bitmap;
		g = Graphics::FromImage(bitmap);
		if (DrawASquare){
			g->DrawRectangle(pen, e->Location.X, e->Location.Y, 50, 50);
			MySquare* sqr = new MySquare(*currentPoint, 50);
			graphics->push_back(sqr);
	//		cout << graphics->size() << endl;
			editSupport->postEdit(new DrawingSquareEdit(*graphics, sqr));
	//		DrawingSquareEdit* edit = (DrawingSquareEdit*)manager->getEdit();
	//		cout << edit->getSize() << endl;
			checkBox1->Checked = false;
		}
		else if (DrawATriangle)
		{
			array<PointF>^ points = {
				PointF(e->Location.X, e->Location.Y),
				PointF(e->Location.X - 25, e->Location.Y + 25 * sqrt(3)),
				PointF(e->Location.X + 25, e->Location.Y + 25 * sqrt(3)),
				PointF(e->Location.X, e->Location.Y)
			};
			g->DrawLines(pen, points);
			
			MyTriangle* tri = new MyTriangle(*currentPoint, 50);
			graphics->push_back(tri);
			editSupport->postEdit(new DrawingTriangleEdit(*graphics, tri));

			checkBox2->Checked = false;

		//	cout << e->Location.X << endl;
	///		g->DrawLine(pen, e->Location.X, e->Location.Y, e->Location.X - 25, e->Location.Y - 25 * sqrt(3));
	///		g->DrawLine(pen, e->Location.X, e->Location.Y, e->Location.X + 25, e->Location.Y + 25 * sqrt(3));
	///		g->DrawLine(pen, e->Location.X - 25, e->Location.Y - 25 * sqrt(3), e->Location.X + 25, e->Location.Y + 25 * sqrt(3));
		}
	    DrawASquare = false;
	    DrawATriangle = false;
		checkBox1->Enabled = true;
		checkBox2->Enabled = true;
		button1->Enabled = true;
		button2->Enabled = true;
		button4->Enabled = true;
		cout << manager->getEdit()->getPresentationName() << endl;
		setCanUndo();
		setCanRedo();
	}


	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		manager->discardAllEdits();
		graphics->clear();
		ClearDrawingMap();
		repaint();
		setCanUndo();
		setCanRedo();
	}
	private: void ClearDrawingMap(){
		bitmap = gcnew Bitmap(bitmap);
		drawMap->Image = bitmap;

		g = Graphics::FromImage(bitmap);
		g->Clear(drawMap->BackColor);
	}

	private: void repaint(){
		bitmap = gcnew Bitmap(bitmap);
		drawMap->Image = bitmap;

		g = Graphics::FromImage(bitmap);
		
		if (manager->getEdit() == NULL)
		{
			g->Clear(drawMap->BackColor);
			return;
		}
	//	*squares = edit->getSquares();
		AbstractUndoableEdit* edit = (AbstractUndoableEdit*)manager->getEdit();
		*graphics = edit->getGraphics();
		
		vector<MyGraphic*>::iterator ite = graphics->begin();
		for (; ite != graphics->end(); ++ite){
			if ((*ite)->getID() == 1)
			{
				MySquare* sqr = (MySquare*)(*ite);
				g->DrawRectangle(pen, sqr->getPos()->getX(), sqr->getPos()->getY(),
					sqr->getsideLen(), sqr->getsideLen());
			}
			else if ((*ite)->getID() == 2)
			{
				MyTriangle* tri = (MyTriangle*)(*ite);
				int len = tri->getsideLen();
				int x = tri->getPos()->getX();
				int y = tri->getPos()->getY();
				array<PointF>^ points = {
					PointF(x, y),
					PointF(x - len/2, y + len/2 * sqrt(3)),
					PointF(x + len / 2, y + len / 2 * sqrt(3)),
					PointF(x, y)
				};
				g->DrawLines(pen, points);
			}
		}
	}

	private:Void setCanUndo(){
		if (manager->canUndo())
			button1->Enabled = true;
		else
		{
			button1->Enabled = false;
		}
	}
	private:Void setCanRedo(){
	if (manager->canRedo())
		button4->Enabled = true;
	else
	{
	    button4->Enabled = false;
	}
}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		manager->undo();
//		cout << manager->getEdit()->getPresentationName() << endl;
//		editSupport->postEdit(new DrawingSquareEdit(*graphics, sqr));
//		DrawingSquareEdit* edit = (DrawingSquareEdit*)manager->getEdit();
//		cout << edit->getSize() << endl;
		ClearDrawingMap();
		repaint();
		cout << "##########" << graphics->size() << endl;
		setCanUndo();
		setCanRedo();
	}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	manager->redo();
//	DrawingSquareEdit* edit = (DrawingSquareEdit*)manager->getEdit();
//	cout << edit->getSize() << endl;
	ClearDrawingMap();
	repaint();
	cout << "#########" << graphics->size() << endl;
	setCanUndo();
	setCanRedo();
}
 private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	 DrawASquare = true;
	 DrawATriangle = false;
	 button1->Enabled = false;
	 button2->Enabled = false;
	 button4->Enabled = false;
	 checkBox1->Enabled = false;
	 checkBox2->Enabled = false;
}
private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	DrawASquare = false;
	DrawATriangle = true;
	button1->Enabled = false;
	button2->Enabled = false;
	button4->Enabled = false;
	checkBox1->Enabled = false;
	checkBox2->Enabled = false;
}

};
}







