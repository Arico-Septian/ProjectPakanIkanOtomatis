# Proyek Pakan Ikan Otomatis

Proyek ini merupakan sistem **pakan ikan otomatis** yang memungkinkan pemberian pakan pada ikan secara terjadwal dan otomatis menggunakan komponen-komponen elektronik seperti **ESP32 Wroom**, **ESP32 Cam**, **Kamera OV2640**, **Servo**, **Sensor Waktu DS3231**, dan **LCD 16x2 L2C**.

Dengan menggunakan sensor waktu **DS3231**, sistem ini dapat mengatur waktu pemberian pakan ikan secara otomatis. Kamera **OV2640** yang terpasang pada ESP32 Cam digunakan untuk memantau kondisi akuarium secara real-time. Semua informasi status dan waktu dapat dilihat pada **LCD 16x2 L2C**, yang juga terhubung dengan **ESP32 Wroom**.

## Daftar Komponen ##

- **ESP32 Wroom** x1  
  Mikrocontroller dengan kemampuan Wi-Fi dan Bluetooth.
  
- **ESP32 Cam** x1  
  Modul kamera dengan sensor **OV2640** untuk memantau akuarium secara real-time.
  
- **Kamera OV2640** x1  
  Kamera untuk menangkap gambar atau video kondisi akuarium.

- **Servo** x1  
  Digunakan untuk menggerakkan mekanisme pemberian pakan ikan secara otomatis.

- **Sensor Waktu DS3231** x1  
  Modul RTC (Real Time Clock) yang digunakan untuk mencatat dan mengatur waktu pemberian pakan ikan secara tepat.

- **LCD 16x2 L2C** x1  
  Layar LCD yang menampilkan status waktu dan kondisi sistem pakan ikan otomatis.

- **Kabel Jumper Male to Female** x beberapa  
  Kabel jumper untuk menghubungkan komponen-komponen ke ESP32.



## Cara Penggunaan ##

### Persiapan Hardware ###
**Sambungkan Komponen Sesuai Schematic**:
- Hubungkan **ESP32 Wroom** ke **Sensor DS3231** untuk membaca waktu.
- Sambungkan **ESP32 Wroom** ke **Servo** untuk mengendalikan mekanisme pemberian pakan.
- Pasang **ESP32 Cam** dengan **Kamera OV2640** untuk memantau akuarium.
- Sambungkan **LCD 16x2 L2C** ke **ESP32 Wroom** untuk menampilkan status.

### Upload Program ###
1. **Buka Arduino IDE**.
2. Pilih board **ESP32** dan port yang sesuai.
3. Buka file **pakan_ikan_otomatis.ino** di Arduino IDE.
4. Pastikan untuk mengganti **Auth Token** dari Blynk pada kode.
5. Klik **Upload** untuk meng-upload kode ke ESP32.

### Pengoperasian ###
1. Setelah program di-upload, ESP32 akan mulai bekerja sesuai dengan waktu yang telah ditetapkan pada **Sensor DS3231**.
2. Sistem secara otomatis akan memberikan pakan pada ikan sesuai dengan jadwal yang telah diprogram.
3. **ESP32 Cam** akan memantau kondisi akuarium dan menampilkan gambar atau video secara real-time.
4. **LCD 16x2 L2C** akan menampilkan waktu dan status sistem.
5. **Aplikasi Blynk** memungkinkan kamu untuk mengontrol dan memonitor sistem pakan ikan otomatis dari jarak jauh.

### Langkah-langkah Integrasi Blynk

1. **Instal Aplikasi Blynk**  
   Unduh aplikasi **Blynk** dari **Google Play Store** atau **Apple App Store**:
   - [Google Play Store](https://play.google.com/store/apps/details?id=cc.blynk&hl=en&gl=US)
   - [Apple App Store](https://apps.apple.com/us/app/blynk/id1291731814)

2. **Buat Proyek di Blynk**  
   - Buka aplikasi Blynk dan buat akun jika belum punya.
   - Buat **proyek baru** di Blynk dengan memilih **ESP32** sebagai board.
   - Setelah proyek dibuat, kamu akan mendapatkan **Auth Token** yang digunakan untuk menghubungkan aplikasi dengan ESP32.

3. **Tambahkan Widget di Blynk**  
   - Tambahkan widget yang dibutuhkan, seperti:
     - **Button** untuk mengendalikan pakan ikan secara manual.
     - **Video Streaming** untuk memantau kondisi aquarium secara real time.
   
4. **Salin Auth Token**  
   - Salin **Auth Token** dari aplikasi Blynk. Token ini akan digunakan dalam kode Arduino untuk menghubungkan ESP32 ke aplikasi Blynk.

### Menambahkan Blynk ke Kode

1. **Instal Library Blynk**  
   - Di **Arduino IDE**, buka **Sketch > Include Library > Manage Libraries**.
   - Cari dan instal library **Blynk**.

2. **Modifikasi Kode untuk Integrasi Blynk**  
   - Buka file `pakan_ikan_otomatis.ino` di Arduino IDE.
   - Masukkan **Auth Token** yang telah kamu salin dari aplikasi Blynk ke dalam kode berikut:
     ```cpp
     #define BLYNK_AUTH_TOKEN "YourAuthTokenHere"
     ```
   - Pastikan untuk mengganti `"YourAuthTokenHere"` dengan **Auth Token** yang kamu dapatkan dari aplikasi Blynk.

3. **Upload Program ke ESP32**  
   Setelah kamu menambahkan informasi **Auth Token**, upload program ke **ESP32** seperti biasa.

### Penggunaan Blynk

Setelah kode di-upload ke **ESP32**, kamu bisa membuka aplikasi **Blynk** di perangkat mobile untuk:

- **Mengontrol Pakan Ikan**: Gunakan **Button Widget** untuk memberikan pakan ikan secara manual kapan saja dari jarak jauh.
- **Memantau Kondisi Aquarium**: Gunakan **Video Streaming** untuk memantau kondisi aquarium secara real time.
- **Menghidupkan flash**: Gunakan **Button Widget** untuk menghidupkan flash agar seisi aquarium terlihat

## Schematic ##

Berikut adalah schematic rangkaian dari proyek pakan ikan otomatis:

![Schema![skema](https://github.com/user-attachments/assets/e2457738-0a50-4ef8-8cfc-b098b79187a9)
tic](skema.jpg)

> **Catatan**: Pastikan komponen terhubung dengan benar agar sistem berjalan dengan lancar.

## Lisensi

Proyek ini menggunakan **MIT License**. Lihat file `LICENSE` untuk detail lebih lanjut.

