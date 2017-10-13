#include "mathhelpers.h"
#define foreach(a, b, c) for (int a = b; a < c; a++)
#define for_i foreach(i, 0, n)
#define for_j foreach(j, 0, n)
#define for_k foreach(k, 0, n)
#define for_ij for_i for_j
#define for_ijk for_ij for_k
#define _dim int n
#define _swap(x, y) { typeof(x) tmp = x; x = y; y = tmp; }
#define _sum_k(a, b, c, s) { s = 0; foreach(k, a, b) s+= c; }

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

bool isSingular ( Matrix matrix ) {
    for ( int i = 0; i< matrix.size(); i++ ) {
        if ( matrix[i][i] == 0.0 ) {
            return true;
        }
    }
    return false;
}

Matrix pivotize ( Matrix matrix ) {
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
            for ( int i = 0; i < matrix.size(); i++ ) {
                double tmp = pivoteMatrix[j][i];
                pivoteMatrix[j][i] = pivoteMatrix[row][i];
                pivoteMatrix[row][i] = tmp;
            }
        }
    }
    return pivoteMatrix;
}

Matrix pivotize2 ( Matrix matrix ) {
    Matrix pivoteMatrix = matrix;
    int n = matrix.size();
    for(int i = 0;i<n;i++){
      for (int j = 0;j < n;j+){
	pivoteMatrix[i][j] = i==j;
      }
    }
    for(int i = 0;i<n;i++){
      int maxJ = i;
      for(int j = 0;j < i;j++){
	if (fabs(matrix[j][i]) > )
      }
    }
    return pivoteMatrix;
}
/*
//PA kell meghivni
std::vector<Matrix> LUDecomposition ( Matrix matrix ) {
    Matrix l = initMatrix ( matrix.size() ), u = initMatrix ( matrix.size() );
    int n = matrix.size();
    for ( int j = 0; j < n; j++ ) {
        for ( int i = 0; i < j; i++ ) {
            double s1 = 0.0;
            for ( int k = 0; k < i - 1; ++k ) {
                s1 += u[k][j] * l[i][k];
            }
            u[i][j] = matrix[i][j] - s1;
        }
        for ( int i = j + 1; i < n; ++i ) {
            double s2 = 0.0;
            for ( int k = 0; k < j - 1; ++k ) {
                s2 += u[k][j] * l[i][k];
            }

            double dividend = matrix[i][j] - s2;
            double divisor = u[j][j];
            double res = dividend / divisor;
            if ( res != res ) {
                res = 0.666;
            }
            l[i][j] = res;

        }
    }
    print(l);
    print(u);
    std::vector<Matrix> result;
    result.push_back(l);
    result.push_back(u);
    return result;
}*/


//3. megoldás
//PA kell meghivni
std::vector<Matrix> LUDecomposition ( Matrix matrix ) {
    Matrix l = initMatrix ( matrix.size() ), u = initMatrix ( matrix.size() );
    int n = matrix.size();
    for (int i = 0;i< n;i++){
      l[i][i] = 1;
    }
    for (int i = 0;i< n;i++){
      for (int j = 0;j< n;j++){
	double s = 0.0;
	if (j <= i) {
	  for (int k = 0; k < j; k++){
	    s += l[j][k] * u[k][i];
	  }
	  u[j][i] = matrix[j][i] - s;
	}
	if (j >= i) {
	  for (int k = 0; k < i; k++){
	    s += l[j][k] * u[k][i];
	  }
	  l[j][i] = (matrix[j][i] - s) / u[i][i];
	}
      }
    }
    print(l);
    print(u);
    std::vector<Matrix> result;
    result.push_back(l);
    result.push_back(u);
    return result;
}

/*
std::vector<Matrix> LUDecomposition ( Matrix matrix ) {
    Matrix l = initMatrix(matrix.size()), u = initMatrix(matrix.size());
    int n = matrix.size();
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < n; j++ ) {
            if ( j < i )
                l[j][i] = 0;
            else {
                l[j][i] = matrix[j][i];
                for ( int k = 0; k < i; k++ ) {
                    l[j][i] = l[j][i] - l[j][k] * u[k][i];
                }
            }
        }
        for ( int j = 0; j < n; j++ ) {
            if ( j < i )
                u[i][j] = 0;
            else if ( j == i )
                u[i][j] = 1;
            else {
                u[i][j] = matrix[i][j] / l[i][i];
                for ( int k = 0; k < i; k++ ) {
                    u[i][j] = u[i][j] - ( ( l[i][k] * u[k][j] ) / l[i][i] );
                }
            }
        }
    }
    print(l);
    std::vector<Matrix> result;
    result.push_back(l);
    result.push_back(u);
    return result;
}

*/
int main() {

    int n,m;
    std::cin >> n;
    Matrix matrix = readMatrix ( n,n );
    /*while ( n != 0 ) {
        Matrix matrix;
        matrix = readMatrix ( n,n );
    std::cin >> m;
        for ( int vectorCounter = 0; vectorCounter < m; vectorCounter++ ) {
            Vector vector;
            vector = readVector ( n );

            }
    std::cout << m << std::endl;
    std::cin >> n;
        }*/
    return 0;
}


