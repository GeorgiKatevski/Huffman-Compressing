# File compression by Huffman encoding

## Overview

The **Huffman Encoding Project** is designed to compress and decompress files using the Huffman coding algorithm, enhanced by canonical representation. Huffman coding is a well-known algorithm for lossless data compression. It assigns variable-length codes to input characters based on their frequencies, with more frequent characters receiving shorter codes, leading to efficient compression.

## What is Huffman Compression?

Huffman compression is a technique used to reduce the size of data files by assigning shorter codes to more frequently occurring characters and longer codes to less frequent characters. The process involves creating a binary tree (Huffman Tree) where each leaf node represents a character from the input data, and the path from the root to the leaf represents the character's code.

![image](https://github.com/user-attachments/assets/a415b8ee-9ae6-4a89-9219-56ee893e59b4)

### How Huffman Compression Works

1. **Calculate Frequencies**: Determine the frequency of each character in the input data.
2. **Build Huffman Tree**: Create a binary tree where each node represents a character or a group of characters. Characters with higher frequencies are closer to the root of the tree.
3. **Generate Codes**: Assign binary codes to each character based on its position in the Huffman tree.
4. **Encode Data**: Replace each character in the input data with its corresponding binary code.
5. **Store Compressed Data**: Save the encoded data along with the Huffman tree structure to enable decoding.

## Project Objectives

- **File Compression**: Implement an efficient algorithm to compress text files, reducing their size for storage or transmission.
- **File Decompression**: Provide a method to accurately decompress files that were compressed using the Huffman encoding, restoring the original content.
- **Canonical Representation**: Utilize canonical Huffman codes to standardize the encoding and decoding process, ensuring consistent and efficient operations.

## Key Components

### 1. HuffmanCoding Class
- **Purpose**: Manages the primary functionalities of the project, including file archiving (zipping), extracting (unzipping), and displaying archive information.
- **Main Functions**:
  - `zip(String toPack, String toCreate, Vector<std::string> item)`: Compresses specified files into an archive.
  - `unzip(String toUnpack, String dir)`: Decompresses files from an archive.
  - `info(String toList)`: Displays information about the files in an archive.

### 2. HuffmanTable Class
- **Purpose**: Constructs the Huffman tree, generates Huffman codes, and creates a canonical Huffman table.
- **Main Functions**:
  - `buildHuffmanTree(int* freq, size_t size)`: Constructs the Huffman tree from given symbol frequencies.
  - `cannonicalHuffman(DataNode* root)`: Converts the Huffman tree into a canonical representation, ensuring a standardized encoding/decoding process.
  - `countFr(int* totalFr, size_t size, unsigned char* content)`, `initTable(ByteEncoding* table)`, `generateLength(DataNode* root, int len, ByteEncoding*& arr)`, `finalTable(ByteEncoding sortedTable[], ByteEncoding finalTable[], size_t size)`: Support functions for building and managing the Huffman table.

### 3. MinHeap Class
- **Purpose**: Implements a min-heap data structure to facilitate the construction of the Huffman tree.
- **Main Functions**:
  - `insert(DataNode* val)`: Adds a new node to the heap.
  - `removeMin()`: Removes the node with the smallest frequency from the heap.
  - `getMin()`: Retrieves the node with the smallest frequency without removing it.

### 4. ByteEncoding Struct
- **Purpose**: Represents each symbol's Huffman code and its length.
- **Main Attributes**:
  - `key`: The symbol.
  - `code`: The Huffman code assigned to the symbol.
  - `codeLength`: The length of the Huffman code.

### 5. File Handling
- **Purpose**: Manages file input/output operations, including reading content for compression and writing compressed data to an archive.

## Canonical Huffman Representation

The project employs **canonical Huffman codes**, which provide a standardized and efficient method for encoding and decoding. Canonical Huffman representation:
- **Simplifies Decoding**: Standardizes code lengths and bit sequences, making the decoding process straightforward and efficient.
- **Optimizes Storage**: Reduces the amount of metadata needed to describe the Huffman tree, leading to better compression performance.
