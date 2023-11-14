#include "randtimes.h"
#include "request.h"
#include <stdlib.h>
#include <time.h>

double randtime(double min, double max)
{
    return ((double) rand()) / RAND_MAX * (max - min) + min;
}

void rand_req(request_t *req, double min, double max)
{
    req->exec_time = ((double) rand()) / RAND_MAX * (max - min) + min;
}