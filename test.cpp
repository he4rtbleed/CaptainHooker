#include <iostream>
#include <fstream>

int main()
{
    std::ofstream output("patched_bin", std::ios_base::binary | std::ios_base::out);
    std::ifstream dump("dumped_bin", std::ios_base::binary | std::ios_base::in);
    if (dump.is_open() && output.is_open())
    {
        char buffer[0x4800];
        dump.seekg(0, std::ios::end);
        size_t length = dump.tellg();
        dump.seekg(0, std::ios::beg);

        if (length > sizeof(buffer))
        {
            length = sizeof(buffer);
        }

        dump.read(buffer, length);

        for (int i = 0; i < length; i += 2)
            output << (uint8_t)((int)((buffer[i] << 4) | buffer[i + 1]));
        std::cout << "Patched!!!" << std::endl;
    }
}