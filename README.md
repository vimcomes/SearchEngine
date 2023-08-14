#  Search engine
***
## It is the final work of the course "C++ Developer" from [Skillbox](https://skillbox.ru).

## 1. Description
How a search engine works:
- The names of the files that the search engine will search for are set in the configuration file [`config.json`](https://github.com/vimcomes/SearchEngine/blob/master/config.json), before starting the application.
- The search engine independently bypasses all the files in the [`config.json`](https://github.com/vimcomes/SearchEngine/blob/master/config.json) and indexes them to find the most relevant documents for any search query.
- The user sets a request through a JSON file [`requests.json`](https://github.com/vimcomes/SearchEngine/blob/master/requests.json). The query consists of the words you need to find in the documents.
- The request is converted into a list of unique words. Compiles a list of documents that contain these words.
- Search results are ranked and sorted and the top 5 results displayed to the user.
- At the end, the program generates `answers.json` file and writes the search results into it.

## 2. Tech
Search engine uses a number of open source projects to work properly:
- To read and generate JSON format documents, a third-party library [nlohmann/json](https://github.com/nlohmann/json) is used.
- For unit tests, the [GoogleTest](https://github.com/google/googletest) library is used.

## 3. Instruction

To build the project to be installed:
- [CMake](https://cmake.org/download/) build system.
- [MVS](https://visualstudio.microsoft.com/ru/downloads/) or [MinGW-w64](https://www.mingw-w64.org/downloads/#mingw-builds) compiler.

### 3.1 Build

  <details>
  <summary> - Building using the Windows command line:</summary>
  <br>

  - From the command line, navigate to the project's root directory `C:\...\search_engine` and create a build directory:

    ```sh
    mkdir build
    ```
  - Next, navigate to the build directory and run CMake to configure the project and generate a native build system:

    ```sh
    cd build
    cmake ..
    ```

  - Then call that build system to actually compile/link the project:

    ```sh
    cmake --build .
    ```

  - Upon completion of the compilation process, the executable file `SearchEngine.exe` will appear in the `..\search_engine\build` folder if you are using the MinGW-w64 compiler, and `..\search_engine\build\Debug` for MVS compiler.

  </details>

### 3.2 Launch preparation

- For the program to work correctly, it is necessary that the executable file be in the same directory as the files: [`config.json`](https://github.com/vimcomes/SearchEngine/blob/master/config.json), [`requests.json`](https://github.com/vimcomes/SearchEngine/blob/main/requests.json).

- In order for the search engine to process custom documents, add the path to this document to the "files" list in [`config.json`](https://github.com/vimcomes/SearchEngine/blob/master/config.json):
   ```sh
   {
       "files": [
           "resources\\file001.txt",
           "..." ,
           "user\\custom_document.txt",
       ]
   }
   ```
   > Note: By default, paths to files from the [`resources`](https://github.com/vimcomes/SearchEngine/tree/master/resources) folder are specified. The executable and the `resources` folder must be in the same directory.


- The [`requests.json`](https://github.com/vimcomes/SearchEngine/blob/master/requests.json) file contains custom requests:
   ```sh
   {
       "requests": [
           "london",
           "moscow is the capital of russia",
           "water milk"
       ]
   }
   ```
   > Note: The request can only contain Latin characters.

- The number of responses depends on the "max_responses" parameter, the default is 5. You can change the value in [`config.json`](https://github.com/vimcomes/SearchEngine/blob/master/config.json).

### 3.3 Launch

  <details>
  <summary> - Launching the program using the Windows command line:</summary>
  <br>

  - From the command line, change to the directory containing the `SearchEngine.exe` executable and enter:

    ```sh
    SearchEngine
    ```

    If the conditions described in paragraph 3.2 have been met, then the search results will be written to the `answers.json` file and displayed in the console, as shown below:

    ```sh
    Started execution SearchEngine v1.0
    Max responses: 5

    request001:
      result: true
      relevance:
        docID: 0, rank: 1

    request002:
      result: true
      relevance:
        docID: 7, rank: 1
        docID: 14, rank: 1
        docID: 0, rank: 0.666667
        docID: 1, rank: 0.666667
        docID: 2, rank: 0.666667

    request003:
      result: false

    Enter "exit" to exit the program:
    ```


  - To exit the program, enter `exit` at the command line.

  </details>
