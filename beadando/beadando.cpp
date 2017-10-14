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
    for ( int j = 0; j < matrix.size(); j++ ) {
        int row = j;
        double val = 0.0;
        for ( int i = j; i < matrix.size(); i++ ) {
            double cand = fabs ( matrix[i][j] );
            if ( val < cand ) {
                val = cand;
                row = i;
            }
        }
        if ( j != row ) {
            double tmp = p[row];
            p[row] = p[j];
            p[j] = tmp;
            for ( int i = 0; i < matrix.size(); i++ ) {
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
        pivotize ( k );
        for ( int i = k + 1; i < n; i++ ) {
            matrix[i][k] = matrix[i][k] / matrix[k][k];
            for ( int j = k + 1; j < n; j++ ) {
                matrix[i][j] = matrix[i][j] - matrix[i][k] * matrix[k][j];
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
	  std::cout << sum <<  A[i][j] << " " <<  y[j] <<std::endl;
            sum += A[i][j] * y[j];
	    std::cout << sum <<  "EZ sum"<<std::endl;
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
    return x;
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
	    std::cout << "LU:"<< std::endl; 
	    
	     std::cout <<  std::endl;
            for ( int vectorCounter = 0; vectorCounter < m; vectorCounter++ ) {
                Vector B;
                B = readVector ( n );
                Vector BP = calculateBP ( B, P );
		std::cout << "BP:"<< std::endl; 
	    print(BP);
	     std::cout <<  std::endl;
                //Matrix UniqeL = makeUniqL ( matrix );
	     print(matrix);
                Vector Y = calculateY ( matrix, BP );
		std::cout << "Y:"<< std::endl; 
	    print(Y);
	     std::cout <<  std::endl;
		Vector X = calculateX ( matrix, Y );
                 print ( X );
		 std::cout <<  std::endl;
            }

        }

        std::cin >> n;
    }
    return 0;
}


