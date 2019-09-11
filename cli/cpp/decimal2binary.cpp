#include <iostream>
#include <sstream>

static void usage();
static std::string decimal2binary(int n);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage();
        return 0;
    }

    for (int i=1; i<argc; i++) {
        int n = atoi(argv[i]);
        std::cout 
            << "(" << n << ")10 = (" 
            << decimal2binary(n) << ")2" << std::endl;
    }

    return 0;
}

static void usage() {
    std::cout 
        << "Usage: tobinary <decimal number 1> <decimal number 2> ..." 
        << std::endl;
}

static std::string decimal2binary(int n) {
    int nbits = sizeof(n)*8 - 1;
    while (!(n & (1 << nbits)) && nbits > 0) {
        nbits --;
    }

    std::ostringstream oss; 

    while (nbits >= 0) {
        oss << ((n >> nbits) & 1);
        nbits --;
    }

    return oss.str();
}
