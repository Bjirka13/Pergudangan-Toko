#include <iostream>
using namespace std;

// Struct untuk menyimpan informasi barang
struct Barang
{
    int stok;
    int kode;
};

// Struct untuk menyimpan informasi pengiriman barang
struct PengirimanInfo
{
    int kodeBarang;
    int jumlah;
    PengirimanInfo* next; // Pointer untuk linked list
};

// Variabel global untuk menyimpan data barang
Barang barang;

// Fungsi untuk menampilkan menu
void tampilkanMenu()
{
    cout << "Selamat Datang di Sistem Pergudangan Toko Frans\n";
    cout << "Menu yang tersedia:\n";
    cout << "1. Cek Stok Barang\n";
    cout << "2. Tambah Stok Barang\n";
    cout << "3. Kurangi Stok Barang\n";
    cout << "4. Proses Pengiriman\n";
    cout << "5. Tampilkan Riwayat Pengiriman\n";
    cout << "6. Keluar\n";
}

// Fungsi untuk mengecek stok barang
void cekStok()
{
    cout << "Stok barang saat ini: " << barang.stok << " unit\n";
}

// Fungsi untuk menambah stok barang
void tambahStok()
{
    int jumlah;
    cout << "Masukkan jumlah barang yang ingin ditambahkan: ";
    cin >> jumlah;
    barang.stok += jumlah;
    cout << "Stok barang berhasil ditambahkan sebanyak " << jumlah << " unit.\n";
}

// Fungsi untuk mengurangi stok barang
void kurangiStok()
{
    int jumlah;
    cout << "Masukkan jumlah barang yang ingin dikurangkan: ";
    cin >> jumlah;

    if (jumlah > barang.stok)
    {
        cout << "Maaf, stok barang tidak mencukupi.\n";
    }
    else
    {
        barang.stok -= jumlah;
        cout << "Stok barang berhasil dikurangkan sebanyak " << jumlah << " unit.\n";
    }
}

// Fungsi untuk memproses pengiriman barang
void prosesPengiriman(PengirimanInfo* &head, int &jumlahPengiriman)
{
    PengirimanInfo* pengirimanData = new PengirimanInfo;

    cout << "Masukkan Kode Barang yang Akan Dikirim: ";
    cin >> pengirimanData->kodeBarang;

    cout << "Masukkan jumlah barang yang akan dikirim: ";
    cin >> pengirimanData->jumlah;

    if (pengirimanData->jumlah > barang.stok)
    {
        cout << "Maaf, stok barang tidak mencukupi untuk pengiriman.\n";
        delete pengirimanData;
    }
    else
    {
        barang.stok -= pengirimanData->jumlah;
        cout << "Pengiriman barang dengan Kode Barang " << pengirimanData->kodeBarang << " sebanyak " << pengirimanData->jumlah << " unit berhasil.\n";

        // Menambahkan pengiriman baru ke dalam linked list
        pengirimanData->next = head;
        head = pengirimanData;
        jumlahPengiriman++;
    }
}

// Fungsi untuk menampilkan riwayat pengiriman
void tampilkanRiwayatPengiriman(PengirimanInfo* head)
{
    if (head == nullptr)
    {
        cout << "Belum ada riwayat pengiriman barang.\n";
        return;
    }

    cout << "Riwayat Pengiriman Barang:\n";
    PengirimanInfo* current = head;
    while (current != nullptr)
    {
        cout << "Pengiriman barang dengan Kode Barang " << current->kodeBarang << " sebanyak " << current->jumlah << " unit\n";
        current = current->next;
    }
}

int main()
{
    barang.stok = 100;
    barang.kode = 123; // Contoh kode barang

    // Pointer untuk linked list riwayat pengiriman
    PengirimanInfo* riwayatPengiriman = nullptr;
    int jumlahPengiriman = 0;

    // Loop utama program
    while (true)
    {
        tampilkanMenu();

        int pilihan;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            cekStok();
            break;
        case 2:
            tambahStok();
            break;
        case 3:
            kurangiStok();
            break;
        case 4:
            prosesPengiriman(riwayatPengiriman, jumlahPengiriman);
            break;
        case 5:
            tampilkanRiwayatPengiriman(riwayatPengiriman);
            break;
        case 6:
            cout << "Terima kasih telah menggunakan sistem pergudangan barang. Sampai jumpa!\n";
            // Menghapus semua node dalam linked list sebelum keluar dari program
            while (riwayatPengiriman != nullptr)
            {
                PengirimanInfo* temp = riwayatPengiriman;
                riwayatPengiriman = riwayatPengiriman->next;
                delete temp;
            }
            return 0; // Keluar dari program
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }

    return 0;
}
