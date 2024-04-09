# Project

### Cloning
```bash
git clone --recursive https://github.com/Alexeyha/solana-assign.git
```

### Dependencies and libraries

* **Boost** for thread pool. Modern C++ does not contain thread pool in standard library, although it is effective solution for potential ample number of background task.
* **curl** for send request to Solana RPC API. Despite C-foundation, this library is one of the most popular for HTTP requests.
* **jsoncons** for json parsing. Header-only fast library for json, linked as submodule.

### How to build and run

There are 2 targets: `latency-tracking` that implements tracking standard deviation each second and `cli-app` that allow to interact with the app via command set.

### Architecture

To be honest there are several bottlenecks in my solution that need to be improved.

The whole project is split in 3 parts:
1. Static library **network** that includes *curl* dependency. Curl wrapper (RAII class wrapped curl C-library) and Request manager (class for creation and sending request to Solana) are implemented there.
2. Static library **core** that includes *network* and *boost* dependencies. There are two entities: Storage (interface that implements storing GET responses) and Event handler (interface that implements processing different events).
3. Object **engine** that include *core* dependency. Engine contains all necessary entities to implement the complete cycle of requests and collect the statistics.

### Algorithms

To implement latency tracking feature I chose the following algorithm: store all results in multiset ordered by timestamp. 
* All "outdated" results are being removed during adding new result.
* Sum of latencies and sum of squared latencies are maintained during both adding and removing.

To sum up:
* Time complexity: O(log(n)) for adding new result; O(1) asymptotically for get standard deviation; O(1) for retrieve the oldest result.
* Memory complexity: O(n).

### Configuration

Parameter PERIOD can be configured in `#define PERIOD` in `engine/Engine.hpp`.
