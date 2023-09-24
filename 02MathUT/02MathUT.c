#include "SLC/errno.h"
#include "SLC/Log.h"
#include <stdlib.h>

SLCerrno_t MiniBLASUT();

int main(int argc, const char* argv[])
{
    int err = EXIT_SUCCESS;
    SLCLog_Sink = stdout;
    SLCLog_Level = SLCLog_LevelALL;
    do {
        err = MiniBLASUT();
        if (err) break;
        // err = MiniLAUT();
        // if (err) break;
    } while (0);
    return err;
}