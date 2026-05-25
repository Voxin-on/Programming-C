#include <iostream>
#include "TextFile.h"
#include "FormatRowFile.h"

using namespace std;

int main(){
    cout << "Loading file..." << endl;
    TextFile<FormatRowFile> file1("STARLINK/chirp_20210126_084300_003_out.dat");

    cout << "Read " << file1.data.size() << " formatted rows from file1." << endl;

    TextFile<FormatRowFile> file1_copy = file1;
    cout << "Copied to file1_copy. Rows count: " << file1_copy.data.size() << endl;

    cout << "Appending f2.txt to the data file" << endl;
    TextFile<FormatRowFile>::appendFileToFile("STARLINK/chirp_20210126_084300_003_out.dat","f2.txt");
    
    TextFile<FormatRowFile> file1_after_append("STARLINK/chirp_20210126_084300_003_out.dat");
    
    vector<string> files = {
        "STARLINK/chirp_20210126_084300_003_out.dat",
        "f2.txt"
    };

    cout << "Creating file with UNIQUE rows" << endl;
    TextFile<FormatRowFile>::createUniqueRowsFile(files, "unique_result.txt");

    cout << "Creating file with COMMON rows..." << endl;
    TextFile<FormatRowFile>::createCommonRowsFile(files, "common_result.txt");

    return 0;
}