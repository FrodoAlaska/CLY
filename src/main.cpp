#include <cstddef>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

/// -------------------------------------------------------------------------------------------------
/// DEFS

#define COMMANDS_MAX 4

/// DEFS
/// -------------------------------------------------------------------------------------------------

/// -------------------------------------------------------------------------------------------------
/// CLYState
struct CLYState {
  std::filesystem::path working_dir;
  std::vector<std::string> tasks;
};
/// CLYState
/// -------------------------------------------------------------------------------------------------

/// -------------------------------------------------------------------------------------------------
/// CLYState functions

bool cly_state_init(CLYState* state) {
  // Getting the working directory
  state->working_dir = (std::filesystem::current_path() / std::string("tasks.txt"));
  
  std::fstream file;

  // First check if the file exists or not and create it if it doesn't
  if(!std::filesystem::exists(state->working_dir)) {
    file.open(state->working_dir, std::ios::in | std::ios::out | std::ios::trunc);
    file.close();
    
    return true;
  }

  // Loading the tasks file
  file.open(state->working_dir, std::ios::in | std::ios::out);
  if(!file.is_open()) {
    printf("[CLY-ERROR]: Failed to open TASKS file at \'%s\'\n", state->working_dir.c_str());
    return false;
  }

  // Add all of the tasks from the file
  std::string line; 
  while(std::getline(file, line)) {
    state->tasks.push_back(line);
  }
  
  file.close();
  return true;
}

void cly_state_save(CLYState& state) {
  // Open the tasks file
  std::ofstream file(state.working_dir, std::ios::trunc);
  if(!file.is_open()) {
    printf("[CLY-ERROR]: Failed to open TASKS file at \'%s\'", state.working_dir.c_str());
    return;
  }

  // Write all of the tasks into the file
  for(auto& task : state.tasks) {
    file << task; 
    file << '\n';
  }

  file.close();
}

void cly_state_add_tasks(CLYState& state, char** tasks, const int begin, const int end) {
  printf("\n\n");
  
  for(int i = begin; i < end; i++) {
    state.tasks.push_back(tasks[i]);
    printf("Task \'%s\' was added to the list. Make sure to finish it!\n", tasks[i]);
  }

  cly_state_save(state);
  printf("\n\n");
}

void cly_state_remove_tasks(CLYState& state, char** indices, const int begin, const int end) {
  printf("\n\n");

  int offset = 0; 
  for(int i = begin; i < end; i++) {
    int index     = std::stoi(indices[i]) - 1;
    const auto it = state.tasks.begin() + (index - offset);

    printf("Congrats! The task \'%s\' was finished and removed from the list\n", it->c_str());
    state.tasks.erase(it);

    offset++;
  }
  
  cly_state_save(state);
  printf("\n\n");
}

void cly_state_show(CLYState& state) {
  printf("\n\n+++++ TODO ++++++\n\n"); 
 
  for(size_t i = 0; i < state.tasks.size(); i++) {
    printf("%zu. %s\n", i + 1, state.tasks[i].c_str());
  }
  
  printf("\n+++++ TODO ++++++\n\n"); 
}

/// CLYState functions
/// -------------------------------------------------------------------------------------------------

/// -------------------------------------------------------------------------------------------------
/// Args functions

void args_show_help() {
  printf("\n\n----- CLY: A TODO command line application -----\n\n"); 
  printf("CLY usage: \n");
  printf("\tcly add <task>          = Add a new task to the list\n");
  printf("\tcly remove <task_index> = Remove a specific task from the list\n");
  printf("\tcly show                = Show all of the current tasks in the list\n");
  printf("\tcly help                = Show this help screen\n");
  printf("\n\n----- CLY: A TODO command line application -----\n\n"); 
}

void args_parse(int argc, char** argv, CLYState& state) {
  if(argc < 2) {
    printf("[CLY-ERROR]: Insufficient number of arguments given\n");
    return;
  }

  // All the possible commands
  std::string commands[COMMANDS_MAX] = {
    "add", 
    "remove", 
    "show",
    "help",
  };

  // Go through all the possible commands and compare
  for(int i = 1; i <= argc; i++) {
    // Add 
    if(commands[0] == argv[i]) {
      cly_state_add_tasks(state, argv, i + 1, argc);
      break;
    }
    // Remove
    else if(commands[1] == argv[i]) {
      cly_state_remove_tasks(state, argv, i + 1, argc);
      break;
    }
    // Show
    else if(commands[2] == argv[i]) {
      cly_state_show(state);
      break;
    }
    // Help
    else if(commands[3] == argv[i]) {
      args_show_help();
      break;
    }
    // Error!
    else {
      printf("[CLY-ERROR]: The given argument \'%s\' is invalid\n", argv[i]);
      args_show_help();
    }
  }
}

/// Args functions
/// -------------------------------------------------------------------------------------------------

/// -------------------------------------------------------------------------------------------------
/// Main function

int main(int argc, char** argv) {
  // Create the state
  CLYState state; 
  if(!cly_state_init(&state)) {
    return -1;
  }

  // Parse the arguments and act accordingly
  args_parse(argc, argv, state);
}

/// Main function
/// -------------------------------------------------------------------------------------------------
