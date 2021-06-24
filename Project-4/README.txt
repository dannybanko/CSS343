Group Member Names:
   Danny Banko
   Ahmad Yousif
   Aniley Sabi

Demo on how to run our code:
   Using Linux:
      g++ -std=c++11 *cpp
      ./a.out
      
Group Member Contributions:
   Danny:
   - Design document (all of it)
   - Thorough commenting
   - Implemented:
       main.cpp
       store.h & store.cpp
       customerHash.h & customerHash.cpp
       factory.h & factory.cpp
       customer.h & customer.cpp
       inventoryTree.h & inventoryTree.cpp
       helped with movie and child classes
       helped with transaction and child classes
       
   Ahmad:
   - Design document (all of it)
   - Thorough commenting
   - Implemented:
       movie.h & movie.cpp
       classic.h & classic.cpp
       comedy.h & comedy.cpp
       drama.h & drama.cpp
       helped with inventoryTree
       helped with store
       helped with customer
       
   Aniley:
   - Design document (all of it)
   - Thorough commenting
   - Implemented:
       transaction.h & transaction.cpp
       borrow.h & borrow.cpp
       returnItem.h & returnItem.cpp
       history.h & history.cpp
       helped with inventoryTree
       helped with store
       helped with customer
       
Overview:
Our project using a hash table to store Customers. We use inheritance in two areas,
for movies and for transactions. We use a factory to determine the proper type of
movie or transaction object to create. We store movies in a Binary Search Tree, and
store holds an array of BSTs to allow for movies of the same type to be kept
together. Transactions are stored in a vecror of transactions that represents that
customers history of transactions. Our program handles data errors and prints
appropriate error messages as needed. We are free of memory leaks :).

      
