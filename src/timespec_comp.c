#include <time.h>

int timespec_gt(struct timespec t_1, struct timespec t_2)
{
    return (t_1.tv_sec > t_2.tv_sec ||
            (t_1.tv_sec == t_2.tv_sec &&
             t_1.tv_nsec > t_2.tv_nsec));
}

int timespec_lt(struct timespec t_1, struct timespec t_2)
{
    return (t_1.tv_sec < t_2.tv_sec ||
            (t_1.tv_sec == t_2.tv_sec &&
             t_1.tv_nsec < t_2.tv_nsec));
}
