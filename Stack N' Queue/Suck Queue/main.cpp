#include <iostream>
using namespace std;

//kapaitas maksimum dari index antrian atau queue
#define MaxEl 100

typedef int infotype;//untuk memberi inisial pada tipe data integer menjadi infotype agar tidak membingungkan saat mengoding

class Queue //queue diimplementasikan dengan class
{
public:                           //seluruh komponen antrian diletakkan di public agar bisa diakses
    int head, tail, address[MaxEl]; //deklarasikan komponen dari queuenya, yaitu head sebagai index first, tail sebagai index last, dan array sebagai tempat menampung queuenya
    Queue()                       //konstraktor dari classnya yang akan memberi nilai head, dan tail menjadi -1 / isinya masih kosong
    {
        head = -1;
        tail = -1;
    }
    void Allocation(infotype value); //deklarasikan fungsi Allocation
    void Deallocation();             //deklarasikan fungsi Deallocation
    void Print();                    //deklarasikan fungsi Print
};

//untuk meletakkan atau memasukkan infotype ke dalam list array
void Queue::Allocation(infotype value)
{
    if (this->head == -1) //jika queue masih kosong maka index pertama akan diset ke 0
    {
        this->head = 0;
    }
    address[++this->tail] = value; //dan index terakhirnya akan dimajukan 1 nomor kedepan
}

//untuk mengeksekusi proses penghapusan infotype dengan menggeser index head antrian
void Queue::Deallocation()
{
    if (this->tail != -1) //jika queue tidak kosong maka index pertama akan dimajukan 1 nomor
    {
        this->head++;
    }
}

//untuk menampilkan infotype dari array
void Queue::Print()
{
    for (int i = this->head; i <= this->tail; i++) //melakukan perulangan dari bagian head antrian ke pertama dan ditampilkan infotype dari array
    {
        cout << address[i];
    }
}

//untuk menambahkan list pada array
void Add(Queue *Q, Queue *MainQueue) 
{
    if (MainQueue->head <= MainQueue->tail) //jika index headnya tidak sampai melewati nilai dari index tailnya maka nilai index head akan selalu maju jika di Deallocation
    {
        if (MainQueue->address[MainQueue->head] > Q->address[Q->tail]) //jika nilai dari Secondary utamanya atau nilai yang mau dimasukan itu berurut atau lebih besar dari nilai sebelumnya maka
        {
            Q->Allocation(MainQueue->address[MainQueue->head]); //nilainya akan dimasukan kedalam queue
            MainQueue->Deallocation();                          //dan queue utamanya akan di Deallocation karena nilainya telah diambil
        }
    }
}

int main()
{
    Queue Primary; //deklarasikan queue utamanya
    int ManyCases; //jumlah data yang akan diinputkan

    cout << "Banyak Kasus: ";
    cin >> ManyCases;

    cout << "\nInput: " << endl;
    for (int i = 0; i < ManyCases; i++)
    {
        int x;
        cin >> x;
        Primary.Allocation(x); //masing masing data akan dimasukan sementara kedalam queue utama
    }
    Queue Secondary[3]; //deklarasikan 3 Secondary Queue yang akan menampung nilai dan memprosesnya secara berurut

    for (int i = 0; i < 3; i++) //masing masing Secondary Queue akan menerima input data
    {
        if (Secondary[i].tail == -1) //jika Secondary [i] masih kosong maka akan diisi terlebih dahulu agar memiliki nilai awal dan dapat dibandingkan datanya
        {
            Secondary[i].Allocation(Primary.address[Primary.head]);
            Primary.Deallocation();// setiap kali menginputkan nilai dari queue utamanya maka queue utamanya juga akan di Deallocation
        }
        while (Primary.address[Primary.head] > Secondary[i].address[Secondary[i].tail] && (Primary.head <= Primary.tail)) //dan melakukan perulangan selama data yang akan diinput ke dalam Secondary [i] lebih besar daripada data akhir dari Secondary[i] dan selama index headnya tidak melebihi index tailnya maka Secondary[i] akan di Allocation secara terus menerus
        {
            Add(&Secondary[i], &Primary);
        }
    }
    for (int i = 0; i < 3; i++) //pengecekkan ulang agar jika ada angka yang tersisa di queue utama tetapi masih bisa masuk ke salah satu Secondary [i]
    {
        Add(&Secondary[i], &Primary);
    }

    int i = 0; //sebagai index

    while (Primary.head < Primary.tail) //selama headnya tidak melebihi tailnya (index) yang artinya masih ada nilai di dalam queue utamanya maka nilai yang ada di dalam Secondary 1,2,3 akan dihapus dimulai dari yang paling kecil
    {
        if (Secondary[i].address[Secondary[i].head] > Secondary[i + 1].address[Secondary[i + 1].head]) //percabangan bersarang ini untuk case Secondary [i]
        {
            if (Secondary[i].address[Secondary[i].head] > Secondary[i + 2].address[Secondary[i + 2].head])
            {
                if (Secondary[i + 1].address[Secondary[i + 1].head] > Secondary[i + 2].address[Secondary[i + 2].head])
                {
                    Secondary[i + 2].Deallocation();
                    Primary.Deallocation();
                }
                else
                {
                    Secondary[i + 1].Deallocation();
                    Primary.Deallocation();
                }
            }
            else
            {
                Secondary[i].Deallocation();
                Primary.Deallocation();
            }
        }
        else if (Secondary[i + 1].address[Secondary[i + 1].head] > Secondary[i + 2].address[Secondary[i + 2].head] && Secondary[i + 2].head != Secondary[i + 2].tail + 1) //percabangan bersarang ini untuk case Secondary [i+1]
        {
            if (Secondary[i + 1].address[Secondary[i + 1].head] > Secondary[i].address[Secondary[i].head])
            {
                if (Secondary[i + 2].address[Secondary[i + 2].head] > Secondary[i].address[Secondary[i].head])
                {
                    Secondary[i].Deallocation();
                    Primary.Deallocation();
                }
                else
                {
                    Secondary[i + 2].Deallocation();
                    Primary.Deallocation();
                }
            }
            else
            {
                Secondary[i + 1].Deallocation();
                Primary.Deallocation();
            }
        }
        else if (Secondary[i + 2].address[Secondary[i + 2].head] > Secondary[i].address[Secondary[i].head]) //percabgan bersarang ini untuk case Secondary [i+2]
        {
            if (Secondary[i + 2].address[Secondary[i + 2].head] > Secondary[i + 1].address[Secondary[i + 1].head])
            {
                if (Secondary[i].address[Secondary[i].head] > Secondary[i + 1].address[Secondary[i + 1].head])
                {
                    Secondary[i + 1].Deallocation();
                    Primary.Deallocation();
                }
                else
                {
                    Secondary[i].Deallocation();
                    Primary.Deallocation();
                }
            }
            else
            {
                Secondary[i + 2].Deallocation();
                Primary.Deallocation();
            }
        }
        //kondisi jika terdapat data yang sama dengan data terkecilnya
        if (Secondary[i + 1].address[Secondary[i + 1].head] > Secondary[i].address[Secondary[i].head] && Secondary[i + 2].head > Secondary[i + 2].tail)
        {
            Secondary[i].Deallocation();
        }
        else if (Secondary[i + 1].address[Secondary[i + 1].head] > Secondary[i + 2].address[Secondary[2].head] && Secondary[i].head > Secondary[i].tail)
        {
            Secondary[i + 2].Deallocation();
        }
    }
    cout << "\nOutput: " << endl; //print data yang sudah di olah sesuai arahan soal
    for (int i = 0; i < 3; i++)
    {
        cout << "Antrian " << i + 1 << ":["; Secondary[i].Print(); cout << "]" << endl;
    }
}
