#pragma once


#include<iostream>
#include<vector>

#include "DrawingSquareEdit.h"



namespace Project1 {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Runtime::InteropServices;


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

	private:Bitmap^ bitmap;
	private:Pen^ pen = gcnew Pen(Color::Red, 1);
	private:Pen^ EraserPen;
	private:Graphics^ g;
	private:Point^ sourcePoint;
	private:Point^ currentPoint;
	private:Point^ previousPoint;





	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;




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
			this->button3 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->drawMap))->BeginInit();
			this->SuspendLayout();
			// 
			// drawMap
			// 
			this->drawMap->Cursor = System::Windows::Forms::Cursors::Default;
			this->drawMap->Location = System::Drawing::Point(1, 0);
			this->drawMap->Name = L"drawMap";
			this->drawMap->Size = System::Drawing::Size(499, 278);
			this->drawMap->TabIndex = 1;
			this->drawMap->TabStop = false;
			this->drawMap->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::drawMap_MouseUp);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(76, 295);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 47);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Clear";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(288, 295);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(119, 47);
			this->button3->TabIndex = 3;
			this->button3->Text = L"RePaint";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 365);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->drawMap);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->drawMap))->EndInit();
			this->ResumeLayout(false);

		}

#pragma endregion

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		bitmap = gcnew Bitmap(drawMap->Width, drawMap->Height);
		drawMap->Image = bitmap;
		int i = 1;
		EraserPen = gcnew Pen(drawMap->BackColor, 2);
		squares = new vector < MySquare* >;
	}



	private: System::Void drawMap_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		currentPoint = e->Location;
		bitmap = gcnew Bitmap(bitmap);
		drawMap->Image = bitmap;

		g = Graphics::FromImage(bitmap);
		g->DrawEllipse(pen, e->Location.X, e->Location.Y, 25, 25);
		MySquare* sqr = new MySquare(*currentPoint, 25);
		squares->push_back(sqr);
		//	MouseDown = false;

	}


	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		ClearDrawingMap();
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
		vector<MySquare*>::iterator ite = squares->begin();
		for (; ite != squares->end(); ++ite){
			g->DrawRectangle(pen, (*ite)->getPos()->getX(), (*ite)->getPos()->getY(),
				(*ite)->getsideLen(), (*ite)->getsideLen());
		}
	}


	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		repaint();
	}
	};
}







