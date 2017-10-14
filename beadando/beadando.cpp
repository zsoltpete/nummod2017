#include "mathhelpers.h"

Matrix matrix;
Vector P;

Matrix initMatrix ( int n ) {
    Matrix result;
    for ( int i = 0; i< n; i++ ) {
        Vector vector;
        for ( int i = 0; i< n; i++ ) {
            vector.push_back ( 0.0 );
        }
        result.push_back ( vector );
    }
    return result;
}

Vector initVector ( int n ) {
    Vector vector;
    for ( int i = 0; i < n; i++ ) {
        vector.push_back ( 0 );
    }
    return vector;
}

Vector initPVector ( int n ) {
    Vector vector;
    for ( int i = 0; i < n; i++ ) {
        vector.push_back ( i+1 );
    }
    return vector;
}

bool isSingular ( Matrix matrix ) {
    for ( int i = 0; i< matrix.size(); i++ ) {
        if ( matrix[i][i] == 0.0 ) {
            return true;
        }
    }
    return false;
}

std::vector<Matrix> pivotize ( Matrix matrix, Vector p ) {
    Matrix pivoteMatrix = matrix;
    for ( int j = 0; j < pivoteMatrix.size(); j++ ) {
        int row = j;
        double val = 0.0;
        for ( int i = j; i < pivoteMatrix.size(); i++ ) {
            double cand = fabs ( pivoteMatrix[i][j] );
//             std::cout << "fabs: " << cand <<std::endl;
            if ( val < cand ) {
                val = cand;
                row = i;
            }
        }
        if ( j != row ) {
//             std::cout<< j <<row << std::endl;
            double tmp = p[row];
            p[row] = p[j];
            p[j] = tmp;
            for ( int i = 0; i < pivoteMatrix.size(); i++ ) {
                double tmp = pivoteMatrix[j][i];
                pivoteMatrix[j][i] = pivoteMatrix[row][i];
                pivoteMatrix[row][i] = tmp;
            }
        }
    }
    std::vector<Matrix> result;
    Matrix vectorContainer;
    result.push_back ( pivoteMatrix );
    vectorContainer.push_back ( p );
    result.push_back ( vectorContainer );
    return result;
}

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
//         print ( matrix );
        pivotize ( k );
//         print ( matrix );
//         std::cout << std::endl;
        for ( int i = k + 1; i < n; i++ ) {
//             std::cout << matrix[i][k] << " = " << matrix[i][k] << " / " << matrix[k][k] << "// ";
            matrix[i][k] = matrix[i][k] / matrix[k][k];
//             std::cout << matrix[i][k] << std::endl;
            for ( int j = k + 1; j < n; j++ ) {
//                 std::cout << matrix[i][j] << " = " << matrix[i][j] << " - " << matrix[i][k] << " * " << matrix[k][j] << "// ";
                matrix[i][j] = matrix[i][j] - matrix[i][k] * matrix[k][j];
//                 std::cout << matrix[i][j] << std::endl;
            }
        }
    }
    
}

Vector calculateBP ( Vector B, Vector P ) {
    Vector BP;
    for ( int i = 0; i < P.size(); i++ ) {
        BP.push_back ( B[P[i] - 1] );
    }
    return BP;
}

Vector calculateY ( Matrix A, Vector BP ) {
    int n = BP.size();
    Vector y = initVector ( n );
    for ( int i = 0; i < n; i++ ) {
        double sum = 0.0;
        for ( int j = 0; j < i; j++ ) {
            sum += A[i][j] * y[j];
        }
        y[i] = BP[i] - sum;
    }
    return y;
}

Vector calculateX ( Matrix A, Vector y ) {
    int n = y.size();
    Vector x = initVector ( n );
    for ( int i = n -1; i >= 0; i-- ) {
        double sum = 0.0;
        for ( int j = i+1; j < n; j++ ) {
            sum += A[i][j] * x[j];
        }
        
        x[i] = ( y[i] - sum ) / A[i][i];
    }
    return y;
}

Matrix makeUniqL ( Matrix matrix ) {
    Matrix result = matrix;
    for ( int i = 0; i < matrix.size(); i++ ) {
        result[i][i] = 1;
    }
    return result;
}

int main() {

    int n,m;
    std::cin >> n;
    while ( n != 0 ) {
        
        matrix = readMatrix ( n,n );

        P = initPVector ( n );
	std::vector<Matrix> container = pivotize ( matrix, P );
        Matrix checkSingularyA = container[0];
        if ( isSingular ( checkSingularyA ) ) {
            std::cout << "szingularis" << std::endl;
            std::cin >> m;
            for ( int vectorCounter = 0; vectorCounter < m; vectorCounter++ ) {
                Vector vector;
                vector = readVector ( n );

            }
        } else {
            LU();
            std::cin >> m;
            for ( int vectorCounter = 0; vectorCounter < m; vectorCounter++ ) {
                Vector B;
                B = readVector ( n );
// 		print(B);
                Vector BP = calculateBP ( B, P );
//  		print(matrix);
		std::cout <<  std::endl;
                Matrix UniqeL = makeUniqL ( matrix );
		//print(UniqeL);
                Vector Y = calculateY ( UniqeL, BP );
// // 		print(UniqeL);
//                 print(BP);
		std::cout <<  std::endl;
// 		print(Y);
		print(matrix);
		print(Y);
		Vector X = calculateX ( matrix, Y );
//                 print ( X );
                std::cout <<  std::endl;
		std::cout <<  std::endl;
            }

        }

        std::cin >> n;
    }

//     std::cout << std::endl;
//     Matrix lu = LU ( A );
//     print ( lu );
    return 0;
}


