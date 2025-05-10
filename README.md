# CLY 

Another innovative idea from yours truely. A TODO application, but this time in the CLI! CLY (pronounced 'KLAI') is born out of frustration and annoyance. I was tired of constantly having to write my very important and essential tasks of the day in a very fancy sticky note. So, instead, I decided to spend the better part of the morning creating a CLI application in C++ to do it for me. I tired to use actual applications but they all had a simple mistake I did not tolerate: they were all _fucking_ awful and filled with ads. And, in the case of Microsoft, required me to **sign into** my Microsoft account. Lovely. 

Now, is CLY fancy? No. Is it the _best_ TODO app out there? Obviously, not. Could I have used someone else's CLI TODO application? Absolutely, yes. Could this have been a simple bash script? Well, yeah. But, in all honesty, I thought the name was funny and I was procrastinating other projects. So. Here comes CLY.


## Build Instructions

Like any other C++ project out there, CLY uses CMake for its build system. And there's no trickery here. It's only a single file (`main.cpp`), using only `C++17` features. No dependencies. I still have my dignity.

Anyway, if you run the commands below, you should be able to compile CLY. 

```bash
mkdir build && cd build 
cmake ..

# On Linux
make

# On Windows
cmake --build .
```

Now these commands only build CLY and generate a `cly` executable and a `tasks.txt` file. However, if you want to _use_ CLY, you should keep reading to learn how.

## Usage 

There are only _four_ simple commands CLY supports: 

```
cly add <task>          = Add a new task to the list
cly remove <task_index> = Remove a specific task from the list
cly show                = Show all of the current tasks in the list
cly help                = Show this help screen
```

And, as you can see, they are pretty self-explanatory. Here's a simple example of adding a "Finish major big project" task to the list: 

```
cly add "Finish major big project"
```

You can also string together multiple tasks to add them all at once: 


```
cly add "Finish major big project" "Contemplate life" "Listen to The Beatles" "Look at a cat for 2 hours"
```

If you use the `show` command, you will get the following result: 


```
+++++ TODO ++++++

1. Finish major big project
2. Contemplate life
3. Listen to The Beatles
4. Look at a cat for 2 hours

+++++ TODO ++++++
```

You can also see that the tasks are numbered. This makes it easier to remove task from the list. 

```
cly remove 1
```

And the result:


```
+++++ TODO ++++++

1. Contemplate life
2. Listen to The Beatles
3. Look at a cat for 2 hours

+++++ TODO ++++++
```

The numbers shift around and the task is now removed. And, like adding tasks, you can also remove multiple tasks at once.


```
cly remove 2 3
```

Which should end up with something like this:


```
+++++ TODO ++++++

1. Contemplate life

+++++ TODO ++++++
```

Cool.

## Installation 

CLY works best when it's installed on your system so you can access these three magic letters from anywhere. First make sure to build CLY, obviously. Then, you can use the following command on Linux: 

```bash
sudo make install
```

On Windows, you can either build CLY somewhere and leave it there or place it somewhere else. It doesn't really matter. What matters is that you should add the directory where CLY lives to your enviornment variables.

## Contribute 

Don't.
