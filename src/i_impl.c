#include "dataStructure.h"
#include "impl.h"
#include "logs.h"
#include <stdio.h>

#define METHOD  0
#define PATH    1
#define CLEANUP 10

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

    // Dynamic String for method
    String method_s;
    create_string(&method_s);
    String path_s;
    create_string(&path_s);


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
        } else if (part == PATH) {
            printf("current char: %c\n", current_char);
            if (current_char == ' ') {
                path = malloc(string_lenght(&path_s));                
                if (method == NULL) {
                    request->is_valid = false;
                    break;
                }
                copy_string(&path_s, path, string_lenght(&path_s));
                part = 4;
            } else {
                add_char(&path_s, current_char);
            }
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
    log_info(request->method);
    log_info(request->path);

    // cleanup
    destroy_string(&method_s);
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
