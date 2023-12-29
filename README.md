Creating a C++ application for visualizing a Fibonacci Heap. 
Here's a high-level overview of the application:

  - Application Structure:
    - Frontend: This will handle the user interface.
    - Backend: This will handle the Fibonacci Heap logic in C++.

  - Frontend:
    - Header:
      - A text box for inputting the key of the node (an integer value).
      - A button labeled "Insert" to create a new node and insert it into the heap.
      - A button labeled "Remove Smallest" to invoke a backend function that removes the smallest element from the heap.
      - A "Clear Heap" button to reset the heap.
    - Visualization Screen:
      - Dynamically display the heap as nodes are inserted or removed.

  - Backend (C++ Logic):
    - Fibonacci Heap Implementation:
      - Fibonacci Heap data structure in C++ with operations such as insert, remove smallest, and clear.

 -  Integration with Frontend:
     - Achieved by creating QtQuick application in Qt Creator. The application uses "qml" file for application rendering.
