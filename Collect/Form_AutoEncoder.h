#pragma once
#include <cstdio>  // fopen, fread, fseek için (Saf C Kütüphanesi)
#include <cmath>
#include <ctime>
#include <algorithm>

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
		System::Windows::Forms::Button^ btn_Load;
		System::Windows::Forms::Button^ btn_Init;
		System::Windows::Forms::Button^ btn_Train;
		System::Windows::Forms::Button^ btn_Test;
		System::Windows::Forms::PictureBox^ pBox_Visual;
		System::Windows::Forms::RichTextBox^ rtb_Logs;
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
		// Windows "String^" kullanýr, fopen "char*" ister. Bu köprü þart.
		void StringToChar(String^ s, char* output) {
			IntPtr p = Marshal::StringToHGlobalAnsi(s);
			const char* chars = static_cast<const char*>(p.ToPointer());
			strcpy(output, chars);
			Marshal::FreeHGlobal(p);
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->btn_Load = (gcnew System::Windows::Forms::Button());
			this->btn_Init = (gcnew System::Windows::Forms::Button());
			this->btn_Train = (gcnew System::Windows::Forms::Button());
			this->btn_Test = (gcnew System::Windows::Forms::Button());
			this->pBox_Visual = (gcnew System::Windows::Forms::PictureBox());
			this->rtb_Logs = (gcnew System::Windows::Forms::RichTextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBox_Visual))->BeginInit();
			this->SuspendLayout();

			this->btn_Load->Location = System::Drawing::Point(12, 12);
			this->btn_Load->Size = System::Drawing::Size(120, 40);
			this->btn_Load->Text = L"1. Veri Yükle";
			this->btn_Load->Click += gcnew System::EventHandler(this, &Form_AutoEncoder::btn_Load_Click);

			this->btn_Init->Location = System::Drawing::Point(12, 60);
			this->btn_Init->Size = System::Drawing::Size(120, 40);
			this->btn_Init->Text = L"2. Aðý Kur";
			this->btn_Init->Click += gcnew System::EventHandler(this, &Form_AutoEncoder::btn_Init_Click);

			this->btn_Train->Location = System::Drawing::Point(12, 110);
			this->btn_Train->Size = System::Drawing::Size(120, 40);
			this->btn_Train->Text = L"3. Eðit";
			this->btn_Train->Click += gcnew System::EventHandler(this, &Form_AutoEncoder::btn_Train_Click);

			this->btn_Test->Location = System::Drawing::Point(12, 160);
			this->btn_Test->Size = System::Drawing::Size(120, 40);
			this->btn_Test->Text = L"4. Test Et";
			this->btn_Test->Click += gcnew System::EventHandler(this, &Form_AutoEncoder::btn_Test_Click);

			this->pBox_Visual->BackColor = System::Drawing::Color::Black;
			this->pBox_Visual->Location = System::Drawing::Point(150, 12);
			this->pBox_Visual->Size = System::Drawing::Size(580, 280);

			this->rtb_Logs->Location = System::Drawing::Point(12, 310);
			this->rtb_Logs->Size = System::Drawing::Size(718, 150);
			this->rtb_Logs->Text = L"";

			this->Controls->Add(this->rtb_Logs);
			this->Controls->Add(this->pBox_Visual);
			this->Controls->Add(this->btn_Test);
			this->Controls->Add(this->btn_Train);
			this->Controls->Add(this->btn_Init);
			this->Controls->Add(this->btn_Load);
			this->Name = L"Form_AutoEncoder";
			this->Text = L"AutoEncoder (Saf C Okuma)";
			this->Size = System::Drawing::Size(760, 520);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBox_Visual))->EndInit();
			this->ResumeLayout(false);
		}
#pragma endregion

		// --- 1. VERÝ YÜKLEME (SAF C: fopen, fread, fseek) ---
	private: System::Void btn_Load_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Title = "train-images dosyasýný seç";
		if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

		// Windows yolunu C yoluna çevir
		char dosya_yolu[256];
		StringToChar(ofd->FileName, dosya_yolu);

		// SAF C DOSYA AÇMA
		FILE* dosya = fopen(dosya_yolu, "rb"); // rb: Read Binary (Ýkilik Oku)

		if (dosya != NULL) {
			// 1. Header (Baþlýk) Atla
			// MNIST dosyalarýnýn ilk 16 baytý gereksiz bilgidir.
			// fseek: Dosya içinde zýplama komutu. 16 bayt ileri git.
			fseek(dosya, 16, SEEK_SET);

			numTrain = 1000; // 1000 resim alalým
			if (TrainImages) delete[] TrainImages;
			TrainImages = new float[numTrain * 784];

			rtb_Logs->AppendText("Dosya açýldý, okunuyor...\n");

			unsigned char tampon[784]; // Bir resmi tutacak geçici hafýza

			for (int i = 0; i < numTrain; i++) {
				// Dosyadan 784 bayt oku ve tampona yaz
				fread(tampon, 1, 784, dosya);

				// 0-255 arasýný 0-1 arasýna çevir
				for (int p = 0; p < 784; p++) {
					TrainImages[i * 784 + p] = (float)tampon[p] / 255.0f;
				}
			}

			fclose(dosya); // Dosyayý kapat
			rtb_Logs->AppendText("Tamamlandý. 1000 resim yüklendi.\n");
		}
		else {
			MessageBox::Show("Dosya açýlamadý!");
		}
	}

		   // --- 2. AÐI KUR ---
	private: System::Void btn_Init_Click(System::Object^ sender, System::EventArgs^ e) {
		int gizli_boyut = 64;

		if (Weights) delete[] Weights; if (Biases) delete[] Biases;
		if (Layers) delete[] Layers;

		// Mimari: 784 -> 64 -> 784
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

		rtb_Logs->AppendText("Að Hazýr: 784 -> " + gizli_boyut + " -> 784\n");
	}

		   // --- 3. EÐÝTÝM ---
	private: System::Void btn_Train_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numTrain == 0) return;

		int epochs = 50;
		rtb_Logs->AppendText("Eðitim Baþladý...\n");

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
				rtb_Logs->AppendText("Epoch " + ep + " Hata: " + (toplam_hata / numTrain) + "\n");
				rtb_Logs->Update();
			}
		}
		MessageBox::Show("Eðitim Tamamlandý!");
	}

		   // --- 4. TEST VE ÇÝZÝM ---
	private: System::Void btn_Test_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numTrain == 0) return;

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

		// ÇÝZÝM (SetPixel - En kolayý)
		Bitmap^ bmp = gcnew Bitmap(pBox_Visual->Width, pBox_Visual->Height);
		int zoom = 10;

		for (int y = 0; y < 28; y++) {
			for (int x = 0; x < 28; x++) {
				// Sol: Orjinal
				float p1 = TrainImages[s * 784 + (y * 28 + x)];
				int c1 = (int)(p1 * 255);
				if (c1 < 0) c1 = 0; if (c1 > 255) c1 = 255;
				Color renk1 = Color::FromArgb(c1, c1, c1);

				// Sað: Yapay Zeka
				float p2 = Activations[out_idx + (y * 28 + x)];
				int c2 = (int)(p2 * 255);
				if (c2 < 0) c2 = 0; if (c2 > 255) c2 = 255;
				Color renk2 = Color::FromArgb(c2, c2, c2);

				// Zoom yap (Pikseli büyüt)
				for (int zx = 0; zx < zoom; zx++) {
					for (int zy = 0; zy < zoom; zy++) {
						bmp->SetPixel(x * zoom + zx, y * zoom + zy, renk1);       // Sol
						bmp->SetPixel(300 + x * zoom + zx, y * zoom + zy, renk2); // Sað
					}
				}
			}
		}
		pBox_Visual->Image = bmp;
		rtb_Logs->AppendText("Örnek " + s + " çizildi.\n");
	}
	};
}