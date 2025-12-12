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

			// Momentum Temizliği
			if (dWeights) delete[] dWeights;
			if (dBiases) delete[] dBiases;
		}

	private:
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

		// Momentum UI
		System::Windows::Forms::Label^ lbl_Momentum;
		System::Windows::Forms::TextBox^ txt_Momentum;

		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::ComboBox^ ClassNoBox;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ processToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ trainingToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ testingToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ regressionToolStripMenuItem;
		System::ComponentModel::Container^ components;

		// --- DEĞİŞKENLER ---
		int numSample = 0;
		int inputDim = 2;
		float* Samples = nullptr;
		float* targets = nullptr;

		// --- AĞ YAPISI ---
		int TotalLayers = 0;
		int* Layers = nullptr;
		int* NeuronOffsets = nullptr;
		int* WeightOffsets = nullptr;

		// Toplam ağırlık ve bias sayılarını saklayalım (Reset için)
		int total_weights_count = 0;
		int total_biases_count = 0;

		float* Activations = nullptr;
		float* Errors = nullptr;
		float* Weights = nullptr;
		float* Biases = nullptr;

		// Momentum Dizileri
		float* dWeights = nullptr;
		float* dBiases = nullptr;

		float learningRate = 0.1f;
		float momentum = 0.5f;

		// --- MATEMATİK ---
		float sigmoid(float x) {
			// NaN Koruması: Sayı çok büyükse exp patlar
			if (x > 20.0f) return 0.999999f;
			if (x < -20.0f) return 0.000001f;
			return 1.0f / (1.0f + exp(-x));
		}

		float sigmoid_derivative(float y) {
			return y * (1.0f - y);
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

			// groupBox1 (Settings)
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
			this->groupBox1->Location = System::Drawing::Point(830, 40);
			this->groupBox1->Size = System::Drawing::Size(220, 280);
			this->groupBox1->Text = L"Network Architecture";

			// Class Count
			this->label1->Location = System::Drawing::Point(10, 25); this->label1->Text = L"Sınıf Sayısı:"; this->label1->Size = System::Drawing::Size(80, 15);
			this->ClassCountBox->Location = System::Drawing::Point(100, 22); this->ClassCountBox->Size = System::Drawing::Size(50, 21);
			this->ClassCountBox->Items->AddRange(gcnew cli::array<System::Object^>(6) { L"2", L"3", L"4", L"5", L"6", L"7" }); this->ClassCountBox->Text = L"2";

			// Hidden Layers
			this->lbl_Hidden->Location = System::Drawing::Point(10, 55); this->lbl_Hidden->Text = L"Gizli Katman:"; this->lbl_Hidden->Size = System::Drawing::Size(80, 15);
			this->txt_HiddenLayer->Location = System::Drawing::Point(100, 52); this->txt_HiddenLayer->Size = System::Drawing::Size(50, 20); this->txt_HiddenLayer->Text = L"1";

			// Neurons
			this->lbl_Neurons->Location = System::Drawing::Point(10, 85); this->lbl_Neurons->Text = L"Nöron Sayısı:"; this->lbl_Neurons->Size = System::Drawing::Size(80, 15);
			this->txt_NeuronCount->Location = System::Drawing::Point(100, 82); this->txt_NeuronCount->Size = System::Drawing::Size(50, 20); this->txt_NeuronCount->Text = L"5";

			// Learning Rate
			this->lbl_LR->Location = System::Drawing::Point(10, 115); this->lbl_LR->Text = L"Learn Rate:"; this->lbl_LR->Size = System::Drawing::Size(80, 15);
			this->txt_LearnRate->Location = System::Drawing::Point(100, 112); this->txt_LearnRate->Size = System::Drawing::Size(50, 20); this->txt_LearnRate->Text = L"0.1";

			// Momentum
			this->lbl_Momentum->Location = System::Drawing::Point(10, 145); this->lbl_Momentum->Text = L"Momentum:"; this->lbl_Momentum->Size = System::Drawing::Size(80, 15);
			this->txt_Momentum->Location = System::Drawing::Point(100, 142); this->txt_Momentum->Size = System::Drawing::Size(50, 20); this->txt_Momentum->Text = L"0.5";

			// Set Net Button
			this->Set_Net->Location = System::Drawing::Point(10, 180); this->Set_Net->Size = System::Drawing::Size(180, 35); this->Set_Net->Text = L"Ağı Kur (Init)";
			this->Set_Net->Click += gcnew System::EventHandler(this, &Form_MultiLayerMomentum::Set_Net_Click);

			// groupBox2 (Data)
			this->groupBox2->Controls->Add(this->label2); this->groupBox2->Controls->Add(this->ClassNoBox); this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Location = System::Drawing::Point(830, 340);
			this->groupBox2->Size = System::Drawing::Size(220, 100); this->groupBox2->Text = L"Data Collection";

			this->label2->Location = System::Drawing::Point(10, 30); this->label2->Text = L"Etiket:";
			this->ClassNoBox->Location = System::Drawing::Point(100, 27); this->ClassNoBox->Size = System::Drawing::Size(50, 21);
			this->ClassNoBox->Items->AddRange(gcnew cli::array<System::Object^>(9) { L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9" }); this->ClassNoBox->Text = L"1";
			this->label3->Location = System::Drawing::Point(10, 60); this->label3->Text = L"Örnek Sayısı: 0"; this->label3->AutoSize = true;

			// Menu
			this->menuStrip1->Items->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>(1) { this->processToolStripMenuItem });
			this->processToolStripMenuItem->Text = L"Process";
			this->processToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>(3) { this->trainingToolStripMenuItem, this->testingToolStripMenuItem, this->regressionToolStripMenuItem });
			this->trainingToolStripMenuItem->Text = L"Training"; this->trainingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayerMomentum::trainingToolStripMenuItem_Click);
			this->testingToolStripMenuItem->Text = L"Testing"; this->testingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayerMomentum::testingToolStripMenuItem_Click);
			this->regressionToolStripMenuItem->Text = L"Regression"; this->regressionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MultiLayerMomentum::regressionToolStripMenuItem_Click);

			// Form
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1100, 700);
			this->Controls->Add(this->groupBox1); this->Controls->Add(this->groupBox2); this->Controls->Add(this->pictureBox1); this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form_MultiLayerMomentum";
			this->Text = L"Multi-Layer Network (Momentum Fixed)";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false); this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false); this->groupBox2->PerformLayout();
			this->menuStrip1->ResumeLayout(false); this->menuStrip1->PerformLayout();
			this->ResumeLayout(false); this->PerformLayout();
		}
#pragma endregion

		// --- VERİ EKLEME ---
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

		   // --- AĞI KUR (Init) ---
	private: System::Void Set_Net_Click(System::Object^ sender, System::EventArgs^ e) {
		if (Activations) delete[] Activations; if (Errors) delete[] Errors;
		if (Weights) delete[] Weights; if (Biases) delete[] Biases;
		if (Layers) delete[] Layers;
		if (NeuronOffsets) delete[] NeuronOffsets; if (WeightOffsets) delete[] WeightOffsets;

		// Momentum Temizliği
		if (dWeights) delete[] dWeights; if (dBiases) delete[] dBiases;

		try {
			int numHidden = Convert::ToInt32(txt_HiddenLayer->Text);
			int numNeurons = Convert::ToInt32(txt_NeuronCount->Text);
			int numClasses = Convert::ToInt32(ClassCountBox->Text);
			learningRate = (float)Convert::ToDouble(txt_LearnRate->Text);
			momentum = (float)Convert::ToDouble(txt_Momentum->Text);

			TotalLayers = numHidden + 2;
			Layers = new int[TotalLayers];
			Layers[0] = inputDim;
			for (int i = 1; i <= numHidden; i++) Layers[i] = numNeurons;
			Layers[TotalLayers - 1] = numClasses;

			NeuronOffsets = new int[TotalLayers];
			WeightOffsets = new int[TotalLayers];

			int total_neurons = 0;
			// Toplam ağırlık sayısını hesaplayalım (dWeights için lazım)
			total_weights_count = 0;
			total_biases_count = 0;

			for (int i = 0; i < TotalLayers; i++) {
				NeuronOffsets[i] = total_neurons;
				total_neurons += Layers[i];
				if (i < TotalLayers - 1) {
					WeightOffsets[i] = total_weights_count;
					total_weights_count += Layers[i] * Layers[i + 1];
					total_biases_count += Layers[i + 1];
				}
			}

			Activations = new float[total_neurons];
			Errors = new float[total_neurons];
			Weights = new float[total_weights_count];
			Biases = new float[total_biases_count];

			// Momentum Bellek Tahsisi
			dWeights = new float[total_weights_count];
			dBiases = new float[total_biases_count];

			// Değerleri Ata ve Momentumu Sıfırla (NaN Önlemi)
			for (int i = 0; i < total_weights_count; i++) {
				Weights[i] = ((float)rand() / RAND_MAX) - 0.5f;
				dWeights[i] = 0.0f; // KESİNLİKLE 0 OLMALI
			}
			for (int i = 0; i < total_biases_count; i++) {
				Biases[i] = ((float)rand() / RAND_MAX) - 0.5f;
				dBiases[i] = 0.0f; // KESİNLİKLE 0 OLMALI
			}

			Set_Net->Text = "Ağ Hazır (" + TotalLayers + " L)";
			MessageBox::Show("Ağ Kuruldu! Momentum Hazır.");
		}
		catch (...) { MessageBox::Show("Değerleri kontrol edin."); }
	}

		   // --- TRAINING (SINIFLANDIRMA) ---
	private: System::Void trainingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numSample == 0 || TotalLayers == 0) return;
		try { learningRate = (float)Convert::ToDouble(txt_LearnRate->Text); momentum = (float)Convert::ToDouble(txt_Momentum->Text); }
		catch (...) { return; }

		// Eğitim başlarken momentum hafızasını sıfırla (NaN riskini azaltır)
		if (dWeights) for (int i = 0; i < total_weights_count; i++) dWeights[i] = 0.0f;
		if (dBiases) for (int i = 0; i < total_biases_count; i++) dBiases[i] = 0.0f;

		int max_epoch = 5000; int epoch = 0; double total_mse = 0;

		do {
			total_mse = 0;
			for (int s = 0; s < numSample; s++) {
				int input_start_index = NeuronOffsets[0];
				for (int i = 0; i < inputDim; i++) Activations[input_start_index + i] = Samples[s * inputDim + i];

				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l]; int out_start = NeuronOffsets[l + 1]; int w_start = WeightOffsets[l];
					int giris_sayisi = Layers[l]; int cikis_sayisi = Layers[l + 1];
					for (int j = 0; j < cikis_sayisi; j++) {
						float net = 0;
						for (int i = 0; i < giris_sayisi; i++) {
							int w_index = w_start + (i * cikis_sayisi) + j;
							net += Activations[in_start + i] * Weights[w_index];
						}
						int b_index = out_start + j - inputDim;
						net += Biases[b_index];
						Activations[out_start + j] = sigmoid(net);
					}
				}

				int son_katman = TotalLayers - 1; int son_start = NeuronOffsets[son_katman]; int hedef_sinif = (int)targets[s];
				for (int k = 0; k < Layers[son_katman]; k++) {
					float desired = (k == hedef_sinif) ? 1.0f : 0.0f;
					float output = Activations[son_start + k];
					float error = desired - output;
					total_mse += error * error;
					Errors[son_start + k] = error * sigmoid_derivative(output);
				}

				for (int l = TotalLayers - 2; l > 0; l--) {
					int curr_start = NeuronOffsets[l]; int next_start = NeuronOffsets[l + 1]; int w_start = WeightOffsets[l];
					int curr_cnt = Layers[l]; int next_cnt = Layers[l + 1];
					for (int i = 0; i < curr_cnt; i++) {
						float sum = 0;
						for (int j = 0; j < next_cnt; j++) {
							int w_index = w_start + (i * next_cnt) + j;
							sum += Errors[next_start + j] * Weights[w_index];
						}
						Errors[curr_start + i] = sum * sigmoid_derivative(Activations[curr_start + i]);
					}
				}

				// UPDATE (MOMENTUM)
				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l]; int out_start = NeuronOffsets[l + 1]; int w_start = WeightOffsets[l];
					int in_cnt = Layers[l]; int out_cnt = Layers[l + 1];
					for (int j = 0; j < out_cnt; j++) {
						float delta = Errors[out_start + j];
						int b_idx = out_start + j - inputDim;

						float bias_change = (learningRate * delta) + (momentum * dBiases[b_idx]);
						Biases[b_idx] += bias_change;
						dBiases[b_idx] = bias_change;

						for (int i = 0; i < in_cnt; i++) {
							int w_idx = w_start + (i * out_cnt) + j;
							float weight_change = (learningRate * delta * Activations[in_start + i]) + (momentum * dWeights[w_idx]);
							Weights[w_idx] += weight_change;
							dWeights[w_idx] = weight_change;
						}
					}
				}
			}
			epoch++;
		} while (epoch < max_epoch && total_mse > 0.001);
		MessageBox::Show("Training Bitti!\nEpoch: " + epoch + "\nMSE: " + total_mse);
	}

		   // --- 2. TESTING (BOYAMA) ---
	private: System::Void testingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (TotalLayers == 0) return;
		Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		float scaleX = pictureBox1->Width / 2.0f; float scaleY = pictureBox1->Height / 2.0f;

		for (int y = 0; y < pictureBox1->Height; y += 4) {
			for (int x = 0; x < pictureBox1->Width; x += 4) {
				float inputX = (float)(x - scaleX) / scaleX; float inputY = (float)(scaleY - y) / scaleY;
				Activations[NeuronOffsets[0]] = inputX; Activations[NeuronOffsets[0] + 1] = inputY;

				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l]; int out_start = NeuronOffsets[l + 1]; int w_start = WeightOffsets[l];
					int in_cnt = Layers[l]; int out_cnt = Layers[l + 1];
					for (int j = 0; j < out_cnt; j++) {
						float net = 0;
						for (int i = 0; i < in_cnt; i++) {
							int w_index = w_start + (i * out_cnt) + j;
							net += Activations[in_start + i] * Weights[w_index];
						}
						net += Biases[out_start + j - inputDim];
						Activations[out_start + j] = sigmoid(net);
					}
				}
				int son = TotalLayers - 1; float maxVal = -9999.0f; int winner = -1;
				for (int k = 0; k < Layers[son]; k++) {
					if (Activations[NeuronOffsets[son] + k] > maxVal) { maxVal = Activations[NeuronOffsets[son] + k]; winner = k; }
				}
				Color c; if (winner == 0) c = Color::FromArgb(50, 255, 0, 0); else if (winner == 1) c = Color::FromArgb(50, 0, 0, 255); else c = Color::FromArgb(50, 0, 255, 0);
				for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (x + i < pictureBox1->Width && y + j < pictureBox1->Height) surface->SetPixel(x + i, y + j, c);
			}
		}
		pictureBox1->Image = surface;
		Graphics^ g = Graphics::FromImage(surface);
		for (int i = 0; i < numSample; i++) {
			Pen^ p; int t = (int)targets[i];
			if (t == 0) p = gcnew Pen(Color::Red, 5); else if (t == 1) p = gcnew Pen(Color::Blue, 5); else p = gcnew Pen(Color::Green, 5);
			int px = (int)(Samples[i * inputDim] * scaleX + scaleX); int py = (int)(scaleY - Samples[i * inputDim + 1] * scaleY);
			g->DrawEllipse(p, px - 3, py - 3, 6, 6);
		}
	}

		   // --- REGRESYON (MOMENTUM ENTEGRE EDİLDİ) ---
	private: System::Void regressionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numSample < 2 || TotalLayers == 0) return;
		try { learningRate = (float)Convert::ToDouble(txt_LearnRate->Text); momentum = (float)Convert::ToDouble(txt_Momentum->Text); }
		catch (...) { return; }

		// Eğitim başlarken momentum hafızasını sıfırla (NaN ÇÖZÜMÜ)
		if (dWeights) for (int i = 0; i < total_weights_count; i++) dWeights[i] = 0.0f;
		if (dBiases) for (int i = 0; i < total_biases_count; i++) dBiases[i] = 0.0f;

		int max_epoch = 10000; int epoch = 0; double total_mse = 0;

		do {
			total_mse = 0;
			for (int s = 0; s < numSample; s++) {
				float inputX = Samples[s * inputDim]; float targetY = Samples[s * inputDim + 1];
				// Normalizasyon 0.2 - 0.8
				float normX = 0.2f + ((inputX + 1.0f) / 2.0f) * 0.6f;
				float normY = 0.2f + ((targetY + 1.0f) / 2.0f) * 0.6f;

				Activations[NeuronOffsets[0]] = normX; Activations[NeuronOffsets[0] + 1] = 1.0f;

				// Forward
				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l]; int out_start = NeuronOffsets[l + 1]; int w_start = WeightOffsets[l];
					int in_cnt = Layers[l]; int out_cnt = Layers[l + 1];
					for (int j = 0; j < out_cnt; j++) {
						float net = 0;
						for (int i = 0; i < in_cnt; i++) {
							int w_index = w_start + (i * out_cnt) + j;
							net += Activations[in_start + i] * Weights[w_index];
						}
						net += Biases[out_start + j - inputDim];
						Activations[out_start + j] = sigmoid(net);
					}
				}

				// Backward
				int son = TotalLayers - 1; float outputY = Activations[NeuronOffsets[son]];
				float error = normY - outputY;
				total_mse += error * error;

				// NaN Koruması
				if (std::isnan(total_mse)) { total_mse = 9999.0; break; }

				Errors[NeuronOffsets[son]] = error * sigmoid_derivative(outputY);
				for (int k = 1; k < Layers[son]; k++) Errors[NeuronOffsets[son] + k] = 0.0f;

				for (int l = TotalLayers - 2; l > 0; l--) {
					int curr_start = NeuronOffsets[l]; int next_start = NeuronOffsets[l + 1]; int w_start = WeightOffsets[l];
					int curr_cnt = Layers[l]; int next_cnt = Layers[l + 1];
					for (int i = 0; i < curr_cnt; i++) {
						float sum = 0;
						for (int j = 0; j < next_cnt; j++) {
							int w_index = w_start + (i * next_cnt) + j;
							sum += Errors[next_start + j] * Weights[w_index];
						}
						Errors[curr_start + i] = sum * sigmoid_derivative(Activations[curr_start + i]);
					}
				}

				// Update (MOMENTUM)
				for (int l = 0; l < TotalLayers - 1; l++) {
					int in_start = NeuronOffsets[l]; int out_start = NeuronOffsets[l + 1]; int w_start = WeightOffsets[l];
					int in_cnt = Layers[l]; int out_cnt = Layers[l + 1];
					for (int j = 0; j < out_cnt; j++) {
						float delta = Errors[out_start + j];
						int b_idx = out_start + j - inputDim;

						float bias_change = (learningRate * delta) + (momentum * dBiases[b_idx]);
						Biases[b_idx] += bias_change;
						dBiases[b_idx] = bias_change;

						for (int i = 0; i < in_cnt; i++) {
							int w_idx = w_start + (i * out_cnt) + j;
							float weight_change = (learningRate * delta * Activations[in_start + i]) + (momentum * dWeights[w_idx]);
							Weights[w_idx] += weight_change;
							dWeights[w_idx] = weight_change;
						}
					}
				}
			}
			epoch++;
		} while (epoch < max_epoch && total_mse > 0.0005);
		MessageBox::Show("Regresyon Bitti!\nEpoch: " + epoch + "\nMSE: " + total_mse);

		// Çizim
		Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		Graphics^ g = Graphics::FromImage(surface);
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
		float cx = pictureBox1->Width / 2.0f; float cy = pictureBox1->Height / 2.0f;
		// Hata düzeltildi: scaleX ve scaleY burada tanımlandı
		float scaleX = pictureBox1->Width / 2.0f;
		float scaleY = pictureBox1->Height / 2.0f;

		g->DrawLine(Pens::Black, cx, 0.0f, cx, (float)pictureBox1->Height); g->DrawLine(Pens::Black, 0.0f, cy, (float)pictureBox1->Width, cy);

		for (int i = 0; i < numSample; i++) {
			int px = (int)(Samples[i * inputDim] * scaleX + scaleX); int py = (int)(scaleY - Samples[i * inputDim + 1] * scaleY);
			g->FillEllipse(Brushes::Blue, px - 3, py - 3, 6, 6);
		}

		Point prev(-1, -1); Pen^ redPen = gcnew Pen(Color::Red, 2.0f);
		for (int x = 0; x < pictureBox1->Width; x += 2) {
			float normX = (float)(x - cx) / cx;
			float inX = 0.2f + ((normX + 1.0f) / 2.0f) * 0.6f;
			Activations[NeuronOffsets[0]] = inX; Activations[NeuronOffsets[0] + 1] = 1.0f;

			for (int l = 0; l < TotalLayers - 1; l++) {
				int in_start = NeuronOffsets[l]; int out_start = NeuronOffsets[l + 1]; int w_start = WeightOffsets[l];
				int in_cnt = Layers[l]; int out_cnt = Layers[l + 1];
				for (int j = 0; j < out_cnt; j++) {
					float net = 0;
					for (int i = 0; i < in_cnt; i++) {
						int w_index = w_start + (i * out_cnt) + j;
						net += Activations[in_start + i] * Weights[w_index];
					}
					net += Biases[out_start + j - inputDim];
					Activations[out_start + j] = sigmoid(net);
				}
			}
			float outY = Activations[NeuronOffsets[TotalLayers - 1]];
			float normY = ((outY - 0.2f) / 0.6f) * 2.0f - 1.0f;
			int py = (int)(cy - normY * cy);
			Point curr(x, py);
			if (prev.X != -1 && py > -100 && py < pictureBox1->Height + 100) g->DrawLine(redPen, prev, curr);
			prev = curr;
		}
		pictureBox1->Image = surface;
	}
	};
}