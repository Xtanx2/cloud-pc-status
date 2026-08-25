#include <stdio.h>
#include <unistd.h>
#include "system_info.h"

void get_hostname(char *hostname, int size)
{
    if (gethostname(hostname, size) != 0) {
        hostname[0] = '\0';
    }
}

double get_cpu_load(void)
{
    double cpu = 0.0;

    FILE *fp = popen("awk '{print $1}' /proc/loadavg", "r");

    if (fp != NULL) {
        fscanf(fp, "%lf", &cpu);
        pclose(fp);
    }

    return cpu;
}

double get_ram_usage(void)
{
    double ram = 0.0;

    FILE *fp = popen(
        "free | awk '/Mem:/ {printf \"%.1f\", $3/$2*100}'",
        "r"
    );

    if (fp != NULL) {
        fscanf(fp, "%lf", &ram);
        pclose(fp);
    }

    return ram;
}

double get_disk_usage(void)
{
    double disk = 0.0;

    FILE *fp = popen(
        "df / | awk 'NR==2 {gsub(\"%\", \"\"); print $5}'",
        "r"
    );

    if (fp != NULL) {
        fscanf(fp, "%lf", &disk);
        pclose(fp);
    }

    return disk;
}