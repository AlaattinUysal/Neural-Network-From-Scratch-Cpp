#pragma once
#include "Process.h"
#include "network.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class Form_MultiLayerMomentum : public System::Windows::Forms::Form
	{
	public:
		Form_MultiLayerMomentum(void)
		{
			InitializeComponent();
			srand((unsigned int)time(0));
		}

	protected:
		~Form_MultiLayerMomentum()
		{
			if (components) delete components;

			if (Samples != nullptr) delete[] Samples;
			if (targets != nullptr) delete[] targets;

			if (Layers) delete[] Layers;
			if (NeuronOffsets) delete[] NeuronOffsets;
			if (WeightOffsets) delete[] WeightOffsets;

			if (Activations) delete[] Activations;
			if (Errors) delete[] Errors;
			if (Weights) delete[] Weights;
			if (Biases) delete[] Biases;

			if (prevWeightChanges) delete[] prevWeightChanges;
			if (prevBiasChanges) delete[] prevBiasChanges;
		}

	private:
		// ARAYÜZ ELEMANLARI
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::GroupBox^ groupBox1;
		System::Windows::Forms::GroupBox^ groupBox2;
		System::Windows::Forms::Button^ Set_Net;

		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::ComboBox^ ClassCountBox;

		System::Windows::Forms::Label^ lbl_Hidden;
		System::Windows::Forms::TextBox^ txt_HiddenLayer;
		System::Windows::Forms::Label^ lbl_Neurons;
		System::Windows::Forms::TextBox^ txt_NeuronCount;
		System::Windows::Forms::Label^ lbl_LR;
		System::Windows::Forms::TextBox^ txt_LearnRate;

		System::Windows::Forms::Label^ lbl_Momentum;
		System::Windows::Forms::TextBox^ txt_Momentum;
		System::Windows::Forms::CheckBox^ chk_UseMomentum;

		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::ComboBox^ ClassNoBox;
		System::Windows::Forms::Label^ label3;

		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ processToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ trainingToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ testingToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ regressionToolStripMenuItem;

		System::Windows::Forms::OpenFileDialog^ openFileDialog1;
		System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
		System::ComponentModel::Container^ components;

		// DEĞİŞKENLER
		int numSample = 0;
		int inputDim = 2;
		float* Samples = nullptr;
		float* targets = nullptr;

		// AĞ YAPISI
		int TotalLayers = 0;
		int* Layers = nullptr;
		int* NeuronOffsets = nullptr;
		int* WeightOffsets = nullptr;

		float* Activations = nullptr;
		float* Errors = nullptr;
		float* Weights = nullptr;
		float* Biases = nullptr;

		// MOMENTUM DEĞİŞKENLERİ
		float* prevWeightChanges = nullptr;
		float* prevBiasChanges = nullptr;
		bool useMomentum = false;
		float momentumValue = 0.5f;

		float learningRate = 0.1f;

		// MATEMATİKSEL FONKSİYONLAR
		float sigmoid(float x) {
			if (x > 10) return 0.9999f;
			if (x < -10) return 0.0001f;
			return 1.0f / (1.0f + exp(-x));
		}

		float sigmoid_derivative(float x) {
			return x * (1.0f - x);
		}

		// Sayı çok büyük veya çok küçük mü kontrol et
		bool sayi_gecerli_mi(float sayi) {
			// Sonsuz veya tanımsız değilse geçerlidir
			if (sayi != sayi) return false; // NaN kontrolü (sayı kendine eşit değilse NaN'dır)
			if (sayi > 1e30f) return false;  // Çok büyük
			if (sayi < -1e30f) return false; // Çok küçük
			return true;
		}

		// Sayıyı makul sınırlar içinde tut
		float sinirla(float sayi, float max_deger) {
			if (sayi > max_deger) return max_deger;
			if (sayi < -max_deger) return -max_deger;
			return sayi;
		}

		// Momentum hesapla
		float momentum_hesapla(float onceki_degisim) {
			if (useMomentum) {
				return momentumValue * onceki_degisim;
			}
			return 0.0f;
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Set_Net = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ClassCountBox = (gcnew System::Windows::Forms::ComboBox());
			this->lbl_Hidden = (gcnew System::Windows::Forms::Label());
			this->txt_HiddenLayer = (gcnew System::Windows::Forms::TextBox());
			this->lbl_Neurons = (gcnew System::Windows::Forms::Label());
			this->txt_NeuronCount = (gcnew System::Windows::Forms::TextBox());
			this->lbl_LR = (gcnew System::Windows::Forms::Label());
			this->txt_LearnRate = (gcnew System::Windows::Forms::TextBox());
			this->lbl_Momentum = (gcnew System::Windows::Forms::Label());
			this->txt_Momentum = (gcnew System::Windows::Forms::TextBox());
			this->chk_UseMomentum = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->ClassNoBox = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->processToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->trainingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->testingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->regressionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();

			// pictureBox1
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Location = System::Drawing::Point(12, 40);
			this->pictureBox1->Size = System::Drawing::Size(800, 600);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form_MultiLayerMomentum::pictureBox1_Paint);
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form_MultiLayerMomentum::pictureBox1_MouseClick);

			// groupBox1 (Network Settings)
			this->groupBox1->Controls->Add(this->Set_Net);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->ClassCountBox);
			this->groupBox1->Controls->Add(this->lbl_Hidden);
			this->groupBox1->Controls->Add(this->txt_HiddenLayer);
			this->groupBox1->Controls->Add(this->lbl_Neurons);
			this->groupBox1->Controls->Add(this->txt_NeuronCount);
			this->groupBox1->Controls->Add(this->lbl_LR);
			this->groupBox1->Controls->Add(this->txt_LearnRate);
			this->groupBox1->Controls->Add(this->lbl_Momentum);
			this->groupBox1->Controls->Add(this->txt_Momentum);
			this->groupBox1->Controls->Add(this->chk_UseMomentum);
			this->groupBox1->Location = System::Drawing::Point(830, 40);
			this->groupBox1->Size = System::Drawing::Size(220, 300);
			this->groupBox1->Text = L"Network Architecture";

			// Class Count
			this->label1->Location = System::Drawing::Point(10, 25);
			this->label1->Text = L"Sınıf Sayısı:";
			this->label1->Size = System::Drawing::Size(80, 15);
			this->ClassCountBox->Location = System::Drawing::Point(100, 22);
			this->ClassCountBox->Size = System::Drawing::Size(50, 21);
			this->ClassCountBox->Items->AddRange(gcnew cli::array<System::Object^>(6) { L"2", L"3", L"4", L"5", L"6", L"7" });
			this->ClassCountBox->Text = L"2";

			// Hidden Layers
			this->lbl_Hidden->Location = System::Drawing::Point(10, 55);
			this->lbl_Hidden->Text = L"Gizli Katman:";
			this->lbl_Hidden->Size = System::Drawing::Size(80, 15);
			this->txt_HiddenLayer->Location = System::Drawing::Point(100, 52);
			this->txt_HiddenLayer->Size = System::Drawing::Size(50, 20);
			this->txt_HiddenLayer->Text = L"1";

			// Neurons
			this->lbl_Neurons->Location = System::Drawing::Point(10, 85);
			this->lbl_Neurons->Text = L"Nöron Sayısı:";
			this->lbl_Neurons->Size = System::Drawing::Size(80, 15);
			this->txt_NeuronCount->Location = System::Drawing::Point(100, 82);
			this->txt_NeuronCount->Size = System::Drawing::Size(50, 20);
			this->txt_NeuronCount->Text = L"5";

			// Learning Rate
			this->lbl_LR->Location = System::Drawing::Point(10, 115);
			this->lbl_LR->Text = L"Learn Rate:";
			this->lbl_LR->Size = System::Drawing::Size(80, 15);
			this->txt_LearnRate->Location = System::Drawing::Point(100, 112);
			this->txt_LearnRate->Size = System::Drawing::Size(50, 20);
			this->txt_LearnRate->Text = L"0.1";

			// Momentum Value
			this->lbl_Momentum->Location = System::Drawing::Point(10, 145);
			this->lbl_Momentum->Text = L"Momentum:";
			this->lbl_Momentum->Size = System::Drawing::Size(80, 15);
			this->txt_Momentum->Location = System::Drawing::Point(100, 142);
			this->txt_Momentum->Size = System::Drawing::Size(50, 20);
			this->txt_Momentum->Text = L"0.5";

			// Use Momentum Checkbox
			this->chk_UseMomentum->Location = System::Drawing::Point(10, 175);
			this->chk_UseMomentum->Size = System::Drawing::Size(150, 20);
			this->chk_UseMomentum->Text = L"Momentum Kullan";
			this->chk_UseMomentum->Checked = false;

			// Set Net Button
			this->Set_Net->Location = System::Drawing::Point(10, 210);
			this->Set_Net->Size = System::Drawing::Size(180, 35);
			this->Set_Net->Text = L"Ağı Kur (Init)";
			this->Set_Net->Click += gcnew System::EventHandler(this, &Form_MultiLayerMomentum::Set_Net_Click);

			// groupBox2 (Data Collection)
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->ClassNoBox);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Location = System::Drawing::Point(830, 350);
			this->groupBox2->Size = System::Drawing::Size(220, 100);
			this->groupBox2->Text = L"Data Collection";

			this->label2->Location = System::Drawing::Point(10, 30);
			this->label2->Text = L"Etiket:";
			this->ClassNoBox->Location = System::Drawing::Point(100, 27);
			this->ClassNoBox->Size = System::Drawing::Size(50, 21);
			this->ClassNoBox->Items->AddRange(gcnew cli::array<System::Object^>(9) { L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9" });
			this->ClassNoBox->Text = L"1";
			this->label3->Location = System::Drawing::Point(10, 60);
			this->label3->Text = L"Örnek Sayısı: 0";
			this->label3->AutoSize = true;

			// Menu
			this->menuStrip1->Items->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>(1) { this->processToolStripMenuItem });
			this->processToolStripMenuItem->Text = L"Process";
			this->processToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>(3) { this->trainingToolStripMenuItem, this->testingToolStripMenuItem, this->regressionToolStripMenuItem });
			this->trainingToolStripMenuItem->Text = L"Training";
			this->trainingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayerMomentum::trainingToolStripMenuItem_Click);
			this->testingToolStripMenuItem->Text = L"Testing";
			this->testingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayerMomentum::testingToolStripMenuItem_Click);
			this->regressionToolStripMenuItem->Text = L"Regression";
			this->regressionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayerMomentum::regressionToolStripMenuItem_Click);

			// Form
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1100, 700);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form_MultiLayer";
			this->Text = L"Multi-Layer Network with Momentum";
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

	private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		float scaleX = pictureBox1->Width / 2.0f;
		float scaleY = pictureBox1->Height / 2.0f;

		float* x = new float[inputDim];
		x[0] = (float)(e->X - scaleX) / scaleX;
		x[1] = (float)(scaleY - e->Y) / scaleY;

		int label = Convert::ToInt32(ClassNoBox->Text) - 1;

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

		Pen^ pen;
		if (label == 0) pen = gcnew Pen(Color::Red, 3.0f);
		else if (label == 1) pen = gcnew Pen(Color::Blue, 3.0f);
		else pen = gcnew Pen(Color::Green, 3.0f);

		pictureBox1->CreateGraphics()->DrawEllipse(pen, e->X - 3, e->Y - 3, 6, 6);
		label3->Text = "Sample: " + Convert::ToString(numSample);
		delete[] x;
	}

	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Pen^ pen = gcnew Pen(Color::Black, 1.0f);
		int cx = pictureBox1->Width / 2;
		int cy = pictureBox1->Height / 2;
		e->Graphics->DrawLine(pen, cx, 0, cx, pictureBox1->Height);
		e->Graphics->DrawLine(pen, 0, cy, pictureBox1->Width, cy);
	}

	private: System::Void Set_Net_Click(System::Object^ sender, System::EventArgs^ e) {
		// Eski belleği temizle
		if (Activations) delete[] Activations;
		if (Errors) delete[] Errors;
		if (Weights) delete[] Weights;
		if (Biases) delete[] Biases;
		if (Layers) delete[] Layers;
		if (NeuronOffsets) delete[] NeuronOffsets;
		if (WeightOffsets) delete[] WeightOffsets;
		if (prevWeightChanges) delete[] prevWeightChanges;
		if (prevBiasChanges) delete[] prevBiasChanges;

		try {
			int numHidden = Convert::ToInt32(txt_HiddenLayer->Text);
			int numNeurons = Convert::ToInt32(txt_NeuronCount->Text);
			int numClasses = Convert::ToInt32(ClassCountBox->Text);
			learningRate = (float)Convert::ToDouble(txt_LearnRate->Text);
			momentumValue = (float)Convert::ToDouble(txt_Momentum->Text);
			useMomentum = chk_UseMomentum->Checked;

			// Momentum değerini makul sınırlar içinde tut
			if (momentumValue < 0.0f) momentumValue = 0.0f;
			if (momentumValue > 0.95f) momentumValue = 0.95f;

			// Katman yapısını oluştur
			TotalLayers = numHidden + 2;
			Layers = new int[TotalLayers];
			Layers[0] = inputDim;
			for (int i = 1; i <= numHidden; i++) Layers[i] = numNeurons;
			Layers[TotalLayers - 1] = numClasses;

			// Her katmanın bellekteki yerini hesapla
			NeuronOffsets = new int[TotalLayers];
			WeightOffsets = new int[TotalLayers];

			int total_neurons = 0;
			int total_weights = 0;
			int total_biases = 0;

			for (int i = 0; i < TotalLayers; i++) {
				NeuronOffsets[i] = total_neurons;
				total_neurons += Layers[i];

				if (i < TotalLayers - 1) {
					WeightOffsets[i] = total_weights;
					total_weights += Layers[i] * Layers[i + 1];
					total_biases += Layers[i + 1];
				}
			}

			// Bellek ayır
			Activations = new float[total_neurons];
			Errors = new float[total_neurons];
			Weights = new float[total_weights];
			Biases = new float[total_biases];

			prevWeightChanges = new float[total_weights];
			prevBiasChanges = new float[total_biases];

			// Ağırlıkları küçük rastgele değerlerle başlat
			float weight_scale = sqrt(2.0f / (float)inputDim);
			for (int i = 0; i < total_weights; i++) {
				Weights[i] = (((float)rand() / RAND_MAX) - 0.5f) * weight_scale;
				prevWeightChanges[i] = 0.0f;
			}
			for (int i = 0; i < total_biases; i++) {
				Biases[i] = 0.0f;
				prevBiasChanges[i] = 0.0f;
			}

			// Tüm değerleri sıfırla
			for (int i = 0; i < total_neurons; i++) {
				Activations[i] = 0.0f;
				Errors[i] = 0.0f;
			}

			Set_Net->Text = "Ağ Hazır (" + TotalLayers + " L)";

			String^ durum = useMomentum ? "Aktif" : "Pasif";
			MessageBox::Show("Ağ Başarıyla Kuruldu!\nMomentum: " + durum);
		}
		catch (...) {
			MessageBox::Show("Lütfen değerleri kontrol edin.");
		}
	}

	private: System::Void trainingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numSample == 0 || TotalLayers == 0) {
			MessageBox::Show("Lütfen önce veri ekleyin ve 'Ağı Kur' butonuna basın.");
			return;
		}

		try {
			learningRate = (float)Convert::ToDouble(txt_LearnRate->Text);
			momentumValue = (float)Convert::ToDouble(txt_Momentum->Text);
			useMomentum = chk_UseMomentum->Checked;

			// Öğrenme hızını kontrol et
			if (learningRate <= 0.0f || learningRate > 1.0f) {
				MessageBox::Show("Learning Rate 0 ile 1 arasında olmalı!");
				return;
			}

			// Momentum değerini sınırla
			if (momentumValue < 0.0f) momentumValue = 0.0f;
			if (momentumValue > 0.95f) momentumValue = 0.95f;

			// Momentum kullanılacaksa geçmiş değişimleri sıfırla
			if (useMomentum) {
				int total_w = 0, total_b = 0;
				for (int i = 0; i < TotalLayers - 1; i++) {
					total_w += Layers[i] * Layers[i + 1];
					total_b += Layers[i + 1];
				}
				for (int i = 0; i < total_w; i++) prevWeightChanges[i] = 0.0f;
				for (int i = 0; i < total_b; i++) prevBiasChanges[i] = 0.0f;
			}
		}
		catch (...) { return; }

		int max_epoch = 5000;
		int epoch = 0;
		double total_mse = 0;

		do {
			total_mse = 0;

			for (int s = 0; s < numSample; s++) {

				// İLERİ YAYILIM - Giriş katmanını doldur
				int input_start_index = NeuronOffsets[0];
				for (int i = 0; i < inputDim; i++) {
					Activations[input_start_index + i] = Samples[s * inputDim + i];
				}

				// İLERİ YAYILIM - Katman katman ilerle
				for (int l = 0; l < TotalLayers - 1; l++) {
					int giris_baslangic = NeuronOffsets[l];
					int cikis_baslangic = NeuronOffsets[l + 1];
					int agirlik_baslangic = WeightOffsets[l];

					int giris_sayisi = Layers[l];
					int cikis_sayisi = Layers[l + 1];

					for (int j = 0; j < cikis_sayisi; j++) {
						float net = 0;

						for (int i = 0; i < giris_sayisi; i++) {
							int w_index = agirlik_baslangic + (i * cikis_sayisi) + j;
							net += Activations[giris_baslangic + i] * Weights[w_index];
						}

						int b_index = cikis_baslangic + j - inputDim;
						net += Biases[b_index];

						Activations[cikis_baslangic + j] = sigmoid(net);
					}
				}

				// GERİ YAYILIM - Çıkış katmanı hatasını hesapla
				int son_katman_id = TotalLayers - 1;
				int son_katman_baslangic = NeuronOffsets[son_katman_id];
				int son_katman_sayisi = Layers[son_katman_id];
				int hedef_sinif = (int)targets[s];

				for (int k = 0; k < son_katman_sayisi; k++) {
					float desired = (k == hedef_sinif) ? 1.0f : 0.0f;
					float output = Activations[son_katman_baslangic + k];

					float error = desired - output;
					total_mse += error * error;

					Errors[son_katman_baslangic + k] = error * sigmoid_derivative(output);
				}

				// GERİ YAYILIM - Gizli katman hatalarını hesapla
				for (int l = TotalLayers - 2; l > 0; l--) {
					int suanki_baslangic = NeuronOffsets[l];
					int sonraki_baslangic = NeuronOffsets[l + 1];
					int agirlik_baslangic = WeightOffsets[l];

					int suanki_sayi = Layers[l];
					int sonraki_sayi = Layers[l + 1];

					for (int i = 0; i < suanki_sayi; i++) {
						float hata_toplami = 0;

						for (int j = 0; j < sonraki_sayi; j++) {
							int w_index = agirlik_baslangic + (i * sonraki_sayi) + j;
							hata_toplami += Errors[sonraki_baslangic + j] * Weights[w_index];
						}

						Errors[suanki_baslangic + i] = hata_toplami * sigmoid_derivative(Activations[suanki_baslangic + i]);
					}
				}

				// AĞIRLIKLARI GÜNCELLE
				for (int l = 0; l < TotalLayers - 1; l++) {
					int giris_baslangic = NeuronOffsets[l];
					int cikis_baslangic = NeuronOffsets[l + 1];
					int agirlik_baslangic = WeightOffsets[l];

					int giris_sayisi = Layers[l];
					int cikis_sayisi = Layers[l + 1];

					for (int j = 0; j < cikis_sayisi; j++) {
						float delta = Errors[cikis_baslangic + j];

						// Sayı geçerli mi kontrol et
						if (sayi_gecerli_mi(delta) == false) delta = 0.0f;

						// Bias güncelle
						int b_index = cikis_baslangic + j - inputDim;

						float bias_gradient = learningRate * delta;
						float bias_momentum = momentum_hesapla(prevBiasChanges[b_index]);
						float bias_degisim = bias_gradient + bias_momentum;

						// Değişimi makul sınırlar içinde tut
						bias_degisim = sinirla(bias_degisim, 10.0f);

						Biases[b_index] += bias_degisim;
						prevBiasChanges[b_index] = bias_degisim;

						// Ağırlıkları güncelle
						for (int i = 0; i < giris_sayisi; i++) {
							int w_index = agirlik_baslangic + (i * cikis_sayisi) + j;
							float giris_degeri = Activations[giris_baslangic + i];

							// Sayı geçerli mi kontrol et
							if (sayi_gecerli_mi(giris_degeri) == false) giris_degeri = 0.0f;

							float weight_gradient = learningRate * delta * giris_degeri;
							float weight_momentum = momentum_hesapla(prevWeightChanges[w_index]);
							float weight_degisim = weight_gradient + weight_momentum;

							// Değişimi makul sınırlar içinde tut
							weight_degisim = sinirla(weight_degisim, 10.0f);

							Weights[w_index] += weight_degisim;
							prevWeightChanges[w_index] = weight_degisim;
						}
					}
				}
			}

			epoch++;
		} while (epoch < max_epoch && total_mse > 0.001);

		String^ durum = useMomentum ? "Aktif (" + momentumValue + ")" : "Pasif";
		MessageBox::Show("Eğitim Tamamlandı!\nEpoch: " + epoch + "\nHata (MSE): " + total_mse + "\nMomentum: " + durum);
	}

	private: System::Void testingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (TotalLayers == 0) return;

		Bitmap^ yuzey = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);

		float scaleX = pictureBox1->Width / 2.0f;
		float scaleY = pictureBox1->Height / 2.0f;

		// Ekranın her noktasını test et
		for (int y = 0; y < pictureBox1->Height; y += 4) {
			for (int x = 0; x < pictureBox1->Width; x += 4) {

				float inputX = (float)(x - scaleX) / scaleX;
				float inputY = (float)(scaleY - y) / scaleY;

				int input_start = NeuronOffsets[0];
				Activations[input_start + 0] = inputX;
				Activations[input_start + 1] = inputY;

				// İleri yayılım yap
				for (int l = 0; l < TotalLayers - 1; l++) {
					int giris_baslangic = NeuronOffsets[l];
					int cikis_baslangic = NeuronOffsets[l + 1];
					int agirlik_baslangic = WeightOffsets[l];

					int giris_sayisi = Layers[l];
					int cikis_sayisi = Layers[l + 1];

					for (int j = 0; j < cikis_sayisi; j++) {
						float net = 0;
						for (int i = 0; i < giris_sayisi; i++) {
							int w_index = agirlik_baslangic + (i * cikis_sayisi) + j;
							net += Activations[giris_baslangic + i] * Weights[w_index];
						}

						int b_index = cikis_baslangic + j - inputDim;
						if (b_index >= 0) net += Biases[b_index];

						Activations[cikis_baslangic + j] = sigmoid(net);
					}
				}

				// En yüksek değere sahip sınıfı bul
				int son_katman = TotalLayers - 1;
				int son_baslangic = NeuronOffsets[son_katman];
				int son_sayi = Layers[son_katman];

				int kazanan_sinif = 0;
				float en_yuksek_skor = Activations[son_baslangic + 0];

				for (int k = 1; k < son_sayi; k++) {
					if (Activations[son_baslangic + k] > en_yuksek_skor) {
						en_yuksek_skor = Activations[son_baslangic + k];
						kazanan_sinif = k;
					}
				}

				// Rengini belirle
				Color renk;
				if (kazanan_sinif == 0) renk = Color::FromArgb(50, 255, 0, 0);
				else if (kazanan_sinif == 1) renk = Color::FromArgb(50, 0, 0, 255);
				else if (kazanan_sinif == 2) renk = Color::FromArgb(50, 0, 255, 0);
				else renk = Color::FromArgb(50, 255, 165, 0);

				// 4x4 kare boya
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						if (x + i < pictureBox1->Width && y + j < pictureBox1->Height) {
							yuzey->SetPixel(x + i, y + j, renk);
						}
					}
				}
			}
		}

		pictureBox1->Image = yuzey;

		// Veri noktalarını tekrar çiz
		Graphics^ cizici = Graphics::FromImage(yuzey);
		for (int i = 0; i < numSample; i++) {
			Pen^ kalem;
			int sinif = (int)targets[i];

			if (sinif == 0) kalem = gcnew Pen(Color::Red, 5);
			else if (sinif == 1) kalem = gcnew Pen(Color::Blue, 5);
			else if (sinif == 2) kalem = gcnew Pen(Color::Green, 5);
			else kalem = gcnew Pen(Color::Orange, 5);

			int px = (int)(Samples[i * inputDim] * scaleX + scaleX);
			int py = (int)(scaleY - Samples[i * inputDim + 1] * scaleY);

			cizici->DrawEllipse(kalem, px - 3, py - 3, 6, 6);
		}
	}

	private: System::Void regressionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numSample < 2 || TotalLayers == 0) {
			MessageBox::Show("Lütfen önce Ağı Kurun ve en az 2 nokta ekleyin.");
			return;
		}

		learningRate = 0.3f;

		try {
			momentumValue = (float)Convert::ToDouble(txt_Momentum->Text);
			useMomentum = chk_UseMomentum->Checked;

			if (momentumValue < 0.0f) momentumValue = 0.0f;
			if (momentumValue > 0.95f) momentumValue = 0.95f;

			// Momentum kullanılacaksa geçmiş değişimleri sıfırla
			if (useMomentum) {
				int total_w = 0, total_b = 0;
				for (int i = 0; i < TotalLayers - 1; i++) {
					total_w += Layers[i] * Layers[i + 1];
					total_b += Layers[i + 1];
				}
				for (int i = 0; i < total_w; i++) prevWeightChanges[i] = 0.0f;
				for (int i = 0; i < total_b; i++) prevBiasChanges[i] = 0.0f;
			}
		}
		catch (...) {}

		int max_epoch = 10000;
		int epoch = 0;
		double total_mse = 0;

		do {
			total_mse = 0;
			for (int s = 0; s < numSample; s++) {

				float rawX = Samples[s * inputDim];
				float rawY = Samples[s * inputDim + 1];

				// Veriyi 0.2-0.8 aralığına normalize et
				float inputX = 0.2f + ((rawX + 1.0f) / 2.0f) * 0.6f;
				float targetY = 0.2f + ((rawY + 1.0f) / 2.0f) * 0.6f;

				Activations[NeuronOffsets[0] + 0] = inputX;
				Activations[NeuronOffsets[0] + 1] = 1.0f;

				// İleri yayılım
				for (int l = 0; l < TotalLayers - 1; l++) {
					int giris_bas = NeuronOffsets[l];
					int cikis_bas = NeuronOffsets[l + 1];
					int agirlik_bas = WeightOffsets[l];
					int giris_sayisi = Layers[l];
					int cikis_sayisi = Layers[l + 1];

					for (int j = 0; j < cikis_sayisi; j++) {
						float net = 0;
						for (int i = 0; i < giris_sayisi; i++) {
							int w_idx = agirlik_bas + (i * cikis_sayisi) + j;
							net += Activations[giris_bas + i] * Weights[w_idx];
						}

						int b_idx = cikis_bas + j - inputDim;
						if (b_idx >= 0) net += Biases[b_idx];

						Activations[cikis_bas + j] = sigmoid(net);
					}
				}

				// Çıkış hatasını hesapla
				int son_katman = TotalLayers - 1;
				int son_bas = NeuronOffsets[son_katman];

				float outputY = Activations[son_bas + 0];
				float error = targetY - outputY;
				total_mse += error * error;

				Errors[son_bas + 0] = error * sigmoid_derivative(outputY);

				// Diğer çıkışlar varsa sıfırla
				for (int k = 1; k < Layers[son_katman]; k++) {
					Errors[son_bas + k] = 0.0f;
				}

				// Geri yayılım
				for (int l = TotalLayers - 2; l > 0; l--) {
					int curr_start = NeuronOffsets[l];
					int next_start = NeuronOffsets[l + 1];
					int w_start = WeightOffsets[l];
					int curr_count = Layers[l];
					int next_count = Layers[l + 1];

					for (int i = 0; i < curr_count; i++) {
						float hata_toplami = 0;
						for (int j = 0; j < next_count; j++) {
							int w_idx = w_start + (i * next_count) + j;
							hata_toplami += Errors[next_start + j] * Weights[w_idx];
						}
						Errors[curr_start + i] = hata_toplami * sigmoid_derivative(Activations[curr_start + i]);
					}
				}

				// Ağırlıkları güncelle
				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l];
					int out_start = NeuronOffsets[l + 1];
					int w_start = WeightOffsets[l];
					int in_count = Layers[l];
					int out_count = Layers[l + 1];

					for (int j = 0; j < out_count; j++) {
						float delta = Errors[out_start + j];

						// Sayı geçerli mi kontrol et
						if (sayi_gecerli_mi(delta) == false) delta = 0.0f;

						int b_idx = out_start + j - inputDim;
						if (b_idx >= 0) {
							float bias_gradient = learningRate * delta;
							float bias_momentum = momentum_hesapla(prevBiasChanges[b_idx]);
							float bias_degisim = bias_gradient + bias_momentum;

							bias_degisim = sinirla(bias_degisim, 10.0f);

							Biases[b_idx] += bias_degisim;
							prevBiasChanges[b_idx] = bias_degisim;
						}

						for (int i = 0; i < in_count; i++) {
							int w_idx = w_start + (i * out_count) + j;
							float inputVal = Activations[in_start + i];

							if (sayi_gecerli_mi(inputVal) == false) inputVal = 0.0f;

							float weight_gradient = learningRate * delta * inputVal;
							float weight_momentum = momentum_hesapla(prevWeightChanges[w_idx]);
							float weight_degisim = weight_gradient + weight_momentum;

							weight_degisim = sinirla(weight_degisim, 10.0f);

							Weights[w_idx] += weight_degisim;
							prevWeightChanges[w_idx] = weight_degisim;
						}
					}
				}
			}
			epoch++;

		} while (epoch < max_epoch && total_mse > 0.0005);

		String^ durum = useMomentum ? "Aktif" : "Pasif";
		MessageBox::Show("Regresyon Tamam!\nEpoch: " + epoch + "\nMSE: " + total_mse + "\nMomentum: " + durum);

		// Sonucu çiz
		Bitmap^ yuzey = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		Graphics^ cizici = Graphics::FromImage(yuzey);
		cizici->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

		float cx = (float)pictureBox1->Width / 2.0f;
		float cy = (float)pictureBox1->Height / 2.0f;

		// Eksenleri çiz
		Pen^ siyah_kalem = gcnew Pen(Color::Black, 1.0f);
		cizici->DrawLine(siyah_kalem, cx, 0.0f, cx, (float)pictureBox1->Height);
		cizici->DrawLine(siyah_kalem, 0.0f, cy, (float)pictureBox1->Width, cy);

		// Veri noktalarını çiz
		System::Drawing::SolidBrush^ mavi_firca = gcnew System::Drawing::SolidBrush(Color::Blue);
		for (int i = 0; i < numSample; i++) {
			float sx = Samples[i * inputDim];
			float sy = Samples[i * inputDim + 1];

			int px = (int)(sx * cx + cx);
			int py = (int)(cy - sy * cy);

			cizici->FillEllipse(mavi_firca, px - 4, py - 4, 8, 8);
		}

		// Regresyon eğrisini çiz
		int onceki_x = -1;
		int onceki_y = -1;
		Pen^ redPen = gcnew Pen(Color::Red, 2.0f);

		for (int x = 0; x < pictureBox1->Width; x += 2) {

			float normalizedX = (float)(x - cx) / cx;
			float inputX = 0.2f + ((normalizedX + 1.0f) / 2.0f) * 0.6f;

			Activations[NeuronOffsets[0] + 0] = inputX;
			Activations[NeuronOffsets[0] + 1] = 1.0f;

			// İleri yayılım
			for (int l = 0; l < TotalLayers - 1; l++) {
				int giris_bas = NeuronOffsets[l];
				int cikis_bas = NeuronOffsets[l + 1];
				int agirlik_bas = WeightOffsets[l];
				int giris_say = Layers[l];
				int cikis_say = Layers[l + 1];

				for (int j = 0; j < cikis_say; j++) {
					float net = 0;
					for (int i = 0; i < giris_say; i++) {
						int w_idx = agirlik_bas + (i * cikis_say) + j;
						net += Activations[giris_bas + i] * Weights[w_idx];
					}
					int b_idx = cikis_bas + j - inputDim;
					if (b_idx >= 0) net += Biases[b_idx];
					Activations[cikis_bas + j] = sigmoid(net);
				}
			}

			float outputY = Activations[NeuronOffsets[TotalLayers - 1]];
			float normalizedY = ((outputY - 0.2f) / 0.6f) * 2.0f - 1.0f;
			int py = (int)(cy - normalizedY * cy);

			// Çizgiyi çiz
			if (onceki_x != -1) {
				if (py > 0 && py < pictureBox1->Height) {
					cizici->DrawLine(redPen, onceki_x, onceki_y, x, py);
				}
			}
			onceki_x = x;
			onceki_y = py;
		}

		pictureBox1->Image = yuzey;
	}
	};
}