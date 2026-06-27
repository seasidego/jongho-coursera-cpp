# graph / 6/21/2026

## 1.Motivation
- Leaned from class.
- https://www.coursera.org/learn/cs-fundamentals-3/programming/pK1Sk/graph-search-project

## 2.Working Functions
- compressionForPrint()
- uncompression

### Expected Output
- expected output
```
  input :
  abbcccddddeeeee
  
  output:
  code: e: 0  d: 10  a: 1100  b: 1101  c: 111
  compressed line: 1100 1101 1101 111 111 111 10 10 10 10 0 0 0 0 0
  uncompressed line: abbcccddddeeeee
```

### How it works
#### Compress :
- Counts the frequency of each char.
- Sort them by frequency in descending order.
- Assigns shorter bit if it has higher frequency.
- Change vector of chars to bit.

#### Uncompress :
- Find compressed data in the code and get the matching value
- Put value in vector
- Change vector to string
