/*  OOP Lab9
/*  The part with " // ... " means that is not complete.
 */

#include<iostream>
#include<iomanip>
using std::cout;    using std::endl;  using std::setw ; 

//=========================== Class ===========================//

//Abstract Class Mtx
template<class T>
class Mtx
{  
    public:
        virtual T& operator()(int i, int j) = 0;
        virtual void showMatrix() = 0;
        virtual ~Mtx(){}
};

//Abstract Class Triangular_Mtx
template<class T>
class Triangular_Mtx : public Mtx<T>
{  
    public:
        virtual T& operator()(int i, int j) = 0;
        virtual void showMatrix() = 0;
        virtual ~Triangular_Mtx(){}
        T **matrix;
        int dim;
};
template<class T>
class FullMatrix : public Mtx<T>{      
    public:
        FullMatrix(int n)
        {
            this->dim =n;
            this->matrix = new T*[n];
            for(int i=0;i<n;i++)
            {
                this->matrix[i] = new T[n]; 
            }
            for(int i=0;i<this->dim;i++)
            {
                for(int j=0;j<this->dim;j++)
                {
                    this->matrix[i][j] =0;
                }
            }
        }
        T& operator()(int i, int j);
        void showMatrix()
        {
            for(int i=0;i<this->dim;i++)
            {
                for(int j=0;j<this->dim;j++)
                {
                    cout<<setw(4)<<this->matrix[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        
    private:
        T **matrix;
        int dim;
};


// n x n Upper Triangle Matrix
template<class T>
class UpperTriMatrix : public Triangular_Mtx<T>
{
    
    public:
        UpperTriMatrix(int n)
        {
            this->dim =n;
            this->matrix = new T*[this->dim];
            for(int i=0;i<this->dim;i++)
            {
                this->matrix[i] = new T[this->dim];
            }
            for(int i=0;i<this->dim;i++)
            {
                for(int j=0;j<this->dim;j++)
                {
                    this->matrix[i][j] =0;
                }
            }
        }
        T& operator()(int i, int j)
        {
            return this->matrix[i][j];
        }
        void showMatrix()
        {
            
            for(int i=0;i<this->dim;i++)
            {
                for(int j=0;j<this->dim;j++)
                {
                    if(j<i)
                    {
                        cout<<setw(4)<<"0"<<" ";
                    }
                    else
                    cout<<setw(4)<<this->matrix[i][j]<<" ";
                }
                cout<<endl;
            }
        } 
};

//n x n Lower Triangle Matrix
template<class T>
class LowTriMatrix : public Triangular_Mtx<T>
{
    
    public:
        LowTriMatrix(int n)
        {
            this->dim =n;
            this->matrix = new T*[this->dim];
            for(int i=0;i<this->dim;i++)
            {
                this->matrix[i] = new T[this->dim];
            }
            for(int i=0;i<this->dim;i++)
            {
                for(int j=0;j<this->dim;j++)
                {
                    this->matrix[i][j] =0;
                }
            }
        }
        T& operator()(int i, int j)
        {
            return this->matrix[i][j];
        }
        void showMatrix()
        {
            
            for(int i=0;i<this->dim;i++)
            {
                for(int j=0;j<this->dim;j++)
                {
                    if(j>i)
                    {
                        cout<<setw(4)<<"0"<<" ";
                    }
                    else
                    cout<<setw(4)<<this->matrix[i][j]<<" ";
                }
                cout<<endl;
            }
        }
};

template<class T>
T& FullMatrix<T>::operator()(int i, int j){
    // boundary checking
    if(i >= dim || j >= dim){
        cout << "error : matrix boundary check violation" << endl;
        exit(-1);
    }

    return this->matrix[i][j];
}
template<class T>
T& Triangular_Mtx<T>::operator()(int i,int j)
{
    return this->matrix[i][j];
}





//===========================main function===========================//
int main(){
    FullMatrix<int  > A(2);
    A(0,0) = 5; A(0,1) = 4; A(1,0) = 3; A(1,1) = 6; 
	  //A.showMatrix() ; 
	  //cout << endl ; 
    
    LowTriMatrix<int> B(2);
    B(0,0) = 1; B(0,1) = 2; B(1,0) = 3; B(1,1) = 4; 
	  //B.showMatrix() ; 
	  //cout << endl ;  
	
    UpperTriMatrix<int> C(3);
    C(0,0) = 1; C(0,1) = 2; C(0,2) = 4;
    C(1,1) = 3; C(1,2) = 5; C(2,2) = 6;
	  //C.showMatrix() ; 
	  //cout << endl ;
	
    LowTriMatrix<double> D(3);
    D(0,0) = 9.1; D(1,0) = 8.3; D(2,0) = 7.1;
    D(1,1) = 6.2; D(2,1) = 5.5; D(2,2) = 4.2;
	  //D.showMatrix() ; 
	  //cout << endl ;

    UpperTriMatrix<double> E(3);
    E(0,0) = 1.3; E(1,0) = 2.2; E(2,0) = 4.7;
    E(1,1) = 3.5; E(2,1) = 5.9; E(2,2) = 6.1; 
	  //E.showMatrix() ; 
	  //cout << endl ;

    LowTriMatrix<double> F(3);
    F(0,0) = 9.7; F(0,1) = 8.1; F(0,2) = 7.1;
    F(1,1) = 6.5; F(1,2) = 5.5; F(2,2) = 4.3;
     //F.showMatrix() ; 
	 //cout << endl ;


    Mtx<int> *vecA[3];
    vecA[0] = &A; vecA[1] = &B; vecA[2] = &C; 
    for (int i = 0; i < 3; ++i) {
        vecA[i]->showMatrix(); cout << endl;
    }

    Mtx<double> *vecB[3];
    vecB[0] = &D; vecB[1] = &E; vecB[2] = &F;
    for (int i = 0; i < 3; ++i) {
        vecB[i]->showMatrix(); cout << endl;
    }

    return 0;
}