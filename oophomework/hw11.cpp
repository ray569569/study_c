#include<iostream>
#include<fstream>
using namespace std;

template<class T>
class insert
{
private:
    int size;
    T* arr;
public:
    insert(int a,T* b)
    {
        size =a;
        arr = new T[size];
        for(int i=0;i<size;i++)
        {
            arr[i] = b[i];
        }
    }
    void intersectionSort();
    void printarr()
    {
        for(int i=0;i<size;i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
};
template<class T>
void insert<T>::intersectionSort() 
{
    T temp;
    for (int i = 0; i < size-1; i++) {
        for (int j = i+1; j < size; j++) {
            if (arr[j] < arr[i]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
};
int main(int argc,char* argv[])
{
    int n;
    string type;
    ifstream in;
    in.open("input.txt");
    in>>n>>type;
    
    if(type == "int")
    {
        int t[n];
        for(int i=0;i<n;i++)
        {
            in>>t[i];
        }
        insert<int> a(n,t);
        a.intersectionSort();
        a.printarr();
    }
    else if(type =="float")
    {
        float t[n];
        for(int i=0;i<n;i++)
        {
            in>>t[i];
        }
        
        insert<float> a(n,t);
        a.intersectionSort();
        a.printarr();
    }
    in.close();
    return 0;

}