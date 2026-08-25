#include "health.h"

int get_health_score(double cpu, double ram, double disk)
{
    int score = 100;

    if (cpu > 2.0)
        score -= 20;

    if (ram > 80.0)
        score -= 30;

    if (disk > 80.0)
        score -= 30;

    if (score < 0)
        score = 0;

    return score;
}

const char *get_health_status(int score)
{
    if (score >= 75)
        return "HEALTHY";

    if (score >= 50)
        return "WARNING";

    return "CRITICAL";
}