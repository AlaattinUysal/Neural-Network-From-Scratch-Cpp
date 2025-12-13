#pragma once
#include <cstdio>  // Eski usül C dosya okuma (fopen, fread)
#include <cmath>
#include <ctime>
#include <algorithm>

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
		// Windows'un "String" yapýsýný, C'nin anladýðý "char array"e çevirir.
		void DosyaYolunuAl(String^ s, char* cikis) {
			IntPtr p = Marshal::StringToHGlobalAnsi(s);
			const char* chars = static_cast<const char*>(p.ToPointer());
			strcpy(cikis, chars); // Kopyala
			Marshal::FreeHGlobal(p);
		}

		// --- YARDIMCI: TERS OKUMA (BIG ENDIAN -> LITTLE ENDIAN) ---
		// MNIST dosyalarý sayýlarý ters yazar. Biz düzeltiyoruz.
		int TersCevir(int sayi) {
			unsigned char c1, c2, c3, c4;
			c1 = sayi & 255;
			c2 = (sayi >> 8) & 255;
			c3 = (sayi >> 16) & 255;
			c4 = (sayi >> 24) & 255;
			return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
		}

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

			this->btn_LoadMNIST->Location = System::Drawing::Point(12, 12);
			this->btn_LoadMNIST->Size = System::Drawing::Size(150, 40);
			this->btn_LoadMNIST->Text = L"1. MNIST Yükle";
			this->btn_LoadMNIST->Click += gcnew System::EventHandler(this, &Form_MNIST::btn_LoadMNIST_Click);

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

			this->btn_Train->Location = System::Drawing::Point(12, 130);
			this->btn_Train->Size = System::Drawing::Size(150, 40);
			this->btn_Train->Text = L"2. Eðit (Train)";
			this->btn_Train->Click += gcnew System::EventHandler(this, &Form_MNIST::btn_Train_Click);

			this->btn_Test->Location = System::Drawing::Point(12, 190);
			this->btn_Test->Size = System::Drawing::Size(150, 40);
			this->btn_Test->Text = L"3. Test Et";
			this->btn_Test->Click += gcnew System::EventHandler(this, &Form_MNIST::btn_Test_Click);

			this->pBox_Graph->BackColor = System::Drawing::Color::White;
			this->pBox_Graph->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pBox_Graph->Location = System::Drawing::Point(180, 12);
			this->pBox_Graph->Size = System::Drawing::Size(600, 300);

			this->lbl_Status->AutoSize = true;
			this->lbl_Status->ForeColor = System::Drawing::Color::Blue;
			this->lbl_Status->Location = System::Drawing::Point(12, 250);
			this->lbl_Status->Text = L"Hazýr: Bekliyor...";

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

		// --- 1. VERÝ YÜKLEME (SAF KAN C - fopen/fread) ---
	private: System::Void btn_LoadMNIST_Click(System::Object^ sender, System::EventArgs^ e) {
		// Dosya Seçme Penceresi (Windows Mecburiyeti)
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Title = "Lütfen 'train-images' dosyasýný seçin";
		if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
		char yol_resim[256]; DosyaYolunuAl(ofd->FileName, yol_resim); // C Stringine çevir

		ofd->Title = "Lütfen 'train-labels' dosyasýný seçin";
		if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
		char yol_etiket[256]; DosyaYolunuAl(ofd->FileName, yol_etiket);

		// --- MANUEL DOSYA AÇMA ---
		FILE* f_resim = fopen(yol_resim, "rb"); // rb = Read Binary (Ýkilik Oku)
		FILE* f_etiket = fopen(yol_etiket, "rb");

		if (f_resim && f_etiket) {
			// Header (Baþlýk) Bilgilerini Oku ve Atla
			int temp;
			// Resim dosyasýnýn baþýndaki 4 tane int (16 byte) gereksiz bilgi
			fread(&temp, 4, 1, f_resim); // Magic Number
			fread(&temp, 4, 1, f_resim); // Resim Sayýsý
			fread(&temp, 4, 1, f_resim); // Satýr
			fread(&temp, 4, 1, f_resim); // Sütun

			// Etiket dosyasýnýn baþýndaki 2 tane int (8 byte) gereksiz bilgi
			fread(&temp, 4, 1, f_etiket); // Magic
			fread(&temp, 4, 1, f_etiket); // Etiket Sayýsý

			// --- DENGELÝ VERÝ SETÝ ---
			int hedef_rakam_basina = 100; // Her rakamdan 100 tane
			int toplam_hedef = 1000;      // Toplam 1000 resim

			int sayaclar[10] = { 0 };     // Hangi rakamdan kaç tane aldýk?
			int toplanan = 0;

			// Bellek Aç
			if (TrainImages) delete[] TrainImages;
			if (TrainLabels) delete[] TrainLabels;
			TrainImages = new float[toplam_hedef * 784];
			TrainLabels = new int[toplam_hedef];
			numTrain = toplam_hedef;

			rtb_Logs->AppendText("Veri taranýyor... (Manuel C Okuma)\n");
			Application::DoEvents();

			unsigned char tampon_etiket;
			unsigned char tampon_resim[784]; // Bir resmi geçici tutmak için

			// --- DÖNGÜ ---
			while (toplanan < toplam_hedef) {
				// 1. Etiketi Oku (1 Byte)
				if (fread(&tampon_etiket, 1, 1, f_etiket) != 1) break; // Dosya bitti mi?
				int etiket = (int)tampon_etiket;

				// 2. Ýhtiyacýmýz var mý?
				if (sayaclar[etiket] < hedef_rakam_basina) {
					// EVET, ALALIM
					TrainLabels[toplanan] = etiket;

					// 784 pikseli dosyadan oku
					fread(tampon_resim, 1, 784, f_resim);

					// Veriyi kaydet ve normalize et
					for (int p = 0; p < 784; p++) {
						TrainImages[toplanan * 784 + p] = (float)tampon_resim[p] / 255.0f;
					}
					sayaclar[etiket]++;
					toplanan++;
				}
				else {
					// HAYIR, ATLAYALIM (Seek ile Zýpla)
					// fseek: Dosya imlecini kaydýrýr. 784 bayt ileri git.
					fseek(f_resim, 784, SEEK_CUR);
				}
			}

			fclose(f_resim);
			fclose(f_etiket);

			lbl_Status->Text = "Hazýr: " + Convert::ToString(toplanan) + " örnek.";
			rtb_Logs->AppendText("Tamamlandý. Dengeli set yüklendi.\n");
		}
		else {
			MessageBox::Show("Dosyalar açýlamadý (fopen hatasý)!");
		}
	}

		   // --- 2. EÐÝTÝM (Ayný) ---
	// --- 2. EÐÝTÝM (DÜZELTÝLMÝÞ) ---
	private: System::Void btn_Train_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numTrain == 0) { MessageBox::Show("Veri yok!"); return; }

		int n_hidden = Convert::ToInt32(txt_Hidden->Text);
		int n_epochs = Convert::ToInt32(txt_Epoch->Text);

		// Bellek Temizle / Aç
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
				// 1. Girdi
				int input_idx = NeuronOffsets[0];
				for (int k = 0; k < 784; k++) Activations[input_idx + k] = TrainImages[s * 784 + k];

				// 2. Forward (Ýleri)
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

				// 3. Hata (Error)
				int out_s = NeuronOffsets[2];
				int target = TrainLabels[s];
				for (int k = 0; k < 10; k++) {
					float desired = (k == target) ? 1.0f : 0.0f;
					float out = Activations[out_s + k];
					float err = desired - out;
					epoch_error += err * err;
					Errors[out_s + k] = err * sigmoid_derivative(out);
				}

				// 4. Backward (Geri)
				for (int l = 1; l > 0; l--) {
					int curr = NeuronOffsets[l]; int next = NeuronOffsets[l + 1]; int w_s = WeightOffsets[l];
					int n_curr = Layers[l]; int n_next = Layers[l + 1];
					for (int i = 0; i < n_curr; i++) {
						float sum = 0;
						for (int j = 0; j < n_next; j++) sum += Errors[next + j] * Weights[w_s + i * n_next + j];
						Errors[curr + i] = sum * sigmoid_derivative(Activations[curr + i]);
					}
				}

				// 5. Update (Güncelle)
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

			// Hata Kaydý ve Ekrana Yazma (DÜZELTÝLDÝ)
			ErrorHistory[epoch] = (float)epoch_error / numTrain;

			if (epoch % 10 == 0) {
				// BURASI EKLENDÝ: Artýk hata deðerini de yazýyor
				rtb_Logs->AppendText("Epoch " + Convert::ToString(epoch) + " Hata: " + Convert::ToString(ErrorHistory[epoch]) + "\n");
				rtb_Logs->ScrollToCaret(); // En alta kaydýr
				Application::DoEvents();   // Arayüz donmasýn
			}
		}
		DrawGraph(n_epochs);
		MessageBox::Show("Eðitim Bitti!");
	}

		   // --- 3. TEST (Ayný) ---
	private: System::Void btn_Test_Click(System::Object^ sender, System::EventArgs^ e) {
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
		lbl_Status->Text = "Baþarý: %" + accuracy;
		MessageBox::Show("Baþarý: %" + accuracy);
	}

		   // --- BASÝTLEÞTÝRÝLMÝÞ GRAFÝK ---
		   void DrawGraph(int epochs) {
			   if (epochs < 2) return;
			   Bitmap^ bmp = gcnew Bitmap(pBox_Graph->Width, pBox_Graph->Height);
			   Graphics^ g = Graphics::FromImage(bmp);
			   g->Clear(Color::White);

			   // En yüksek hatayý bul (Ölçekleme için)
			   float maxHata = 0;
			   for (int i = 0; i < epochs; i++) if (ErrorHistory[i] > maxHata) maxHata = ErrorHistory[i];

			   Pen^ p = gcnew Pen(Color::Red, 2);
			   float adim = (float)pBox_Graph->Width / epochs;

			   for (int i = 0; i < epochs - 1; i++) {
				   // Y eksenini ters çeviriyoruz (0 yukarýdadýr)
				   float y1 = pBox_Graph->Height - (ErrorHistory[i] / maxHata * (pBox_Graph->Height - 10));
				   float y2 = pBox_Graph->Height - (ErrorHistory[i + 1] / maxHata * (pBox_Graph->Height - 10));
				   g->DrawLine(p, i * adim, y1, (i + 1) * adim, y2);
			   }
			   pBox_Graph->Image = bmp;
		   }
	};
}