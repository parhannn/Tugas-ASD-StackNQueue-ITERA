#include <iostream>

using namespace std;

//kapasitas maksimum dari stack
#define MaxEl 100

typedef char infotype;//info dari list bertipe karakter
typedef struct TNodeStack *address;//sebagai alamat list


typedef struct TNodeStack
{
    //info isi data dari linked list
    infotype info;
    //alamat next dari linked list
    address next;
} NodeStack;

typedef struct TStack
{
    //alamat dari top atau bagian atas stack
    address top;
} Stack;

//prosedur membuat stack kosong atau stack baru
void CreateEmpty(Stack *S)
{
    (*S).top = NULL;
}

//pengecekan apakah stack dalam keadaan kosong atau tidak bertipe boolean
bool IsEmpty(Stack S)
{
    return (S).top == NULL;
}

//menghitung banyak tumpukan saat terkini
int CountStack(Stack S)
{
    address cur;
    int sum = 0;

    cur = S.top;
    while(cur != NULL)
    {
        sum++;
        cur = cur->next;
    }
    return sum;
}

//mengecek kondisi stack apakah dalam keadaan penuh atau tidak bertipe boolean
bool IsFull(Stack S)
{
    return (CountStack(S) == MaxEl);
}

//untuk mengalokasikan atau meletakkan info dari data yang akan dilist
address Allocation(infotype x)
{
    address NewNode;

    NewNode = new NodeStack;

    NewNode->info = x;
    NewNode->next = NULL;

    return NewNode;
}

//untuk mengeksekusi proses penghapusan list beserta isi infonya
void Deallocation(address del)
{
    delete del;
}

//untuk memasukkan info ke dalam tumpukan atau stack
void Push(Stack *S, infotype x)
{
    address NewNode;

    NewNode = Allocation(x);

    NewNode->next = (*S).top;
    (*S).top = NewNode;
}

//untuk menghapus list beserta infonya di dalam stack atau tumpukan
void Pop(Stack *S, infotype *del)
{
    if(!IsEmpty(*S))
    {
        address temp;

        temp = (*S).top;
        *del = temp->info;
        (*S).top = (*S).top->next;
        temp->next = NULL;

        Deallocation(temp);
    }
    else
    {
        cout << "Stack Kosong" << endl;
    }
}

//untuk mencetak semua info list dalam stack yang telah diproses
void Print(Stack S) {
    address tmp;

    tmp = S.top;

    while (tmp != NULL) 
    {
        cout << tmp->info << " ";

        tmp = tmp->next;
    }
}

//main
int main()
{
    infotype DeleteData;
    char tmp;
    int ManyCases;

    //input kasus
    cout << "Input: " << endl;
    cout << "Banyak Kasus: "; cin >> ManyCases;

    string x[ManyCases], Case;
    Stack DataTest[ManyCases];

    //pengecekan setiap karakter pada string sekaligus menjalankan proses push dan pop stack
    for(int i = 0; i < ManyCases; i++)
    {
        Case = x[i];
        CreateEmpty(&DataTest[i]);
        cout << "Masukkan String: "; cin >> Case;
        for (int j = 0; Case[j] != '\0'; j++)
        {
            tmp = Case[j];

            if(tmp >= '0' && tmp <= '9')
            {
                Push(&DataTest[i], tmp);
            }
            else if(tmp == '_')
            {
                Pop(&DataTest[i], &DeleteData);
            }
        }
    }

    //mencetak hasil dari pemrosesan inputan user 
    cout << "\nHasil Output: " << endl;
    for(int i = 0; i < ManyCases; i++)
    {
        Print(DataTest[i]);
        cout << endl;
    }
}
