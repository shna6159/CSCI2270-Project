CSCI 2270 Project
File Compression
Shreeyash Nadella , Neel Karsanbhai, Jake Hugenberg 

Data Structures Used
For Huffman Encoding, we used a hash table, min heap, queue, and a binary tree.  While run length encoding does not use any data structure, it acts as an effective benchmarking tool with respect to Huffman Encoding .
Methodology
All characters in the text file to be compressed were added to the hash table. Once that was completed, a node was created which had each character and its count. The node was then added to a min heap. Once all characters had been added to the min heap, nodes were popped from the min heap, and then added to the queue. From the queue, the first two nodes were popped, and their frequencies combined into a parent node, with its children as the nodes that had been popped from the queue. The parent was then pushed back to the queue. This process stopped until the queue only contained one node, the root node. This process created the Huffman Tree to be used to generate prefix codes for each unique character in the original text file. 
UI
We used QT Framework to design the UI for our program. Each button in the program has  an event associated with it. Upon pressing the button, a version of the main function is run to compress the file. We have also made use of slots and signals to take in input from the GUI. Our program is cross platform in the sense that it will run anywhere with the QT environment.
Attempted Ideas
The most ambitious idea we tried to carry out was to include multithreading to the frequency finding part of the Huffman Encoding.To attempt it, we tried to break our file into 4 parts using the length of the file.We then assigned each file to each thread tried count the frequencies.We were not able to determine how to integrate the results from the various threads. We did not get to complete this addition, due to time constraints.



Results
Based on our results, we have determined the different ways of file compression are good for different types of files. The run length encoding is great for files with repeated characters. But Huffman Encoding is relatively better with respect to unique words. Huffman Encoding has a time complexity of O(n^2)(where n is the number of unique words) . We have also added cross platform functionality to our project for Windows and Mac OS. 


