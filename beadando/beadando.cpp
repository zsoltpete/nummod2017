#include "mathhelpers.h"

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
//         std::cout << std::endl;
    }
//     if ( pivoteMatrix.size() > 3 ) {
//         Vector tmp = pivoteMatrix[2];
//         pivoteMatrix[2] = pivoteMatrix[3];
//         pivoteMatrix[3] = tmp;
//     }
    std::vector<Matrix> result;
    Matrix vectorContainer;
    result.push_back ( pivoteMatrix );
    vectorContainer.push_back ( p );
    result.push_back ( vectorContainer );
    return result;
}

Matrix LU ( Matrix matrix ) {
    int n = matrix.size();
    Matrix result = matrix;
    for ( int k = 0; k < n; k++ ) {
        for ( int i = k + 1; i < n; i++ ) {
//             std::cout << result[i][k] << " = " << result[i][k] << " / " << result[k][k] << "// ";
            result[i][k] = result[i][k] / result[k][k];
//             std::cout << result[i][k] << std::endl;
            for ( int j = k + 1; j < n; j++ ) {
//                 std::cout << result[i][j] << " = " << result[i][j] << " - " << result[i][0] << " * " << result[0][j] << "// ";
                result[i][j] = result[i][j] - result[i][0] * result[0][j];
//                 std::cout << result[i][j] << std::endl;
            }
        }
    }
    return result;
}

Vector calculateBP ( Vector B, Vector P ) {
    Vector BP;
    for ( int i = 0; i < P.size(); i++ ) {
        BP.push_back ( B[P[i]] );
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
        Matrix matrix;
        matrix = readMatrix ( n,n );

        Vector P = initPVector ( n );
        std::vector<Matrix> container = pivotize ( matrix, P );
        Matrix A = container[0];
        P = container[1][0];
	std::cout << "A:" << std::endl;
        print ( A );
        if ( isSingular ( A ) ) {
            std::cout << "szingularis" << std::endl;
            std::cin >> m;
            for ( int vectorCounter = 0; vectorCounter < m; vectorCounter++ ) {
                Vector vector;
                vector = readVector ( n );

            }
        } else {
            Matrix lu = LU ( A );
	    std::cout << "LU:" << std::endl;
            print ( lu );
	    std::cout << "P:" << std::endl;
	    print(P);
	    std::cout <<  std::endl;
            std::cin >> m;
            for ( int vectorCounter = 0; vectorCounter < m; vectorCounter++ ) {
                Vector B;
                B = readVector ( n );
                Vector BP = calculateBP ( B, P );
                Matrix UniqeL = makeUniqL ( lu );
                Vector Y = calculateY ( UniqeL, BP );
                Vector X = calculateX ( lu, Y );
                print ( X );
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


