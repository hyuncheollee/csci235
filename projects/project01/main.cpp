#include <iostream>
#include "FileUtils.hpp"

int main() {
    std::string fileName = "IMG_4096.png";
    std::string empty_string = "";
    std::string no_extension = "spotify";
    std::string weird_name = "weird.file.name.tar.gz";

    // TEST CASES FOR FILE EXTENSIONS
    std::cout << "TEST CASES FOR FILE EXTENSIONS" << std::endl;
    std::cout << "file extension: " << FileUtils::findFileExtension(fileName) << std::endl;
    std::cout << "empty string: " << FileUtils::findFileExtension(empty_string) << std::endl;
    std::cout << "no extension: " << FileUtils::findFileExtension(no_extension) << std::endl;
    std::cout << "weird long name: " << FileUtils::findFileExtension(weird_name) << std::endl;
    std::cout << std::endl;

    // init new simple errors
    std::string case1 = " ";
    std::string case2 = "a b";
    std::string case3 = "myfile.txt ";
    std::string case4 = " myfile.txt";

    // (\n, \v, \f, \r, \t)
    std::string caseN = "IMG_40\n96.png";
    std::string caseV = "IMG_40\v96.png";
    std::string caseF = "IMG_40\f96.png";
    std::string caseR = "IMG_40\r96.png";
    std::string caseT = "IMG_40\t96.png";

    // TEST CASES FOR WHITESPACES OLD
    std::cout << "TEST CASES FOR WHITESPACES OLD" << std::endl;
    std::cout << "file extension (should be 0): " << FileUtils::hasWhitespaces(fileName) << std::endl;
    std::cout << "empty string (should be 0): " << FileUtils::hasWhitespaces(empty_string) << std::endl;
    std::cout << "no extension (should be 0): " << FileUtils::hasWhitespaces(no_extension) << std::endl;
    std::cout << "weird long name (should be 0): " << FileUtils::hasWhitespaces(weird_name) << std::endl;
    std::cout << std::endl;

    // TEST CASES FOR WHITESPACES SIMPLE
    std::cout << "TEST CASES FOR WHITESPACES SIMPLE" << std::endl;
    std::cout << "just space: " << FileUtils::hasWhitespaces(case1) << std::endl;
    std::cout << "space in between: " << FileUtils::hasWhitespaces(case2) << std::endl;
    std::cout << "space at the end: " << FileUtils::hasWhitespaces(case3) << std::endl;
    std::cout << "space at the beginning: " << FileUtils::hasWhitespaces(case4) << std::endl;
    std::cout << std::endl;

    // TEST CASES FOR WHITESPACES /
    std::cout << "TEST CASES FOR WHITESPACES /" << std::endl;
    std::cout << "/n: " << FileUtils::hasWhitespaces(caseN) << std::endl;
    std::cout << "/v: " << FileUtils::hasWhitespaces(caseV) << std::endl;
    std::cout << "/f: " << FileUtils::hasWhitespaces(caseF) << std::endl;
    std::cout << "/r: " << FileUtils::hasWhitespaces(caseR) << std::endl;
    std::cout << "/t: " << FileUtils::hasWhitespaces(caseT) << std::endl;

    return 0;
}
