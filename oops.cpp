#include<iostream.h>
#include<fstream>
#include<conio.h>
//using namespace std;
class student_info
{
    char name[20];
    int age;
    char sex;
    float height;
    float weight;
public:
    void read();
    void write();
};

void student_info::read()
{
    cout << "Enter Name : ";
    cin >> name;
    cout << "Enter Age : ";
    cin >> age;
    cout << "Enter Gender(M/F) : ";
    cin >> sex;
    cout << "Enter Height(in cm) : ";
    cin >> height;
    cout << "Enter Weight(in kg) : ";
    cin >> weight;
};
void student_info::write()
{
    cout << "Name : " << name << endl;
    cout << "Age : " << age << endl;
    cout << "Gender : " << sex << endl;
    cout << "Height : " << height << "cm" << endl;
    cout << "Weight : " << weight << "kg" << endl ;
};

int main()
{
    int n;
    clrscr();
    cout << "Enter how many records are to be stored : ";
    cin >> n;
    student_info s[n];
    ofstream fout;
    fout.open("data.txt");
    for(int i = 0 ; i < n ; i++)
    {
        s[i].read();
        fout.write((char *)&s[i], sizeof(s[i]));
        s[i].write();
    }
    fout.close();
    getch;
    return 0;
}
