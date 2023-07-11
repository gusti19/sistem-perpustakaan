#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>

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
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

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
            // Periksa apakah judul buku kosong
            if (!judul.empty()) {
                Buku buku;
                buku.judul = judul;
                buku.status = status;
                daftarBuku.push_back(buku);
            }
        }
        file.close();
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
            file << buku.judul << ",Tersedia" << endl;
        }
        file.close();
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
void pinjamBuku(string judul) {
    cout << "Metode Peminjaman Buku:" << endl;
    cout << "1. Masukkan keyword" << endl;
    cout << "2. Pilih berdasarkan urutan nomor" << endl;

    int metode;
    cout << "Pilih metode: ";
    cin >> metode;
    cin.ignore();

    if (metode == 1) {
        cout << "Masukkan keyword judul buku yang ingin dipinjam: ";
        getline(cin >> ws, judul);
    } else if (metode == 2) {
        // Tampilkan daftar buku
        tampilkanBuku();

        cout << "Masukkan nomor urutan buku yang ingin dipinjam: ";
        int nomor;
        cin >> nomor;
        cin.ignore();

        if (nomor >= 1 && nomor <= daftarBuku.size()) {
            // Ambil judul buku dari daftarBuku
            judul = daftarBuku[nomor - 1].judul;
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
        if (buku.judul == judul && buku.status == "Tersedia") {
            buku.status = "Terpinjam";
            found = true;
            break;
        }
    }

    if (found) {
        cout << "\nBuku berhasil dipinjam!" << endl;
        simpanDataBuku();
    } else {
       cout << "\nBuku tidak tersedia atau tidak ditemukan." << endl;
    }
}

// Fungsi untuk mengembalikan buku
void kembalikanBuku(string judul) {
    string kembalikanBuku();
    cout << "Metode Pengembalian Buku:" << endl;
    cout << "1. Masukkan judul buku" << endl;
    cout << "2. Pilih berdasarkan urutan nomor" << endl;

    int metode;
    cout << "Pilih metode: ";
    cin >> metode;
    cin.ignore();

    if (metode == 1) {
        string judul;
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
    } else if (metode == 2) {
        tampilkanBuku();

        cout << "Masukkan nomor urutan buku yang ingin dikembalikan: ";
        int nomor;
        cin >> nomor;
        cin.ignore();

        if (nomor >= 1 && nomor <= daftarBuku.size()) {
            string judul = daftarBuku[nomor - 1].judul;

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
        } else {
            cout << "Nomor urutan buku tidak valid." << endl;
        }
    } else {
        cout << "Pilihan metode tidak valid." << endl;
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

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void kop()
{
    
    SetConsoleTextAttribute(h,2);
    cout << "=============================================================\n||" ;
    SetConsoleTextAttribute(h,6);
    cout << "                    PERPUSTAKAAN v2.0                    " ;
    SetConsoleTextAttribute(h,2);
    cout << "||\n=============================================================" <<endl;
    
    for (int y = 3; y < 18 ; y++)
    {
        gotoxy(0,y);
        cout << "||";
        gotoxy(59,y);
        cout << "||";
    }   
    gotoxy(0,18);cout << "=============================================================" <<endl;
    SetConsoleTextAttribute(h,7); 
}

int main() {
    
    bacaDataAnggota();
    bacaDataBuku();

    bool isLoggedIn = false;
    bool isAdmin = false;
    string nim;
    string namaUser;

    while (true) {
        if (isLoggedIn) {
            
            if (isAdmin) {
            	system("cls");
                kop();
                SetConsoleTextAttribute(h,6);
                gotoxy(3,3);cout << "Selamat datang, ";
                SetConsoleTextAttribute(h,4);
                cout << namaUser << "!" << endl;
                SetConsoleTextAttribute(h,7);
                gotoxy(3,5);cout << "Menu Admin:" << endl;
                gotoxy(3,6);cout << "1. Tambah Buku" << endl;
                gotoxy(3,7);cout << "2. Cari Buku" << endl;
                gotoxy(3,8);cout << "3. Tampilkan Buku" << endl;
                gotoxy(3,9);cout << "4. Tampilkan Anggota" << endl;
                gotoxy(3,10);cout << "5. Ganti Password" << endl;
                gotoxy(3,11);cout << "6. Keluar dari Program" << endl;
                gotoxy(3,12);cout << "7. Logout" << endl;
            } else {
            	system("cls");
                kop();
                SetConsoleTextAttribute(h,6);
                gotoxy(3,3);cout << "Selamat datang, ";
                SetConsoleTextAttribute(h,10);
                cout << namaUser << "!" << endl;
                SetConsoleTextAttribute(h,7);
                gotoxy(3,5);cout << "Menu User Mahasiswa:" << endl;
                gotoxy(3,6);cout << "1. Cari Buku" << endl;
                gotoxy(3,7);cout << "2. Tampilkan Buku" << endl;
                gotoxy(3,8);cout << "3. Pinjam Buku" << endl;
                gotoxy(3,9);cout << "4. Kembalikan Buku" << endl;
                gotoxy(3,10);cout << "5. Ganti Password" << endl;
                gotoxy(3,11);cout << "6. Keluar dari Program" << endl;
                gotoxy(3,12);cout << "7. Logout" << endl;
                
            }

            int pilihan;
            gotoxy(3,14);cout << "Pilih menu: ";
            cin >> pilihan;

            cin.ignore();

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
                    cout << "\nTekan enter untuk kembali ke menu" << endl;
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
                    cout << "\nTekan enter untuk kembali ke menu" << endl;
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
                    cout << "\nTekan enter untuk kembali ke menu" << endl;
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
                    cout << "\nTekan enter untuk kembali ke menu" << endl;
                    getch();
                    break;
                case 5:
                    system("cls");
                    if (isAdmin) {
                    	gantiPassword(nim);
                    } else {
                        gantiPassword(nim);
                    }
                    cout << "\nTekan enter untuk kembali ke menu" << endl;
                    getch();
                    break;
                case 6:
                    system("cls");
                    cout << "Terima kasih telah menggunakan program ini. Sampai jumpa!" << endl;
                    return 0;  
                case 7:
                	isLoggedIn = false;
                    system("cls");
                    cout << "Telah berhasil Logout. \nTekan enter untuk kembali ke menu utama" << endl;
                    getch();
                    system("cls");
                	break;                          
                default:
                    gotoxy(3,16);cout << "Pilihan tidak valid." << endl;
                    getch();
                    break;
                
            }
        } else {
            system("cls");
            kop();
            gotoxy(3,3);cout << "Daftar/Login:" << endl;
            gotoxy(3,5);cout << "1. Daftar" << endl;
            gotoxy(3,6);cout << "2. Login" << endl;
            gotoxy(3,7);cout << "3. Keluar dari Program" << endl;
            cout << endl;
            int pilihan;
            gotoxy(3,9);cout << "Pilih menu: ";
            cin >> pilihan;
            cout << endl;

            cin.ignore();

            switch (pilihan) {
                case 1:
                    {
                        system("cls");
                        kop();
                        string nama, nim, password;
                        gotoxy(3,3);cout << "Masukkan nama: ";
                        getline(cin >> ws, nama);
                        gotoxy(3,4);cout << "Masukkan NIM: ";
                        getline(cin >> ws, nim);
                        gotoxy(3,5);cout << "Masukkan password: ";
                        getline(cin >> ws, password);

                        Anggota anggota;
                        anggota.nama = nama;
                        anggota.nim = nim;
                        anggota.password = password;
                        daftarAnggota.push_back(anggota);
                        simpanDataAnggota();
                        
                        gotoxy(3,8);cout << "Registrasi berhasil!" << endl;
                        getch();
                        system("cls");
                    }
                    break;
                case 2:
					{
                        system("cls");
                        kop();
					    string inputNIM, inputPassword;
					    gotoxy(3,3);cout << "Masukkan NIM: ";
					    getline(cin >> ws, inputNIM);
					    gotoxy(3,4);cout << "Masukkan password: ";
					    getline(cin >> ws, inputPassword);
					
					    isAdmin = (inputNIM == "admin");
					    isLoggedIn = login(inputNIM, inputPassword, isAdmin);
					    if (isLoggedIn) {
					        nim = inputNIM;
					        gotoxy(3,7);cout << "Login berhasil!" << endl;
                            
					        // Mencari nama user berdasarkan NIM
					        for (const auto& anggota : daftarAnggota) {
					            if (anggota.nim == inputNIM) {
					                namaUser = anggota.nama;
					                break;
					            }
					        }
					        getch();
                            system("cls");
					    } else {
					        gotoxy(3,7);cout << "NIM atau password salah." << endl;
					        getch();
					        system("cls");
					    }
					}
					break;

                case 3:
                    system("cls");
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
