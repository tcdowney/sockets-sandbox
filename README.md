# sockets-sandbox
Exercises designed to help folks get more acquainted with sockets. 

Originally intended for a Systems Programming Club at Pivotal San Francisco, these exercises take inspiration from the [Exercism C exercises](http://exercism.io/languages/c/about) and similarly use the [Unity C testing framework](https://github.com/ThrowTheSwitch/Unity) to help drive out method implementations.

The exercises are intended to be worked in order and will guide you through the the various socket related syscalls. Each exercise includes links to the relevant `man` pages and section within [Beej's Guid to Network Programming](http://beej.us/guide/bgnet/html/multi/syscalls.html) to help you create and use your very own sockets!

**CAUTION:** I'm not a C expert by any means. These exercises are just here to get the ball rolling on your own sockets education. Be warned that the solutions are not necessarily idiomatic C code and do a pretty poor job of ensuring all memory is freed and open file descriptors are closed when errors occur. If I have time, I'd like to improve them (and I plan on it), but be warned! :smiling_imp:

## Requirements and Setup
These exercises were implemented and tested against Ubuntu `17.10 ArtfulAardvark`.

While developing this, I personally used the Vagrant using the following setup:
* https://github.com/craigfurman/linux-playground

If you have your own Linux box or want to use a Docker image or something else, I believe you should just need to follow the [Exercism C installation guide](http://exercism.io/languages/c/installation). There's nothing too crazy in here, but there are some pthreads which likely won't work on Mac.

## Instructions
Just `cd` into each exercise directory (strongly recommended to work them in order) and run `make test`. This will run the test file and you'll see where you currently stand. Next, read the comments at the top of the files in `src` and implement the necessary functionality to get the tests to pass.

Solutions are available within each `test/solutions` directory.

### Exercise 6 (Parrot Server) Instructions
Exercise 6 is the culmination of everything you've learned. You'll make a "Parrot Server" that repeats messages that are sent to it.

I haven't had a chance to write automated tests for this one yet. Just run `make parrot_server` and run the output executable: `./parrot_server -h`

You can interact with the server by using a tool such as `nc`. Once implemented just do the following to see your message parroted back!

Terminal 1:
```
./parrot_server -p 9000
```

Terminal 2:
```
$ nc localhost 9000
> Hello!
> Hello!
```
