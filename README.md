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
4. Klik **Upload** untuk meng-upload kode ke ESP32.

### Pengoperasian ###
1. Setelah program di-upload, ESP32 akan mulai bekerja sesuai dengan waktu yang telah ditetapkan pada **Sensor DS3231**.
2. Sistem secara otomatis akan memberikan pakan pada ikan sesuai dengan jadwal yang telah diprogram.
3. **ESP32 Cam** akan memantau kondisi akuarium dan menampilkan gambar atau video secara real-time.
4. **LCD 16x2 L2C** akan menampilkan waktu dan status sistem.

## Schematic ##

Berikut adalah schematic rangkaian dari proyek pakan ikan otomatis:

![Schematic](schematic.png)

> **Catatan**: Pastikan komponen terhubung dengan benar agar sistem berjalan dengan lancar.

## Lisensi

Proyek ini menggunakan **MIT License**. Lihat file `LICENSE` untuk detail lebih lanjut.

