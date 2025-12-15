#pragma once
#include <cstdio>  // Eski usül C dosya okuma (fopen, fread)
#include <cmath>
#include <ctime>
#include <algorithm>
#include <string>

// String dönüþümü için mecburi (Windows ile C arasý köprü)
using namespace System::Runtime::InteropServices;

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
			// Çöpçü (Bellek Temizliði)
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
		// --- ARAYÜZ ELEMANLARI (STANDART YAPI) ---
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::GroupBox^ groupBox1;
		System::Windows::Forms::Button^ btn_InitNet;

		System::Windows::Forms::Label^ lbl_Hidden;
		System::Windows::Forms::TextBox^ txt_Hidden;
		System::Windows::Forms::Label^ lbl_Epoch;
		System::Windows::Forms::TextBox^ txt_Epoch;
		System::Windows::Forms::Label^ lbl_LR;
		System::Windows::Forms::TextBox^ txt_LearnRate;

		System::Windows::Forms::GroupBox^ groupBox2;
		System::Windows::Forms::Button^ btn_LoadMNIST; // Dosya yükleme butonu
		System::Windows::Forms::Label^ lbl_DataStatus;

		System::Windows::Forms::TextBox^ textBox1; // Log Ekraný

		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ processToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ trainingToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ testingToolStripMenuItem;

		System::ComponentModel::Container^ components;

		// --- TEMEL DEÐÝÞKENLER ---
		int numTrain = 0;
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

		float* ErrorHistory = nullptr;
		float learningRate = 0.1f;

		// --- MATEMATÝK ---
		float sigmoid(float x) { return 1.0f / (1.0f + exp(-x)); }
		float sigmoid_derivative(float y) { return y * (1.0f - y); }

		// --- YARDIMCI: DOSYA YOLU DÖNÜÞTÜRÜCÜ ---
		void DosyaYolunuAl(String^ s, char* cikis) {
			IntPtr p = Marshal::StringToHGlobalAnsi(s);
			const char* chars = static_cast<const char*>(p.ToPointer());
			strcpy(cikis, chars);
			Marshal::FreeHGlobal(p);
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btn_InitNet = (gcnew System::Windows::Forms::Button());
			this->lbl_Hidden = (gcnew System::Windows::Forms::Label());
			this->txt_Hidden = (gcnew System::Windows::Forms::TextBox());
			this->lbl_Epoch = (gcnew System::Windows::Forms::Label());
			this->txt_Epoch = (gcnew System::Windows::Forms::TextBox());
			this->lbl_LR = (gcnew System::Windows::Forms::Label());
			this->txt_LearnRate = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->btn_LoadMNIST = (gcnew System::Windows::Forms::Button());
			this->lbl_DataStatus = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->processToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->trainingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->testingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();

			// pictureBox1 (Grafik Ekraný)
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(17, 43);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1069, 711);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;

			// groupBox1 (Network Architecture)
			this->groupBox1->Controls->Add(this->btn_InitNet);
			this->groupBox1->Controls->Add(this->lbl_Hidden);
			this->groupBox1->Controls->Add(this->txt_Hidden);
			this->groupBox1->Controls->Add(this->lbl_Epoch);
			this->groupBox1->Controls->Add(this->txt_Epoch);
			this->groupBox1->Controls->Add(this->lbl_LR);
			this->groupBox1->Controls->Add(this->txt_LearnRate);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(162)));
			this->groupBox1->Location = System::Drawing::Point(1159, 62);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(267, 180);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Network Architecture";

			// Hidden Nodes
			this->lbl_Hidden->AutoSize = true;
			this->lbl_Hidden->Location = System::Drawing::Point(144, 30);
			this->lbl_Hidden->Text = L"Gizli Nöron";
			this->txt_Hidden->Location = System::Drawing::Point(13, 27);
			this->txt_Hidden->Size = System::Drawing::Size(108, 20);
			this->txt_Hidden->Text = L"64";

			// Epoch
			this->lbl_Epoch->AutoSize = true;
			this->lbl_Epoch->Location = System::Drawing::Point(144, 60);
			this->lbl_Epoch->Text = L"Epoch";
			this->txt_Epoch->Location = System::Drawing::Point(13, 57);
			this->txt_Epoch->Size = System::Drawing::Size(108, 20);
			this->txt_Epoch->Text = L"50";

			// Learn Rate
			this->lbl_LR->AutoSize = true;
			this->lbl_LR->Location = System::Drawing::Point(144, 90);
			this->lbl_LR->Text = L"Learn Rate";
			this->txt_LearnRate->Location = System::Drawing::Point(13, 87);
			this->txt_LearnRate->Size = System::Drawing::Size(108, 20);
			this->txt_LearnRate->Text = L"0.1";

			// Init Button (Göstermelik - Asýl iþi Load yapýyor ama yapýyý koruduk)
			this->btn_InitNet->Location = System::Drawing::Point(13, 125);
			this->btn_InitNet->Size = System::Drawing::Size(175, 41);
			this->btn_InitNet->Text = L"Network Ready";
			this->btn_InitNet->UseVisualStyleBackColor = true;

			// groupBox2 (Data Loading)
			this->groupBox2->Controls->Add(this->btn_LoadMNIST);
			this->groupBox2->Controls->Add(this->lbl_DataStatus);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(162)));
			this->groupBox2->Location = System::Drawing::Point(1172, 260);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(253, 100);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Dataset Loading";

			// Load Button
			this->btn_LoadMNIST->Location = System::Drawing::Point(10, 25);
			this->btn_LoadMNIST->Size = System::Drawing::Size(230, 40);
			this->btn_LoadMNIST->Text = L"Load MNIST Files";
			this->btn_LoadMNIST->UseVisualStyleBackColor = true;
			this->btn_LoadMNIST->Click += gcnew System::EventHandler(this, &Form_MNIST::btn_LoadMNIST_Click);

			// Data Status Label
			this->lbl_DataStatus->AutoSize = true;
			this->lbl_DataStatus->Location = System::Drawing::Point(10, 75);
			this->lbl_DataStatus->Text = L"Durum: Bekliyor...";

			// textBox1 (Logs)
			this->textBox1->Location = System::Drawing::Point(1159, 380);
			this->textBox1->Multiline = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(328, 367);
			this->textBox1->TabIndex = 5;

			// Menu
			this->menuStrip1->Items->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>(1) { this->processToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1550, 24);
			this->menuStrip1->Text = L"menuStrip1";

			this->processToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>(2) {
				this->trainingToolStripMenuItem, this->testingToolStripMenuItem
			});
			this->processToolStripMenuItem->Text = L"Process";

			this->trainingToolStripMenuItem->Text = L"Training";
			this->trainingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MNIST::trainingToolStripMenuItem_Click);

			this->testingToolStripMenuItem->Text = L"Testing";
			this->testingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_MNIST::testingToolStripMenuItem_Click);

			// Form
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1550, 800);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form_MNIST";
			this->Text = L"Form_MNIST";
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

		// --- 1. VERÝ YÜKLEME (ORÝJÝNAL KOD KORUNDU) ---
	private: System::Void btn_LoadMNIST_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Title = "Lütfen 'train-images' dosyasýný seçin";
		if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
		char yol_resim[256]; DosyaYolunuAl(ofd->FileName, yol_resim);

		ofd->Title = "Lütfen 'train-labels' dosyasýný seçin";
		if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
		char yol_etiket[256]; DosyaYolunuAl(ofd->FileName, yol_etiket);

		FILE* f_resim = fopen(yol_resim, "rb");
		FILE* f_etiket = fopen(yol_etiket, "rb");

		if (f_resim && f_etiket) {
			int temp;
			fread(&temp, 4, 1, f_resim); fread(&temp, 4, 1, f_resim);
			fread(&temp, 4, 1, f_resim); fread(&temp, 4, 1, f_resim);
			fread(&temp, 4, 1, f_etiket); fread(&temp, 4, 1, f_etiket);

			int hedef_rakam_basina = 100; // Dengeli olmasý için sýnýr koyduk
			int toplam_hedef = 1000;
			int sayaclar[10] = { 0 };
			int toplanan = 0;

			if (TrainImages) delete[] TrainImages;
			if (TrainLabels) delete[] TrainLabels;
			TrainImages = new float[toplam_hedef * 784];
			TrainLabels = new int[toplam_hedef];
			numTrain = toplam_hedef;

			textBox1->AppendText("Veri yükleniyor... Lütfen bekleyin.\r\n");
			Application::DoEvents();

			unsigned char tampon_etiket;
			unsigned char tampon_resim[784];

			while (toplanan < toplam_hedef) {
				if (fread(&tampon_etiket, 1, 1, f_etiket) != 1) break;
				int etiket = (int)tampon_etiket;

				if (sayaclar[etiket] < hedef_rakam_basina) {
					TrainLabels[toplanan] = etiket;
					fread(tampon_resim, 1, 784, f_resim);
					for (int p = 0; p < 784; p++) {
						TrainImages[toplanan * 784 + p] = (float)tampon_resim[p] / 255.0f;
					}
					sayaclar[etiket]++;
					toplanan++;
				}
				else {
					fseek(f_resim, 784, SEEK_CUR);
				}
			}

			fclose(f_resim);
			fclose(f_etiket);

			lbl_DataStatus->Text = "Yüklendi: " + Convert::ToString(toplanan) + " örnek.";
			textBox1->AppendText("MNIST Dosyalarý Baþarýyla Yüklendi!\r\n");
			MessageBox::Show("Dosyalar Yüklendi!");
		}
		else {
			MessageBox::Show("Dosya hatasý!");
		}
	}

		   // --- 2. EÐÝTÝM (PROCESS -> TRAINING) ---
	private: System::Void trainingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numTrain == 0) { MessageBox::Show("Önce Dosyalarý Yükleyin!"); return; }

		int n_hidden = Convert::ToInt32(txt_Hidden->Text);
		int n_epochs = Convert::ToInt32(txt_Epoch->Text);
		learningRate = (float)Convert::ToDouble(txt_LearnRate->Text);

		// Bellek Yönetimi
		if (Weights) delete[] Weights; if (Biases) delete[] Biases;
		if (Layers) delete[] Layers;
		if (NeuronOffsets) delete[] NeuronOffsets; if (WeightOffsets) delete[] WeightOffsets;
		if (Activations) delete[] Activations; if (Errors) delete[] Errors;
		if (ErrorHistory) delete[] ErrorHistory;

		// 784 -> Hidden -> 10 (Sabit MNIST yapýsý)
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

		// Baþlatma
		for (int i = 0; i < total_w; i++) Weights[i] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
		for (int i = 0; i < total_b; i++) Biases[i] = 0.0f;

		textBox1->AppendText("Eðitim Baþladý...\r\n");

		// --- EÐÝTÝM DÖNGÜSÜ ---
		for (int epoch = 0; epoch < n_epochs; epoch++) {
			double epoch_error = 0;

			for (int s = 0; s < numTrain; s++) {
				// Input
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

				// Error
				int out_s = NeuronOffsets[2];
				int target = TrainLabels[s];
				for (int k = 0; k < 10; k++) {
					float desired = (k == target) ? 1.0f : 0.0f;
					float out = Activations[out_s + k];
					float err = desired - out;
					epoch_error += err * err;
					Errors[out_s + k] = err * sigmoid_derivative(out);
				}

				// Backprop
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
				textBox1->AppendText("Epoch " + epoch + " Error: " + ErrorHistory[epoch] + "\r\n");
				Application::DoEvents();
			}
		}

		DrawGraph(n_epochs);
		textBox1->AppendText("Eðitim Tamamlandý.\r\n");
		MessageBox::Show("Eðitim Tamamlandý!");
	}

		   // --- 3. TEST (PROCESS -> TESTING) ---
	private: System::Void testingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numTrain == 0) return;
		int dogru = 0;

		for (int s = 0; s < numTrain; s++) {
			int input_idx = NeuronOffsets[0];
			for (int k = 0; k < 784; k++) Activations[input_idx + k] = TrainImages[s * 784 + k];

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

			int out_s = NeuronOffsets[2];
			int predicted = 0; float maxVal = -1;
			for (int k = 0; k < 10; k++) {
				if (Activations[out_s + k] > maxVal) { maxVal = Activations[out_s + k]; predicted = k; }
			}
			if (predicted == TrainLabels[s]) dogru++;
		}

		float accuracy = (float)dogru / numTrain * 100.0f;
		textBox1->AppendText("Test Sonucu: %" + accuracy + " Baþarý.\r\n");
		MessageBox::Show("Test Baþarýsý: %" + accuracy);
	}

		   // --- GRAFÝK ÇÝZÝMÝ (PictureBox1 Üzerine) ---
		   void DrawGraph(int epochs) {
			   if (epochs < 2) return;
			   Bitmap^ bmp = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
			   Graphics^ g = Graphics::FromImage(bmp);
			   g->Clear(Color::White);

			   float maxHata = 0;
			   for (int i = 0; i < epochs; i++) if (ErrorHistory[i] > maxHata) maxHata = ErrorHistory[i];

			   Pen^ p = gcnew Pen(Color::Red, 2);
			   float adim = (float)pictureBox1->Width / epochs;

			   for (int i = 0; i < epochs - 1; i++) {
				   float y1 = pictureBox1->Height - (ErrorHistory[i] / maxHata * (pictureBox1->Height - 20));
				   float y2 = pictureBox1->Height - (ErrorHistory[i + 1] / maxHata * (pictureBox1->Height - 20));
				   g->DrawLine(p, i * adim, y1, (i + 1) * adim, y2);
			   }

			   // Eksenler
			   g->DrawLine(Pens::Black, 0, pictureBox1->Height - 1, pictureBox1->Width, pictureBox1->Height - 1);
			   g->DrawLine(Pens::Black, 0, 0, 0, pictureBox1->Height);

			   pictureBox1->Image = bmp;
		   }
	};
}