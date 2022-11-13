#include <stdio.h>
#include <string>
#include <algorithm>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: rev.exe input_file output_file\n");
        return -1;
    }

    int ret = 0;
    FILE *fin = fopen(argv[1], "rb");
    FILE *fout = fopen(argv[2], "wb");
    if (fin && fout)
    {
        char buf[1024];
        std::string str;

        str.reserve(1024 * 1024 * 4);

        for (;;)
        {
            size_t cb = fread(buf, 1, sizeof(buf), fin);
            if (cb == 0)
                break;

            str.append(buf, cb);
        }

        std::reverse(str.begin(), str.end());

        if (!fwrite(str.c_str(), str.size(), 1, fout))
        {
            fprintf(stderr, "!fwrite\n");
        }
    }
    else
    {
        fprintf(stderr, "!fopen\n");
        ret = -2;
    }

    if (fin)
        fclose(fin);
    if (fout)
        fclose(fout);
    return ret;
}
