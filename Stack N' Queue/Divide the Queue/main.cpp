#include <iostream>

using namespace std;

//kapasitas maksimum dari queue atau antrian
#define MaxEl 100

typedef int infotype;//info dari list bertipe integer (bilangan bulat riil)
typedef struct TNodeQueue *address;//sebagai alamat dari list

typedef struct TNodeQueue
{
    //info isi data dari linked list
    infotype info;
    //alamat prev atau sebelumnya dari linked list
    address prev;
    //alamat next atau selanjutnya dari linked list
    address next;
} NodeQueue;


typedef struct TQueue
{
    //alamat dari antrian pertama queue
    address head;
    //alamat dari antrian terakhir queue atau sering orang lain menyebutnya ekor
    address tail;
} Queue;

//memberi inisial pada selector untuk mempermudah saat mengoding
#define Head(Q)    Q.head
#define Tail(Q)    Q.tail

//prosedur untuk membuat antrian kosong atau antrian baru
void CreateEmpty(Queue *Q)
{
    (*Q).head = NULL;
    (*Q).tail = NULL;
}

//mengecek antrian apakah dalam keadaan kosong atau tidak
bool IsEmpty(Queue Q)
{
    return ((Head(Q) == NULL) && (Tail(Q) == NULL));
}

//menghitung banyak antrian terkini
int NbNode(Queue Q)
{
    address cur;
    int sum = 0;

    cur = Q.head;
    while(cur != NULL)
    {
        sum++;
        cur = cur->next;
    }
    return sum;
}

//pengecekkan antrian apakah dalam keadaan penuh atau tidak
bool IsFull(Queue Q)
{
    return (NbNode(Q) == MaxEl);
}

//untuk mengalokasikan atau meletakkan info dari data yang akan dilist
address Allocation(infotype x)
{
    address NewNode;

    NewNode = new NodeQueue;

    NewNode->info = x;
    NewNode->next = NULL;
    NewNode->prev = NULL;

    return NewNode;
}

//untuk mengeksekusi proses penghapusan list beserta isi infonya
void Deallocation(address del)
{
    delete del;
}

//untuk menambahkan antrian pada queue, input data mulai dari belakang
void Add(Queue *Q, infotype x)
{
    address NewNode;

    NewNode = Allocation(x);

    NewNode->prev = (*Q).tail;

    if(!IsFull(*Q))
    {
        if(!IsEmpty(*Q))
            (*Q).tail->next = NewNode;
        else
            (*Q).head = NewNode;
        
        (*Q).tail = NewNode;
    }
    else
    {
        cout << "Antrian Penuh" << endl;
    }

}

//untuk menghapus list antrian terdepan beserta isi infonya
void Dell(Queue *Q, infotype *del)
{
    if(!IsEmpty(*Q))
    {
        address temp;

        temp = (*Q).head;
        *del = temp->info;

        if((*Q).head == (*Q).tail)
            (*Q).tail = NULL;
        else
            (*Q).head->next->prev = NULL;

        (*Q).head = (*Q).head->next;
        temp->next = NULL;

        Deallocation(temp);
    }
}

//untuk mencetak hasil pemrosesan data pada queue
void Print(Queue Q) {
    address tmp;

    tmp = Q.head;

    while (tmp != NULL) 
    {
        cout << tmp->info << " ";

        tmp = tmp->next;
    }
}

//main
int main()
{
    infotype del;
    int ManyCases, ManyQueue, Cases;

    //input banyak kasus dan banyak antrian yang ingin dibentuk dari pembagian banyak kasus
    cout << "Banyak Kasus: "; cin >> ManyCases;
    cout << "Banyak Antrean: "; cin >> ManyQueue;

    Queue DataQueue[ManyQueue];
    int x[ManyCases], tail, head = 0, batas;

    //input data antrian
    cout << "\nInput: " << endl;
    for(int i = 0; i < ManyCases; i++)
    {
        cin >> x[i];
    }

    batas = ManyCases/ManyQueue;//batas maksimum setiap antrian yang dibentuk
    tail = batas;//urutan ujung antrian sama dengan batas maksimum antrian
    //proses memasukkan data ke list info linked list dengan metode antrian atau queue
    for(int i = 0; i < ManyQueue; i++)
    {
        CreateEmpty(&DataQueue[i]);//buat antrian baru
        for(int j = head; j < tail; j++)
        {
            Add(&DataQueue[i], x[j]);//memasukkan info data ke antrian
        }
        //pemilihan index data antrian dari inputan user tadi
        head+=batas;
        tail+=batas;
    }

    //ouput hasil pemrosesan data
    cout << "\nOuput: " << endl;
    for(int i = 0; i < ManyQueue; i++)
    {
        Print(DataQueue[i]);
        cout << endl;
    }
}
