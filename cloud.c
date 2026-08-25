#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "cloud.h"

void upload_status(
    const char *hostname,
    double cpu,
    double ram,
    double disk,
    int health_score,
    const char *health_status)
{
    const char *url = getenv("SUPABASE_URL");
    const char *key = getenv("SUPABASE_KEY");

    if (url == NULL || key == NULL) {
        printf("Supabase credentials are not set.\n");
        return;
    }

    char endpoint[512];

    snprintf(
        endpoint,
        sizeof(endpoint),
        "%s/rest/v1/pc_status",
        url
    );

    char json[1024];

    snprintf(
        json,
        sizeof(json),
        "{\"hostname\":\"%s\","
        "\"cpu_usage\":%.2f,"
        "\"ram_usage\":%.2f,"
        "\"disk_usage\":%.2f,"
        "\"health_score\":%d,"
        "\"health_status\":\"%s\","
        "\"heartbeat\":true}",
        hostname,
        cpu,
        ram,
        disk,
        health_score,
        health_status
    );

    CURL *curl = curl_easy_init();

    if (curl == NULL) {
        printf("Could not initialize CURL.\n");
        return;
    }

    struct curl_slist *headers = NULL;

    char auth_header[1024];

    snprintf(
        auth_header,
        sizeof(auth_header),
        "apikey: %s",
        key
    );

    headers = curl_slist_append(headers, auth_header);
    headers = curl_slist_append(
        headers,
        "Content-Type: application/json"
    );
    headers = curl_slist_append(
        headers,
        "Prefer: return=minimal"
    );

    curl_easy_setopt(curl, CURLOPT_URL, endpoint);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

    CURLcode result = curl_easy_perform(curl);

    long response_code = 0;

    curl_easy_getinfo(
        curl,
        CURLINFO_RESPONSE_CODE,
        &response_code
    );

    if (result != CURLE_OK) {
        printf(
            "Upload failed: %s\n",
            curl_easy_strerror(result)
        );
    }
    else if (response_code >= 200 && response_code < 300) {
        printf("Status uploaded to cloud successfully.\n");
    }
    else {
        printf(
            "Supabase rejected upload. HTTP status: %ld\n",
            response_code
        );
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}