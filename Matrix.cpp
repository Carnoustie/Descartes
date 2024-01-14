#include "Matrix.hpp"
// #include "Vector.hpp"
#include <cassert>
#include "math.h"

using namespace std;


//Contructor
Matrix::Matrix(int numRows, int numColumns){
  rows = numRows;
  columns = numColumns;
  Data = new double* [rows];
  for(int i=0; i<rows; i++){
    Data[i] = new double[columns];
  }
}



//Addition
Matrix Matrix::operator+(Matrix const otherMatrix){
  //assert here
  Matrix sum(rows,columns);
  for(int i=0; i<rows; i++){
    for(int j=0; j<columns; j++){
      sum.Data[i][j] = otherMatrix.Data[i][j] + Data[i][j];
    }
  }
  return sum;
}

//Subtraction
Matrix Matrix::operator-(Matrix const otherMatrix){
  //assert here
  Matrix difference(rows,columns);
  for(int i=0; i<rows; i++){
    for(int j=0; j<columns; j++){
      difference.Data[i][j] =  Data[i][j] - otherMatrix.Data[i][j];
    }
  }
  return difference;
}



//Matrix-Matrix Multiplication
Matrix Matrix::operator*(Matrix const M){
  Matrix matrixProduct(rows, M.columns);
  for(int i=0; i<rows; i++){
    for(int j=0; j<M.columns; j++){
      double element = 0;
      for(int k=0; k<columns; k++){
        element+= Data[i][k]*M.Data[k][j];
      }
      matrixProduct.Data[i][j] = element;
      element=0;
    }
  }
  return matrixProduct;
}

//Matrix-Vector Multiplication
Vector Matrix::operator*(Vector const x){
  Vector product(rows);
  double productElement;
  for(int i=0; i<rows; i++){
    productElement = 0;
    for(int j=0; j<columns; j++){
      productElement+=Data[i][j]*x[j];
    }
    product[i] = productElement;
  }
  return product;
}

//Element Access
double &Matrix::operator()(int row, int column) const{
  return Data[row][column];
}




//Transpose
Matrix Matrix::transpose(){
  Matrix transposed(columns, rows);
  for(int i=0; i<columns; i++){
    for(int j=0; j<rows; j++){
      transposed.Data[i][j] = Data[j][i];
    }
  }
  return transposed;
}

double Matrix::determinant(){
  // cout << "\n\n\nSubmatrix:";
  print();
  if(rows==2 && columns==2){
    return Data[0][0]*Data[1][1] - Data[0][1]*Data[1][0];
  }
  double sum=0.0;
    for(int i=0; i<columns; i++){
      double k = Data[0][i]*(pow(-1,i));
      // cout << "\n\n\nk:" << k;
      Matrix minorMatrix(columns-1,rows-1);
      for(int j=0;j<columns-1;j++){
        for(int u=0;u<rows-1;u++){
          int skip = (int) j>=i;
          minorMatrix.Data[u][j] = Data[u+1][j+skip];
        }
      }
      sum+=k*minorMatrix.determinant();
    }
    return sum;
  }




void Matrix::swapRows(int row1, int row2, int width){
  double temp;

  for(int k=0; k<width; k++){
    temp = Data[row1][k];
    Data[row1][k] = Data[row2][k];
    Data[row2][k] = temp;
  }

}

void Matrix::swapColumns(int col1, int col2, int height){
  double temp;

  for(int k=0; k<height; k++){
    temp = Data[k][col1];
    Data[k][col1] = Data[k][col2];
    Data[k][col2] = temp;
  }

}

void Matrix::LU_Decomposition(Matrix* L, Matrix* U, int n){
  double l;
  double a1;
  double a2;

  U = this;
  cout << "\n\n\nprints1: \n\n\n";
  (*U).print();
  for(int k=0; k<n-1;k++){
    (*L)(k,k) = 1;
    for(int i = k+1; i<n; i++){
      a2 = (*U)(k,k);
      a1 = (*U)(i,k);
      l = a1/a2;
      for(int q=k; q<n; q++){
        (*U)(i,q) = (*U)(i,q) - l*((*U)(k,q));
      }
      (*L)(i,k) = l;
    }
  }
  (*L)(n-1,n-1) = 1;

  // cout<< "\n\n\nprints:\n\n\n";
  // (*L).print();
  // cout << "\n\n\n";
  // (*U).print();

}




//   if(Data[0][0]==0){
//     for(int k=0; k<rows; k++){
//       if(Data[k][0]!=0){
//         tempMatrix.swapRows(0,k,columns);
//         double t = b[0];
//         b[0] = b[k];
//         b[k] = t;
//         break;
//       }
//     }
//   }
// }



Vector Matrix::solve(Vector b){
  assert(rows==columns); //Solver only for square matrices for now
  double det = abs((*this).determinant());
  assert(rows==columns && det >= 0.00001); //Solver only for square matrices for now



  Matrix tempMatrix = *this;
  int n = columns;

  // cout << "\n\n\nunswapped:\n\n\n";
  // tempMatrix.print();

  //ensure upper-leftmost elemnt is nonzero
  int k=0;
  if(Data[0][0]==0){
    for(int k=0; k<rows; k++){
      if(Data[k][0]!=0){
        tempMatrix.swapRows(0,k,columns);
        double t = b[0];
        b[0] = b[k];
        b[k] = t;
        break;
      }
    }
  }
  // cout << "\n\n\nswapped:\n\n\n";
  // tempMatrix.print();
  return b;
}




void Matrix::print(){
  cout << "\n\n\n";
  for(int i=0; i<rows; i++){
    cout << "[";
    for(int j=0; j<columns; j++){
    cout << "    " << Data[i][j] ;
  }
  cout << "   ]\n\n";
}
  return;
}


void Matrix::printMatrixInfo(){
  cout <<"\n\nNumber of rows: " << rows;
  cout <<"\n\nNumber of columns: " << columns;
}
