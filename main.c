#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "system_info.h"
#include "health.h"
#include "cloud.h"

int main(int argc, char *argv[])
{
    char hostname[256];

    get_hostname(hostname, sizeof(hostname));

    int once = 0;

    if (argc > 1 && strcmp(argv[1], "once") == 0) {
        once = 1;
    }

    while (1)
    {
        double cpu = get_cpu_load();
        double ram = get_ram_usage();
        double disk = get_disk_usage();

        int health_score =
            get_health_score(cpu, ram, disk);

        const char *health_status =
            get_health_status(health_score);

        printf("\n============================\n");
        printf("      CLOUD PC STATUS\n");
        printf("============================\n");

        printf("Hostname : %s\n", hostname);
        printf("CPU Load : %.2f\n", cpu);
        printf("RAM      : %.1f%%\n", ram);
        printf("Disk     : %.1f%%\n", disk);

        printf(
            "Health   : %d/100\n",
            health_score
        );

        printf(
            "Status   : %s\n",
            health_status
        );

        printf(
            "Heartbeat: ONLINE\n"
        );

        printf("\nUploading to cloud...\n");

        upload_status(
            hostname,
            cpu,
            ram,
            disk,
            health_score,
            health_status
        );

        if (once) {
            printf("Single check completed.\n");
            break;
        }

        printf("Next update in 10 seconds...\n");

        sleep(10);
    }

    return 0;
}