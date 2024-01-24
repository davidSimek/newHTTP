#include "dataStructure.h"
#include "impl.h"
#include "logs.h"
#include <stdio.h>

#define METHOD  0
#define PATH    1
#define VERSION 2
#define HEADERS 3
#define DATA    4


void i_parse_request(Request* request) {
    log_info("parsing");
    request->headers = (char**)malloc(2 * sizeof(char*)); 
    request->headers[0] = (char*)malloc(sizeof(char*) * 6);
    request->headers[1] = request->headers[0] + 3;
    log_info("headers allocated");
    memcpy(request->headers[0], "no", 3);
    log_info("first header set");
    memcpy(request->headers[1], "no", 3);
    log_info("headers set");
    request->headers_count = 2;

    request->http_version = "HTTP3";
    request->body = (char*)malloc(sizeof(char) * 6);
    memcpy(request->body, "nanan", 6);
    request->host = (char*)malloc(sizeof(char) * 5);
    memcpy(request->host, "hello", 5);

    char* position = request->raw;
    if (position == NULL) {
        request->is_valid = false;
        return;
    }

    char current_char = *position;

    // result stings
    char* method;
    char* path;
    char* version;

    // Dynamic String for method
    String method_s;
    create_string(&method_s);
    String path_s;
    create_string(&path_s);
    String version_s;
    create_string(&version_s);
    StringView headers_s;
    char* headers_start;

    int part = METHOD;
    while (current_char != 0) {
        printf("part = %d\t current_char = %c\n", part, current_char);
        // METHOD PARSING
        if (part == METHOD) {
            printf("current char: %c\n", current_char);
            if (current_char == ' ') {
                method = malloc(string_lenght(&method_s));
                if (method == NULL) {
                    request->is_valid = false;    
                    break;
                }
                copy_string(&method_s, method, string_lenght(&method_s));
                part = PATH;
            } else {
                add_char(&method_s, current_char);
            }
        // PATH PARSING
        } else if (part == PATH) {
            printf("current char: %c\n", current_char);
            if (current_char == ' ') {
                path = malloc(string_lenght(&path_s));                
                if (method == NULL) {
                    request->is_valid = false;
                    break;
                }
                copy_string(&path_s, path, string_lenght(&path_s));
                part = VERSION;
            } else {
                add_char(&path_s, current_char);
            }
        // VERSION PARSING
        } else if (part == VERSION) {
            printf("current char: %c\n", current_char);
            if ( position[0] == '\r' &&
                &position[1] != NULL &&
                 position[1] == '\n') {
                version = malloc(string_lenght(&version_s)); 
                if (version == NULL) {
                    request->is_valid = false;
                    break;
                }
                copy_string(&version_s, version, string_lenght(&version_s));
                part = HEADERS;
                ++position;
                headers_start = position += 1;
            } else {
                add_char(&version_s, current_char);
            }
        // find where headers start and end
        } else if (part == HEADERS) {
            if ( position[0] == '\r' &&
                &position[1] != NULL &&
                 position[1] == '\n' &&
                &position[2] != NULL &&
                 position[2] == '\r' &&
                &position[3] != NULL &&
                 position[3] == '\n') {
                create_string_view(&headers_s, headers_start, position);
                part = DATA;
            }
        } else if (part == DATA) {
            
        }


        // next iteration setup
        position++;
        if (position == NULL) {
            request->is_valid = false;
            break;
        }
        current_char = *position;
    }

    // assign
    request->method = method;
    request->path = path;
    request->http_version = version;
    log_info(request->method);
    log_info(request->path);
    log_info(request->http_version);
    printf("headers are:\n");
    print_string_view(&headers_s);

    // cleanup
    destroy_string(&method_s);
    destroy_string(&path_s);
    destroy_string(&version_s);
}

void i_preview_request(Request* request) {
    printf("REQUEST INFO {\n\tHTTP version: %s\n\tmethod: %s\n}\n", request->http_version, request->method);
}

void i_delete_request(Request* request) {
    free(request->method);
    request->method = 0;
    free(request->host);
    request->host = 0;
    free(request->path);
    request->path = 0;
    free(request->headers[0]);
    request->headers = 0;
    free(request->body);
    request->body = 0;
    free(request->raw);
    request->raw = 0;
}
