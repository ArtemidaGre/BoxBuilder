/*#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <filesystem>


int main(int argc, char* argv[]) {
    if (argc >= 3) {
        std::string arg1 = argv[1];
        std::string arg2 = argv[2];
        std::string arg3 = argc >= 4 ? argv[3] : "";

        if (arg1 == "-s" && argc >= 2) {
            std::string scssDir = arg2;
            std::string tsDir = argv[3];
            std::string outputDir = argv[4];

            std::string stylesDir = outputDir + "/styles";
            std::string jsDir = outputDir + "/js";

            std::string mkdirStylesCommand = "mkdir -p " + stylesDir;
            std::string mkdirJsCommand = "mkdir -p " + jsDir;

            std::system(mkdirStylesCommand.c_str());
            std::system(mkdirJsCommand.c_str());

            std::string scssCommand = "sass --style=compressed --update --sourcemap=none --watch " + scssDir + "/:" + stylesDir + "/";
            std::system(scssCommand.c_str());

            std::string tsCommand = "tsc --outDir " + jsDir + " " + tsDir + "/*.ts --removeComments --pretty";
            std::system(tsCommand.c_str());

            std::cout << "Build complete!" << std::endl;
        } else if (arg1 == "-js" && argc >= 2) {
            std::string tsDir = arg2;
            std::string outputDir = arg3;

            std::string jsDir = outputDir + "/js";
            std::string mkdirJsCommand = "mkdir -p " + jsDir;

            std::system(mkdirJsCommand.c_str());

            std::string tsCommand = "tsc --outDir " + jsDir + " " + tsDir + "/*.ts --removeComments --pretty";
            std::system(tsCommand.c_str());

            std::cout << "Build complete!" << std::endl;
        } else if (arg1 == "-scss" && argc >= 2) {
            std::string scssDir = arg2;
            std::string outputDir = arg3;

            std::string stylesDir = outputDir + "/styles";
            std::string mkdirStylesCommand = "mkdir -p " + stylesDir;

            std::system(mkdirStylesCommand.c_str());

            std::string scssCommand = "sass --style=compressed --update --sourcemap=none --watch " + scssDir + "/:" + stylesDir + "/";
            std::system(scssCommand.c_str());

            std::cout << "Build complete!" << std::endl;
        }else if (arg1 == "build" && argc >= 2){
            
        } 
        else {
            std::cout << "Invalid arguments." << std::endl;
            return 1;
        }
    } else {
        std::string scssDir;
        std::string tsDir;
        std::string outputDir;

        std::cout << "Enter the path to the SCSS folder: ";
        std::getline(std::cin, scssDir);

        std::cout << "Enter the path to the TS folder: ";
        std::getline(std::cin, tsDir);

        std::cout << "Enter the path to the output folder: ";
        std::getline(std::cin, outputDir);

        std::string stylesDir = outputDir + "/styles";
        std::string jsDir = outputDir + "/js";

        std::string mkdirStylesCommand = "mkdir -p " + stylesDir;
        std::string mkdirJsCommand = "mkdir -p " + jsDir;

        std::system(mkdirStylesCommand.c_str());
        std::system(mkdirJsCommand.c_str());

        std::string scssCommand = "sass --style=compressed --update --sourcemap=none --watch " + scssDir + "/:" + stylesDir + "/";
        std::system(scssCommand.c_str());

        std::string tsCommand = "tsc --outDir " + jsDir + " " + tsDir + "/*.ts --removeComments --pretty";
        std::system(tsCommand.c_str());

        std::cout << "Build complete!" << std::endl;
    }

    return 0;
}
*/



#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;

void createDirectory(const std::string& directoryPath) {
    if (!fs::exists(directoryPath)) {
        fs::create_directories(directoryPath);
    }
}

void buildSCSS(const std::string& scssDir, const std::string& outputDir, const bool& newFolder = true) {
    std::string scssCommand;
    std::cout << "Build SCSS started..." << std::endl;
    if (newFolder){
        std::string stylesDir = outputDir + "/styles";
        createDirectory(stylesDir);
        std::string scssCommand = "sass --style=compressed --update --sourcemap=none --watch " + scssDir + "/:" + stylesDir + "/";
        if (std::system(scssCommand.c_str()) != 0) {
            std::cout << "Error: SASS compilation failed." << std::endl;
            std::exit(1);
        }else{
            std::cout << "Build complete!" << std::endl;
        }
    }else{
        std::string scssCommand = "sass --style=compressed --update --sourcemap=none --watch " + scssDir + "/:" + outputDir + "/";
        if (std::system(scssCommand.c_str()) != 0) {
            std::cout << "Error: SASS compilation failed." << std::endl;
            std::exit(1);
        }else{
            std::cout << "Build complete!" << std::endl;
        }
    }
}

void buildJS(const std::string& tsDir, const std::string& outputDir,const bool newFolder = true) {
    std::string tsCommand;
    std::cout << "Build TS started..." << std::endl;
    if (newFolder){
        std::string jsDir = outputDir + "/js";
        createDirectory(jsDir);
        std::string tsCommand = "tsc --outDir " + jsDir + " " + tsDir + "/*.ts --removeComments --pretty";
        if (std::system(tsCommand.c_str()) != 0) {
            std::cout << "Error: TypeScript compilation failed." << std::endl;
            std::exit(1);
        }else{
            std::cout << "Build complete!" << std::endl;
        }
    }else{
        std::string tsCommand = "tsc --outDir " + outputDir + " " + tsDir + "/*.ts --removeComments --pretty";
        if (std::system(tsCommand.c_str()) != 0) {
            std::cout << "Error: TypeScript compilation failed." << std::endl;
            std::exit(1);
        }else{
            std::cout << "Build complete!" << std::endl;
        }
    }

    
}

int main(int argc, char* argv[]) {
    std::string configFile = ".bbldcfg";
    std::ifstream bbldcfg(configFile);
    
    if (bbldcfg.is_open()) {
        std::string line;
        std::string scssDir;
        std::string tsDir;
        std::string outputDir;
        std::string outScssDir;
        std::string outJsDir;
        
        while (std::getline(bbldcfg, line)) {
            std::istringstream iss(line);
            std::string key, value;
            std::getline(iss, key, ':');
            std::getline(iss, value);
            /*std::cout << key + ":" + value << std::endl;
            std::cout << key[0] << std::endl;*/
            if (!(key[0]=='#')){
                if (key == "scss") {
                    scssDir = value;
                } else if (key == "ts") {
                    tsDir = value;
                } else if (key == "out") {
                    outputDir = value;
                } else if (key == "out_scss"){
                    outScssDir = value;
                } else if (key == "out_js"){
                    outJsDir = value;
                }
            }else{
                //std::cout <<"comm in "+key+":"+value << std::endl;
            }
        }
        if (!scssDir.empty() && !tsDir.empty()){
            if (!outScssDir.empty() && !outJsDir.empty()){
                buildSCSS(scssDir, outScssDir);
                buildJS(tsDir, outJsDir);
            }else if (!outputDir.empty()){
                if (!outScssDir.empty() && outJsDir.empty()){
                    buildSCSS(scssDir, outScssDir, false);
                    buildJS(tsDir, outputDir);
                }else if (outScssDir.empty() && !outJsDir.empty()){
                    buildSCSS(scssDir, outputDir);
                    buildJS(tsDir, outJsDir, false);
                }else if (!outScssDir.empty() && !outJsDir.empty()){
                    buildSCSS(scssDir, outScssDir, false);
                    buildJS(tsDir, outJsDir, false);
                }
                else{
                    buildSCSS(scssDir, outputDir);
                    buildJS(tsDir, outputDir);
                }
            }else{
                std::cout << "Error: Invalid configuration file format ." << std::endl;
                return 1;
            }
        } else if (!tsDir.empty() && (!outputDir.empty() || !outJsDir.empty())){
            if (!outputDir.empty() && outJsDir.empty()){
                buildJS(tsDir, outputDir);
            }
            else{
                buildJS(tsDir, outJsDir, false);
            }
        }else if (!scssDir.empty() && (!outputDir.empty() || !outScssDir.empty())){
            if (!outputDir.empty() && outScssDir.empty()){
                buildSCSS(scssDir, outputDir);
            }else{
                buildSCSS(scssDir, outScssDir, false);
            }
        }
        else {
            std::cout << "Error: Invalid configuration file format." << std::endl;
            return 1;
        }
        
        bbldcfg.close();
    } else if (argc >= 3) {
        std::string arg1 = argv[1];
        std::string arg2 = argv[2];

        if (arg1 == "-scss") {
            std::string scssDir = arg2;
            std::string outputDir = argc >= 4 ? argv[3] : "";

            buildSCSS(scssDir, outputDir, false);
        } else if (arg1 == "-js") {
            std::string tsDir = arg2;
            std::string outputDir = argc >= 4 ? argv[3] : "";

            buildJS(tsDir, outputDir, false);
        } else {
            std::cout << "Invalid arguments." << std::endl;
            return 1;
        }
    } else {
        std::cout << "Error: No valid configuration file or command-line arguments found." << std::endl;
        return 1;
    }

    return 0;
}
