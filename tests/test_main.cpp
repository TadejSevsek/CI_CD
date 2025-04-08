#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <fstream>

extern bool Branje_Stevil(std::vector<int>& vec, const char s[]);
extern void Izpis_Stevil(int* polje, unsigned int velikost);

void testAlgorithm(const char* algoFlag, const char* inputFile, const char* expectedOutputFile) {
    std::vector<int> vec;
    assert(Branje_Stevil(vec, inputFile));

    int* arr = new int[vec.size()];
    for (size_t i = 0; i < vec.size(); ++i) {
        arr[i] = vec[i];
    }

    // preusmerimo v začasni izpis zaradi prglednosti
    std::string tempOutput = "temp_output.txt";
    std::ofstream tempStream(tempOutput);
    std::streambuf* oldCout = std::cout.rdbuf(tempStream.rdbuf());

    // pokliče program z parametri
    char* args[] = {const_cast<char*>("program"), const_cast<char*>(algoFlag), const_cast<char*>(inputFile)};
    main(3, args);

    // vrnemo nazaj na standerden izpis
    std::cout.rdbuf(oldCout);
    tempStream.close();

    // primerja pridobljen izpis z pričakovanim
    std::ifstream tempOut(tempOutput);
    std::ifstream expectedOut(expectedOutputFile);

    std::string tempLine, expectedLine;
    while (std::getline(tempOut, tempLine) && std::getline(expectedOut, expectedLine)) {
        assert(tempLine == expectedLine);
    }

    // pobrišemo pointer
    delete[] arr;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: test_runner <algo_flag> <input_file> <expected_output_file>" << std::endl;
        return 1;
    }

    const char* algoFlag = argv[1];
    const char* inputFile = argv[2];
    const char* expectedOutputFile = argv[3];

    testAlgorithm(algoFlag, inputFile, expectedOutputFile);

    return 0;
}