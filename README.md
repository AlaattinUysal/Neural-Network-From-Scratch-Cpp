<h1 align="center">
  🧠 Neural Network From Scratch (C++ / CLI)
</h1>

<p align="center">
  <strong>Hazır Kütüphane Yok. Sadece Matematik ve Saf C++.</strong><br>
  Yapay Sinir Ağlarının çalışma mantığını (Backpropagation, Gradient Descent, Activation Functions) en temelden anlamak için geliştirilmiştir.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=c%2B%2B" alt="C++">
  <img src="https://img.shields.io/badge/Framework-Windows%20Forms-purple?style=for-the-badge&logo=windows" alt="WinForms">
  <img src="https://img.shields.io/badge/IDE-Visual%20Studio-5C2D91?style=for-the-badge&logo=visual-studio" alt="VS">
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License">
</p>

<p align="center">
  <a href="#-proje-hakkında">Proje Hakkında</a> •
  <a href="#-modüller-ve-özellikler">Modüller</a> •
  <a href="#-teknik-detaylar">Teknik Detaylar</a> •
  <a href="#-ekran-görüntüleri">Görseller</a> •
  <a href="#-kurulum">Kurulum</a>
</p>

---

## 🚀 Proje Hakkında

Bu proje, TensorFlow veya PyTorch gibi hiçbir hazır yapay zeka kütüphanesi kullanılmadan geliştirilmiştir. **Tek Katmanlı Algılayıcı (Perceptron)** yapısından başlayarak, **Derin Öğrenme (Deep Learning)** konseptlerine kadar uzanan bir simülasyon ortamıdır.

> **Temel Felsefe:** "Bir şeyi sıfırdan kodlayamıyorsan, onu tam olarak anlamış sayılmazsın."

Proje, bellek yönetimi (memory management), pointer aritmetiği ve matematiksel türev işlemlerini manuel olarak yöneterek C++ dilinin gücünü gösterir.

---

## ⚡ Modüller ve Özellikler

Uygulama 5 ana modülden oluşmaktadır:

| Modül | Açıklama |
| :--- | :--- |
| **1. Single Layer Perceptron** | Doğrusal (Linear) sınıflandırma ve regresyon işlemleri. |
| **2. Multi-Layer Perceptron** | XOR gibi doğrusal olmayan problemlerin çözümü ve Karar Sınırlarının (Decision Boundaries) çizimi. |
| **3. Momentum Optimization** | Standart öğrenme sürecinin hızlandırılması ve yerel minimumlardan kaçış teknikleri. |
| **4. MNIST Digit Recognition** | El yazısı rakamların (0-9) binary dosya formatından okunup sınıflandırılması. |
| **5. AutoEncoder** | Görüntü sıkıştırma ve yeniden oluşturma (Unsupervised Learning). |

---

## 🛠 Teknik Detaylar

Projenin kalbinde yatan matematiksel algoritmalar şunlardır:

* **İleri Yayılım (Forward Propagation):** Matris çarpımları ve Bias eklemeleri.
* **Aktivasyon Fonksiyonları:**
    * `Sigmoid`: Çıkış katmanlarında olasılık dağılımı için.
    * `Tanh`: Gizli katmanlarda veri aralığını genişletmek için (-1, 1).
* **Geri Yayılım (Backpropagation):** Zincir kuralı (Chain Rule) kullanılarak hatanın geriye doğru dağıtılması.
* **Optimizasyon:** Stochastic Gradient Descent (SGD) ve Momentum.

<details>
<summary>💻 <b>Örnek Kod: Backpropagation Algoritması (Tıklayıp Genişletin)</b></summary>

```cpp
// Backpropagation Döngüsü (Multi-Layer)
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
            // Hatayı ağırlıklarla çarparak geriye taşı
            sum += Errors[next_start + j] * Weights[w_idx];
        }
        // Türev ile çarp (Sigmoid Derivative)
        Errors[curr_start + i] = sum * sigmoid_derivative(Activations[curr_start + i]);
    }
}

```
</details>


## 📸 Ekran Görüntüleri

### 1. Single-Layer Perceptron (Karar Sınırları)
 Doğrusal (Linear) sınıflandırma ve regresyon işlemleri. 
 
<img width="775" height="446" alt="image" src="https://github.com/user-attachments/assets/81c19dc0-da9a-4262-908c-9480d62967e8" />
<img width="945" height="538" alt="image" src="https://github.com/user-attachments/assets/550dc6f6-ac87-4118-a75d-75672cebf17c" />

 

### 1. Multi-Layer Perceptron (Karar Sınırları)
Ağın karmaşık veri setlerini (XOR Problemi gibi) nasıl bölgelere ayırdığını gösteren renkli alan görselleştirmesi.

<img width="945" height="552" alt="image" src="https://github.com/user-attachments/assets/f370c824-08e7-417f-9763-52b6a3522392" />

<img width="945" height="551" alt="image" src="https://github.com/user-attachments/assets/11ec4d7c-1af8-4546-878a-bbc47e79825b" />


### 2. AutoEncoder (Görüntü Sıkıştırma & Reconstruction)
MNIST veri setindeki rakamların sıkıştırılıp (Encoder) tekrar oluşturulması (Decoder). Sol taraf orijinal, sağ taraf yapay zekanın çıktısıdır.

| Orijinal Görüntü | Yapay Zeka Çıktısı |
<img width="763" height="443" alt="image" src="https://github.com/user-attachments/assets/9aeb6edb-f251-4920-aab4-5178069fa281" />
<img width="768" height="446" alt="image" src="https://github.com/user-attachments/assets/f650c4c2-100a-4cea-911c-22ee11650622" />
<img width="776" height="473" alt="image" src="https://github.com/user-attachments/assets/8ad159e0-c199-43dc-874f-bc1d1a92efa6" />


### 3. Momentum Etkisi
Standart eğitim ile Momentum destekli eğitimin hata (Loss) grafiği üzerindeki karşılaştırması.

<img width="945" height="555" alt="image" src="https://github.com/user-attachments/assets/c30668f9-34f2-451d-896f-15b2571824a2" />

### 4. Eğitim Hata Grafiği (Loss Graph)
Epoch başına hatanın (MSE) düşüşünü gösteren grafik.

<img width="815" height="477" alt="image" src="https://github.com/user-attachments/assets/183129c2-f7d9-48da-8f74-f8526c3d97c9" />

---

## 💾 Kurulum ve Kullanım

Projeyi kendi bilgisayarınızda çalıştırmak için:

1.  **Repoyu Klonlayın:**
    ```bash
    git clone [https://github.com/AlaattinUysal/Neural-Network-From-Scratch-Cpp.git]
    ```
2.  **Visual Studio ile Açın:**
    `CppCLR_WinformsProjekt.sln` dosyasını çalıştırın.
3.  **Veri Setlerini Yükleyin:**
    * MNIST ve AutoEncoder modülleri için proje dizininde `Data` klasörü oluşturun.
    * `train-images.idx3-ubyte` ve `train-labels.idx1-ubyte` dosyalarını bu klasöre atın.
4.  **Derleyin ve Çalıştırın:**
    `Ctrl + F5` ile projeyi başlatın.

---

## 👨‍💻 Geliştirici

**Alaattin Uysal**
* İlgi Alanları: Yapay Zeka Mimarileri, Gömülü Sistemler, C/C++ Optimizasyonu.

---
<p align="center">
  Bu proje eğitim amaçlı geliştirilmiştir. Matematiksel türevlerin koda dökülmesi sürecini içerir.
</p>
