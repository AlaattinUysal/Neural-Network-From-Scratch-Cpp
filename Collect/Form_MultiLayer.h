#pragma once
#include "Process.h"
#include "network.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <string>

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class Form_MultiLayer : public System::Windows::Forms::Form
	{
	public:
		Form_MultiLayer(void)
		{
			InitializeComponent();
			srand((unsigned int)time(0));
		}

	protected:
		~Form_MultiLayer()
		{
			if (components) delete components;

			// --- BELLEK TEMİZLİĞİ ---
			if (Samples != nullptr) delete[] Samples;
			if (targets != nullptr) delete[] targets;

			if (Layers) delete[] Layers;
			if (NeuronOffsets) delete[] NeuronOffsets;
			if (WeightOffsets) delete[] WeightOffsets;

			if (Activations) delete[] Activations;
			if (Errors) delete[] Errors;
			if (Weights) delete[] Weights;
			if (Biases) delete[] Biases;
			if (errorHistory) delete[] errorHistory;
		}

	private:
		// --- ARAYÜZ BİLEŞENLERİ ---
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::GroupBox^ groupBox1;
		System::Windows::Forms::Button^ Set_Net;
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::ComboBox^ ClassCountBox;

		// MultiLayer Parametreleri
		System::Windows::Forms::Label^ lbl_Hidden;
		System::Windows::Forms::TextBox^ txt_HiddenLayer;
		System::Windows::Forms::Label^ lbl_Neurons;
		System::Windows::Forms::TextBox^ txt_NeuronCount;
		System::Windows::Forms::Label^ lbl_LR;
		System::Windows::Forms::TextBox^ txt_LearnRate;

		System::Windows::Forms::GroupBox^ groupBox2;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::ComboBox^ ClassNoBox;
		System::Windows::Forms::Label^ label3;

		System::Windows::Forms::PictureBox^ chartBox;

		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ processToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ trainingToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ testingToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ regressionToolStripMenuItem;

		System::ComponentModel::Container^ components;

		// --- MANTIKSAL DEĞİŞKENLER ---
		int numSample = 0;
		int inputDim = 2;
		float* Samples = nullptr;
		float* targets = nullptr;
		float* errorHistory = nullptr;
		int errorHistoryCount = 0;

		// MLP Yapısı
		int TotalLayers = 0;
		int* Layers = nullptr;
		int* NeuronOffsets = nullptr;
		int* WeightOffsets = nullptr;
		float* Activations = nullptr;
		float* Errors = nullptr;
		float* Weights = nullptr;
		float* Biases = nullptr;
		float learningRate = 0.1f;

		// fonksiyonlar
		float sigmoid(float x) {
			if (x > 10) return 0.9999f;
			if (x < -10) return 0.0001f;
			return 1.0f / (1.0f + exp(-x));
		}

		float sigmoid_derivative(float x) {    
			return x * (1.0f - x);
		}

#pragma region Windows Form Designer generated code
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
			this->processToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->trainingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->testingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->regressionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->chartBox = (gcnew System::Windows::Forms::PictureBox());

			this->lbl_Hidden = (gcnew System::Windows::Forms::Label());
			this->txt_HiddenLayer = (gcnew System::Windows::Forms::TextBox());
			this->lbl_Neurons = (gcnew System::Windows::Forms::Label());
			this->txt_NeuronCount = (gcnew System::Windows::Forms::TextBox());
			this->lbl_LR = (gcnew System::Windows::Forms::Label());
			this->txt_LearnRate = (gcnew System::Windows::Forms::TextBox());

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();

			// pictureBox1
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->pictureBox1->Location = System::Drawing::Point(17, 43);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1069, 711);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form_MultiLayer::pictureBox1_Paint);
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form_MultiLayer::pictureBox1_MouseClick);

			// groupBox1
			this->groupBox1->Controls->Add(this->Set_Net);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->ClassCountBox);
			this->groupBox1->Controls->Add(this->lbl_Hidden);
			this->groupBox1->Controls->Add(this->txt_HiddenLayer);
			this->groupBox1->Controls->Add(this->lbl_Neurons);
			this->groupBox1->Controls->Add(this->txt_NeuronCount);
			this->groupBox1->Controls->Add(this->lbl_LR);
			this->groupBox1->Controls->Add(this->txt_LearnRate);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(162)));
			this->groupBox1->Location = System::Drawing::Point(1159, 62);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4);
			this->groupBox1->Size = System::Drawing::Size(267, 200);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Network Architecture";

			// Class Count
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(144, 28);
			this->label1->Text = L"Sınıf Sayısı";
			this->ClassCountBox->FormattingEnabled = true;
			this->ClassCountBox->Items->AddRange(gcnew cli::array< System::Object^  >(7) { L"1", L"2", L"3", L"4", L"5", L"6", L"7" });			this->ClassCountBox->Location = System::Drawing::Point(13, 25);
			this->ClassCountBox->Size = System::Drawing::Size(108, 25);
			this->ClassCountBox->Text = L"1";

			// Hidden Layer
			this->lbl_Hidden->AutoSize = true;
			this->lbl_Hidden->Location = System::Drawing::Point(144, 60);
			this->lbl_Hidden->Text = L"Gizli Katman";
			this->txt_HiddenLayer->Location = System::Drawing::Point(13, 57);
			this->txt_HiddenLayer->Size = System::Drawing::Size(108, 20);
			this->txt_HiddenLayer->Text = L"1";

			// Neuron Count
			this->lbl_Neurons->AutoSize = true;
			this->lbl_Neurons->Location = System::Drawing::Point(144, 90);
			this->lbl_Neurons->Text = L"Nöron Sayısı";
			this->txt_NeuronCount->Location = System::Drawing::Point(13, 87);
			this->txt_NeuronCount->Size = System::Drawing::Size(108, 20);
			this->txt_NeuronCount->Text = L"5";

			// Learning Rate
			this->lbl_LR->AutoSize = true;
			this->lbl_LR->Location = System::Drawing::Point(144, 120);
			this->lbl_LR->Text = L"Learn Rate";
			this->txt_LearnRate->Location = System::Drawing::Point(13, 117);
			this->txt_LearnRate->Size = System::Drawing::Size(108, 20);
			this->txt_LearnRate->Text = L"0.1";

			// Set Net Button
			this->Set_Net->Location = System::Drawing::Point(13, 150);
			this->Set_Net->Margin = System::Windows::Forms::Padding(4);
			this->Set_Net->Name = L"Set_Net";
			this->Set_Net->Size = System::Drawing::Size(175, 41);
			this->Set_Net->Text = L"Network Setting";
			this->Set_Net->UseVisualStyleBackColor = true;
			this->Set_Net->Click += gcnew System::EventHandler(this, &Form_MultiLayer::Set_Net_Click);

			// groupBox2
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->ClassNoBox);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(162)));
			this->groupBox2->Location = System::Drawing::Point(1172, 280);
			this->groupBox2->Margin = System::Windows::Forms::Padding(4);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(4);
			this->groupBox2->Size = System::Drawing::Size(253, 75);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Data Collection";

			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(131, 28);
			this->label2->Text = L"Örnek Etiketi";
			this->ClassNoBox->FormattingEnabled = true;
			this->ClassNoBox->Items->AddRange(gcnew cli::array< System::Object^  >(9) { L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9" });
			this->ClassNoBox->Location = System::Drawing::Point(9, 25);
			this->ClassNoBox->Size = System::Drawing::Size(99, 25);
			this->ClassNoBox->Text = L"1";

			// label3
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(1168, 370);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(44, 16);
			this->label3->Text = L"Samples Count: 0";

			// textBox1
			this->chartBox->BackColor = System::Drawing::Color::WhiteSmoke;
			this->chartBox->Location = System::Drawing::Point(1159, 400); // Eski textbox konumu
			this->chartBox->Name = L"chartBox";
			this->chartBox->Size = System::Drawing::Size(328, 347);   // Eski textbox boyutu
			this->chartBox->TabIndex = 5;
			this->chartBox->TabStop = false;

			// menuStrip1
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {
				this->processToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1924, 28);
			this->menuStrip1->Text = L"menuStrip1";

			this->processToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->trainingToolStripMenuItem,
					this->testingToolStripMenuItem,
					this->regressionToolStripMenuItem
			});
			this->processToolStripMenuItem->Text = L"Process";

			this->trainingToolStripMenuItem->Text = L"Training";
			this->trainingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayer::trainingToolStripMenuItem_Click);

			this->testingToolStripMenuItem->Text = L"Testing";
			this->testingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayer::testingToolStripMenuItem_Click);

			this->regressionToolStripMenuItem->Text = L"Regression";
			this->regressionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayer::regressionToolStripMenuItem_Click);

			// Form_MultiLayer
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1550, 800);
			this->Controls->Add(this->chartBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form_MultiLayer";
			this->Text = L"Form_MultiLayer";
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
#pragma endregion

	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		// DÜZELTME: Ambiguous hatası olmaması için yeni Pen ve float cast
		Pen^ axisPen = gcnew Pen(Color::Black, 2.0f);
		float cx = (float)(pictureBox1->Width / 2);
		float cy = (float)(pictureBox1->Height / 2);

		e->Graphics->DrawLine(axisPen, cx, 0.0f, cx, (float)pictureBox1->Height);
		e->Graphics->DrawLine(axisPen, 0.0f, cy, (float)pictureBox1->Width, cy);
	}

	private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		float scaleX = pictureBox1->Width / 2.0f;
		float scaleY = pictureBox1->Height / 2.0f;

		// 1. Veriyi Normalize Et (-1 ile 1 arası)
		float* x = new float[inputDim];
		x[0] = (float)(e->X - scaleX) / scaleX;
		x[1] = (float)(scaleY - e->Y) / scaleY;

		int label = Convert::ToInt32(ClassNoBox->Text) - 1;

		// 2. Veriyi Kaydet
		if (numSample == 0) {
			numSample = 1;
			Samples = new float[inputDim];
			targets = new float[1];
			Samples[0] = x[0]; Samples[1] = x[1];
			targets[0] = (float)label;
		}
		else {
			float* newSamples = new float[(numSample + 1) * inputDim];
			float* newTargets = new float[numSample + 1];

			for (int i = 0; i < numSample * inputDim; i++) newSamples[i] = Samples[i];
			for (int i = 0; i < numSample; i++) newTargets[i] = targets[i];

			newSamples[numSample * inputDim] = x[0];
			newSamples[numSample * inputDim + 1] = x[1];
			newTargets[numSample] = (float)label;

			delete[] Samples; delete[] targets;
			Samples = newSamples; targets = newTargets;
			numSample++;
		}

		// 3. Ekrana ARTI (+) ÇİZ
		Pen^ pen;
		switch (label) {
		case 0: pen = gcnew Pen(Color::Black, 3.0f); break;
		case 1: pen = gcnew Pen(Color::Red, 3.0f); break;
		case 2: pen = gcnew Pen(Color::Blue, 3.0f); break;
		case 3: pen = gcnew Pen(Color::Green, 3.0f); break;
		default: pen = gcnew Pen(Color::Yellow, 3.0f);
		}

		Graphics^ g = pictureBox1->CreateGraphics();
		// Yatay çizgi (-)
		g->DrawLine(pen, e->X - 5, e->Y, e->X + 5, e->Y);
		// Dikey çizgi (|)
		g->DrawLine(pen, e->X, e->Y - 5, e->X, e->Y + 5);

		label3->Text = "Samples Count: " + Convert::ToString(numSample);

		//textBox1->Text += "Sample: " + Convert::ToString(x[0]) + ", " + Convert::ToString(x[1]) + " Class: " + label + "\r\n";
		delete[] x;
	}

		   void DrawErrorChart() {
			   if (errorHistoryCount < 2) return;

			   Bitmap^ chartBmp = gcnew Bitmap(chartBox->Width, chartBox->Height);
			   Graphics^ gg = Graphics::FromImage(chartBmp);
			   gg->Clear(Color::White);
			   gg->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			   // Kenar boşlukları
			   int marginLeft = 60;
			   int marginRight = 20;
			   int marginTop = 40;
			   int marginBottom = 40;
			   int graphWidth = chartBox->Width - marginLeft - marginRight;
			   int graphHeight = chartBox->Height - marginTop - marginBottom;

			   // --- ÖLÇEK HESAPLAMA (ZOOM) ---
			   // Grafiğin tavan yapmasını engellemek için ilk epochları atlıyoruz
			   float maxVal = 0;
			   int startCheckIndex = (errorHistoryCount > 50) ? 10 : 0;

			   for (int i = startCheckIndex; i < errorHistoryCount; i++)
				   if (errorHistory[i] > maxVal) maxVal = errorHistory[i];

			   // Güvenlik: maxVal 0 olmasın
			   if (maxVal < 0.0001f) maxVal = 0.0001f;

			   // --- GRID VE SAYILAR (Y EKSENİ) ---
			   Pen^ gridPen = gcnew Pen(Color::LightGray, 1);
			   System::Drawing::Font^ fontAxis = gcnew System::Drawing::Font("Arial", 7);
			   Brush^ textBrush = Brushes::Black;

			   // 5 parçaya bölerek çizgileri ve sayıları çiz
			   int numDivisions = 5;
			   for (int i = 0; i <= numDivisions; i++) {
				   // Yükseklik hesapla (Aşağıdan yukarıya)
				   int yPos = marginTop + graphHeight - (int)((float)i / numDivisions * graphHeight);

				   // Değer hesapla
				   float val = maxVal * ((float)i / numDivisions);

				   // Yatay çizgi (Grid)
				   if (i > 0) // En alt çizgi ana eksen olacak, onu grid olarak çizme
					   gg->DrawLine(gridPen, marginLeft, yPos, marginLeft + graphWidth, yPos);

				   // Yan tarafa sayıyı yaz (Format: Virgülden sonra 4 hane)
				   String^ label = String::Format("{0:F4}", val);
				   // Yazıyı sağa dayalı çizmek için ölçü alıyoruz (Basit hiza)
				   gg->DrawString(label, fontAxis, textBrush, 5, yPos - 6);
			   }

			   // --- ANA EKSEN ÇİZGİLERİ (SİYAH L ŞEKLİ) ---
			   Pen^ axisPen = gcnew Pen(Color::Black, 2);
			   // Y Ekseni (Dikey)
			   gg->DrawLine(axisPen, marginLeft, marginTop, marginLeft, marginTop + graphHeight);
			   // X Ekseni (Yatay)
			   gg->DrawLine(axisPen, marginLeft, marginTop + graphHeight, marginLeft + graphWidth, marginTop + graphHeight);

			   // --- GRAFİK ÇİZİMİ ---
			   Pen^ penBlue = gcnew Pen(Color::DodgerBlue, 2.0f);
			   float stepX = (float)graphWidth / (float)(errorHistoryCount > 1 ? errorHistoryCount - 1 : 1);

			   for (int i = 0; i < errorHistoryCount - 1; i++) {
				   // X koordinatları
				   float x1 = marginLeft + i * stepX;
				   float x2 = marginLeft + (i + 1) * stepX;

				   // Y koordinatları (Değer maxVal'dan büyükse tavana sabitle)
				   float val1 = (errorHistory[i] > maxVal) ? maxVal : errorHistory[i];
				   float val2 = (errorHistory[i + 1] > maxVal) ? maxVal : errorHistory[i + 1];

				   float y1 = marginTop + graphHeight - ((val1 / maxVal) * graphHeight);
				   float y2 = marginTop + graphHeight - ((val2 / maxVal) * graphHeight);

				   // Çizim alanı dışına taşmayı engelle
				   if (y1 < marginTop) y1 = (float)marginTop;
				   if (y2 < marginTop) y2 = (float)marginTop;

				   gg->DrawLine(penBlue, x1, y1, x2, y2);
			   }

			   System::Drawing::Font^ fontInfo = gcnew System::Drawing::Font("Arial", 8, FontStyle::Bold);
			   // Gerçek Max hatayı bul (Zoomsuz hali)
			   float realMax = 0;
			   for (int i = 0; i < errorHistoryCount; i++) if (errorHistory[i] > realMax) realMax = errorHistory[i];

			   String^ info = String::Format("Epoch: {0} | Max Hata: {1:F5} | Son Hata: {2:F6}",
				   errorHistoryCount, realMax, errorHistory[errorHistoryCount - 1]);

			   gg->DrawString(info, fontInfo, Brushes::DarkBlue, marginLeft, 10);

			   chartBox->Image = chartBmp;
		   }

	private: System::Void Set_Net_Click(System::Object^ sender, System::EventArgs^ e) {
		// Önce Temizlik
		if (Activations) delete[] Activations; if (Errors) delete[] Errors;  //boş olan şeyleri silmesin diye ilk kontrol ediyoruz, sonra nullptr değilse siliyoruz. yeni ağ kurduğumuzda eskisini sileriz.
		if (Weights) delete[] Weights; if (Biases) delete[] Biases;
		if (Layers) delete[] Layers;
		if (NeuronOffsets) delete[] NeuronOffsets; if (WeightOffsets) delete[] WeightOffsets;

		try {
			int numHidden = Convert::ToInt32(txt_HiddenLayer->Text);  //Gizli katmanları buradan 
			int numNeurons = Convert::ToInt32(txt_NeuronCount->Text); 
			int numClasses = Convert::ToInt32(ClassCountBox->Text); //Çıkış katmanları buradan
			learningRate = (float)Convert::ToDouble(txt_LearnRate->Text);

			TotalLayers = numHidden + 2;   //Giriş+çıkış (2) + Hiddenlayers
			Layers = new int[TotalLayers]; 
			Layers[0] = inputDim; //X ve Y koord. giriş katmanları    
			for (int i = 1; i <= numHidden; i++) Layers[i] = numNeurons; //Gizli katman çok büyük olursa, ağın başı öğrenemez, sigmoid_derivate küçülerek yok olabilir.1-2 tane gizli katman idealdir.
			Layers[TotalLayers - 1] = numClasses;  //Kaç tane sınıf varsa çıkış katmanlarım buradna geliyor.

			NeuronOffsets = new int[TotalLayers];
			WeightOffsets = new int[TotalLayers];

			int total_neurons = 0;
			int total_weights = 0;
			int total_biases = 0;

			for (int i = 0; i < TotalLayers; i++) {
				//Burada nöronların yerini belirleriz.
				NeuronOffsets[i] = total_neurons; //Neuronoffset[0] = 0 dır.
				total_neurons += Layers[i]; //Layers[0] = 2 dir, toplam nöron sayısı 2 oldu.
				if (i < TotalLayers - 1) {  
					WeightOffsets[i] = total_weights;  //Weightoffset[0] = 0 (baslangıc indeksi) total weight = 2x3 olur FCN
					total_weights += Layers[i] * Layers[i + 1];
					total_biases += Layers[i + 1]; //giriş nöronlarını es geçtim, çünkü giriş nöronları işlemde yer kaplamamalı
				}								
												// Net = Giriş x Ağırlık + Bias
			}

			Activations = new float[total_neurons];
			Errors = new float[total_neurons]; //her bir nöron için hata değeri ayıralım
			Weights = new float[total_weights];
			Biases = new float[total_biases];

			for (int i = 0; i < total_weights; i++) Weights[i] = ((float)rand() / RAND_MAX) - 0.5f;  //sigmoid türevi tepe noktalarda 0 lar o yüzden en iyi aralık -0.5 ile 0.5 arasıdır.
			for (int i = 0; i < total_biases; i++) Biases[i] = ((float)rand() / RAND_MAX) - 0.5f; //Denge için negatif değerler koydum. (0-1 hep pozitif)

			Set_Net->Text = "Network is Ready: ";

		}
		catch (...) { MessageBox::Show("Ayarları kontrol ediniz."); }
	}

	private: System::Void trainingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numSample == 0 || TotalLayers == 0) return;

		int max_epoch = 5000;
		int epoch = 0;
		double total_mse = 0;  //MSE = Toplam / ÖrnekSayısı  global degisken, döngü bittiginde toplam hatayı verir, ekrana yazdırılır.

		if (errorHistory) delete[] errorHistory;
		errorHistory = new float[max_epoch];
		errorHistoryCount = 0;

		do {
			total_mse = 0; //Local değişken, her epoch basında sıfırlanacak. ve tüm örnekler icin toplanır.
			for (int s = 0; s < numSample; s++) {
				// 1. Forward   (Gelen her veriyi weights ile çarp , bias ekle , sonucu sigmoid fonksiyonuna sok)
				int input_start = NeuronOffsets[0];  //Giriş katmanı adresi
				for (int i = 0; i < inputDim; i++) Activations[input_start + i] = Samples[s * inputDim + i]; //Veriyi adresten alıp nörona yazıyorum
																											//I1 ve I2 değerlerini belirliyorum.
				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l]; 
					int out_start = NeuronOffsets[l + 1];  //veriyi yazacagım katman 
					int w_start = WeightOffsets[l]; 
					int in_count = Layers[l];  
					int out_count = Layers[l + 1]; //hedefteki nöron 

					for (int j = 0; j < out_count; j++) {
						float net = 0;
						for (int i = 0; i < in_count; i++) {
							int w_idx = w_start + (i * out_count)  + j; // matrisi düz dizide tutuyorum. bir sonrakine geçerken öncekinin baglandıgı tüm nöronları atla.
							net += Activations[in_start + i] * Weights[w_idx]; //net+yeni deger
						}
						int b_idx = out_start + j - inputDim;  
						net += Biases[b_idx];  // y = wx + b
						Activations[out_start + j] = sigmoid(net); //gizli ve çıkış katmanları için aktivasyon hesaplarız, sonraki turda kullancaz
					}
				}

				// 2. Error Calculation
				int last_layer = TotalLayers - 1;
				int last_start = NeuronOffsets[last_layer];  //çıkış katmanı başlangıc adresi.
				int last_count = Layers[last_layer]; //Çıkış katmanı kaç tane nöron var?
				int target_class = (int)targets[s];  //tıkladığım nokta hangi sınıfa ait

				for (int k = 0; k < last_count; k++) {
					float desired = (k == target_class) ? 1.0f : 0.0f;
					float output = Activations[last_start + k];
					float error = desired - output;
					total_mse += error * error;
					Errors[last_start + k] = error * sigmoid_derivative(output); //hangi nöronun ne kadar güncelleneceğini belirliyoruz 
				}																//Çıkış katmanı hatası belirlenir. backprop da kullanacagız
				
				// Backprop  ; çıkış katmanındaki hatayı alıcaz, geriye doğru (ağın icine doğru) dağıtarak hangi gizli nöronun bu hatada ne kadar payı var hesaplıcaz. 
				for (int l = TotalLayers - 2; l > 0; l--) { 
					int curr_start = NeuronOffsets[l]; // hata buraya yazılcak
					int next_start = NeuronOffsets[l + 1];  //  hata buradan okunacak
					int w_start = WeightOffsets[l]; 
					int curr_count = Layers[l];
					int next_count = Layers[l + 1];  

					for (int i = 0; i < curr_count; i++) {
						float sum = 0;  //her bir gizli nöron için sum değişkeni baştan sıfırlanır.
						for (int j = 0; j < next_count; j++) {
							int w_idx = w_start + (i * next_count) + j;
							sum += Errors[next_start + j] * Weights[w_idx];	//  Gizli Hata hesabı
							       //Çıkış katmanından gelen hatalar (01  ,  02 ) 
						}
						Errors[curr_start + i] = sum * sigmoid_derivative(Activations[curr_start + i]);  //Hatayı nöronun içine koy ve değişimi bul.
					} // bir sonraki katmanın hatasını, aradaki ağırlıklarla çarparak geriye taşıyoruz.
				}

				// 3. Update   Weights ve bias dizisindeki sayılarda çok küçük değişiklikler yaparak ağın öğrenmesini sağlar
				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l];
					int out_start = NeuronOffsets[l + 1];  //hatayı düzeltecek nöron 
					int w_start = WeightOffsets[l];
					int in_count = Layers[l];
					int out_count = Layers[l + 1];

					for (int j = 0; j < out_count; j++) {
						float delta = Errors[out_start + j];   // Delta -> nöronu düzeltme miktarıdır , Error calcl. gelen ve backprop dan gelen error yapısı
						int b_idx = out_start + j - inputDim;
						Biases[b_idx] += learningRate * delta; // Byeni = Beski + Öğrenme Hızı * Hata

						for (int i = 0; i < in_count; i++) {
							int w_idx = w_start + (i * out_count) + j; 
							Weights[w_idx] += learningRate * delta * Activations[in_start + i];  //Wyeni = Weski + Öğrenme Hızı * Hata * Giriş
						}
					}
				}
			}
			if (epoch < max_epoch) {
				errorHistory[epoch] = (float)total_mse;
			}
			epoch++;
		} while (epoch < max_epoch && total_mse > 0.001);

		errorHistoryCount = epoch;
		DrawErrorChart();

		//textBox1->Text += "Training işlemi tamamlandı. Epoch: " + epoch + " MSE: " + total_mse + "\r\n";

		MessageBox::Show("Eğitim Tamamlandı!\nEpoch: " + epoch + "\nHata (MSE): " + total_mse);
	}

	private: System::Void testingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (TotalLayers == 0) return;

		Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		float scaleX = pictureBox1->Width / 2.0f;
		float scaleY = pictureBox1->Height / 2.0f;

		for (int y = 0; y < pictureBox1->Height; y += 4) {
			for (int x = 0; x < pictureBox1->Width; x += 4) {
				float inputX = (float)(x - scaleX) / scaleX;
				float inputY = (float)(scaleY - y) / scaleY;

				Activations[NeuronOffsets[0] + 0] = inputX;
				Activations[NeuronOffsets[0] + 1] = inputY;

				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l];
					int out_start = NeuronOffsets[l + 1];
					int w_start = WeightOffsets[l];
					int in_count = Layers[l];
					int out_count = Layers[l + 1];

					for (int j = 0; j < out_count; j++) {
						float net = 0;
						for (int i = 0; i < in_count; i++) {
							int w_idx = w_start + (i * out_count) + j;
							net += Activations[in_start + i] * Weights[w_idx];
						}
						int b_idx = out_start + j - inputDim;
						net += Biases[b_idx];
						Activations[out_start + j] = sigmoid(net);
					}
				}

				int last_start = NeuronOffsets[TotalLayers - 1];
				int last_count = Layers[TotalLayers - 1];
				int winner = -1;
				float max_score = -999.0f;

				for (int k = 0; k < last_count; k++) {
					if (Activations[last_start + k] > max_score) {
						max_score = Activations[last_start + k];
						winner = k;
					}
				}

				Color col;
				if (winner == 0) col = Color::FromArgb(50, 0, 0, 0);
				else if (winner == 1) col = Color::FromArgb(50, 255, 0, 0);
				else if (winner == 2) col = Color::FromArgb(50, 0, 0, 255);
				else col = Color::FromArgb(50, 0, 255, 0);

				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						if (x + i < pictureBox1->Width && y + j < pictureBox1->Height)
							surface->SetPixel(x + i, y + j, col);
			}
		}

		Graphics^ g = Graphics::FromImage(surface);
		Pen^ axisPen = gcnew Pen(Color::Black, 2.0f);
		float cx = (float)(pictureBox1->Width / 2);
		float cy = (float)(pictureBox1->Height / 2);
		g->DrawLine(axisPen, cx, 0.0f, cx, (float)pictureBox1->Height);
		g->DrawLine(axisPen, 0.0f, cy, (float)pictureBox1->Width, cy);

		for (int i = 0; i < numSample; i++) {
			Pen^ p;
			int t = (int)targets[i];
			if (t == 0) p = gcnew Pen(Color::Black, 3);
			else if (t == 1) p = gcnew Pen(Color::Red, 3);
			else if (t == 2) p = gcnew Pen(Color::Blue, 3);
			else p = gcnew Pen(Color::Green, 3);

			int px = (int)(Samples[i * inputDim] * scaleX + scaleX);
			int py = (int)(scaleY - Samples[i * inputDim + 1] * scaleY);

			// YENİ ARTI (+) ŞEKLİ
			g->DrawLine(p, px - 5, py, px + 5, py);
			g->DrawLine(p, px, py - 5, px, py + 5);
		}
		pictureBox1->Image = surface;
	}

		  

	private: System::Void regressionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		int currentClassCount = Convert::ToInt32(ClassCountBox->Text);

		if (currentClassCount != 1) {
			MessageBox::Show("Hata: Regresyon işlemi sadece 'Sınıf Sayısı' 1 olduğunda yapılabilir.");
			return;
		}

		if (numSample < 2 || TotalLayers == 0) {
			MessageBox::Show("En az 2 örnek gerekli ve ağ kurulmalı!");
			return;
		}

		learningRate = 0.5f;
		int max_epoch = 50000;
		int epoch = 0;
		double total_mse = 0;

		if (errorHistory) delete[] errorHistory;
		errorHistory = new float[max_epoch];
		errorHistoryCount = 0;

		// EĞİTİM
		do {
			total_mse = 0;

			for (int s = 0; s < numSample; s++) {
				float inputX = Samples[s * inputDim];
				float targetY = Samples[s * inputDim + 1];

				// FORWARD (Gizli katmanlarda sigmoid, ÇIKIŞTA LINEAR)
				int input_start = NeuronOffsets[0];
				Activations[input_start + 0] = inputX;
				Activations[input_start + 1] = 1.0f; // bias

				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l];
					int out_start = NeuronOffsets[l + 1];
					int w_start = WeightOffsets[l];
					int in_count = Layers[l];
					int out_count = Layers[l + 1];

					bool isOutputLayer = (l == TotalLayers - 2); // Son katman mı?

					for (int j = 0; j < out_count; j++) {
						float net = 0;
						for (int i = 0; i < in_count; i++) {
							int w_idx = w_start + (i * out_count) + j;
							net += Activations[in_start + i] * Weights[w_idx];
						}
						int b_idx = out_start + j - inputDim;
						if (b_idx >= 0) net += Biases[b_idx];

						// KRITÝK: Çıkış katmanında LINEAR, diğerlerinde sigmoid
						if (isOutputLayer) {
							Activations[out_start + j] = net;  // LINEAR OUTPUT
						}
						else {
							Activations[out_start + j] = sigmoid(net);
						}
					}
				}

				// HATA HESAPLA
				int last_start = NeuronOffsets[TotalLayers - 1];
				float predicted_Y = Activations[last_start];
				float error = targetY - predicted_Y;
				total_mse += error * error;

				// Çıkış katmanı delta (LINEAR türev = 1)
				Errors[last_start] = error;  // Sigmoid türevi YOK

				// BACKPROP (Gizli katmanlar sigmoid türevli)
				for (int l = TotalLayers - 2; l > 0; l--) {
					int curr_start = NeuronOffsets[l];
					int next_start = NeuronOffsets[l + 1];
					int w_start = WeightOffsets[l];
					int curr_count = Layers[l];
					int next_count = Layers[l + 1];

					for (int i = 0; i < curr_count; i++) {
						float sum = 0;
						for (int j = 0; j < next_count; j++) {
							int w_idx = w_start + (i * next_count) + j;
							sum += Errors[next_start + j] * Weights[w_idx];
						}
						Errors[curr_start + i] = sum * sigmoid_derivative(Activations[curr_start + i]);
					}
				}

				// GÜNCELLEME
				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l];
					int out_start = NeuronOffsets[l + 1];
					int w_start = WeightOffsets[l];
					int in_count = Layers[l];
					int out_count = Layers[l + 1];

					for (int j = 0; j < out_count; j++) {
						float delta = Errors[out_start + j];
						int b_idx = out_start + j - inputDim;
						if (b_idx >= 0) Biases[b_idx] += learningRate * delta;

						for (int i = 0; i < in_count; i++) {
							int w_idx = w_start + (i * out_count) + j;
							Weights[w_idx] += learningRate * delta * Activations[in_start + i];
						}
					}
				}
			}

			total_mse = total_mse / (double)numSample;
			if (epoch < max_epoch) errorHistory[epoch] = (float)total_mse;
			epoch++;

		} while (epoch < max_epoch && total_mse > 0.001);

		errorHistoryCount = epoch;

		// GÖRSELLEŞTİRME
		Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		Graphics^ g = Graphics::FromImage(surface);
		g->Clear(Color::White);
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

		float cx = (float)(pictureBox1->Width / 2);
		float cy = (float)(pictureBox1->Height / 2);

		Pen^ axisPen = gcnew Pen(Color::Black, 2.0f);
		g->DrawLine(axisPen, cx, 0.0f, cx, (float)pictureBox1->Height);
		g->DrawLine(axisPen, 0.0f, cy, (float)pictureBox1->Width, cy);

		// NOKTALARI ÇİZ
		Pen^ bluePen = gcnew Pen(Color::Blue, 4.0f);
		for (int i = 0; i < numSample; i++) {
			int px = (int)(Samples[i * inputDim] * cx + cx);
			int py = (int)(cy - Samples[i * inputDim + 1] * cy);
			g->DrawLine(bluePen, px - 5, py, px + 5, py);
			g->DrawLine(bluePen, px, py - 5, px, py + 5);
		}

		Pen^ redPen = gcnew Pen(Color::Red, 3.0f);
		System::Collections::Generic::List<Point>^ curvePoints =
			gcnew System::Collections::Generic::List<Point>();

		for (int screenX = 0; screenX < pictureBox1->Width; screenX += 2) {
			float normX = (float)(screenX - cx) / cx;

			// FORWARD PASS (Test)
			int input_start = NeuronOffsets[0];
			Activations[input_start + 0] = normX;
			Activations[input_start + 1] = 1.0f;

			for (int l = 0; l < TotalLayers - 1; l++) {
				int in_start = NeuronOffsets[l];
				int out_start = NeuronOffsets[l + 1];
				int w_start = WeightOffsets[l];
				int in_count = Layers[l];
				int out_count = Layers[l + 1];

				bool isOutputLayer = (l == TotalLayers - 2);

				for (int j = 0; j < out_count; j++) {
					float net = 0;
					for (int i = 0; i < in_count; i++) {
						int w_idx = w_start + (i * out_count) + j;
						net += Activations[in_start + i] * Weights[w_idx];
					}
					int b_idx = out_start + j - inputDim;
					if (b_idx >= 0) net += Biases[b_idx];

					// Çıkış linear, gizli sigmoid
					if (isOutputLayer) {
						Activations[out_start + j] = net;
					}
					else {
						Activations[out_start + j] = sigmoid(net);
					}
				}
			}

			float predicted_Y = Activations[NeuronOffsets[TotalLayers - 1]];
			int screenY = (int)(cy - predicted_Y * cy);

			if (screenY >= 0 && screenY < pictureBox1->Height) {
				curvePoints->Add(Point(screenX, screenY));
			}
		}

		if (curvePoints->Count > 1) {
			array<Point>^ pointArray = curvePoints->ToArray();
			g->DrawLines(redPen, pointArray);
		}

		pictureBox1->Image = surface;
		DrawErrorChart();

		MessageBox::Show("Regresyon Tamamlandý!\nEpoch: " + epoch +
			"\nMSE: " + total_mse.ToString("F6"));
	}
	};
}