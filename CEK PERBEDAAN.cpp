#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <conio.h>
#include <cstdlib>

using namespace std;

struct Anggota {
    string nama;
    string nim;
    string password;
};

struct Buku {
    string judul;
    string status;
};

vector<Anggota> daftarAnggota;
vector<Buku> daftarBuku;


// Fungsi untuk membaca data anggota dari file
void bacaDataAnggota() {
    ifstream file("DaftarAnggota.txt");
    if (file) {
        string nama, nim, password;
        while (getline(file, nama, ',') && getline(file, nim, ',') && getline(file, password)) {
            Anggota anggota;
            anggota.nama = nama;
            anggota.nim = nim;
            anggota.password = password;
            daftarAnggota.push_back(anggota);
        }
        file.close();
    }
} 


// Fungsi untuk membaca data buku dari file
void bacaDataBuku() {
    ifstream file("DaftarBuku.txt");
    if (file) {
        string judul, status;
        while (getline(file, judul, ',') && getline(file, status)) {
            // Periksa apakah judul buku atau status buku kosong
            if (!judul.empty() && !status.empty()) {
                Buku buku;
                buku.judul = judul;
                buku.status = status;
                daftarBuku.push_back(buku);
            }
        }
        file.close();
    } else {
        cout << "Gagal membuka file DaftarBuku.txt." << endl;
    }
}


// Fungsi untuk menyimpan data anggota ke file
void simpanDataAnggota() {
    ofstream file("DaftarAnggota.txt");
    if (file) {
        for (const auto& anggota : daftarAnggota) {
            file << anggota.nama << "," << anggota.nim << "," << anggota.password << endl;
        }
        file.close();
    }
}



// Fungsi untuk menyimpan data buku ke file
void simpanDataBuku() {
    ofstream file("DaftarBuku.txt");
    if (file) {
        for (const auto& buku : daftarBuku) {
            file << buku.judul << "," << buku.status << endl;
        }
        file.close();
    } else {
        cout << "Gagal menyimpan data buku ke file DaftarBuku.txt." << endl;
    }
}



// Fungsi untuk login
bool login(string nim, string password, bool isAdmin) {
    for (const auto& anggota : daftarAnggota) {
        if (anggota.nim == nim && anggota.password == password) {
            if (isAdmin && nim == "admin") {
                return true;
            } else if (!isAdmin && nim != "admin") {
                return true;
            }
        }
    }
    return false;
}

// Fungsi untuk menambah buku
void tambahBuku() {
    string judul;
    cout << "Masukkan judul buku: ";
    getline(cin >> ws, judul);

    Buku buku;
    buku.judul = judul;
    buku.status = "Tersedia";
    daftarBuku.push_back(buku);
    
    cout << "Buku berhasil ditambahkan!" << endl;
    simpanDataBuku();
    
}

// Fungsi untuk menampilkan daftar buku
void tampilkanBuku() {
    cout << "Daftar Buku:" << endl;
    int nomor = 1;
    for (const auto& buku : daftarBuku) {
        if (!buku.judul.empty()) {  // Menambahkan kondisi untuk menghindari judul buku yang kosong
            cout << nomor << ". " << buku.judul << " - " << buku.status << endl;
            nomor++;
        }
    }
}


// Fungsi untuk menampilkan daftar anggota
void tampilkanAnggota() {
    cout << "Daftar Anggota:" << endl;
    int nomor = 1;
    for (const auto& anggota : daftarAnggota) {
        cout << nomor << ". " << anggota.nama << " - " << anggota.nim << endl;
        nomor++;
    }
}

// Fungsi untuk mencari buku berdasarkan keyword
void cariBuku(string keyword) {
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    bool found = false;
    for (const auto& buku : daftarBuku) {
        string judul = buku.judul;
        transform(judul.begin(), judul.end(), judul.begin(), ::tolower);

        if (judul.find(keyword) != string::npos) {
            cout << buku.judul << " - " << buku.status << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Buku tidak ditemukan." << endl;
    }
}

// Fungsi untuk pinjam buku
void pinjamBuku(string nim) {
    cout << "Metode Peminjaman Buku:" << endl;
    cout << "1. Masukkan keyword" << endl;
    cout << "2. Pilih berdasarkan urutan nomor" << endl;

    int metode;
    cout << "Pilih metode: ";
    cin >> metode;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string judul; // Tambahkan variabel judul di sini

    if (metode == 1) {
        cout << "Masukkan keyword judul buku yang ingin dipinjam: ";
        getline(cin >> ws, judul);

        // Ubah keyword menjadi lowercase
        transform(judul.begin(), judul.end(), judul.begin(), ::tolower);
    } else if (metode == 2) {
        // Tampilkan daftar buku
        tampilkanBuku();

        cout << "Masukkan nomor urutan buku yang ingin dipinjam: ";
        int nomor;
        cin >> nomor;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (nomor >= 1 && nomor <= daftarBuku.size()) {
	    // Ambil buku dari daftarBuku
	    Buku& buku = daftarBuku[nomor - 1];
	
	    if (buku.status == "Tersedia") {
	        judul = buku.judul;
	    } else {
	        cout << "Buku tidak tersedia." << endl;
	        return;
	    }
	} else {
	    cout << "Nomor urutan buku tidak valid." << endl;
	    return;
	}

    } else {
        cout << "Pilihan metode tidak valid." << endl;
        return;
    }

    bool found = false;
    for (auto& buku : daftarBuku) {
        // Ubah judul buku menjadi lowercase
        string judulBukuLower = buku.judul;
        transform(judulBukuLower.begin(), judulBukuLower.end(), judulBukuLower.begin(), ::tolower);

        // Hapus spasi di awal dan akhir status buku
        string statusBukuTrimmed = buku.status;
        statusBukuTrimmed.erase(0, statusBukuTrimmed.find_first_not_of(' '));
        statusBukuTrimmed.erase(statusBukuTrimmed.find_last_not_of(' ') + 1);

        if (judulBukuLower == judul && statusBukuTrimmed == "Tersedia") {
            buku.status = "Terpinjam";
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Buku berhasil dipinjam!" << endl;
        simpanDataBuku();
    } else {
        cout << "Buku tidak tersedia atau tidak ditemukan." << endl;
    }
}





// Fungsi untuk mengembalikan buku
void kembalikanBuku(string judul) {
    cout << "Masukkan judul buku yang ingin dikembalikan: ";
    getline(cin >> ws, judul);

    bool found = false;
    for (auto& buku : daftarBuku) {
        if (buku.judul == judul && buku.status == "Terpinjam") {
            buku.status = "Tersedia";
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Buku berhasil dikembalikan!" << endl;
        simpanDataBuku();
    } else {
        cout << "Buku tidak dalam status terpinjam atau tidak ditemukan." << endl;
    }
}

// Fungsi untuk mengganti password
void gantiPassword(string nim) {
    string newPassword;
    cout << "Masukkan password baru: ";
    getline(cin >> ws, newPassword);

    for (auto& anggota : daftarAnggota) {
        if (anggota.nim == nim) {
            anggota.password = newPassword;
            simpanDataAnggota();
            break;
        }
    }

    cout << "Password berhasil diubah!" << endl;
}



int main() {
    
    bacaDataAnggota();
    bacaDataBuku();

    bool isLoggedIn = false;
    bool isAdmin = false;
    string nim;

    while (true) {
        if (isLoggedIn) {
            if (isAdmin) {
            	
                cout << "\nMenu Admin:" << endl;
                cout << "1. Tambah Buku" << endl;
                cout << "2. Cari Buku" << endl;
                cout << "3. Tampilkan Buku" << endl;
                cout << "4. Tampilkan Anggota" << endl;
                cout << "5. Ganti Password" << endl;
                cout << "6. Keluar dari Program" << endl;
                cout << "7. Logout" << endl;
            } else {
            	//	system ("cls");
                cout << "\nMenu User Mahasiswa:" << endl;
                cout << "1. Cari Buku" << endl;
                cout << "2. Tampilkan Buku" << endl;
                cout << "3. Pinjam Buku" << endl;
                cout << "4. Kembalikan Buku" << endl;
                cout << "5. Ganti Password" << endl;
                cout << "6. Keluar dari Program" << endl;
                cout << "7. Logout" << endl;
            }

            int pilihan;
            cout << "\nPilih menu: ";
            cin >> pilihan;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (pilihan) {
                case 1:
                    system("cls");
                    if (isAdmin) {
                    	Buku buku;
                    	tambahBuku();
                    	daftarBuku.push_back(buku);
                        simpanDataBuku();
                        
                    } else {
                        string keyword;
                        cout << "Masukkan keyword: ";
                        getline(cin >> ws, keyword);
                        cariBuku(keyword);
                    }
                    cout << "Tekan enter untuk kembali ke menu" << endl;
                    getch();
                    break;
                case 2:
                    system("cls");
                     if (isAdmin){
                        string keyword;
                        cout << "Masukkan keyword: ";
                        getline(cin >> ws, keyword);
                            transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
                        cariBuku(keyword);
                    } else {
                    	tampilkanBuku();
					}
                    cout << "Tekan enter untuk kembali ke menu" << endl;
                    getch();
                    break;
                case 3:
                    system("cls");
                    if (isAdmin) 
					{
                        tampilkanBuku();                        
                    } 
					else {
                        pinjamBuku(nim);
                    }
                    cout << "Tekan enter untuk kembali ke menu" << endl;
                    getch();
                    break;
                case 4:
                    system("cls");
                    if (isAdmin) {
                    	tampilkanAnggota();
                    } else {
                    	kembalikanBuku(nim);
                    	simpanDataBuku();
                        
                    }
                    cout << "Tekan enter untuk kembali ke menu" << endl;
                    getch();
                    break;
                case 5:
                    system("cls");
                    if (isAdmin) {
                    	gantiPassword(nim);
                    } else {
                        gantiPassword(nim);
                    }
                    cout << "Tekan enter untuk kembali ke menu" << endl;
                    getch();
                    break;
                case 6:
                    system("cls");
                    cout << "Terima kasih telah menggunakan program ini. Sampai jumpa!" << endl;
                    return 0;  
                case 7:
                	isLoggedIn = false;
                    system("cls");
                    cout << "Telah berhasil Logout. Tekan enter untuk kembali ke menu utama" << endl;
                    getch();
                    system("cls");
                	break;                          
                default:
                    cout << "Pilihan tidak valid." << endl;
                    break;
                
            }
        } else {
            cout << "\nDaftar/Login:" << endl;
            cout << "1. Daftar" << endl;
            cout << "2. Login" << endl;
            cout << "3. Keluar dari Program" << endl;

            int pilihan;
            cout << "\nPilih menu: ";
            cin >> pilihan;
            cout << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (pilihan) {
                case 1:
                    {
                        string nama, nim, password;
                        cout << "Masukkan nama: ";
                        getline(cin >> ws, nama);
                        cout << "Masukkan NIM: ";
                        getline(cin >> ws, nim);
                        cout << "Masukkan password: ";
                        getline(cin >> ws, password);

                        Anggota anggota;
                        anggota.nama = nama;
                        anggota.nim = nim;
                        anggota.password = password;
                        daftarAnggota.push_back(anggota);
                        simpanDataAnggota();
                        system("cls");

                        cout << "Registrasi berhasil!" << endl;
                    }
                    break;
                case 2:
					{
					    string inputNIM, inputPassword;
					    cout << "Masukkan NIM: ";
					    getline(cin >> ws, inputNIM);
					    cout << "Masukkan password: ";
					    getline(cin >> ws, inputPassword);
					
					    isAdmin = (inputNIM == "admin");
					    isLoggedIn = login(inputNIM, inputPassword, isAdmin);
					    if (isLoggedIn) {
					        nim = inputNIM;
					        system ("cls");
					        cout << "Login berhasil!" << endl;
					        cout << "==========================" << endl;
					        
					        // Mencari nama user berdasarkan NIM
					        string namaUser;
					        for (const auto& anggota : daftarAnggota) {
					            if (anggota.nim == inputNIM) {
					                namaUser = anggota.nama;
					                break;
					            }
					        }
					        
					        cout << "Selamat datang, " << namaUser << "!" << endl;
					    } else {
                            system("cls");
					        cout << "NIM atau password salah." << endl;
					    }
					}
					break;

                case 3:
                    cout << "Terima kasih telah menggunakan program ini. Sampai jumpa!" << endl;
                    return 0;
                default:
                    cout << "Pilihan tidak valid." << endl;
                    break;
            }
        }
    }

    return 0;
}
