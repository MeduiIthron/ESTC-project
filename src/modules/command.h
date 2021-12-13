#ifndef ESTC_PROJECT_COMMAND_H
#define ESTC_PROJECT_COMMAND_H

typedef char* command_identifier_t;
typedef char* command_manual_t;
typedef char* command_result_message_t;

typedef enum command_result_type_t {
    SUCCESS,
    ERROR,
    UNKNOWN
} command_result_type_t;

typedef struct command_result_t {
    command_result_type_t type;
    command_result_message_t message;
} command_result_t;

typedef command_result_t (*command_handler_t) (void* args, ...);

typedef struct command_descriptor_t {
    command_identifier_t name;
    command_handler_t handler;
    command_manual_t documentation;
} command_descriptor_t;

command_result_t command_handle_command (command_identifier_t identifier, void* args, ...);

#endif //ESTC_PROJECT_COMMAND_H
