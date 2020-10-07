#include "main.ih"

int main(int argc, char **argv)
{
    switch (std::stoi(argv[1]))
    {
        case (SERIAL):
            serial();
            break;
        
        case (LINEAR):
            linear(argc, argv);
            break;
        
        case (BINARY):
            binary(argc, argv);
            break;

        case (NONBLOCKING):
            nonblocking(argc, argv);
            break;
        
        case (GATHER):
            gather(argc, argv);
            break;

        case (REDUCE):
            reduce(argc, argv);
            break;
        
        default:
            std::cout << "unknown operationMode specified\n";
            break;
    }
}
