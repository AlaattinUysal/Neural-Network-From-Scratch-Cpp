#pragma once
#include <cstdio>  // fopen, fread, fseek için (Saf C Kütüphanesi)
#include <cmath>
#include <ctime>
#include <algorithm>
#include <string>

// Mecburi: Windows String'ini C String'ine çevirmek için
using namespace System::Runtime::InteropServices;

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class Form_AutoEncoder : public System::Windows::Forms::Form
	{
	public:
		Form_AutoEncoder(void)
		{
			InitializeComponent();
			srand((unsigned int)time(0));
		}

	protected:
		~Form_AutoEncoder()
		{
			if (components) delete components;

			// Temizlik
			if (TrainImages) delete[] TrainImages;
			if (Layers) delete[] Layers;
			if (NeuronOffsets) delete[] NeuronOffsets;
			if (WeightOffsets) delete[] WeightOffsets;
			if (Activations) delete[] Activations;
			if (Errors) delete[] Errors;
			if (Weights) delete[] Weights;
			if (Biases) delete[] Biases;
		}

	private:
		// --- STANDART ARAYÜZ ELEMANLARI ---
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::GroupBox^ groupBox1;
		System::Windows::Forms::Button^ btn_InitNet; // Aðý Kur Butonu

		System::Windows::Forms::Label^ lbl_Hidden;
		System::Windows::Forms::TextBox^ txt_Hidden;
		System::Windows::Forms::Label^ lbl_Epoch;
		System::Windows::Forms::TextBox^ txt_Epoch;
		System::Windows::Forms::Label^ lbl_LR;
		System::Windows::Forms::TextBox^ txt_LearnRate;

		System::Windows::Forms::GroupBox^ groupBox2;
		System::Windows::Forms::Button^ btn_Load;    // Veri Yükle Butonu
		System::Windows::Forms::Label^ lbl_DataStatus;

		System::Windows::Forms::TextBox^ textBox1;   // Log Ekraný

		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ processToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ trainingToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ testingToolStripMenuItem;

		System::ComponentModel::Container^ components;

		// --- BASÝT DEÐÝÞKENLER ---
		int numTrain = 0;
		float* TrainImages = nullptr;

		// --- AÐ YAPISI ---
		int TotalLayers = 0;
		int* Layers = nullptr;
		int* NeuronOffsets = nullptr;
		int* WeightOffsets = nullptr;

		float* Activations = nullptr;
		float* Errors = nullptr;
		float* Weights = nullptr;
		float* Biases = nullptr;

		float learningRate = 0.1f;

		// --- MATEMATÝK ---
		float sigmoid(float x) { return 1.0f / (1.0f + exp(-x)); }
		float sigmoid_derivative(float y) { return y * (1.0f - y); }
		float tanh_act(float x) { return tanh(x); }
		float tanh_derivative(float y) { return 1.0f - (y * y); }

		// --- YARDIMCI: Windows String -> C String Çevirici ---
		void StringToChar(String^ s, char* output) {
			IntPtr p = Marshal::StringToHGlobalAnsi(s);
			const char* chars = static_cast<const char*>(p.ToPointer());
			strcpy(output, chars);
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
			this->btn_Load = (gcnew System::Windows::Forms::Button());
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

			// pictureBox1
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

			// Init Button (Aðý Kur)
			this->btn_InitNet->Location = System::Drawing::Point(13, 125);
			this->btn_InitNet->Size = System::Drawing::Size(175, 41);
			this->btn_InitNet->Text = L"Network Setup (Init)";
			this->btn_InitNet->UseVisualStyleBackColor = true;
			this->btn_InitNet->Click += gcnew System::EventHandler(this, &Form_AutoEncoder::btn_Init_Click);

			// groupBox2 (Dataset Loading)
			this->groupBox2->Controls->Add(this->btn_Load);
			this->groupBox2->Controls->Add(this->lbl_DataStatus);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(162)));
			this->groupBox2->Location = System::Drawing::Point(1172, 260);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(253, 100);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Dataset Loading";

			// Load Button
			this->btn_Load->Location = System::Drawing::Point(10, 25);
			this->btn_Load->Size = System::Drawing::Size(230, 40);
			this->btn_Load->Text = L"Load Images (C File)";
			this->btn_Load->UseVisualStyleBackColor = true;
			this->btn_Load->Click += gcnew System::EventHandler(this, &Form_AutoEncoder::btn_Load_Click);

			// Status Label
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

			// MenuStrip
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
			this->trainingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_AutoEncoder::trainingToolStripMenuItem_Click);

			this->testingToolStripMenuItem->Text = L"Testing";
			this->testingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form_AutoEncoder::testingToolStripMenuItem_Click);

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
			this->Name = L"Form_AutoEncoder";
			this->Text = L"Form_AutoEncoder";
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

		// --- 1. VERÝ YÜKLEME (SAF C: fopen, fread) ---
	private: System::Void btn_Load_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Title = "train-images dosyasýný seç";
		if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

		char dosya_yolu[256];
		StringToChar(ofd->FileName, dosya_yolu);

		FILE* dosya = fopen(dosya_yolu, "rb");

		if (dosya != NULL) {
			fseek(dosya, 16, SEEK_SET); // 16 byte header atla

			numTrain = 1000;
			if (TrainImages) delete[] TrainImages;
			TrainImages = new float[numTrain * 784];

			textBox1->AppendText("Dosya açýldý, okunuyor...\r\n");
			Application::DoEvents();

			unsigned char tampon[784];

			for (int i = 0; i < numTrain; i++) {
				fread(tampon, 1, 784, dosya);
				for (int p = 0; p < 784; p++) {
					TrainImages[i * 784 + p] = (float)tampon[p] / 255.0f;
				}
			}

			fclose(dosya);
			lbl_DataStatus->Text = "Yüklendi: 1000 resim";
			textBox1->AppendText("Tamamlandý. 1000 resim yüklendi.\r\n");
		}
		else {
			MessageBox::Show("Dosya açýlamadý!");
		}
	}

		   // --- 2. AÐI KUR (INIT) ---
	private: System::Void btn_Init_Click(System::Object^ sender, System::EventArgs^ e) {
		int gizli_boyut = Convert::ToInt32(txt_Hidden->Text);

		if (Weights) delete[] Weights; if (Biases) delete[] Biases;
		if (Layers) delete[] Layers;
		if (NeuronOffsets) delete[] NeuronOffsets; if (WeightOffsets) delete[] WeightOffsets;
		if (Activations) delete[] Activations; if (Errors) delete[] Errors;

		// Mimari: 784 -> Gizli -> 784
		TotalLayers = 3;
		Layers = new int[3];
		Layers[0] = 784; Layers[1] = gizli_boyut; Layers[2] = 784;

		NeuronOffsets = new int[3]; WeightOffsets = new int[3];
		int total_n = 0, total_w = 0, total_b = 0;

		for (int i = 0; i < 3; i++) {
			NeuronOffsets[i] = total_n; total_n += Layers[i];
			if (i < 2) {
				WeightOffsets[i] = total_w;
				total_w += Layers[i] * Layers[i + 1];
				total_b += Layers[i + 1];
			}
		}

		Activations = new float[total_n];
		Errors = new float[total_n];
		Weights = new float[total_w];
		Biases = new float[total_b];

		for (int i = 0; i < total_w; i++) Weights[i] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
		for (int i = 0; i < total_b; i++) Biases[i] = 0.0f;

		btn_InitNet->Text = "Network Ready";
		textBox1->AppendText("Að Hazýr: 784 -> " + gizli_boyut + " -> 784\r\n");
	}

		   // --- 3. EÐÝTÝM (PROCESS -> TRAINING) ---
	private: System::Void trainingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numTrain == 0) { MessageBox::Show("Önce veri yükleyin!"); return; }
		if (TotalLayers == 0) { MessageBox::Show("Önce aðý kurun (Init)!"); return; }

		int epochs = Convert::ToInt32(txt_Epoch->Text);
		learningRate = (float)Convert::ToDouble(txt_LearnRate->Text);

		textBox1->AppendText("Eðitim Baþladý...\r\n");

		for (int ep = 0; ep < epochs; ep++) {
			double toplam_hata = 0;

			for (int s = 0; s < numTrain; s++) {
				// GÝRÝÞ
				int giris_idx = NeuronOffsets[0];
				for (int k = 0; k < 784; k++) Activations[giris_idx + k] = TrainImages[s * 784 + k];

				// ÝLERÝ
				// Katman 1 (Tanh)
				int w1 = WeightOffsets[0]; int h_idx = NeuronOffsets[1];
				for (int j = 0; j < Layers[1]; j++) {
					float net = 0;
					for (int i = 0; i < 784; i++) net += Activations[giris_idx + i] * Weights[w1 + i * Layers[1] + j];
					net += Biases[j];
					Activations[h_idx + j] = tanh_act(net);
				}
				// Katman 2 (Sigmoid)
				int w2 = WeightOffsets[1]; int out_idx = NeuronOffsets[2];
				for (int j = 0; j < 784; j++) {
					float net = 0;
					for (int i = 0; i < Layers[1]; i++) net += Activations[h_idx + i] * Weights[w2 + i * 784 + j];
					net += Biases[Layers[1] + j];
					Activations[out_idx + j] = sigmoid(net);
				}

				// HATA
				for (int k = 0; k < 784; k++) {
					float hedef = Activations[giris_idx + k];
					float cikti = Activations[out_idx + k];
					float hata = hedef - cikti;
					toplam_hata += hata * hata;
					Errors[out_idx + k] = hata * sigmoid_derivative(cikti);
				}

				// GERÝ
				for (int i = 0; i < Layers[1]; i++) {
					float sum = 0;
					for (int j = 0; j < 784; j++) sum += Errors[out_idx + j] * Weights[w2 + i * 784 + j];
					Errors[h_idx + i] = sum * tanh_derivative(Activations[h_idx + i]);
				}

				// GÜNCELLE
				for (int j = 0; j < 784; j++) {
					float d = Errors[out_idx + j];
					Biases[Layers[1] + j] += learningRate * d;
					for (int i = 0; i < Layers[1]; i++) Weights[w2 + i * 784 + j] += learningRate * d * Activations[h_idx + i];
				}
				for (int j = 0; j < Layers[1]; j++) {
					float d = Errors[h_idx + j];
					Biases[j] += learningRate * d;
					for (int i = 0; i < 784; i++) Weights[w1 + i * Layers[1] + j] += learningRate * d * Activations[giris_idx + i];
				}
			}

			if (ep % 10 == 0) {
				textBox1->AppendText("Epoch " + ep + " Hata: " + (toplam_hata / numTrain) + "\r\n");
				Application::DoEvents();
			}
		}
		MessageBox::Show("Eðitim Tamamlandý!");
	}

		   // --- 4. TEST VE GÖRSELLEÞTÝRME (PROCESS -> TESTING) ---
	private: System::Void testingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numTrain == 0 || TotalLayers == 0) return;

		int s = rand() % numTrain;

		int giris_idx = NeuronOffsets[0];
		int h_idx = NeuronOffsets[1];
		int out_idx = NeuronOffsets[2];

		for (int k = 0; k < 784; k++) Activations[giris_idx + k] = TrainImages[s * 784 + k];

		int w1 = WeightOffsets[0];
		for (int j = 0; j < Layers[1]; j++) {
			float net = 0;
			for (int i = 0; i < 784; i++) net += Activations[giris_idx + i] * Weights[w1 + i * Layers[1] + j];
			net += Biases[j];
			Activations[h_idx + j] = tanh_act(net);
		}
		int w2 = WeightOffsets[1];
		for (int j = 0; j < 784; j++) {
			float net = 0;
			for (int i = 0; i < Layers[1]; i++) net += Activations[h_idx + i] * Weights[w2 + i * 784 + j];
			net += Biases[Layers[1] + j];
			Activations[out_idx + j] = sigmoid(net);
		}

		// ÇÝZÝM (Büyük Ekranýn Sol Üst Köþesine)
		// PictureBox artýk çok büyük olduðu için temizlememiz iyi olur
		Bitmap^ bmp;
		if (pictureBox1->Image) bmp = (Bitmap^)pictureBox1->Image;
		else bmp = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);

		Graphics^ g = Graphics::FromImage(bmp);
		g->Clear(Color::White); // Arka planý temizle

		int zoom = 10;
		int marginX = 20; // Kenardan boþluk
		int marginY = 20;

		for (int y = 0; y < 28; y++) {
			for (int x = 0; x < 28; x++) {
				// Sol: Orjinal
				float p1 = TrainImages[s * 784 + (y * 28 + x)];
				int c1 = (int)(p1 * 255);
				if (c1 < 0) c1 = 0; if (c1 > 255) c1 = 255;
				Color renk1 = Color::FromArgb(c1, c1, c1);

				// Sað: Yapay Zeka (AutoEncoder Çýktýsý)
				float p2 = Activations[out_idx + (y * 28 + x)];
				int c2 = (int)(p2 * 255);
				if (c2 < 0) c2 = 0; if (c2 > 255) c2 = 255;
				Color renk2 = Color::FromArgb(c2, c2, c2);

				// Elle Piksel Boyama (Zoomlu)
				for (int zx = 0; zx < zoom; zx++) {
					for (int zy = 0; zy < zoom; zy++) {
						// Sol Resim (Orjinal)
						bmp->SetPixel(marginX + x * zoom + zx, marginY + y * zoom + zy, renk1);
						// Sað Resim (Reconstructed) - 300 piksel saða
						bmp->SetPixel(marginX + 300 + x * zoom + zx, marginY + y * zoom + zy, renk2);
					}
				}
			}
		}

		// Etiketleri Yaz
		System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 16);
		g->DrawString("Orjinal", font, Brushes::Black, marginX, marginY + 280 + 10);
		g->DrawString("Yapay Zeka", font, Brushes::Black, marginX + 300, marginY + 280 + 10);

		pictureBox1->Image = bmp;
		textBox1->AppendText("Örnek " + s + " test edildi ve çizildi.\r\n");
	}
	};
}