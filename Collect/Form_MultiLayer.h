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

	public ref class Form_MultiLayer : public System::Windows::Forms::Form
	{
	public:
		Form_MultiLayer(void)
		{
			InitializeComponent();
			srand((unsigned int)time(0)); // Rastgele sayý üretimi için
		}

	protected:
		~Form_MultiLayer()
		{
			if (components) delete components;

			// --- BELLEK TEMÝZLÝÐÝ (Manuel) ---
			// Form1.h'daki gibi çýkarken temizlik yapýyoruz
			if (Samples != nullptr) delete[] Samples;
			if (targets != nullptr) delete[] targets;

			// Multi-Layer Yapýlarý (Tek Pointer olduklarý için tek delete yeterli)
			if (Layers) delete[] Layers;
			if (NeuronOffsets) delete[] NeuronOffsets;
			if (WeightOffsets) delete[] WeightOffsets;

			if (Activations) delete[] Activations; // Tüm nöron çýktýlarý
			if (Errors) delete[] Errors;           // Tüm hatalar (Deltalar)
			if (Weights) delete[] Weights;         // Tüm aðýrlýklar
			if (Biases) delete[] Biases;           // Tüm biaslar
		}

	private:
		// --- ARAYÜZ ELEMANLARI (Form1.h Temelli) ---
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::GroupBox^ groupBox1; // Network Settings
		System::Windows::Forms::GroupBox^ groupBox2; // Data Collection
		System::Windows::Forms::Button^ Set_Net;

		System::Windows::Forms::Label^ label1; // Sýnýf Sayýsý
		System::Windows::Forms::ComboBox^ ClassCountBox;

		// -- Yeni Eklenenler (Multi-Layer Ýçin Þart) --
		System::Windows::Forms::Label^ lbl_Hidden;
		System::Windows::Forms::TextBox^ txt_HiddenLayer; // Gizli Katman Sayýsý
		System::Windows::Forms::Label^ lbl_Neurons;
		System::Windows::Forms::TextBox^ txt_NeuronCount; // Nöron Sayýsý
		System::Windows::Forms::Label^ lbl_LR;
		System::Windows::Forms::TextBox^ txt_LearnRate;   // Öðrenme Hýzý

		System::Windows::Forms::Label^ label2; // Örnek Etiketi
		System::Windows::Forms::ComboBox^ ClassNoBox;
		System::Windows::Forms::Label^ label3; // Sample Count

		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ processToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ trainingToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ testingToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ regressionToolStripMenuItem;

		System::Windows::Forms::OpenFileDialog^ openFileDialog1;
		System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
		System::ComponentModel::Container^ components;

		// --- DEÐÝÞKENLER ---
		int numSample = 0;
		int inputDim = 2;
		float* Samples = nullptr;
		float* targets = nullptr;

		// --- AÐ YAPISI (Tek Pointer - Flattened) ---
		// Çift pointer (float**) YASAK olduðu için her þeyi tek dizide tutuyoruz.

		int TotalLayers = 0;   // Toplam Katman Sayýsý
		int* Layers = nullptr; // Katman Mimarisi: {2, 5, 5, 3}

		// Adres Defteri (Hangi katman dizinin neresinde baþlýyor?)
		int* NeuronOffsets = nullptr;
		int* WeightOffsets = nullptr;

		// Veri Deposu (Tek Pointer)
		float* Activations = nullptr; // Tüm nöronlarýn çýktýlarý (A)
		float* Errors = nullptr;      // Tüm nöronlarýn hatalarý (D - Delta)
		float* Weights = nullptr;     // Tüm aðýrlýklar (W)
		float* Biases = nullptr;      // Tüm biaslar (B)

		float learningRate = 0.1f;    // Öðrenme Hýzý

		// --- MATEMATÝKSEL FONKSÝYONLAR ---
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
			this->lbl_Hidden = (gcnew System::Windows::Forms::Label());
			this->txt_HiddenLayer = (gcnew System::Windows::Forms::TextBox());
			this->lbl_Neurons = (gcnew System::Windows::Forms::Label());
			this->txt_NeuronCount = (gcnew System::Windows::Forms::TextBox());
			this->lbl_LR = (gcnew System::Windows::Forms::Label());
			this->txt_LearnRate = (gcnew System::Windows::Forms::TextBox());
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
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form_MultiLayer::pictureBox1_Paint);
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form_MultiLayer::pictureBox1_MouseClick);

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
			this->groupBox1->Location = System::Drawing::Point(830, 40);
			this->groupBox1->Size = System::Drawing::Size(220, 250);
			this->groupBox1->Text = L"Network Architecture";

			// Class Count
			this->label1->Location = System::Drawing::Point(10, 25); this->label1->Text = L"Sýnýf Sayýsý:"; this->label1->Size = System::Drawing::Size(80, 15);
			this->ClassCountBox->Location = System::Drawing::Point(100, 22); this->ClassCountBox->Size = System::Drawing::Size(50, 21);
			this->ClassCountBox->Items->AddRange(gcnew cli::array<System::Object^>(6) { L"2", L"3", L"4", L"5", L"6", L"7" }); this->ClassCountBox->Text = L"2";

			// Hidden Layers
			this->lbl_Hidden->Location = System::Drawing::Point(10, 55); this->lbl_Hidden->Text = L"Gizli Katman:"; this->lbl_Hidden->Size = System::Drawing::Size(80, 15);
			this->txt_HiddenLayer->Location = System::Drawing::Point(100, 52); this->txt_HiddenLayer->Size = System::Drawing::Size(50, 20); this->txt_HiddenLayer->Text = L"1";

			// Neurons
			this->lbl_Neurons->Location = System::Drawing::Point(10, 85); this->lbl_Neurons->Text = L"Nöron Sayýsý:"; this->lbl_Neurons->Size = System::Drawing::Size(80, 15);
			this->txt_NeuronCount->Location = System::Drawing::Point(100, 82); this->txt_NeuronCount->Size = System::Drawing::Size(50, 20); this->txt_NeuronCount->Text = L"5";

			// Learning Rate
			this->lbl_LR->Location = System::Drawing::Point(10, 115); this->lbl_LR->Text = L"Learn Rate:"; this->lbl_LR->Size = System::Drawing::Size(80, 15);
			this->txt_LearnRate->Location = System::Drawing::Point(100, 112); this->txt_LearnRate->Size = System::Drawing::Size(50, 20); this->txt_LearnRate->Text = L"0.1";

			// Set Net Button
			this->Set_Net->Location = System::Drawing::Point(10, 160); this->Set_Net->Size = System::Drawing::Size(180, 35); this->Set_Net->Text = L"Aðý Kur (Init)";
			this->Set_Net->Click += gcnew System::EventHandler(this, &Form_MultiLayer::Set_Net_Click);

			// groupBox2 (Data Collection)
			this->groupBox2->Controls->Add(this->label2); this->groupBox2->Controls->Add(this->ClassNoBox); this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Location = System::Drawing::Point(830, 300); this->groupBox2->Size = System::Drawing::Size(220, 100); this->groupBox2->Text = L"Data Collection";

			this->label2->Location = System::Drawing::Point(10, 30); this->label2->Text = L"Etiket:";
			this->ClassNoBox->Location = System::Drawing::Point(100, 27); this->ClassNoBox->Size = System::Drawing::Size(50, 21);
			this->ClassNoBox->Items->AddRange(gcnew cli::array<System::Object^>(9) { L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9" }); this->ClassNoBox->Text = L"1";
			this->label3->Location = System::Drawing::Point(10, 60); this->label3->Text = L"Örnek Sayýsý: 0"; this->label3->AutoSize = true;

			// Menu
			this->menuStrip1->Items->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>(1) { this->processToolStripMenuItem });
			this->processToolStripMenuItem->Text = L"Process";
			this->processToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>(3) { this->trainingToolStripMenuItem, this->testingToolStripMenuItem, this->regressionToolStripMenuItem });
			this->trainingToolStripMenuItem->Text = L"Training"; this->trainingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayer::trainingToolStripMenuItem_Click);
			this->testingToolStripMenuItem->Text = L"Testing"; this->testingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayer::testingToolStripMenuItem_Click);
			this->regressionToolStripMenuItem->Text = L"Regression"; this->regressionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayer::regressionToolStripMenuItem_Click);

			// Form
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1100, 700);
			this->Controls->Add(this->groupBox1); this->Controls->Add(this->groupBox2); this->Controls->Add(this->pictureBox1); this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form_MultiLayer";
			this->Text = L"Multi-Layer Network (Single Pointer)";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false); this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false); this->groupBox2->PerformLayout();
			this->menuStrip1->ResumeLayout(false); this->menuStrip1->PerformLayout();
			this->ResumeLayout(false); this->PerformLayout();
		}
#pragma endregion

		// --- VERÝ EKLEME (Normalization Var!) ---
		// Form1.h'dan farklý olarak burada veriyi küçültüyoruz (Normalize)
		// Çünkü Multi-Layer'ýn Sigmoid fonksiyonu büyük sayýlarda çalýþmaz.
	private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		float scaleX = pictureBox1->Width / 2.0f;
		float scaleY = pictureBox1->Height / 2.0f;

		float* x = new float[inputDim];
		// Normalizasyon: Veriyi -1 ile 1 arasýna sýkýþtýrýyoruz
		x[0] = (float)(e->X - scaleX) / scaleX;
		x[1] = (float)(scaleY - e->Y) / scaleY;

		int label = Convert::ToInt32(ClassNoBox->Text) - 1;

		// Form1.h Mantýðýyla Veri Ekleme (Manuel Resize)
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

		// Noktayý Çiz
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

		   // --- AÐI KUR (Init) - TEK POINTER MANTIÐI ---
		   // Kullanýcýdan bilgileri alýp bellekte yer açýyoruz.
	private: System::Void Set_Net_Click(System::Object^ sender, System::EventArgs^ e) {
		// Temizlik
		if (Activations) delete[] Activations; if (Errors) delete[] Errors;
		if (Weights) delete[] Weights; if (Biases) delete[] Biases;
		if (Layers) delete[] Layers;
		if (NeuronOffsets) delete[] NeuronOffsets; if (WeightOffsets) delete[] WeightOffsets;

		try {
			int numHidden = Convert::ToInt32(txt_HiddenLayer->Text);
			int numNeurons = Convert::ToInt32(txt_NeuronCount->Text);
			int numClasses = Convert::ToInt32(ClassCountBox->Text);
			learningRate = (float)Convert::ToDouble(txt_LearnRate->Text);

			// 1. Katman Mimarisi (Topology)
			TotalLayers = numHidden + 2; // Giriþ + Gizli + Çýkýþ
			Layers = new int[TotalLayers];
			Layers[0] = inputDim; // Giriþ (2)
			for (int i = 1; i <= numHidden; i++) Layers[i] = numNeurons; // Gizliler
			Layers[TotalLayers - 1] = numClasses; // Çýkýþ

			// 2. Hafýza Adreslerini Hesapla (Offsets)
			NeuronOffsets = new int[TotalLayers];
			WeightOffsets = new int[TotalLayers];

			int total_neurons = 0;
			int total_weights = 0;
			int total_biases = 0;

			for (int i = 0; i < TotalLayers; i++) {
				NeuronOffsets[i] = total_neurons;
				total_neurons += Layers[i]; // Toplam nöron sayýsýný büyüt

				if (i < TotalLayers - 1) {
					WeightOffsets[i] = total_weights;
					total_weights += Layers[i] * Layers[i + 1]; // W[i] boyutu
					total_biases += Layers[i + 1];
				}
			}

			// 3. Tek Parça Bellek Tahsisi (Allocation)
			Activations = new float[total_neurons];
			Errors = new float[total_neurons];
			Weights = new float[total_weights];
			Biases = new float[total_biases];

			// 4. Rastgele Deðer Ata (-0.5 ile 0.5 arasý)
			for (int i = 0; i < total_weights; i++) Weights[i] = ((float)rand() / RAND_MAX) - 0.5f;
			for (int i = 0; i < total_biases; i++) Biases[i] = ((float)rand() / RAND_MAX) - 0.5f;

			Set_Net->Text = "Að Hazýr (" + TotalLayers + " L)";
			MessageBox::Show("Að Baþarýyla Kuruldu!");
		}
		catch (...) { MessageBox::Show("Lütfen deðerleri kontrol edin."); }
	}

		   // --- EÐÝTÝM VE TEST FONKSÝYONLARI (Ýleride Doldurulacak) ---
	private: System::Void trainingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		// 1. GÜVENLÝK KONTROLÜ
		// Veri yoksa veya Að kurulmamýþsa iþlem yapma
		if (numSample == 0 || TotalLayers == 0) {
			MessageBox::Show("Lütfen önce veri ekleyin ve 'Aðý Kur' butonuna basýn.");
			return;
		}

		// Parametreleri Arayüzden Al
		try {
			learningRate = (float)Convert::ToDouble(txt_LearnRate->Text);
		}
		catch (...) { return; }

		int max_epoch = 5000;  // En fazla kaç tur dönecek?
		int epoch = 0;
		double total_mse = 0;  // Toplam Hata (Mean Squared Error)

		// --- EÐÝTÝM DÖNGÜSÜ (EPOCH) ---
		do {
			total_mse = 0; // Her turda hatayý sýfýrla

			// Her bir örnek için (Pattern Mode)
			for (int s = 0; s < numSample; s++) {

				// ====================================================
				// ADIM 1: ÝLERÝ YAYILIM (FORWARD PASS)
				// ====================================================

				// A) Giriþ Katmanýný Doldur
				// Ýlk katman (Layer 0), veri setindeki s. örneðin deðerleridir.
				int input_start_index = NeuronOffsets[0];
				for (int i = 0; i < inputDim; i++) {
					Activations[input_start_index + i] = Samples[s * inputDim + i];
				}

				// B) Katman Katman Ýlerle (Gizli -> Çýkýþ)
				for (int l = 0; l < TotalLayers - 1; l++) {
					int giris_baslangic = NeuronOffsets[l];      // Giren nöronlarýn adresi
					int cikis_baslangic = NeuronOffsets[l + 1];  // Çýkan nöronlarýn adresi
					int agirlik_baslangic = WeightOffsets[l];    // Aðýrlýklarýn adresi

					int giris_sayisi = Layers[l];     // Önceki katmandaki nöron sayýsý
					int cikis_sayisi = Layers[l + 1]; // Sonraki katmandaki nöron sayýsý

					for (int j = 0; j < cikis_sayisi; j++) {
						float net = 0;

						// Aðýrlýklý Toplam (Matris Çarpýmý: W * x)
						for (int i = 0; i < giris_sayisi; i++) {
							// Tek boyutlu dizide 2 boyutlu matris gibi geziyoruz:
							// Formül: Baþlangýç + (Satýr * ToplamSütun) + Sütun
							int w_index = agirlik_baslangic + (i * cikis_sayisi) + j;

							// net += x * w
							net += Activations[giris_baslangic + i] * Weights[w_index];
						}

						// Bias Ekle (Her nöronun bir bias'ý vardýr)
						// Biaslar da tek dizi, basitçe o katmanýn baþlangýcýna göre buluyoruz
						int b_index = cikis_baslangic + j - inputDim; // -inputDim çünkü giriþ katmanýnda bias yok
						net += Biases[b_index];

						// Aktivasyon Fonksiyonu (Sigmoid)
						// Notlardaki f(net)
						Activations[cikis_baslangic + j] = sigmoid(net);
					}
				}

				// ====================================================
				// ADIM 2: GERÝ YAYILIM (BACKWARD PASS) - Delta Hesabý
				// ====================================================

				// A) Çýkýþ Katmaný Deltasý (En Sondaki Hata)
				// Zurada Eq 5.14: Delta = (Target - Output) * f'(net)
				int son_katman_id = TotalLayers - 1;
				int son_katman_baslangic = NeuronOffsets[son_katman_id];
				int son_katman_sayisi = Layers[son_katman_id];
				int hedef_sinif = (int)targets[s]; // Örnek: 0 veya 1

				for (int k = 0; k < son_katman_sayisi; k++) {
					// Hedef: Eðer sýnýfým bu nörona aitse 1, deðilse 0 (One-Hot Encoding)
					float desired = (k == hedef_sinif) ? 1.0f : 0.0f;
					float output = Activations[son_katman_baslangic + k];

					float error = desired - output; // Hata = Beklenen - Gerçek
					total_mse += error * error;     // Hata karesini topla (MSE için)

					// Delta = Hata * Türev
					Errors[son_katman_baslangic + k] = error * sigmoid_derivative(output);
				}

				// B) Gizli Katman Deltalarý (Geriye Doðru)
				// Zurada Eq 5.15: Delta_j = f'(net) * Toplam(Delta_k * W_jk)
				for (int l = TotalLayers - 2; l > 0; l--) {
					int suanki_baslangic = NeuronOffsets[l];
					int sonraki_baslangic = NeuronOffsets[l + 1];
					int agirlik_baslangic = WeightOffsets[l];

					int suanki_sayi = Layers[l];
					int sonraki_sayi = Layers[l + 1];

					for (int i = 0; i < suanki_sayi; i++) {
						float hata_toplami = 0;

						// Bir sonraki katmandaki hatalarý, aðýrlýklarla çarparak geri çekiyoruz
						for (int j = 0; j < sonraki_sayi; j++) {
							int w_index = agirlik_baslangic + (i * sonraki_sayi) + j;
							hata_toplami += Errors[sonraki_baslangic + j] * Weights[w_index];
						}

						// Delta = Geri Gelen Hata * Türev
						Errors[suanki_baslangic + i] = hata_toplami * sigmoid_derivative(Activations[suanki_baslangic + i]);
					}
				}

				// ====================================================
				// ADIM 3: AÐIRLIK GÜNCELLEME (WEIGHT UPDATE)
				// ====================================================
				// Zurada Eq 5.22: W_yeni = W_eski + LearningRate * Delta * Input

				for (int l = 0; l < TotalLayers - 1; l++) {
					int giris_baslangic = NeuronOffsets[l];
					int cikis_baslangic = NeuronOffsets[l + 1];
					int agirlik_baslangic = WeightOffsets[l];

					int giris_sayisi = Layers[l];
					int cikis_sayisi = Layers[l + 1];

					for (int j = 0; j < cikis_sayisi; j++) {
						float delta = Errors[cikis_baslangic + j];

						// Bias Güncelle
						int b_index = cikis_baslangic + j - inputDim;
						Biases[b_index] += learningRate * delta;

						// Aðýrlýk Güncelle
						for (int i = 0; i < giris_sayisi; i++) {
							int w_index = agirlik_baslangic + (i * cikis_sayisi) + j;
							float giris_degeri = Activations[giris_baslangic + i];

							// Formül: W = W + n * d * x
							Weights[w_index] += learningRate * delta * giris_degeri;
						}
					}
				}

			} // Örnek Döngüsü Bitti (Sample Loop)

			epoch++;
		} while (epoch < max_epoch && total_mse > 0.001); // Hata çok küçülene kadar devam et

		// Sonucu Göster
		MessageBox::Show("Eðitim Tamamlandý!\nEpoch: " + epoch + "\nHata (MSE): " + total_mse);
	}
private: System::Void testingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	// Güvenlik: Að kurulu deðilse veya aðýrlýklar rastgele ise (hiç eðitilmemiþse) uyarma þansýmýz yok ama kontrol edelim
	if (TotalLayers == 0) return;

	// Çizim Yüzeyi (Hafýzada)
	Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);

	// Normalizasyon Deðerleri (Eðitimdekiyle AYNI olmak zorunda)
	float scaleX = pictureBox1->Width / 2.0f;
	float scaleY = pictureBox1->Height / 2.0f;

	// --- PÝKSEL TARAMA ---
	// Ekranýn her noktasýný geziyoruz (Hýz için 4'er atlýyoruz)
	for (int y = 0; y < pictureBox1->Height; y += 4) {
		for (int x = 0; x < pictureBox1->Width; x += 4) {

			// 1. GÝRÝÞÝ HAZIRLA (Koordinatý Normalize Et)
			// Formül: (Piksel - Merkez) / Yaricap -> Sonuç -1 ile 1 arasý olur
			float inputX = (float)(x - scaleX) / scaleX;
			float inputY = (float)(scaleY - y) / scaleY; // Y ekseni terstir

			// Giriþ Katmanýna Yaz (Activations dizisinin baþý)
			int input_start = NeuronOffsets[0];
			Activations[input_start + 0] = inputX;
			Activations[input_start + 1] = inputY;

			// 2. ÝLERÝ YAYILIM (FORWARD PASS - Sadece Hesaplama)
			// Training'deki Forward kýsmýnýn birebir kopyasý (Sadeleþtirilmiþ)
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

					// Bias Ekle
					int b_index = cikis_baslangic + j - inputDim;
					if (b_index >= 0) net += Biases[b_index];

					// Sigmoid
					Activations[cikis_baslangic + j] = sigmoid(net);
				}
			}

			// 3. KAZANANI BELÝRLE (Winner-Takes-All)
			// Çýkýþ katmanýndaki en büyük deðere sahip nöronu buluyoruz
			int son_katman = TotalLayers - 1;
			int son_baslangic = NeuronOffsets[son_katman];
			int son_sayi = Layers[son_katman];

			int kazanan_sinif = -1;
			float max_skor = -9999.0f;

			for (int k = 0; k < son_sayi; k++) {
				if (Activations[son_baslangic + k] > max_skor) {
					max_skor = Activations[son_baslangic + k];
					kazanan_sinif = k;
				}
			}

			// 4. RENGÝ SEÇ VE BOYA
			Color renk;
			if (kazanan_sinif == 0) renk = Color::FromArgb(50, 255, 0, 0);      // Kýrmýzý (Soluk)
			else if (kazanan_sinif == 1) renk = Color::FromArgb(50, 0, 0, 255); // Mavi (Soluk)
			else if (kazanan_sinif == 2) renk = Color::FromArgb(50, 0, 255, 0); // Yeþil (Soluk)
			else renk = Color::FromArgb(50, 255, 165, 0);                       // Turuncu

			// 4x4'lük kareyi boya (Tek piksel boyamak yavaþ olur)
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					if (x + i < pictureBox1->Width && y + j < pictureBox1->Height)
						surface->SetPixel(x + i, y + j, renk);
		}
	}

	// 5. RESMÝ GÖSTER
	pictureBox1->Image = surface;

	// 6. NOKTALARI TEKRAR ÜSTÜNE ÇÝZ (Kaybolmasýnlar)
	Graphics^ g = Graphics::FromImage(surface);
	for (int i = 0; i < numSample; i++) {
		Pen^ p;
		int t = (int)targets[i];
		if (t == 0) p = gcnew Pen(Color::Red, 5);
		else if (t == 1) p = gcnew Pen(Color::Blue, 5);
		else if (t == 2) p = gcnew Pen(Color::Green, 5);
		else p = gcnew Pen(Color::Orange, 5);

		// Normalizasyonu tersine çevirip piksele dönüþtür
		int px = (int)(Samples[i * inputDim] * scaleX + scaleX);
		int py = (int)(scaleY - Samples[i * inputDim + 1] * scaleY);

		g->DrawEllipse(p, px - 3, py - 3, 6, 6);
	}
}
	private: System::Void regressionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		// 1. GÜVENLÝK
		if (numSample < 2 || TotalLayers == 0) {
			MessageBox::Show("Lütfen önce Aðý Kurun ve en az 2 nokta ekleyin.");
			return;
		}

		// Regresyon için öðrenme hýzýný biraz artýralým (Daha hýzlý otursun)
		learningRate = 0.5f;

		int max_epoch = 10000; // Epoch sýnýrýný artýrdým
		int epoch = 0;
		double total_mse = 0;

		// --- EÐÝTÝM DÖNGÜSÜ ---
		do {
			total_mse = 0;
			for (int s = 0; s < numSample; s++) {

				// ===============================================
				// ADIM A: GÝRÝÞ VE HEDEF HAZIRLAMA (Normalizasyon)
				// ===============================================
				// Sigmoid fonksiyonu (0 ile 1) arasýnda deðer üretir.
				// Verilerimizi [0.2 ile 0.8] arasýna sýkýþtýrýrsak að MÜKEMMEL öðrenir.

				float rawX = Samples[s * inputDim];     // Kayýtlý X (-1..1 arasý)
				float rawY = Samples[s * inputDim + 1]; // Kayýtlý Y (-1..1 arasý)

				// -1..1 aralýðýný -> 0.2..0.8 aralýðýna çeviriyoruz (Güvenli Bölge)
				float inputX = 0.2f + ((rawX + 1.0f) / 2.0f) * 0.6f;
				float targetY = 0.2f + ((rawY + 1.0f) / 2.0f) * 0.6f;

				// Giriþ Katmanýna Yükle
				// [0] -> X koordinatý
				// [1] -> Bias etkisi için sabit 1.0 veriyoruz
				Activations[NeuronOffsets[0] + 0] = inputX;
				Activations[NeuronOffsets[0] + 1] = 1.0f;

				// ===============================================
				// ADIM B: ÝLERÝ YAYILIM (Forward Pass)
				// ===============================================
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

				// ===============================================
				// ADIM C: GERÝ YAYILIM (Hata Hesabý)
				// ===============================================
				int son_katman = TotalLayers - 1;
				int son_bas = NeuronOffsets[son_katman];

				// SADECE ÝLK ÇIKIÞ NÖRONUNU EÐÝTÝYORUZ (Y Tahmini)
				// Diðer nöronlar (varsa) umrumuzda deðil.
				float outputY = Activations[son_bas + 0];
				float error = targetY - outputY;
				total_mse += error * error;

				// Çýkýþ Deltasý (Sigmoid Türevi ile)
				Errors[son_bas + 0] = error * sigmoid_derivative(outputY);

				// Diðer çýkýþlarýn hatasýný sýfýrla (Onlarý eðitme)
				for (int k = 1; k < Layers[son_katman]; k++) Errors[son_bas + k] = 0.0f;

				// Gizli Katman Deltalarý (Ayný Kod)
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

				// ===============================================
				// ADIM D: GÜNCELLEME (Update)
				// ===============================================
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
			epoch++;

			// Hata çok düþerse erken bitir
		} while (epoch < max_epoch && total_mse > 0.0005);

		MessageBox::Show("Regresyon Tamam!\nEpoch: " + epoch + "\nMSE: " + total_mse);

		// --- 2. ÇÝZÝM ÝÞLEMÝ ---
		Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		Graphics^ g = Graphics::FromImage(surface);
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

		float cx = (float)pictureBox1->Width / 2.0f;
		float cy = (float)pictureBox1->Height / 2.0f;

		// Eksenleri Çiz
		Pen^ axisPen = gcnew Pen(Color::Black, 1.0f);
		g->DrawLine(axisPen, cx, 0.0f, cx, (float)pictureBox1->Height);
		g->DrawLine(axisPen, 0.0f, cy, (float)pictureBox1->Width, cy);

		// Noktalarý Çiz (Mavi)
		System::Drawing::SolidBrush^ blueBrush = gcnew System::Drawing::SolidBrush(Color::Blue);
		for (int i = 0; i < numSample; i++) {
			// Samples zaten -1..1 aralýðýnda
			float sx = Samples[i * inputDim];
			float sy = Samples[i * inputDim + 1];

			int px = (int)(sx * cx + cx);
			int py = (int)(cy - sy * cy);

			g->FillEllipse(blueBrush, px - 4, py - 4, 8, 8);
		}

		// Eðriyi Çiz (Kýrmýzý)
		System::Drawing::Point prevPoint = System::Drawing::Point(-1, -1);
		Pen^ redPen = gcnew Pen(Color::Red, 2.0f);

		// Soldan saða her piksel için tahmin yapýyoruz
		for (int x = 0; x < pictureBox1->Width; x += 2) {

			// X'i [0.2 - 0.8] aralýðýna çevir (Ayný eðitimdeki gibi)
			float normalizedX = (float)(x - cx) / cx; // -1..1
			float inputX = 0.2f + ((normalizedX + 1.0f) / 2.0f) * 0.6f;

			// Aða Sor
			Activations[NeuronOffsets[0] + 0] = inputX;
			Activations[NeuronOffsets[0] + 1] = 1.0f; // Sabit Bias Girdisi

			// Forward Pass (Sadece hesaplama)
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

			// Çýktýyý Al (0.2 - 0.8 arasý)
			float outputY = Activations[NeuronOffsets[TotalLayers - 1]];

			// 0.2-0.8 aralýðýndan -> Piksele Çevir
			// Ters Ýþlem: (y - 0.2) / 0.6 -> 0..1 -> *2 -1 -> -1..1
			float normalizedY = ((outputY - 0.2f) / 0.6f) * 2.0f - 1.0f;

			int py = (int)(cy - normalizedY * cy);

			// Çizgi Çek
			System::Drawing::Point currentPoint = System::Drawing::Point(x, py);
			if (prevPoint.X != -1) {
				if (py > 0 && py < pictureBox1->Height)
					g->DrawLine(redPen, prevPoint, currentPoint);
			}
			prevPoint = currentPoint;
		}

		pictureBox1->Image = surface;
	}
	};
}