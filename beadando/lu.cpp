#include "mathhelpers.h"

Vector initPVector ( int n ) {
    Vector vector;
    for ( int i = 0; i < n; i++ ) {
        vector.push_back ( i+1 );
    }
    return vector;
}

Vector P;
Matrix matrix;

void pivotize ( int actualCol ) {
    int n = matrix.size();
    double maxValue = 0.0;
    int row = actualCol;
    for ( int i = actualCol; i < n; i++ ) {
        if ( fabs ( matrix[i][actualCol] ) > maxValue ) {
            maxValue = fabs ( matrix[i][actualCol] );
            row = i;
        }
    }
    if ( maxValue > 0.0 ) {
        double tmp = P[actualCol];
        P[actualCol] = P[row];
        P[row] = tmp;
        for ( int i = 0; i< n; i++ ) {
            double tmp = matrix[actualCol][i];
            matrix[actualCol][i] = matrix[row][i];
            matrix[row][i] = tmp;
        }
    }
}

void LU() {
    int n = matrix.size();
    for ( int k = 0; k < n; k++ ) {
        std::cout << std::endl;
        print ( matrix );
        pivotize ( k );
        print ( matrix );
        std::cout << std::endl;
        for ( int i = k + 1; i < n; i++ ) {
            std::cout << matrix[i][k] << " = " << matrix[i][k] << " / " << matrix[k][k] << "// ";
            matrix[i][k] = matrix[i][k] / matrix[k][k];
            std::cout << matrix[i][k] << std::endl;
            for ( int j = k + 1; j < n; j++ ) {
                std::cout << matrix[i][j] << " = " << matrix[i][j] << " - " << matrix[i][k] << " * " << matrix[k][j] << "// ";
                matrix[i][j] = matrix[i][j] - matrix[i][k] * matrix[k][j];
                std::cout << matrix[i][j] << std::endl;
            }
        }
    }
    
}

int main() {

    int n,m;
    std::cin >> n;
    P = initPVector ( n );
    matrix = readMatrix ( n,n );
    print ( matrix );
    LU();
    print ( P );
    return 0;
}


