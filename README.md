# Sistem Peminjaman Buku

Sistem Peminjaman Buku adalah program sederhana yang memungkinkan pengguna untuk mendaftar, login, mencari, meminjam, mengembalikan buku, dan mengubah password. Program ini menggunakan bahasa C++ dan menyimpan data anggota dan buku dalam file teks.

## Fitur

1. **Daftar**: Pengguna dapat mendaftar sebagai anggota baru dengan memasukkan nama, NIM, dan password.
2. **Login**: Pengguna dapat login dengan memasukkan NIM dan password yang telah terdaftar. Terdapat pilihan login sebagai admin (NIM = "admin") atau user mahasiswa.
3. **Cari Buku**: Pengguna dapat mencari buku berdasarkan judul menggunakan metode keyword atau memilih dari daftar buku yang ditampilkan.
4. **Tampilkan Buku**: Pengguna dapat melihat daftar buku yang tersedia beserta statusnya (tersedia/terpinjam).
5. **Pinjam Buku**: Pengguna dapat meminjam buku dengan memasukkan judul buku yang ingin dipinjam. Buku yang dipinjam akan otomatis berubah statusnya menjadi "terpinjam".
6. **Kembalikan Buku**: Pengguna dapat mengembalikan buku yang telah dipinjam dengan memasukkan judul buku yang ingin dikembalikan. Buku yang dikembalikan akan berubah statusnya menjadi "tersedia".
7. **Ganti Password**: Pengguna dapat mengubah password akun mereka.
8. **Logout**: Pengguna dapat keluar dari akun dan kembali ke menu utama.
9. **Menu Admin**: Jika login sebagai admin, terdapat menu tambahan untuk menambah buku, menampilkan buku, menampilkan anggota, dan mengganti password.
10. **Simpan Data**: Data anggota dan buku akan disimpan dalam file teks untuk penggunaan berikutnya.

## Penggunaan

1. Kompilasi program ini menggunakan kompiler C++.
2. Jalankan program dan ikuti instruksi yang ditampilkan di layar.
3. Pilih opsi yang tersedia untuk menggunakan fitur yang diinginkan.

## Catatan

- File `DaftarAnggota.txt` dan `DaftarBuku.txt` digunakan untuk menyimpan data anggota dan buku. Pastikan file-file ini ada di direktori yang sama dengan program.
- Program ini tidak memvalidasi masukan pengguna secara menyeluruh, sehingga pastikan memasukkan data yang valid sesuai dengan instruksi yang diberikan.

Sistem Peminjaman Buku ini dapat membantu Anda mengelola peminjaman buku dengan mudah dan efisien. Selamat menggunakan!
