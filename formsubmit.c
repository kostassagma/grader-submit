#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define h_addr h_addr_list[0]

#define PORT 80
#define BUFFER_SIZE 4096

void send_http_post_request(const char *hostname, const char *path, const char *cookies, const char *body)
{
    int sock;
    struct sockaddr_in server_addr;
    struct hostent *host;

    // Resolve hostname to IP address
    host = gethostbyname(hostname);
    if (host == NULL)
    {
        herror("gethostbyname failed");
        exit(EXIT_FAILURE);
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    memcpy(&server_addr.sin_addr.s_addr, host->h_addr, host->h_length);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection to server failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Create HTTP POST request
    char request[BUFFER_SIZE];
    snprintf(request, sizeof(request),
             "POST %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Cookie: %s\r\n"
             "Content-Type: application/x-www-form-urlencoded\r\n"
             "Content-Length: %zu\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%s",
             path, hostname, cookies, strlen(body), body);

    // Send request
    send(sock, request, strlen(request), 0);

    // Receive response
    char response[BUFFER_SIZE];
    while (recv(sock, response, sizeof(response) - 1, 0) > 0)
    {
        printf("%s", response);
        memset(response, 0, sizeof(response)); // Clear the buffer
    }

    // Close socket
    close(sock);
}

char *get_cookie_string(const char *value)
{
    // Allocate memory for the formatted string
    char *buffer = (char *)malloc(256); // Adjust size as needed
    if (buffer == NULL)
    {
        perror("Failed to allocate memory");
        return NULL;
    }

    // Format the string
    snprintf(buffer, 256, "PHPSESSID=%s;", value);

    return buffer; // Return the pointer to the formatted string
}

char *get_formdata_string(const char *task, char *filename)
{
    // Allocate memory for the formatted string
    char *buffer = (char *)malloc(256); // Adjust size as needed
    if (buffer == NULL)
    {
        perror("Failed to allocate memory");
        return NULL;
    }

    // Format the string
    snprintf(buffer, 256, "task=%s&lang=%s&filename=%s", task, "C%2B%2B", filename);

    return buffer; // Return the pointer to the formatted string
}

int main()
{
    FILE *file;
    char line[256];
    char param1[50];
    char param2[50];
    char param3[50];

    // Open the file for reading
    file = fopen("config.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read parameters from the file
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "cookie=%s", param1) == 1)
        {
            // Successfully read param1
        }
        else if (sscanf(line, "task=%s", param2) == 1)
        {
            // Successfully read param2
        }
        else if (sscanf(line, "filename=%s", param3) == 1)
        {
            // Successfully read param3
        }
    }

    // Close the file
    fclose(file);

    const char *hostname = "grader.softlab.ntua.gr"; // Change to your desired hostname
    const char *path = "/filesubmitcourses.php";     // Change to your desired path
    const char *cookies = get_cookie_string(param1);

    // Constructing the body with form data
    const char *form_data = get_formdata_string(param2, param3); // Add more parameters as needed

    send_http_post_request(hostname, path, cookies, form_data);

    return 0;
}
