#pragma once
#include "Process.h"
#include <iostream>
#include <fstream>
#include <string>
#include "network.h"  
#include <cmath>      

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	
	

	public ref class Form_SingleLayer : public System::Windows::Forms::Form
	{
	public:
		Form_SingleLayer(void)
		{
			InitializeComponent();
		}

	protected:
		~Form_SingleLayer()
		{
			if (components)
			{
				delete components;
			}
			// Bellek Temizliği
			if (Samples != nullptr) delete[] Samples;
			if (targets != nullptr) delete[] targets;
			if (Weights != nullptr) delete[] Weights;
			if (bias != nullptr) delete[] bias;
			if (errorHistory != nullptr) delete[] errorHistory;

		}

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ chartBox;
	protected:
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ Set_Net;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ ClassCountBox;

	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ ClassNoBox;

	private: System::Windows::Forms::Label^ label3;

	private:
		int  class_count = 0, numSample = 0, inputDim = 2,  errorHistoryCount = 0;
		float* Samples = nullptr;
		float* targets = nullptr;
		float* Weights = nullptr;
		float* bias = nullptr;
		float* errorHistory = nullptr; 

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ readDataToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^ saveDataToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^ processToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ trainingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ testingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ regressionToolStripMenuItem;

		 
		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   /// Tasarımcı desteği için gerekli metot.
		   void InitializeComponent(void)
		   {
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			   this->Set_Net = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->ClassCountBox = (gcnew System::Windows::Forms::ComboBox());
			   this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->ClassNoBox = (gcnew System::Windows::Forms::ComboBox());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->readDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->saveDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->processToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->trainingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->testingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->regressionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->chartBox = (gcnew System::Windows::Forms::PictureBox());
			   this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->groupBox1->SuspendLayout();
			   this->groupBox2->SuspendLayout();
			   this->menuStrip1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			   this->pictureBox1->Location = System::Drawing::Point(17, 43);
			   this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(1069, 711);
			   this->pictureBox1->TabIndex = 0;
			   this->pictureBox1->TabStop = false;
			   this->pictureBox1->Click += gcnew System::EventHandler(this, &Form_SingleLayer::pictureBox1_Click);
			   this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form_SingleLayer::pictureBox1_Paint);
			   this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form_SingleLayer::pictureBox1_MouseClick);
			   // 
			   // groupBox1
			   // 
			   this->groupBox1->Controls->Add(this->Set_Net);
			   this->groupBox1->Controls->Add(this->label1);
			   this->groupBox1->Controls->Add(this->ClassCountBox);
			   this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			   this->groupBox1->Location = System::Drawing::Point(1159, 62);
			   this->groupBox1->Margin = System::Windows::Forms::Padding(4);
			   this->groupBox1->Name = L"groupBox1";
			   this->groupBox1->Padding = System::Windows::Forms::Padding(4);
			   this->groupBox1->Size = System::Drawing::Size(267, 123);
			   this->groupBox1->TabIndex = 1;
			   this->groupBox1->TabStop = false;
			   this->groupBox1->Text = L"Network Architecture";
			   this->groupBox1->Enter += gcnew System::EventHandler(this, &Form_SingleLayer::groupBox1_Enter);
			   // 
			   // Set_Net
			   // 
			   this->Set_Net->Location = System::Drawing::Point(13, 75);
			   this->Set_Net->Margin = System::Windows::Forms::Padding(4);
			   this->Set_Net->Name = L"Set_Net";
			   this->Set_Net->Size = System::Drawing::Size(175, 41);
			   this->Set_Net->TabIndex = 2;
			   this->Set_Net->Text = L"Network Setting";
			   this->Set_Net->UseVisualStyleBackColor = true;
			   this->Set_Net->Click += gcnew System::EventHandler(this, &Form_SingleLayer::Set_Net_Click);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(144, 28);
			   this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(88, 17);
			   this->label1->TabIndex = 1;
			   this->label1->Text = L"Sınıf Sayısı";
			   this->label1->Click += gcnew System::EventHandler(this, &Form_SingleLayer::label1_Click);
			   // 
			   // ClassCountBox
			   // 
			   this->ClassCountBox->FormattingEnabled = true;
			   this->ClassCountBox->Items->AddRange(gcnew cli::array< System::Object^  >(7) { L"1", L"2", L"3", L"4", L"5", L"6", L"7" });			   this->ClassCountBox->Location = System::Drawing::Point(13, 25);
			   this->ClassCountBox->Margin = System::Windows::Forms::Padding(4);
			   this->ClassCountBox->Name = L"ClassCountBox";
			   this->ClassCountBox->Size = System::Drawing::Size(108, 25);
			   this->ClassCountBox->TabIndex = 0;
			   this->ClassCountBox->Text = L"1";
			   this->ClassCountBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_SingleLayer::ClassCountBox_SelectedIndexChanged);
			   // 
			   // groupBox2
			   // 
			   this->groupBox2->Controls->Add(this->label2);
			   this->groupBox2->Controls->Add(this->ClassNoBox);
			   this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(162)));
			   this->groupBox2->Location = System::Drawing::Point(1172, 235);
			   this->groupBox2->Margin = System::Windows::Forms::Padding(4);
			   this->groupBox2->Name = L"groupBox2";
			   this->groupBox2->Padding = System::Windows::Forms::Padding(4);
			   this->groupBox2->Size = System::Drawing::Size(253, 75);
			   this->groupBox2->TabIndex = 2;
			   this->groupBox2->TabStop = false;
			   this->groupBox2->Text = L"Data Collection";
			   this->groupBox2->Enter += gcnew System::EventHandler(this, &Form_SingleLayer::groupBox2_Enter);
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(131, 28);
			   this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(102, 17);
			   this->label2->TabIndex = 1;
			   this->label2->Text = L"Örnek Etiketi";
			   this->label2->Click += gcnew System::EventHandler(this, &Form_SingleLayer::label2_Click);
			   // 
			   // ClassNoBox
			   // 
			   this->ClassNoBox->FormattingEnabled = true;
			   this->ClassNoBox->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				   L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					   L"9"
			   });
			   this->ClassNoBox->Location = System::Drawing::Point(9, 25);
			   this->ClassNoBox->Margin = System::Windows::Forms::Padding(4);
			   this->ClassNoBox->Name = L"ClassNoBox";
			   this->ClassNoBox->Size = System::Drawing::Size(99, 25);
			   this->ClassNoBox->TabIndex = 0;
			   this->ClassNoBox->Text = L"1";
			   this->ClassNoBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_SingleLayer::ClassNoBox_SelectedIndexChanged);
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(1168, 326);
			   this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(44, 16);
			   this->label3->TabIndex = 3;
			   this->label3->Text = L"label3";
			   this->label3->Click += gcnew System::EventHandler(this, &Form_SingleLayer::label3_Click);
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->fileToolStripMenuItem,
					   this->processToolStripMenuItem
			   });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Size = System::Drawing::Size(1924, 28);
			   this->menuStrip1->TabIndex = 4;
			   this->menuStrip1->Text = L"menuStrip1";
			   this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form_SingleLayer::menuStrip1_ItemClicked);
			   // 
			   // fileToolStripMenuItem
			   // 
			   this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->readDataToolStripMenuItem,
					   this->saveDataToolStripMenuItem
			   });
			   this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			   this->fileToolStripMenuItem->Size = System::Drawing::Size(46, 24);
			   this->fileToolStripMenuItem->Text = L"File";
			   this->fileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_SingleLayer::fileToolStripMenuItem_Click);
			   // 
			   // readDataToolStripMenuItem
			   // 
			   this->readDataToolStripMenuItem->Name = L"readDataToolStripMenuItem";
			   this->readDataToolStripMenuItem->Size = System::Drawing::Size(164, 26);
			   this->readDataToolStripMenuItem->Text = L"Read_Data";
			   this->readDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_SingleLayer::readDataToolStripMenuItem_Click);
			   // 
			   // saveDataToolStripMenuItem
			   // 
			   this->saveDataToolStripMenuItem->Name = L"saveDataToolStripMenuItem";
			   this->saveDataToolStripMenuItem->Size = System::Drawing::Size(164, 26);
			   this->saveDataToolStripMenuItem->Text = L"Save_Data";
			   this->saveDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_SingleLayer::saveDataToolStripMenuItem_Click);
			   // 
			   // processToolStripMenuItem
			   // 
			   this->processToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				   this->trainingToolStripMenuItem,
					   this->testingToolStripMenuItem, this->regressionToolStripMenuItem
			   });
			   this->processToolStripMenuItem->Name = L"processToolStripMenuItem";
			   this->processToolStripMenuItem->Size = System::Drawing::Size(72, 24);
			   this->processToolStripMenuItem->Text = L"Process";
			   this->processToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_SingleLayer::processToolStripMenuItem_Click);
			   // 
			   // trainingToolStripMenuItem
			   // 
			   this->trainingToolStripMenuItem->Name = L"trainingToolStripMenuItem";
			   this->trainingToolStripMenuItem->Size = System::Drawing::Size(164, 26);
			   this->trainingToolStripMenuItem->Text = L"Training";
			   this->trainingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_SingleLayer::trainingToolStripMenuItem_Click);
			   // 
			   // testingToolStripMenuItem
			   // 
			   this->testingToolStripMenuItem->Name = L"testingToolStripMenuItem";
			   this->testingToolStripMenuItem->Size = System::Drawing::Size(164, 26);
			   this->testingToolStripMenuItem->Text = L"Testing";
			   this->testingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_SingleLayer::testingToolStripMenuItem_Click);
			   // 
			   // regressionToolStripMenuItem
			   // 
			   this->regressionToolStripMenuItem->Name = L"regressionToolStripMenuItem";
			   this->regressionToolStripMenuItem->Size = System::Drawing::Size(164, 26);
			   this->regressionToolStripMenuItem->Text = L"Regression";
			   this->regressionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_SingleLayer::regressionToolStripMenuItem_Click);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form_SingleLayer::openFileDialog1_FileOk);
			   // 
			   // chartBox
			   // 
			   this->chartBox->BackColor = System::Drawing::Color::WhiteSmoke;
			   this->chartBox->Location = System::Drawing::Point(1159, 368);
			   this->chartBox->Name = L"chartBox";
			   this->chartBox->Size = System::Drawing::Size(328, 347);
			   this->chartBox->TabIndex = 5;
			   this->chartBox->TabStop = false;
			   // 
			   // saveFileDialog1
			   // 
			   this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form_SingleLayer::saveFileDialog1_FileOk);
			   // 
			   // Form_SingleLayer
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1924, 779);
			   this->Controls->Add(this->chartBox);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->groupBox2);
			   this->Controls->Add(this->groupBox1);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->menuStrip1);
			   this->MainMenuStrip = this->menuStrip1;
			   this->Margin = System::Windows::Forms::Padding(4);
			   this->Name = L"Form_SingleLayer";
			   this->Text = L"Form_SingleLayer";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->groupBox1->ResumeLayout(false);
			   this->groupBox1->PerformLayout();
			   this->groupBox2->ResumeLayout(false);
			   this->groupBox2->PerformLayout();
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
		   void draw_sample(Graphics^ g, int temp_x, int temp_y, int label) {
			   Pen^ pen;
			   switch (label) {
			   case 0: pen = gcnew Pen(Color::Black, 3.0f); break;
			   case 1: pen = gcnew Pen(Color::Red, 3.0f); break;
			   case 2: pen = gcnew Pen(Color::Blue, 3.0f); break;
			   case 3: pen = gcnew Pen(Color::Green, 3.0f); break;
			   case 4: pen = gcnew Pen(Color::Yellow, 3.0f); break;
			   case 5: pen = gcnew Pen(Color::Orange, 3.0f); break;
			   default: pen = gcnew Pen(Color::YellowGreen, 3.0f);
			   }
			   // Graphics nesnesine çiz (Bitmap'e ya da direkt pictureBox'a)
			   g->DrawLine(pen, temp_x - 5, temp_y, temp_x + 5, temp_y);
			   g->DrawLine(pen, temp_x, temp_y - 5, temp_x, temp_y + 5);
		   }//draw_sample

		   // ---------------------------------------------------------
   // EKLENECEK KOD 1: LineCiz Fonksiyonu
   // Amacı: Ağırlıkları (w) kullanarak doğruyu matematiksel olarak çizer.
   // ---------------------------------------------------------
		   void LineCiz(float* w, float* b, int width, int height) {
			   Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
			   Graphics^ g = Graphics::FromImage(surface);
			   g->Clear(Color::White);

			   // 1. Eksenleri Çiz (Siyah Artı İşareti)
			   Pen^ axisPen = gcnew Pen(Color::Black, 2.0f);
			   int cx = width / 2; // Merkez X
			   int cy = height / 2; // Merkez Y
			   g->DrawLine(axisPen, cx, 0, cx, height);
			   g->DrawLine(axisPen, 0, cy, width, cy);

			   // 2. Doğruyu Çiz (Eğer ağırlıklar varsa)
			   // Formül: w1*x + w2*y + bias = 0  =>  y = -(w1*x + bias) / w2
			   if (w != nullptr && w[1] != 0) {
				   Pen^ linePen = gcnew Pen(Color::Red, 3.0f);

				   // Ekranın en solu (-cx) için Y değerini hesapla
				   float x1 = (float)-cx;
				   float y1 = -(w[0] * x1 + b[0]) / w[1];

				   // Ekranın en sağı (+cx) için Y değerini hesapla
				   float x2 = (float)cx;
				   float y2 = -(w[0] * x2 + b[0]) / w[1];

				   // Koordinatları ekran pikseline çevirip çizgiyi çek
				   g->DrawLine(linePen, (int)(x1 + cx), (int)(cy - y1),
					   (int)(x2 + cx), (int)(cy - y2));
			   }

			   // 3. Noktaları Tekrar Çiz (Çizgi noktaların üstünde kalmasın diye)
			   for (int i = 0; i < numSample; i++) {
				   Pen^ p;
				   if (targets[i] == 1 || targets[i] == 0) p = gcnew Pen(Color::Red, 3.0f); // Sınıf 1
				   else p = gcnew Pen(Color::Blue, 3.0f); // Sınıf 2

				   int px = (int)Samples[i * inputDim] + cx;
				   int py = cy - (int)Samples[i * inputDim + 1];
				   g->DrawEllipse(p, px - 3, py - 3, 6, 6);
			   }
			   pictureBox1->Image = surface;
		   }
		   void DrawErrorChart() {
			   if (errorHistoryCount < 2) return;

			   Bitmap^ chartBmp = gcnew Bitmap(chartBox->Width, chartBox->Height);
			   Graphics^ gg = Graphics::FromImage(chartBmp);
			   gg->Clear(Color::White);
			   gg->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			   int marginLeft = 50;
			   int marginRight = 20;
			   int marginTop = 40;
			   int marginBottom = 40;
			   int graphWidth = chartBox->Width - marginLeft - marginRight;
			   int graphHeight = chartBox->Height - marginTop - marginBottom;

			   // Çerçeve çiz
			   Pen^ framePen = gcnew Pen(Color::Black, 2);
			   gg->DrawRectangle(framePen, marginLeft, marginTop, graphWidth, graphHeight);

			   // Grid çizgileri (5 yatay çizgi)
			   Pen^ gridPen = gcnew Pen(Color::LightGray, 1);
			   for (int i = 1; i < 5; i++) {
				   int y = marginTop + (graphHeight * i / 5);
				   gg->DrawLine(gridPen, marginLeft, y, marginLeft + graphWidth, y);
			   }

			   // Maksimum hatayı bul
			   float maxVal = 0;
			   for (int i = 0; i < errorHistoryCount; i++) {
				   if (errorHistory[i] > maxVal) maxVal = errorHistory[i];
			   }

			   // Güvenli bölme için kontrol
			   if (maxVal < 0.0001f) maxVal = 0.0001f;

			   // Hata çizgisini çiz (NORMALIZE EDİLMİŞ)
			   Pen^ penBlue = gcnew Pen(Color::DodgerBlue, 2.5f);
			   float stepX = (float)graphWidth / (float)(errorHistoryCount - 1);

			   for (int i = 0; i < errorHistoryCount - 1; i++) {
				   float x1 = marginLeft + i * stepX;
				   // ÖNEMLİ: Hata değerini maksimuma göre normalize et
				   float normalizedY1 = errorHistory[i] / maxVal;
				   float y1 = marginTop + graphHeight - (normalizedY1 * graphHeight);

				   float x2 = marginLeft + (i + 1) * stepX;
				   float normalizedY2 = errorHistory[i + 1] / maxVal;
				   float y2 = marginTop + graphHeight - (normalizedY2 * graphHeight);

				   gg->DrawLine(penBlue, x1, y1, x2, y2);
			   }

			   // Başlık
			   System::Drawing::Font^ fontTitle = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
			   gg->DrawString("Egitim Hatasi (MSE)", fontTitle, Brushes::Black, marginLeft + 5, 8);

			   // Bilgi kutusu
			   System::Drawing::Font^ fontInfo = gcnew System::Drawing::Font("Arial", 8);
			   String^ info = String::Format("Epoch: {0}\nMax Hata: {1:F6}\nSon Hata: {2:F6}",
				   errorHistoryCount, maxVal, errorHistory[errorHistoryCount - 1]);

			   // Bilgi kutusunun arka planı
			   RectangleF infoRect = RectangleF(marginLeft + graphWidth - 120, marginTop + 5, 115, 55);
			   gg->FillRectangle(gcnew SolidBrush(Color::FromArgb(230, 255, 255, 255)), infoRect);
			   gg->DrawRectangle(gcnew Pen(Color::Gray, 1), Rectangle::Round(infoRect));
			   gg->DrawString(info, fontInfo, Brushes::DarkBlue, marginLeft + graphWidth - 115, marginTop + 10);

			   // Y ekseni etiketleri (5 tane)
			   System::Drawing::Font^ fontAxis = gcnew System::Drawing::Font("Arial", 7);
			   for (int i = 0; i <= 5; i++) {
				   float val = maxVal * (5 - i) / 5.0f;
				   int y = marginTop + (graphHeight * i / 5);
				   gg->DrawString(String::Format("{0:F4}", val), fontAxis, Brushes::Black, 2, y - 7);
			   }

			   chartBox->Image = chartBmp;
		   }
#pragma endregion
	private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (class_count == 0)
			MessageBox::Show("Networku kurunuz");
		else {
			float* x = new float[inputDim];
			int temp_x = (System::Convert::ToInt32(e->X));
			int temp_y = (System::Convert::ToInt32(e->Y));
			x[0] = float(temp_x - (pictureBox1->Width / 2));
			x[1] = float(pictureBox1->Height / 2 - temp_y);
			int label;
			int numLabel = Convert::ToInt32(ClassNoBox->Text);
			if (numLabel > class_count)
				MessageBox::Show("Sınıf etiketi, maksimum sınıf sayısından fazla olamaz.");
			else {
				label = numLabel - 1; //Dögüler 0 dan başladığından, label değeri 0 dan başlaması için bir eksiği alınmıştır
				if (numSample == 0) { //Dinamik alınan ilk örnek için sadece
					numSample = 1;
					Samples = new float[numSample * inputDim]; targets = new float[numSample];
					for (int i = 0; i < inputDim; i++)
						Samples[i] = x[i];
					targets[0] = float(label);
				}
				else {
					numSample++;
					Samples = Add_Data(Samples, numSample, x, inputDim);
					targets = Add_Labels(targets, numSample, label);
				}//else
				draw_sample(pictureBox1->CreateGraphics(), temp_x, temp_y, label);
				label3->Text = "Samples Count: " + System::Convert::ToString(numSample);
				delete[] x;
			}//else of if (Etiket ...
		}//else
	}//pictureMouseClick
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		//Ana eksen doğrularini cizdir
		Pen^ pen = gcnew Pen(Color::Black, 3.0f);
		int center_width, center_height;
		center_width = (int)(pictureBox1->Width / 2);
		center_height = (int)(pictureBox1->Height / 2);
		e->Graphics->DrawLine(pen, center_width, 0, center_width, pictureBox1->Height);
		e->Graphics->DrawLine(pen, 0, center_height, pictureBox1->Width, center_height);
	}
	private: System::Void Set_Net_Click(System::Object^ sender, System::EventArgs^ e) {
		// Network is constructed
		class_count = Convert::ToInt32(ClassCountBox->Text);
		Weights = new float[class_count * inputDim];
		bias = new float[class_count];
		//initialize weights for single layer
		if (class_count > 2) {
			Weights = init_array_random(class_count * inputDim);
			bias = init_array_random(class_count);
		}
		else {
			int numOutNeuron = 1;
			Weights = init_array_random(inputDim);
			bias = init_array_random(numOutNeuron);
		}
		Set_Net->Text = " Network is Ready : ";
	}//Set_Net
	private: System::Void readDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		char** c = new char* [2];
		// Veri Kümesini okunacak 
		MessageBox::Show("Veri Kümesini Yükleyin");
		c[0] = "../Data/Samples.txt";
		c[1] = "../Data/weights.txt";
		std::ifstream file;
		int num, w, h, Dim, label;
		file.open(c[0]);
		if (file.is_open()) {
			//MessageBox::Show("Dosya acildi");
			file >> Dim >> w >> h >> num;
			//textBox1->Text += "Dimension: " + Convert::ToString(Dim) + "- Width: " + Convert::ToString(w) + " - Height: " + Convert::ToString(h) + " - Number of Class: " + Convert::ToString(num) + "\r\n";
			// Set network values
			class_count = num;
			inputDim = Dim;
			Weights = new float[class_count * inputDim];
			bias = new float[class_count];
			numSample = 0;
			float* x = new float[inputDim];
			while (!file.eof())
			{
				if (numSample == 0) { //ilk örnek için sadece
					numSample = 1;
					Samples = new float[inputDim]; targets = new float[numSample];
					for (int i = 0; i < inputDim; i++)
						file >> Samples[i];
					file >> targets[0];
				}
				else {

					for (int i = 0; i < inputDim; i++)
						file >> x[i];
					file >> label;
					if (!file.eof()) {
						numSample++;
						Samples = Add_Data(Samples, numSample, x, inputDim);
						targets = Add_Labels(targets, numSample, label);
					}
				}//else
			} //while
			delete[]x;
			file.close();
			for (int i = 0; i < numSample; i++) {
				draw_sample(pictureBox1->CreateGraphics(), Samples[i * inputDim] + w, h - Samples[i * inputDim + 1], targets[i]);				//for (int j = 0; j < inputDim; j++) 
				//textBox1->Text += Convert::ToString(Samples[i * inputDim + j]) + " ";
				//textBox1->Text += Convert::ToString(targets[i]) + "\r\n";
			}
			//draw_sample(temp_x, temp_y, label);
			label3->Text = "Samples Count: " + System::Convert::ToString(numSample);
			MessageBox::Show("Dosya basari ile okundu");
		}//file.is_open
		else MessageBox::Show("Dosya acilamadi");
		//Get weights
		int Layer;
		file.open(c[1]);
		if (file.is_open()) {
			file >> Layer >> Dim >> num;
			class_count = num;
			inputDim = Dim;
			Weights = new float[class_count * inputDim];
			bias = new float[class_count];
			//textBox1->Text += "Layer: " + Convert::ToString(Layer) + " Dimension: " + Convert::ToString(Dim) + " numClass:" + Convert::ToString(num) + "\r\n";
			while (!file.eof())
			{
				for (int i = 0; i < class_count; i++)
					for (int j = 0; j < inputDim; j++)
						file >> Weights[i * inputDim + j];
				for (int i = 0; i < class_count; i++)
					file >> bias[i];
			}
			file.close();
		}//file.is_open
		delete[]c;
	}//Read_Data
	private: System::Void saveDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numSample != 0) {
			char** c = new char* [2];
			// Veri Kümesi yazılacak
			c[0] = "../Data/Samples.txt";
			c[1] = "../Data/weights.txt";
			std::ofstream ofs(c[0]);
			if (!ofs.bad()) {
				// Width,  Height, number of Class, data+label
				ofs << inputDim << " " << pictureBox1->Width / 2 << " " << pictureBox1->Height / 2 << " " << class_count << std::endl;
				for (int i = 0; i < numSample; i++) {
					for (int d = 0; d < inputDim; d++)
						ofs << Samples[i * inputDim + d] << " ";
					ofs << targets[i] << std::endl;
				}
				ofs.close();
			}
			else MessageBox::Show("Samples icin dosya acilamadi");
			std::ofstream file(c[1]);
			if (!file.bad()) {
				// #Layer Dimension numClass weights biases
				file << 1 << " " << inputDim << " " << class_count << std::endl;
				for (int k = 0; k < class_count * inputDim; k++)
					file << Weights[k] << " ";
				file << std::endl;
				for (int k = 0; k < class_count; k++)
					file << bias[k] << " ";
				file.close();
			}
			else MessageBox::Show("Weight icin dosya acilamadi");
			delete[]c;
		}
		else MessageBox::Show("At least one sample should be given");
	}//Save_Data
	
     private: System::Void testingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (Weights == nullptr) return;

		Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		Graphics^ g = Graphics::FromImage(surface);
		int cx = pictureBox1->Width / 2;
		int cy = pictureBox1->Height / 2;

		// Bölgeleri boya
		for (int y = 0; y < pictureBox1->Height; y += 4) {
			for (int x = 0; x < pictureBox1->Width; x += 4) {
				float inputX = (float)(x - cx);
				float inputY = (float)(cy - y);

				int winner = -1;
				float max_score = -99999.0f;

				for (int c = 0; c < class_count; c++) {
					float net = Weights[c * inputDim] * inputX +
						Weights[c * inputDim + 1] * inputY +
						bias[c];

					if (net > max_score) {
						max_score = net;
						winner = c;
					}
				}

				Color col;
				if (winner == 0) col = Color::FromArgb(50, 0, 0, 0);       
				else if (winner == 1) col = Color::FromArgb(50, 255, 0, 0); 
				else if (winner == 2) col = Color::FromArgb(50, 0, 0, 255); 
				else if (winner == 3) col = Color::FromArgb(50, 0, 255, 0);
				else if (winner == 4) col = Color::FromArgb(50, 255, 255, 0); 
				else if (winner == 5) col = Color::FromArgb(50, 255, 165, 0); 
				else col = Color::FromArgb(50, 154, 205, 50);                 

				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						if (x + i < pictureBox1->Width && y + j < pictureBox1->Height)
							surface->SetPixel(x + i, y + j, col);
			}
		}

		// Eksenleri çiz
		Pen^ axisPen = gcnew Pen(Color::Black, 2);
		g->DrawLine(axisPen, cx, 0, cx, pictureBox1->Height);
		g->DrawLine(axisPen, 0, cy, pictureBox1->Width, cy);

		// Noktaları çiz
		for (int i = 0; i < numSample; i++) {
			Pen^ p;
			int t = (int)targets[i];

			if (t == 0) p = gcnew Pen(Color::Red, 5);
			else if (t == 1) p = gcnew Pen(Color::Blue, 5);
			else if (t == 2) p = gcnew Pen(Color::Green, 5);
			else if (t == 3) p = gcnew Pen(Color::Orange, 5);
			else if (t == 4) p = gcnew Pen(Color::Purple, 5);
			else if (t == 5) p = gcnew Pen(Color::Pink, 5);
			else p = gcnew Pen(Color::Brown, 5);

			int px = (int)Samples[i * inputDim] + cx;
			int py = cy - (int)Samples[i * inputDim + 1];
			draw_sample(g, px, py, (int)targets[i]);
		}

		pictureBox1->Image = surface;
	}
	private: System::Void trainingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numSample == 0) return;

		class_count = Convert::ToInt32(ClassCountBox->Text);
		if (Weights != nullptr) delete[] Weights;
		if (bias != nullptr) delete[] bias;

		Weights = new float[class_count * inputDim];
		bias = new float[class_count];

		for (int i = 0; i < class_count * inputDim; i++) Weights[i] = ((float)rand() / RAND_MAX) - 0.5f;
		for (int i = 0; i < class_count; i++) bias[i] = ((float)rand() / RAND_MAX) - 0.5f;

		float lrn_rate = 0.01f;
		int max_epoch = 50000;
		int epoch = 0;
		bool error = true;

		if (errorHistory != nullptr) delete[] errorHistory;
		errorHistory = new float[max_epoch];
		errorHistoryCount = 0;

		//eğitim döngüsü
		while (error && epoch < max_epoch) {
			error = false; 
			float total_epoch_error = 0;
			for (int k = 0; k < numSample; k++) {
				int target = (int)targets[k];
				for (int c = 0; c < class_count; c++) {
					float net = 0;
					for (int d = 0; d < inputDim; d++)
						net += Weights[c * inputDim + d] * Samples[k * inputDim + d]; // y = w1x1 + w2x2 + b = 0
					net += bias[c];

					float desired = (c == target) ? 1.0f : -1.0f;
					float out = (net >= 0) ? 1.0f : -1.0f;

					if (desired != out) {
						float err = desired - out;
						for (int d = 0; d < inputDim; d++)
							Weights[c * inputDim + d] += lrn_rate * err * Samples[k * inputDim + d]; //wyeni = weski + lr * error * x
						bias[c] += lrn_rate * err;   //byeni = beski + lr * error
						error = true;
						total_epoch_error += fabs(err);  //error toplamı +2 ya da -2 olabilir o yüzden mutlak değer alıyorum. 
					}
				}
			}
			errorHistory[epoch] = total_epoch_error / (float)(numSample * class_count);  //tüm hatalar / bir epochta yapılan toplam işlem sayısı
			epoch++;
		}
		errorHistoryCount = epoch;  //DrawErrorChartta kullanılmak üzere hafızaya kaydediyoruz, gerekli epoch sayısını hafızada tutuyor.

		Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		Graphics^ g = Graphics::FromImage(surface);
		g->Clear(Color::White);

		int cx = pictureBox1->Width / 2;
		int cy = pictureBox1->Height / 2;
		g->DrawLine(Pens::Black, cx, 0, cx, pictureBox1->Height);
		g->DrawLine(Pens::Black, 0, cy, pictureBox1->Width, cy);

		for (int c = 0; c < class_count; c++) {
			Pen^ p;
			if (c == 0) p = gcnew Pen(Color::Black, 2);          
			else if (c == 1) p = gcnew Pen(Color::Red, 2);       
			else if (c == 2) p = gcnew Pen(Color::Blue, 2);     
			else if (c == 3) p = gcnew Pen(Color::Green, 2);    
			else if (c == 4) p = gcnew Pen(Color::Yellow, 2);   
			else if (c == 5) p = gcnew Pen(Color::Orange, 2);   
			else p = gcnew Pen(Color::YellowGreen, 2);           

			float w0 = Weights[c * inputDim];
			float w1 = Weights[c * inputDim + 1];
			float b = bias[c];

			if (System::Math::Abs(w1) > 0.001)  //sıfıra bölme hatasını önle
			{
				float x1 = -cx;  //ekranın en sol ucu 
				float y1 = -(w0 * x1 + b) / w1;
				float x2 = cx;  //ekranın en sağ ucu 
				float y2 = -(w0 * x2 + b) / w1;
				g->DrawLine(p, (int)(x1 + cx), (int)(cy - y1), (int)(x2 + cx), (int)(cy - y2));  //çizgiyi çiz
			}
		}

		for (int i = 0; i < numSample; i++) { // Hafızadaki tüm kayıtlı örnekleri tekrar çiz, çizgi noktaların üstünde kalmasın diye.
			Pen^ p;
			int t = (int)targets[i];
			if (t == 0) p = gcnew Pen(Color::Red, 5);
			else if (t == 1) p = gcnew Pen(Color::Blue, 5);
			else if (t == 2) p = gcnew Pen(Color::Green, 5);
			else p = gcnew Pen(Color::Orange, 5);

			int px = (int)Samples[i * inputDim] + cx;
			int py = cy - (int)Samples[i * inputDim + 1];
			draw_sample(g, px, py, (int)targets[i]);

		}
		pictureBox1->Image = surface;

		// Hata grafiğini çiz
		DrawErrorChart();

		MessageBox::Show("Egitim Bitti! Epoch: " + epoch);
	}
	private: System::Void regressionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	// Eğer ağ kurulmadıysa önce uyar
		if (class_count == 0) {
			class_count = Convert::ToInt32(ClassCountBox->Text); 
		}

		
		if (class_count != 1) {
			MessageBox::Show("Hata: Regresyon işlemi sadece 'Sınıf Sayısı' 1 olduğunda yapılabilir.\nLütfen Sınıf Sayısını 1 yapıp 'Network Setting' butonuna basınız.");
			return; 
		}


		if (numSample < 2) {
			MessageBox::Show("Regresyon için en az 2 nokta gerekli!");
			return;
		}
		 // regresyon denklemimiz: i y = wx + b
		float* x_data = new float[numSample];    // S[0] misal = x1 tutuyor , x dizisini tutanlar için ayrı bir pointer tanımlayalım
		float* y_data = new float[numSample];    // s[1] misal = y1 tutuyor , y dizisini tutanlar için ayrı bir pointer tanımlayalım

		float scaleX = pictureBox1->Width / 2.0f; // normalize etmek için ölçek faktörleri
		float scaleY = pictureBox1->Height / 2.0f;

		for (int i = 0; i < numSample; i++) {
			x_data[i] = Samples[i * inputDim] / scaleX;  //normalizasyon işlemi ile [-1,1] aralığına getiriyoruz
			y_data[i] = Samples[i * inputDim + 1] / scaleY;
		}

		//ilk tahmin blogunu yazayım: 
		float w_reg = ((float)rand() / RAND_MAX) - 0.5f;  //w_reg, b_reg için rastgele başlangıc degerleri  rand() --> 32k ya kadar rastgele bi sayı ataması yapılır , 0.5 -0.5 arası bir değer verilir.
		float b_reg = ((float)rand() / RAND_MAX) - 0.5f;  // hep pozitif cıkmasın diye -0.5f ile cıkarttım.  

		float learning_rate = 0.05f;
		int max_epoch = 2000;
		float total_err;
		int epoch = 0;
		float mse;

		if (errorHistory != nullptr) delete[] errorHistory;
		errorHistory = new float[max_epoch];
		errorHistoryCount = 0;

		do {
			mse = 0.0f;
			total_err = 0.0f;
			for (int k = 0; k < numSample; k++) {
				float prediction = w_reg * x_data[k] + b_reg;
				float err = y_data[k] - prediction; //Hataya göre yukarı ya da aşağı incez.
				w_reg += learning_rate * err * x_data[k];  //çizgi açısını güncelleyelim
				b_reg += learning_rate * err;  // Çizgiyi komple yukarı veya aşağı taşı.

				mse += err * err;

				total_err += 0.5f * err * err; 
			}
			// Epoch başına ortalama MSE
			mse = mse / (2.0f * numSample);  // MSE = (1/2n) * Σ(error²)
			// Hatayı kaydet
			errorHistory[epoch] = mse;
			epoch++;
		} while (total_err > 0.0001f && epoch < max_epoch);

		errorHistoryCount = epoch;  


		Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		Graphics^ g = Graphics::FromImage(surface);
		g->Clear(Color::White);

		Pen^ axisPen = gcnew Pen(Color::Black, 2.0f);
		int cx = pictureBox1->Width / 2;
		int cy = pictureBox1->Height / 2;
		g->DrawLine(axisPen, cx, 0, cx, pictureBox1->Height);
		g->DrawLine(axisPen, 0, cy, pictureBox1->Width, cy);

		Pen^ linePen = gcnew Pen(Color::Red, 3.0f);
		float x1_norm = -1.0f;
		float y1_norm = w_reg * x1_norm + b_reg;
		float x2_norm = 1.0f;
		float y2_norm = w_reg * x2_norm + b_reg;

		g->DrawLine(linePen,
			(int)(x1_norm * scaleX + cx), (int)(cy - y1_norm * scaleY),
			(int)(x2_norm * scaleX + cx), (int)(cy - y2_norm * scaleY));

		for (int i = 0; i < numSample; i++) {
			Pen^ p = gcnew Pen(Color::Blue, 3.0f);
			int px = (int)Samples[i * inputDim] + cx;
			int py = cy - (int)Samples[i * inputDim + 1];
			draw_sample(g, px, py, (int)targets[i]);
		}
		pictureBox1->Image = surface;


		// 9. HATA GRAFİĞİNİ ÇİZ
		DrawErrorChart();

		delete[] x_data;
		delete[] y_data;


		// 10. SONUCU BİLDİR
		MessageBox::Show("Regresyon Tamamlandı!\nEpoch: " + epoch +
			"\nSon ort error: " + mse.ToString("F6") +
			"\nw = " + w_reg.ToString("F4") +
			"\nb = " + b_reg.ToString("F4"));
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void ClassCountBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void groupBox2_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void ClassNoBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	}
	private: System::Void fileToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void processToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void menuStrip1_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void saveFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	}
	};
}