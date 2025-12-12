#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <ctime>
#include <algorithm>

// String dönüþümü için gerekli
using namespace System::Runtime::InteropServices;

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class Form_MNIST : public System::Windows::Forms::Form
	{
	public:
		Form_MNIST(void)
		{
			InitializeComponent();
			srand((unsigned int)time(0));
		}

	protected:
		~Form_MNIST()
		{
			if (components) delete components;

			// --- BELLEK TEMÝZLÝÐÝ ---
			if (TrainImages) delete[] TrainImages;
			if (TrainLabels) delete[] TrainLabels;

			if (Layers) delete[] Layers;
			if (NeuronOffsets) delete[] NeuronOffsets;
			if (WeightOffsets) delete[] WeightOffsets;
			if (Activations) delete[] Activations;
			if (Errors) delete[] Errors;
			if (Weights) delete[] Weights;
			if (Biases) delete[] Biases;
			if (ErrorHistory) delete[] ErrorHistory;
		}

	private:
		System::Windows::Forms::Button^ btn_LoadMNIST;
		System::Windows::Forms::Button^ btn_Train;
		System::Windows::Forms::Button^ btn_Test;
		System::Windows::Forms::PictureBox^ pBox_Graph;
		System::Windows::Forms::Label^ lbl_Status;
		System::Windows::Forms::TextBox^ txt_Hidden;
		System::Windows::Forms::Label^ lbl_Hidden;
		System::Windows::Forms::Label^ lbl_Epoch;
		System::Windows::Forms::TextBox^ txt_Epoch;
		System::Windows::Forms::RichTextBox^ rtb_Logs;

		System::ComponentModel::Container^ components;

		// --- DEÐÝÞKENLER ---
		int input_dim = 784; // 28x28 piksel
		int output_dim = 10; // 0-9 Rakamlar
		int numTrain = 0;    // Yüklenen resim sayýsý

		// Tek Pointerlý Düz Diziler
		float* TrainImages = nullptr;
		int* TrainLabels = nullptr;

		// --- AÐ YAPISI ---
		int TotalLayers = 0;
		int* Layers = nullptr;
		int* NeuronOffsets = nullptr;
		int* WeightOffsets = nullptr;

		float* Activations = nullptr;
		float* Errors = nullptr;
		float* Weights = nullptr;
		float* Biases = nullptr;

		// Grafik Verisi
		float* ErrorHistory = nullptr;
		float learningRate = 0.1f;

		// --- YARDIMCI: String Dönüþtürücü (Hatayý Çözen Kýsým) ---
		void MarshalString(String^ s, std::string& os) {
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		// --- YARDIMCI: Endian Çevirici ---
		int ReverseInt(int i) {
			unsigned char c1, c2, c3, c4;
			c1 = i & 255; c2 = (i >> 8) & 255; c3 = (i >> 16) & 255; c4 = (i >> 24) & 255;
			return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
		}

		// --- MATEMATÝK ---
		float sigmoid(float x) { return 1.0f / (1.0f + exp(-x)); }
		float sigmoid_derivative(float y) { return y * (1.0f - y); }

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->btn_LoadMNIST = (gcnew System::Windows::Forms::Button());
			this->btn_Train = (gcnew System::Windows::Forms::Button());
			this->btn_Test = (gcnew System::Windows::Forms::Button());
			this->pBox_Graph = (gcnew System::Windows::Forms::PictureBox());
			this->lbl_Status = (gcnew System::Windows::Forms::Label());
			this->txt_Hidden = (gcnew System::Windows::Forms::TextBox());
			this->lbl_Hidden = (gcnew System::Windows::Forms::Label());
			this->lbl_Epoch = (gcnew System::Windows::Forms::Label());
			this->txt_Epoch = (gcnew System::Windows::Forms::TextBox());
			this->rtb_Logs = (gcnew System::Windows::Forms::RichTextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBox_Graph))->BeginInit();
			this->SuspendLayout();

			// btn_LoadMNIST
			this->btn_LoadMNIST->Location = System::Drawing::Point(12, 12);
			this->btn_LoadMNIST->Size = System::Drawing::Size(150, 40);
			this->btn_LoadMNIST->Text = L"1. MNIST Yükle";
			this->btn_LoadMNIST->Click += gcnew System::EventHandler(this, &Form_MNIST::btn_LoadMNIST_Click);

			// Ayarlar
			this->lbl_Hidden->Location = System::Drawing::Point(12, 65);
			this->lbl_Hidden->Text = L"Gizli Nöron:";
			this->lbl_Hidden->Size = System::Drawing::Size(70, 20);
			this->txt_Hidden->Location = System::Drawing::Point(90, 62);
			this->txt_Hidden->Text = L"64"; this->txt_Hidden->Size = System::Drawing::Size(70, 20);

			this->lbl_Epoch->Location = System::Drawing::Point(12, 95);
			this->lbl_Epoch->Text = L"Epoch:";
			this->lbl_Epoch->Size = System::Drawing::Size(70, 20);
			this->txt_Epoch->Location = System::Drawing::Point(90, 92);
			this->txt_Epoch->Text = L"50"; this->txt_Epoch->Size = System::Drawing::Size(70, 20);

			// Butonlar
			this->btn_Train->Location = System::Drawing::Point(12, 130);
			this->btn_Train->Size = System::Drawing::Size(150, 40);
			this->btn_Train->Text = L"2. Eðit (Train)";
			this->btn_Train->Click += gcnew System::EventHandler(this, &Form_MNIST::btn_Train_Click);

			this->btn_Test->Location = System::Drawing::Point(12, 190);
			this->btn_Test->Size = System::Drawing::Size(150, 40);
			this->btn_Test->Text = L"3. Test Et";
			this->btn_Test->Click += gcnew System::EventHandler(this, &Form_MNIST::btn_Test_Click);

			// Grafik
			this->pBox_Graph->BackColor = System::Drawing::Color::White;
			this->pBox_Graph->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pBox_Graph->Location = System::Drawing::Point(180, 12);
			this->pBox_Graph->Size = System::Drawing::Size(600, 300);

			// Status & Log
			this->lbl_Status->AutoSize = true;
			this->lbl_Status->ForeColor = System::Drawing::Color::Blue;
			this->lbl_Status->Location = System::Drawing::Point(12, 250);
			this->lbl_Status->Text = L"Durum: Bekliyor...";

			this->rtb_Logs->Location = System::Drawing::Point(180, 330);
			this->rtb_Logs->Size = System::Drawing::Size(600, 150);
			this->rtb_Logs->Text = L"";

			this->Controls->Add(this->lbl_Epoch); this->Controls->Add(this->txt_Epoch);
			this->Controls->Add(this->lbl_Hidden); this->Controls->Add(this->txt_Hidden);
			this->Controls->Add(this->rtb_Logs); this->Controls->Add(this->lbl_Status);
			this->Controls->Add(this->pBox_Graph); this->Controls->Add(this->btn_Test);
			this->Controls->Add(this->btn_Train); this->Controls->Add(this->btn_LoadMNIST);
			this->Name = L"Form_MNIST";
			this->Text = L"MNIST Rakam Tanýma";
			this->Size = System::Drawing::Size(820, 550);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBox_Graph))->EndInit();
			this->ResumeLayout(false); this->PerformLayout();
		}
#pragma endregion

		// --- 1. MNIST YÜKLE (ÝNSANCIL VE HATASIZ) ---
	private: System::Void btn_LoadMNIST_Click(System::Object^ sender, System::EventArgs^ e) {
		// 1. Resim Dosyasýný Seç
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Title = "Lütfen 'train-images' dosyasýný seçin";
		if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

		// Basit String Dönüþümü
		std::string path_images;
		MarshalString(ofd->FileName, path_images);

		// 2. Etiket Dosyasýný Seç
		ofd->Title = "Lütfen 'train-labels' dosyasýný seçin";
		if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

		std::string path_labels;
		MarshalString(ofd->FileName, path_labels);

		// Dosyalarý Aç
		std::ifstream file_images(path_images, std::ios::binary);
		std::ifstream file_labels(path_labels, std::ios::binary);

		if (file_images.is_open() && file_labels.is_open()) {
			int magic, num_img, rows, cols, magic2, num_lbl;

			// Header Oku (Gereksiz ama okuyup geçmemiz lazým)
			file_images.read((char*)&magic, 4); file_images.read((char*)&num_img, 4);
			file_images.read((char*)&rows, 4);  file_images.read((char*)&cols, 4);
			file_labels.read((char*)&magic2, 4); file_labels.read((char*)&num_lbl, 4);

			// --- DENGELÝ VERÝ SETÝ ---
			int target_per_digit = 100; // Her rakamdan 100 tane
			int total_target = 1000;    // Toplam 1000 tane

			int counts[10] = { 0 };
			int collected = 0;

			// Bellek Aç
			if (TrainImages) delete[] TrainImages;
			if (TrainLabels) delete[] TrainLabels;
			TrainImages = new float[total_target * 784];
			TrainLabels = new int[total_target];
			numTrain = total_target;

			rtb_Logs->AppendText("Veri taranýyor...\n");
			Application::DoEvents();

			// --- TARAMA DÖNGÜSÜ ---
			while (collected < total_target && !file_labels.eof() && !file_images.eof()) {
				unsigned char label_byte;
				file_labels.read((char*)&label_byte, 1);
				int label = (int)label_byte;

				if (counts[label] < target_per_digit) {
					// Bu rakamdan henüz 100 tane almamýþýz -> ALALIM
					TrainLabels[collected] = label;

					// 784 pikseli oku
					for (int p = 0; p < 784; p++) {
						unsigned char pixel;
						file_images.read((char*)&pixel, 1);
						// Normalize et (0-1 arasýna çek)
						TrainImages[collected * 784 + p] = (float)pixel / 255.0f;
					}
					counts[label]++;
					collected++;
				}
				else {
					// Bu rakamdan zaten 100 tane var -> ATLA
					file_images.ignore(784);
				}
			}

			lbl_Status->Text = "Hazýr: " + Convert::ToString(collected) + " örnek.";
			rtb_Logs->AppendText("Tamamlandý. Dengeli set (1000 adet) yüklendi.\n");
			for (int i = 0; i < 10; i++) rtb_Logs->AppendText("Rakam " + i + ": " + counts[i] + " adet\n");
		}
		else {
			MessageBox::Show("Dosyalar açýlamadý! Ýsimlerinde Türkçe karakter olmasýn.");
		}
	}

		   // --- 2. EÐÝTÝM (TRAINING) ---
	private: System::Void btn_Train_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numTrain == 0) { MessageBox::Show("Önce veri yükle!"); return; }

		int n_hidden = Convert::ToInt32(txt_Hidden->Text);
		int n_epochs = Convert::ToInt32(txt_Epoch->Text);

		// Bellek Temizle
		if (Weights) delete[] Weights; if (Biases) delete[] Biases;

		// Yapý: 784 -> Gizli -> 10
		TotalLayers = 3;
		Layers = new int[3];
		Layers[0] = 784; Layers[1] = n_hidden; Layers[2] = 10;

		NeuronOffsets = new int[3]; WeightOffsets = new int[3];
		int total_n = 0, total_w = 0, total_b = 0;
		for (int i = 0; i < 3; i++) {
			NeuronOffsets[i] = total_n; total_n += Layers[i];
			if (i < 2) { WeightOffsets[i] = total_w; total_w += Layers[i] * Layers[i + 1]; total_b += Layers[i + 1]; }
		}

		Activations = new float[total_n]; Errors = new float[total_n];
		Weights = new float[total_w]; Biases = new float[total_b];
		ErrorHistory = new float[n_epochs];

		// Rastgele Baþlat
		for (int i = 0; i < total_w; i++) Weights[i] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
		for (int i = 0; i < total_b; i++) Biases[i] = 0.0f;

		rtb_Logs->AppendText("Eðitim baþladý...\n");

		// --- EPOCH DÖNGÜSÜ ---
		for (int epoch = 0; epoch < n_epochs; epoch++) {
			double epoch_error = 0;

			for (int s = 0; s < numTrain; s++) {
				// Girdi
				int input_idx = NeuronOffsets[0];
				for (int k = 0; k < 784; k++) Activations[input_idx + k] = TrainImages[s * 784 + k];

				// Forward
				for (int l = 0; l < 2; l++) {
					int in_s = NeuronOffsets[l]; int out_s = NeuronOffsets[l + 1]; int w_s = WeightOffsets[l];
					int n_in = Layers[l]; int n_out = Layers[l + 1];
					for (int j = 0; j < n_out; j++) {
						float net = 0;
						for (int i = 0; i < n_in; i++) net += Activations[in_s + i] * Weights[w_s + i * n_out + j];
						net += Biases[out_s + j - 784];
						Activations[out_s + j] = sigmoid(net);
					}
				}

				// Hata (One-Hot)
				int out_s = NeuronOffsets[2];
				int target = TrainLabels[s];
				for (int k = 0; k < 10; k++) {
					float desired = (k == target) ? 1.0f : 0.0f;
					float out = Activations[out_s + k];
					float err = desired - out;
					epoch_error += err * err;
					Errors[out_s + k] = err * sigmoid_derivative(out);
				}

				// Backward
				for (int l = 1; l > 0; l--) {
					int curr = NeuronOffsets[l]; int next = NeuronOffsets[l + 1]; int w_s = WeightOffsets[l];
					int n_curr = Layers[l]; int n_next = Layers[l + 1];
					for (int i = 0; i < n_curr; i++) {
						float sum = 0;
						for (int j = 0; j < n_next; j++) sum += Errors[next + j] * Weights[w_s + i * n_next + j];
						Errors[curr + i] = sum * sigmoid_derivative(Activations[curr + i]);
					}
				}

				// Update
				for (int l = 0; l < 2; l++) {
					int in_s = NeuronOffsets[l]; int out_s = NeuronOffsets[l + 1]; int w_s = WeightOffsets[l];
					int n_in = Layers[l]; int n_out = Layers[l + 1];
					for (int j = 0; j < n_out; j++) {
						float delta = Errors[out_s + j];
						Biases[out_s + j - 784] += learningRate * delta;
						for (int i = 0; i < n_in; i++) {
							Weights[w_s + i * n_out + j] += learningRate * delta * Activations[in_s + i];
						}
					}
				}
			}
			ErrorHistory[epoch] = (float)epoch_error / numTrain;
			if (epoch % 10 == 0) {
				rtb_Logs->AppendText("Epoch " + epoch + " Hata: " + ErrorHistory[epoch] + "\n");
				rtb_Logs->ScrollToCaret();
				Application::DoEvents();
			}
		}
		DrawGraph(n_epochs);
		MessageBox::Show("Eðitim Bitti!");
	}

		   // --- 3. TEST ---
	private: System::Void btn_Test_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numTrain == 0) return;
		int dogru = 0;
		// Basitlik için eðitim setini test ediyoruz (Gerçekte test seti yüklenmeli)
		for (int s = 0; s < numTrain; s++) {
			int input_idx = NeuronOffsets[0];
			for (int k = 0; k < 784; k++) Activations[input_idx + k] = TrainImages[s * 784 + k];

			// Forward
			for (int l = 0; l < 2; l++) {
				int in_s = NeuronOffsets[l]; int out_s = NeuronOffsets[l + 1]; int w_s = WeightOffsets[l];
				int n_in = Layers[l]; int n_out = Layers[l + 1];
				for (int j = 0; j < n_out; j++) {
					float net = 0;
					for (int i = 0; i < n_in; i++) net += Activations[in_s + i] * Weights[w_s + i * n_out + j];
					net += Biases[out_s + j - 784];
					Activations[out_s + j] = sigmoid(net);
				}
			}
			// Max Bul
			int out_s = NeuronOffsets[2];
			int predicted = 0; float maxVal = -1;
			for (int k = 0; k < 10; k++) {
				if (Activations[out_s + k] > maxVal) { maxVal = Activations[out_s + k]; predicted = k; }
			}
			if (predicted == TrainLabels[s]) dogru++;
		}

		float accuracy = (float)dogru / numTrain * 100.0f;
		lbl_Status->Text = "Baþarý: %" + accuracy;
		MessageBox::Show("Baþarý Oraný: %" + accuracy);
	}

		   // --- GRAFÝK ---
		   void DrawGraph(int epochs) {
			   Bitmap^ bmp = gcnew Bitmap(pBox_Graph->Width, pBox_Graph->Height);
			   Graphics^ g = Graphics::FromImage(bmp);
			   g->Clear(Color::White);
			   if (epochs > 1) {
				   float maxErr = 0;
				   for (int i = 0; i < epochs; i++) if (ErrorHistory[i] > maxErr) maxErr = ErrorHistory[i];
				   Pen^ p = gcnew Pen(Color::Red, 2);
				   float stepX = (float)pBox_Graph->Width / epochs;
				   for (int i = 0; i < epochs - 1; i++) {
					   float y1 = pBox_Graph->Height - (ErrorHistory[i] / maxErr * (pBox_Graph->Height - 20));
					   float y2 = pBox_Graph->Height - (ErrorHistory[i + 1] / maxErr * (pBox_Graph->Height - 20));
					   g->DrawLine(p, i * stepX, y1, (i + 1) * stepX, y2);
				   }
			   }
			   pBox_Graph->Image = bmp;
		   }
	};
}