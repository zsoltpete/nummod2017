#include "mathhelpers.h"

int main() {

    int n,m;
    std::cin >> n;
    while ( n != 0 ) {
      singular = false;
        matrix = readMatrix ( n,n );
        P = initPVector ( n );
        std::vector<Matrix> container = pivotize ( matrix, P );
        Matrix checkSingularyA = container[0];

        LU();
        if ( singular ) {
            std::cout << "szingularis" << std::endl;
	    std::cin >> m;
	    for ( int vectorCounter = 0; vectorCounter < m; vectorCounter++ ) {
                Vector B;
                B = readVector ( n );
	    }
        } else {

            std::cin >> m;
// 	    std::cout << "LU:"<< std::endl;

// 	     std::cout <<  std::endl;
            for ( int vectorCounter = 0; vectorCounter < m; vectorCounter++ ) {
                Vector B;
                B = readVector ( n );
                Vector BP = calculateBP ( B, P );
// 		std::cout << "BP:"<< std::endl;
// 	    print(BP);
// 	     std::cout <<  std::endl;
                //Matrix UniqeL = makeUniqL ( matrix );
// 	     print(matrix);
                Vector Y = calculateY ( matrix, BP );
// 		std::cout << "Y:"<< std::endl;
// 	    print(Y);
// 	     std::cout <<  std::endl;
                Vector X = calculateX ( matrix, Y );
                print ( X );
                std::cout <<  std::endl;
            }
        }
        std::cout <<  std::endl;
        std::cin >> n;

    }
    return 0;

}