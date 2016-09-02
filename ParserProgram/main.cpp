#include <parser.h>

int main(int argc, char *argv[]){

    try{

        Pr::ParserProgram pr("parse.txt");
        //pr.writeToFile("out.txt");
        pr.printTreeStructure();
    }
    catch(const std::invalid_argument &err){

        std::cerr << err.what();
        exit(1);
    }
    catch(const std::runtime_error &err){

        std::cerr << err.what();
        exit(1);
    }
    catch(const std::bad_alloc &err){

        std::cerr << err.what();
        exit(1);
    }


    return 0;
}
